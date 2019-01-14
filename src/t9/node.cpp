// T9 tree nodes -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#include "t9/node.hpp"

#include "t9/model.hpp"

namespace t9 {

Node::Node(t9_symbol symbol, float probability) :
    symbol(symbol), probability(probability) {

}

CorpusNode::CorpusNode(t9_symbol symbol) :
    Node(symbol, 0.0f), count(0), parent(nullptr) {
}

CorpusNode::~CorpusNode() {
  for (CorpusNode *child : children) {
    delete child;
  }
}

CorpusNode *
CorpusNode::get_child_safe(t9_symbol symbol) {
  // Search for an existing child with the desired symbol.
  for (CorpusNode *child : children) {
    if (child->symbol == symbol) {
      // A child with the symbol already exists.
      return child;
    }
  }

  // There is no child containing with that symbol, create and insert a new one.
  auto child = new CorpusNode(symbol);
  child->parent = this;
  children.push_back(child);

  return child;
}

void
CorpusNode::insert_ngram(std::string_view ngram) {
  CorpusNode *child = get_child_safe(ngram.front());
  child->count++;

  if (ngram.length() > 1) {
    auto begin = &ngram.at(1);
    auto len = ngram.length() - 1;
    std::string_view child_ngram(begin, len);
    child->insert_ngram(child_ngram);
  }
}

void
CorpusNode::calculate_probabilities() {
  for (CorpusNode *child : children) {
    child->probability = static_cast<float>(child->count) / static_cast<float>(this->count);
    child->calculate_probabilities();
  }
}

float
CorpusNode::conditional_probability(std::string_view sequence) const {
  for (CorpusNode *child : children) {
    // Check if there is a child with a symbol corresponding to the first symbol of the sequence.
    if (child->symbol == sequence.front()) {
      // Matching child was found.
      if (sequence.length() == 1) {
        // End of sequence reached, return probability.
        return child->probability;
      } else {
        // Find child for the next character of the sequence.
        std::string_view next_sequence(sequence);
        next_sequence.remove_prefix(1);
        return child->conditional_probability(next_sequence);
      }
    }
  }

  // Sequence is not in tree.
  return 0.0;
}

SearchNode::SearchNode(t9_symbol symbol, float probability) :
    Node(symbol, probability), parent(nullptr) {
}

SearchNode::~SearchNode() {
  for (SearchNode *child : children) {
    delete child;
  }
}

void
SearchNode::insert(t9_symbol symbol, t9_symbol_sequence &sequence, Model *model) {
  t9_symbol_sequence buffer;
  float prob_t_b;
  float prob_b_bb;
  float prob;

  if (is_leaf()) {
    // Append a child for each corpus symbols to the leaf node.
    const std::set<t9_symbol> &corpus_symbols = model->corpus.corpus_set;

    for (auto corpus_symbol : corpus_symbols) {
      size_t sequence_length = sequence.length();

      buffer = sequence;
      if (sequence_length >= model->ngram_length) {
        buffer.erase(0, sequence_length - (model->ngram_length - 1));
      }
      buffer.push_back(corpus_symbol);

      // Calculate child probability.
      prob_t_b = -t9::ln(model->probability_key_when_symbol(symbol, corpus_symbol));
      prob_b_bb = -t9::ln(model->corpus_tree.conditional_probability(buffer));
      prob = prob_t_b + prob_b_bb + this->probability;

      auto child = new SearchNode(corpus_symbol, prob);
      child->parent = this;

      // Add child to parent.
      children.push_back(child);
    }
  } else {
    // Descend the tree until a leaf node.
    for (SearchNode *child : children) {
      buffer = sequence;
      buffer.push_back(child->symbol);

      child->insert(symbol, buffer, model);
    }
  }
}

bool
SearchNode::is_leaf() const {
  return children.empty();
}

void
SearchNode::prune(SearchPath &path, std::vector<SearchPath> &best_paths) {
  bool found;
  std::string path_string;

  if (is_leaf()) {
    // End of tree was reached.
    // Check if the path that was taken to reach this node is one of the best known paths.
    found = false;
    for (const SearchPath &best_path : best_paths) {
      if (best_path == path) {
        // Generated path is one of the best paths. (No pruning required)
        found = true;
        break;
      }
    }
    if (!found) {
      // Path is not known to be one of the best paths.
      // Prune this path.
      path_string = path.to_string();

      // Prune all nodes contained in the path, starting at the end of the path.
      auto path_iter = path.crbegin();
      while (path_iter != path.crend()) {
        // Get a node of the path.
        auto node = *path_iter;

        // We can only prune a node if it has no further children.
        if (node->is_leaf()) {
          // Prune the node.

          // Find and delete the node in the collection of the parents children.
          auto &parent_children = node->parent->children;
          auto child_iter = std::find(parent_children.begin(), parent_children.end(), node);
          if (child_iter != parent_children.end()) {
            parent_children.erase(child_iter);
            delete node;
          }
        } else {
          // There are still children, stop therefore we can not delete the current note or its parent nodes.
          break;
        }

        path_iter++;
      }
    }
  } else {
    // Iterate all over a copy of all children of the node as we might delete some in between.
    auto children_copy(children);
    for (auto child : children_copy) {
      // Descend down a path for each child.
      path.push_back(child);
      child->prune(path, best_paths);
      path.pop_back();
    }
  }
}

void
SearchNode::search_paths(SearchPath &current_path, std::vector<SearchPath> &best_paths, size_t max_paths) {
  if (best_paths.size() >= max_paths) {
    // Maximal number of paths to search was reached.
    if (probability >= best_paths.back().get_probability()) {
      // Current path is not better than the worst path in the list of known best paths.
      // Skip this path.
      return;
    }
  }

  if (is_leaf()) {
    // Leaf node was hit, the taken path therefore spans the whole tree depth.

    // Append a copy of the path to the list of best paths.
    best_paths.push_back(current_path);

    // Sort list of best paths.
    std::sort(best_paths.begin(), best_paths.end());

    // In case there are now more best paths than requested by the model delete the worst path.
    if (best_paths.size() > max_paths) {
      best_paths.pop_back();
    }
  } else {
    // Descend tree until a leaf node is hit.
    for (SearchNode *child : children) {
      // Descend down separate a path for each child.
      current_path.push_back(child);
      child->search_paths(current_path, best_paths, max_paths);
      current_path.pop_back();
    }
  }
}

}  // namesapce t9
