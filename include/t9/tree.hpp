#ifndef CPP_T9_TREE_HPP
#define CPP_T9_TREE_HPP

#include <string>
#include <list>
#include <vector>
#include <algorithm>

namespace t9 {
class Model;
class SearchNode;
}

#include "t9/symbols.hpp"
#include "t9/math.hpp"
#include "t9/node.hpp"
#include "t9/path.hpp"
#include "t9/corpus.hpp"
#include "t9/generator.hpp"

namespace t9 {

/**
 * The corpus tree is used to build a ngram based statistical model of conditional symbol probabilities.
 */
class CorpusTree {
 public:
  // Root note of the tree.
  t9::CorpusNode root;

  /**
   * Construct a corpus tree.
   */
  CorpusTree();

  /**
   * Given a corpus insert all possible ngrams of a given length into a corpus tree.
   * @param corpus Corpus to be used for ngram generation.
   * @param ngram_length Length of the ngrams to be generated.
   */
  void
  insert_ngrams(const Corpus &corpus, size_t ngram_length);

  /**
   * Calculate the conditional probabilities for all tree nodes.
   */
  void
  calculate_probabilities();

  /**
   * Calculate the probability of a symbol sequence in the corpus tree.
   * @param sequence Corpus symbol sequence whose probability should be calculated.
   * @return Probability of the sequence if the sequence was found in the tree. Otherwise 0.0.
   */
  float
  conditional_probability(const std::string &sequence) const;
};

/**
 * The search tree is used to find the most probable sequence of corpus symbols for a given sewuence of T9 keys.
 */
class SearchTree {
 public:
  /**
   * Construct a search tree.
   * @param ngram_length Length of the ngrams to use.
   * @param max_paths Maximal number of best paths to keep track of.
   */
  SearchTree(size_t ngram_length, size_t max_paths);

  /**
   * Type a sequence of keys into the search tree and calculate the best text suggestions for the entered keys.
   * @param sequence Sequence of T9 keys to enter.
   * @param model Model to be used for searching the best text suggestions.
   */
  void
  type(const t9_symbol_sequence &sequence, Model *model);

  /**
   * Type a single symbol into a search tree and update the whole model.
   * This includes searching the best paths and pruning the model.
   * @param symbol T9 key to type.
   * @param model T9 model.
   */
  void
  insert(t9_symbol symbol, Model *model);

  /**
   * Update the list of best scoring paths in the tree.
   */
  void
  search_paths();

  /**
   * Prune the search tree.
   */
  void
  prune();

 public:
  // Collection of best scoring paths in the search tree.
  std::vector<SearchPath> best_paths;

  // Length of the ngrams used constructing and pruning tree.
  size_t ngram_length;

  // Maximal number of best scoring paths to keep track of.
  size_t max_paths;

  // Root note of the tree.
  SearchNode *root;

 protected:
  // Depth of the tree.
  size_t depth;
};

}  // namespace t9

#endif //CPP_T9_TREE_HPP
