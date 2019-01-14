// T9 search tree path -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#include "t9/path.hpp"

#include "t9/tree.hpp"

namespace t9 {

bool
SearchPath::compare(const SearchPath &other) const {
  if (size() != other.size()) {
    return false;
  }

  auto p1_iter = crbegin();
  auto p2_iter = other.crbegin();

  // Iterate over both paths.
  while (p1_iter != crend() && p2_iter != other.crend()) {
    SearchNode *node1 = *p1_iter;
    SearchNode *node2 = *p2_iter;
    // Check if the symbols to not math.
    if (node1->symbol != node2->symbol) {
      return false;
    }
    p1_iter++;
    p2_iter++;
  }

  return true;
}

void
SearchPath::push_back(SearchNode *node) {
  probability = node->probability;
  nodes.push_back(node);
}

void
SearchPath::pop_back() {
  probability = -1.0f;
  nodes.pop_back();
}

void
SearchPath::clear() {
  nodes.clear();
  probability = 0.0f;
}

std::size_t
SearchPath::size() const {
  return nodes.size();
}

t9_symbol_sequence
SearchPath::to_string() const {
  std::string str;
  str.reserve(size());

  for (const SearchNode *node : nodes) {
    str.push_back(node->symbol);
  }

  return str;
}

float
SearchPath::get_probability() const {
  return probability;
}

std::vector<SearchNode *>::const_iterator
SearchPath::begin() const noexcept {
  return nodes.begin();
}

std::vector<SearchNode *>::const_iterator
SearchPath::end() const noexcept {
  return nodes.end();
}

std::vector<SearchNode *>::const_reverse_iterator
SearchPath::crbegin() const noexcept {
  return nodes.crbegin();
}

std::vector<SearchNode *>::const_reverse_iterator
SearchPath::crend() const noexcept {
  return nodes.crend();
}

bool
SearchPath::operator==(const SearchPath &other) const {
  return compare(other);
}
bool
SearchPath::operator!=(const SearchPath &other) const {
  return !(other == *this);
}

}  // namespace t9