// T9 program entry -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#include <filesystem>
#include <iostream>
#include <map>
#include <iterator>
#include <iomanip>
#include <t9/model.hpp>

#include "t9/timer.hpp"

void example_autocomplete(t9::Model &model, const t9_symbol_sequence &input) {
  // Autocomplete text based on a sequence of T9 key presses.

  t9::timer timer;
  std::cout << std::endl << "Typing sequence: " << input << std::endl;

  // Discard any old search information.
  model.reset_search_tree();

  timer.restart();
//    model.reset_search_tree();
  auto suggestions = model.autocomplete(input);
  timer.stop();

  // Output the best `n_paths` suggestions in descending order.
  std::cout << "Autocomplete suggestions: " << std::endl;
  for (auto const &[text, score] : suggestions) {
    std::cout << "    ("
              << std::fixed << std::setprecision(4) << score << "): "
              << "\"" << text << "\""
              << std::endl;
  }

  std::cout << "Autocomplete took: "
            << std::fixed << std::setprecision(2) << timer.duration_ms() << " ms"
            << std::endl;
}

void example_evaluate(t9::Model &model) {
  // Evaluate model using the test corpus.

  t9::timer timer;
  float error;

  // Discard any old search information.
  model.reset_search_tree();

  timer.restart();
  error = model.evaluate();
  timer.stop();
  std::cout << "Evaluation: "
            << "duration: " << std::fixed << std::setprecision(2) << timer.duration_ms() << " ms,  "
            << "error: " << std::fixed << std::setprecision(3) << error
            << std::endl;
}

int main() {
  // Lookup table mapping t9 keys to corpus symbols.
  std::map<t9_symbol, t9_symbol_sequence> key_2_corpus_table;

  // Note: std::filesystem::path is available since C++17.
  std::filesystem::path train_file_path;
  std::filesystem::path test_file_path;

  // Number of symbols to load from the train data file.
  size_t n_train_symbols;
  // Number of symbols to load from the test data file.
  size_t n_test_symbols;

  train_file_path = "data/trump/twitter.txt";
  n_train_symbols = 0;

  test_file_path = "data/trump/twitter.txt";
  n_test_symbols = 140;

  size_t ngram_length;
  size_t n_paths;

  t9::timer timer;

  // Construct a lookup table that assigns the corpus symbols to t9 keys.
  key_2_corpus_table = {
      {'0', SYMBOLS_T0},
      {'1', SYMBOLS_T1},
      {'2', SYMBOLS_T2},
      {'3', SYMBOLS_T3},
      {'4', SYMBOLS_T4},
      {'5', SYMBOLS_T5},
      {'6', SYMBOLS_T6},
      {'7', SYMBOLS_T7},
      {'8', SYMBOLS_T8},
      {'9', SYMBOLS_T9},
      {'*', SYMBOLS_TS},
      {'#', SYMBOLS_TR},
  };

  std::cout << "========================================================" << std::endl;
  std::cout << "Key to Corpus Table:" << std::endl;
  std::cout << "========================================================" << std::endl;
  for (auto const &[key, value] : key_2_corpus_table) {
    std::cout << key << ": \"" << value << "\"" << std::endl;
  }
  std::cout << "========================================================" << std::endl << std::endl;


  // N-gram length to use for building the trees.
  ngram_length = 4;

  // Number best completion paths (completion sequences) to maintain.
  n_paths = 15;

  try {
    // Load the corpus from disk.
    timer.start();
    t9::Corpus corpus(train_file_path, n_train_symbols, test_file_path, n_test_symbols, key_2_corpus_table);
    timer.stop();
    std::cout << "Loading the corpus took: "
              << std::fixed << std::setprecision(2) << timer.duration_ms() << " ms"
              << std::endl;

    // Build the model.
    timer.restart();
    t9::Model model(corpus, ngram_length, n_paths);
    model.build_corpus_tree();
    timer.stop();
    std::cout << "Building the model took: "
              << std::fixed << std::setprecision(2) << timer.duration_ms() << " ms"
              << std::endl;

    // Example 1: Autocomplete text based on a sequence of T9 key presses.
    example_autocomplete(model, "366253#87867");

//     Example 2: Evaluate model using the test corpus.
//    example_evaluate(model);
  }
  catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
    std::cout << "Error: Could not load corpus." << std::endl;
  }

  std::cout << "Done!" << std::endl;
  return 0;
}
