#include "t9/tree.hpp"

#include "t9/model.hpp"

namespace t9 {

CorpusTree::CorpusTree() :
    root(CorpusNode(' ')) {

}

void
CorpusTree::insert_ngrams(const Corpus &corpus, size_t ngram_length) {
  std::string_view ngram;
  t9::NGRAMGenerator generator(corpus, ngram_length);

  while (!generator.is_done()) {
    ngram = generator.generate_ngram();
    root.insert_ngram(ngram);
  }
}

void
CorpusTree::calculate_probabilities() {
  // Count the children of the root node.
  root.count = 0;
  for (CorpusNode *child : root.children) {
    root.count += child->count;
  }

  // Calculate the conditional probabilities of each node.
  root.calculate_probabilities();
}

float
CorpusTree::conditional_probability(const std::string &sequence) const {
  std::string_view view(sequence);

  // Find probability of the sequence in tree.
  return root.conditional_probability(view);
}

SearchTree::SearchTree(size_t ngram_length, size_t max_paths)
    : ngram_length(ngram_length),
      max_paths(max_paths),
      depth(0) {
  root = new SearchNode(' ', 0.0f);

  // Prepare memory for the collection of best paths since we know the max. number already.
  best_paths.reserve(max_paths);
}

void
SearchTree::type(const t9_symbol_sequence &sequence, Model *model) {
  for (auto symbol : sequence) {
    // Add a new search tree table entry for the new level.
    std::vector<SearchNode *> table;
    depth++;

    insert(symbol, model);
  }
}

void
SearchTree::insert(t9_symbol symbol, Model *model) {
  t9_symbol_sequence sequence;

  root->insert(symbol, sequence, model);

  search_paths();

  prune();

// Output the new best paths for debugging.
//  std::string path_string;
//  for (const SearchPath &path : best_paths) {
//    path_string = path.to_string();
//    std::cout << "(" << path.get_probability() << ") \"" << path_string << "\"" << std::endl;
//  }
}

void
SearchTree::search_paths() {
  best_paths.clear();

  SearchPath path;
  root->search_paths(path, best_paths, max_paths);
}

void
SearchTree::prune() {
  if (depth < ngram_length) {
    return;
  }

  SearchPath path;
  // Prune the tree starting at the root node.
  root->prune(path, best_paths);
}

}  // namespace t9
