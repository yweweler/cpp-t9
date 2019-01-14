// T9 model -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#ifndef CPP_T9_MODEL_HPP
#define CPP_T9_MODEL_HPP

#define PROBABILITY_BUTTON 1.0

namespace t9 {
class SearchTree;
class CorpusTree;
}  // namespace t9

#include <vector>
#include <utility>

#include "t9/symbols.hpp"
#include "t9/corpus.hpp"
#include "t9/tree.hpp"

namespace t9 {
class Model {
 public:
  /**
   * Construct a T9 model.
   * @param corpus Corpus object to use for model construction, training and validation.
   * @param ngram_length Length of the ngrams to use for model construction.
   * @param n_paths Number of paths/beams to maintain when building the best suggestions.
   */
  Model(const Corpus &corpus, size_t ngram_length, size_t n_paths);

  /**
   * Destruct the model.
   */
  ~Model();

  /**
   * Construct a statistical model of the likelihood of occurrence of ngram text sequences.
   */
  void
  build_corpus_tree();

  /**
   * Discard and reinitialize the search tree.
   */
  void
  reset_search_tree();

  /**
   * Autocomplete a sequence of T9 keys based on the statistical model.
   * @param input Sequence of T9 keys.
   * @return Collection of the best suggested completions and their scores (in descending order).
   */
  std::vector<std::pair<t9_symbol_sequence, float>>
  autocomplete(const t9_symbol_sequence &input);

  /**
   * Evaluate the model based on the corpus test data.
   * @return Evaluation score. Measures the number of element-wise differing characters between the best generated
   * suggestion and the ground-truth in percent.
   */
  float
  evaluate();

  /**
   * Calculate the conditional probability of `key` being pressed when a corpus symbol `symbol` was seen.
   * @param key T9 key.
   * @param symbol Corpus symbol.
   * @return Probability P(key | symbol)
   */
  float
  probability_key_when_symbol(t9_symbol key, t9_symbol symbol) const;

 public:
  // TODO(yweweler): Refactor: Write getter style access functions.
  SearchTree *search_tree;
  CorpusTree *corpus_tree;
  const Corpus &corpus;
  size_t ngram_length;

 protected:
  size_t n_paths;
};
}  // namespace t9

#endif //CPP_T9_MODEL_HPP
