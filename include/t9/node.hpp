// T9 tree nodes -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#ifndef CPP_T9_NODE_HPP
#define CPP_T9_NODE_HPP

#include <memory>
#include <vector>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <experimental/memory>

namespace t9 {
class Model;
class SearchPath;
}  // namespace t9

#include "t9/symbols.hpp"
#include "t9/path.hpp"

using std::experimental::observer_ptr;
using std::experimental::make_observer;

namespace t9 {

class Node {
 public:
  Node(t9_symbol symbol, float probability);

  t9_symbol symbol;
  float probability;
};

class CorpusNode : public Node {
 public:
  /**
   * Construct a corpus tree node.
   * @param symbol Corpus symbol.
   * @param probability Probability of this specific node for its the position in the tree.
   */
  CorpusNode(t9_symbol symbol);

  /**
   * Destruct a corpus tree node.
   */
  ~CorpusNode();

  /**
   * Search a node with a given symbol within the children of a node.
   * If no child is found, a new child with the searched symbol is created.
   * @param symbol Corpus symbol.
   * @return  Pointer to a corpus node.
   */
  CorpusNode *
  get_child_safe(t9_symbol symbol);

  /**
   * Insert a ngram into the corpus tree originating from this node.
   * @param ngram Ngram to insert.
   */
  void
  insert_ngram(std::string_view ngram);

  /**
   * Calculate probability of a node and it's children.
   */
  void
  calculate_probabilities();

  /**
   * Calculate the probability of a symbol sequence originating from this node.
   * @param sequence Corpus symbol sequence whose probability should be calculated.
   * @return Estimated likelihood of occurrence of the sequence.
   */
  float
  conditional_probability(std::string_view sequence) const;

  std::vector<CorpusNode *> children;
  size_t count;

 protected:
  observer_ptr<CorpusNode> parent;
};

class SearchNode : public Node {
 public:
  /**
   * Construct a search node.
   * @param symbol Corpus symbol.
   * @param probability Probability of the search node.
   */
  SearchNode(t9_symbol symbol, float probability);

  /**
   * Destruct the search node.
   */
  ~SearchNode();

  /**
   * Type a single symbol into a search tree.
   * @param symbol T9 key to type.
   * @param sequence Temporary sequence buffer used by the function to construct ngrams.
   * @param model T9 model used to access all information required to insert the symbol.
   */
  void
  insert(t9_symbol symbol, t9_symbol_sequence &sequence, Model *model);

  /**
   * Check if the node is a leaf node.
   * @return true if the node has children on its own. false otherwise.
   */
  bool
  is_leaf() const;

  /**
   * Prune the node in case it is not a member of on of the best known paths.
   * @param path Path of nodes through the tree up to the current node.
   * @param best_paths Collection of the best scoring paths in the tree.
   */
  void
  prune(SearchPath &path, std::vector<SearchPath> &best_paths);

  /**
   * Populate the list of best paths in a given model, originating from the node.
   * @param current_path Current path of nodes that was taken (up and including the current node).
   * @param best_paths Collection of the best scoring paths in the tree.
   * @param max_paths maximal number of best scoring paths to keep track of before discarding new ones.
   */
  void
  search_paths(SearchPath &current_path, std::vector<SearchPath> &best_paths, size_t max_paths);

 public:
  // Collection of children nodes.
  std::list<SearchNode *> children;

 protected:
  // Parent node.
  observer_ptr<SearchNode> parent;
};

}  // namesapce t9

#endif //CPP_T9_NODE_HPP
