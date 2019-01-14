// Text based data corpus -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#ifndef CPP_T9_CORPUS_HPP
#define CPP_T9_CORPUS_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <iterator>

#include "format.hpp"
#include "t9/symbols.hpp"
#include "t9/io.hpp"


// List of corpus symbols assigned to single T9 keys.
#define SYMBOLS_T0  "0"
#define SYMBOLS_T1 ".,1"
#define SYMBOLS_T2  "aAbBcC2"
#define SYMBOLS_T3  "dDeEfF3"
#define SYMBOLS_T4  "gGhHiI4"
#define SYMBOLS_T5  "jJkKlL5"
#define SYMBOLS_T6  "mMnNoO6"
#define SYMBOLS_T7  "pPqQrRsS7"
#define SYMBOLS_T8  "tTuUvV8"
#define SYMBOLS_T9  "wWxXyYzZ9"
#define SYMBOLS_TS  ""
#define SYMBOLS_TR  " "

namespace t9 {
class Corpus {
 public:
  /***
   * Construct a corpus.
   * @param train_file_path Path to a text file containing the training data.
   * @param n_train Number of bytes to load from the train file.
   * @param test_file_path Path to a text file containing the test data.
   * @param n_test Number of bytes to load from the test file.
   * @param keyboard map defining the mapping between T9 keyboard keys and the corresponding corpus symbols.
   */
  Corpus(const std::filesystem::path &train_file_path, size_t n_train,
         const std::filesystem::path &test_file_path, size_t n_test,
         const std::map<t9_symbol, t9_symbol_sequence> &keyboard);

  /***
   * Get a sequence of all the corpus symbols that are assigned to a key.
   * @param key T9 keyboard key
   * @return Sequence of corpus symbols that are assigned to the key.
   */
  const t9_symbol_sequence &
  ktoc(t9_symbol key) const;

  /***
   * Convert a corpus symbol to corresponding key (T9 key).
   * @param corpus_symbol Corpus symbol to be converted.
   * @return T9 keyboard key.
   */
  t9_symbol
  ctok(t9_symbol corpus_symbol) const;

  /***
   * Check if a symbol sequence only contains valid keys.
   * @param keys Sequence of symbols to validate.
   * @return true if all symbols are valid, false otherwise.
   */
  bool
  validate_t9_keys(const t9_symbol_sequence &keys) const;

  /***
   * Check if a symbol sequence only contains valid corpus symbols.
   * @param symbols Sequence of symbols to validate.
   * @return true if all symbols are valid, false otherwise.
   */
  bool
  validate_corpus_symbols(const t9_symbol_sequence &symbols) const;

  /***
   * Count element wise how many symbols in two sequences are differing.
   * Both sequences are required to have the same length.
   * @param seq1 Sequence 1.
   * @param seq2 Sequence 2.
   * @return Amount of element wise differing characters.
   */
  size_t
  sequence_diff(const t9_symbol_sequence &seq1,
                const t9_symbol_sequence &seq2) const;

  /**
   * Convert a sequence of corpus symbols into a sequence of T9 keys.
   * @param corpus_sequence Sequence to corpus symbols to convert.
   * @return Sequence of T9 keys.
   */
  t9_symbol_sequence
  keys_from_corpus(const t9_symbol_sequence &corpus_sequence) const;

  /**
   * Get the train data.
   * @return Sequence of corpus symbols for training.
   */
  const t9_symbol_sequence &
  get_train_data() const;

  /**
   * Get the test data.
   * @return Sequence of corpus symbols for evaluation.
   */
  const t9_symbol_sequence &
  get_test_data() const;

  // Set of unique keys found in the key to corpus symbol table.
  std::set<t9_symbol> keys_set;

  // Set of unique corpus symbols found in the key to corpus symbol table.
  std::set<t9_symbol> corpus_set;

 protected:
  /***
   * Populate a set with unique symbols found in a sequence.
   * @param data Data sequence to construct the set from.
   * @return A set of thee unique symbols contained.
   */
  std::set<t9_symbol>
  construct_set_from_sequence(const t9_symbol_sequence &data);

 private:
  std::map<t9_symbol, t9_symbol_sequence> key_2_corpus_map;
  std::map<t9_symbol, t9_symbol> corpus_2_key_map;

  // Training data.
  t9_symbol_sequence train_data;

  // Training data.
  t9_symbol_sequence test_data;
};
}  // namespace t9

#endif //CPP_T9_CORPUS_HPP
