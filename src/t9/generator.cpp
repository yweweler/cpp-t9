// T9 NGRAM generator -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#include "t9/generator.hpp"

namespace t9 {
NGRAMGenerator::NGRAMGenerator(const Corpus &corpus, size_t ngram_length)
    : corpus(corpus), ngram_length(ngram_length) {
  corpus_iterator = corpus.get_train_data().begin();
  corpus_iterator_end = corpus.get_train_data().end() - ngram_length + 1;
}

bool
NGRAMGenerator::is_done() const {
  return (corpus_iterator == corpus_iterator_end);
}

std::string_view
NGRAMGenerator::generate_ngram() {
  std::string_view ngram;
  if (!is_done()) {
    // Construct a string view for the new ngram.
    ngram = {corpus_iterator.base(), ngram_length};
    corpus_iterator++;
  } else {
    std::string error_msg = format(
        "Error: No more ngrams are available. Please check is_done() before requesting an ngram from the generator.");
    throw std::runtime_error(error_msg);
  }

  return ngram;
}
}  // namespace t9
