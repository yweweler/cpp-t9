// Text based data corpus -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#include "t9/corpus.hpp"

namespace t9 {
Corpus::Corpus(const std::filesystem::path &train_file_path, size_t n_train,
               const std::filesystem::path &test_file_path, size_t n_test,
               const std::unordered_map<t9_symbol, t9_symbol_sequence> &keyboard)
    : key_2_corpus_map(keyboard) {

  std::unordered_set<t9_symbol> train_data_set;
  std::unordered_set<t9_symbol> test_data_set;
  bool symbols_valid;

  // Construct the key set and the corpus symbol set.
  for (auto const &[key, value] : key_2_corpus_map) {
    // Update the the t9 key set.
    keys_set.insert(key);

    // Update the corpus symbol set and.
    // populate the reverse corpus_2_key_map table.
    for (auto symbol : value) {
      corpus_set.insert(symbol);
      corpus_2_key_map[symbol] = key;
    }
  }

  // Load the train data.
  train_data = t9::io::load_text_file(train_file_path, n_train);
  std::cout << "Loaded train data (" << train_data.size() << " bytes)" << std::endl;

  // Construct a set of symbols contained in the train data.
  train_data_set = construct_set_from_sequence(train_data);
//  std::cout << "Unique symbols found " << train_data_set.size() << std::endl;

  // Check if the loaded train data only contains valid symbols.
  symbols_valid = validate_corpus_symbols(train_data);
  if (!symbols_valid) {
    std::string error_msg = format("The train data contains invalid symbols.");
    throw std::runtime_error(error_msg);
  }
  std::cout << "Train data validated successfully" << std::endl;

  // Load the test data.
  test_data = t9::io::load_text_file(test_file_path, n_test);
  std::cout << "Loaded test data (" << test_data.size() << " bytes)" << std::endl;

  // Construct a set of symbols contained in the test data.
  test_data_set = construct_set_from_sequence(test_data);
//  std::cout << "Unique symbols found " << test_data_set.size() << std::endl;

  // Check if the loaded test data only contains valid symbols.
  symbols_valid = validate_corpus_symbols(test_data);
  if (!symbols_valid) {
    std::string error_msg = format("The test data contains invalid symbols.");
    throw std::runtime_error(error_msg);
  }
  std::cout << "Test data validated successfully" << std::endl;
}

const t9_symbol_sequence &
Corpus::ktoc(t9_symbol key) const {
  // Search for the key.
  auto corpus_symbol = key_2_corpus_map.find(key);

  if (corpus_symbol != key_2_corpus_map.end()) {
    // The key was found, return the corresponding corpus symbols.
    return corpus_symbol->second;
  } else {
    // The passed key is unknown.
    std::string error_msg = format("Failed to find key \"%c\": No such key in the lookup table.", key);
    throw std::runtime_error(error_msg);
  }
}

t9_symbol
Corpus::ctok(t9_symbol corpus_symbol) const {
  // Search for the corpus symbol.
  auto key = corpus_2_key_map.find(corpus_symbol);

  if (key != corpus_2_key_map.end()) {
    // The corpus symbols was found, return the corresponding key.
    return key->second;
  } else {
    // The passed corpus symbol is unknown.
    std::string error_msg = format(
        "Failed to find corpus symbol \"%c\": No such symbol in the lookup table.", key);
    throw std::runtime_error(error_msg);
  }
}

bool
Corpus::validate_t9_keys(const t9_symbol_sequence &keys) const {
  for (auto key : keys) {
    // Check if the key is a known (valid) key.
    auto lookup = keys_set.find(key);

    if (lookup == keys_set.end()) {
      // The key was not found and hence is not a valid.
      return false;
    }
  }

  // Each key was found, the sequence is valid.
  return true;
}

bool
Corpus::validate_corpus_symbols(const t9_symbol_sequence &symbols) const {
  for (auto symbol : symbols) {
    // Check if the symbol is a known (valid) corpus symbol.
    auto lookup = corpus_set.find(symbol);
    if (lookup == corpus_set.end()) {
      // The symbol was not found and hence is not a valid.
      return false;
    }
  }

  // Each symbol was found, the sequence is valid.
  return true;
}

size_t
Corpus::sequence_diff(const t9_symbol_sequence &seq1,
                      const t9_symbol_sequence &seq2) const {
  t9_symbol_sequence::const_iterator seq1_iter;
  t9_symbol_sequence::const_iterator seq2_iter;
  size_t diff;

  // Make sure both sequences are of equal length.
  if (seq1.length() != seq2.length()) {
    const std::string error_msg("Failed to compare sequences: Sequences have different length.");
    throw std::runtime_error(error_msg);
  }

  seq1_iter = seq1.begin();
  seq2_iter = seq2.begin();
  diff = 0;

  // Iterate over both sequences.
  while (seq1_iter != seq1.end() && seq2_iter != seq2.end()) {
    // Check if the symbols do not match.
    if (*seq1_iter != *seq2_iter) {
      // Increase distance for each non matching pair.
      diff++;
    }
    seq1_iter++;
    seq2_iter++;
  }

  return diff;
}

t9_symbol_sequence
Corpus::keys_from_corpus(const t9_symbol_sequence &corpus_sequence) const {
  t9_symbol_sequence keys;

  // Convert each corpus symbol to its corresponding key.
  for (auto corpus_symbol : corpus_sequence) {
    keys.push_back(ctok(corpus_symbol));
  }

  return keys;
}

std::unordered_set<t9_symbol>
Corpus::construct_set_from_sequence(const t9_symbol_sequence &data) {
  std::unordered_set<t9_symbol> symbol_set;

  for (auto symbol : data) {
    symbol_set.insert(symbol);
  }

  return symbol_set;
}

const t9_symbol_sequence &
Corpus::get_train_data() const {
  return train_data;
}

const t9_symbol_sequence &
Corpus::get_test_data() const {
  return test_data;
}
}  // namespace t9
