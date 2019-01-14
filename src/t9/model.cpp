// T9 model -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#include "t9/model.hpp"

namespace t9 {

Model::Model(const Corpus &corpus, size_t ngram_length, size_t n_paths)
    : corpus(corpus),
      ngram_length(ngram_length),
      n_paths(n_paths) {
  search_tree = new SearchTree(ngram_length, n_paths);
  corpus_tree = new CorpusTree();
}

Model::~Model() {
  delete corpus_tree;
  delete search_tree;
}

void
Model::build_corpus_tree() {
  corpus_tree->insert_ngrams(corpus, ngram_length);
  corpus_tree->calculate_probabilities();
}

void
Model::reset_search_tree() {
  delete search_tree;
  search_tree = new SearchTree(ngram_length, n_paths);
}

std::vector<std::pair<t9_symbol_sequence, float>>
Model::autocomplete(const t9_symbol_sequence &input) {
  std::vector<std::pair<t9_symbol_sequence, float>> suggestions;
  std::pair<t9_symbol_sequence, float> suggestion;

  // Validate that the sequence to be inserted only contains valid lexicon symbols.
  if (corpus.validate_t9_keys(input)) {
    // Autocomplete a given input sequence based onm the model.
    search_tree->type(input, this);

    // Create a collection containing the suggested completions and their scores.
    for (const auto &path : search_tree->best_paths) {
      suggestion = {
          path.to_string(),
          path.get_probability()
      };
      suggestions.push_back(suggestion);
    }
    return suggestions;
  } else {
    std::string error_msg = format("The key sequence contains invalid symbols.");
    throw std::runtime_error(error_msg);
  }

}

float
Model::evaluate() {
  float error;
  const t9_symbol_sequence &ground_truth(corpus.get_test_data());
  t9_symbol_sequence input;
  std::vector<std::pair<t9_symbol_sequence, float>> suggestions;
  t9_symbol_sequence best_suggestion;
  size_t n_diff_symbols;

  // Validate that the sequence to be inserted only contains valid corpus symbols.
  if (corpus.validate_corpus_symbols(input)) {
    // Convert corpus symbols into key symbols.
    input = corpus.keys_from_corpus(ground_truth);

//    reset_search_tree();

    // Collect the best suggestions.
    suggestions = autocomplete(input);

    // Only use the best scoring suggestion for error calculation.
    best_suggestion = suggestions.front().first;

    // Calculate the deviation between the suggestion and the ground-truth.
    n_diff_symbols = corpus.sequence_diff(best_suggestion, ground_truth);

    // Calculate the error.
    error = static_cast<float>(n_diff_symbols) / static_cast<float>(best_suggestion.length());

  } else {
    std::string error_msg = format("The test corpus sequence contains invalid symbols.");
    throw std::runtime_error(error_msg);
  }

  return error;
}

float
Model::probability_key_when_symbol(t9_symbol key, t9_symbol symbol) const {
  float prob;
  const t9_symbol_sequence &corpus_symbols(corpus.ktoc(key));

  prob = PROBABILITY_BUTTON;

  t9_symbol_sequence::size_type location = corpus_symbols.find(symbol);

  if (location != t9_symbol_sequence::npos) {
    // Symbol is assigned to the button.
    return prob;
  }

  // Letter is not assigned to the button.
  return 1.0f - prob;
}

}  // namespace t9
