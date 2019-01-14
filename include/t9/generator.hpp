// T9 NGRAM generator -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#ifndef CPP_T9_GENERATOR_HPP
#define CPP_T9_GENERATOR_HPP

#include <string>

#include "t9/symbols.hpp"
#include "t9/corpus.hpp"

namespace t9 {
class NGRAMGenerator {
 public:
  /**
   * Construct a ngram generator.
   * @param corpus Corpus object to generate ngrams from.
   * @param ngram_length Length of the ngrams to be generated.
   * @note The generator generates ngrams over the training portion of the corpus.
   */
  NGRAMGenerator(const Corpus &corpus, size_t ngram_length);

  /**
   * Check if the generator is finished.
   * @return true if the generator is finished, false if there are still ngrams available.
   */
  bool
  is_done() const;

  /**
   * Generate a ngram from the corpus train portion.
   * @return ngram.
   */
  std::string_view
  generate_ngram();

 protected:
  const Corpus &corpus;
  size_t ngram_length;
  t9_symbol_sequence::const_iterator corpus_iterator;
  t9_symbol_sequence::const_iterator corpus_iterator_end;
};
}  // namespace t9

#endif //CPP_T9_GENERATOR_HPP
