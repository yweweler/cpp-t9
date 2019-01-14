// T9 search tree path -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#ifndef CPP_T9_PATH_HPP
#define CPP_T9_PATH_HPP

#include <vector>

#include "t9/node.hpp"

namespace t9 {
class SearchNode;
}  // namespace t9

namespace t9 {

class SearchPath {
 private:
  std::vector<SearchNode *> nodes;

 protected:
  float probability;

  /**
   * Compare to another path based on the symbols of the traversed nodes.
   * @param other Path to compare to.
   * @return true if all symbols are equal. false otherwise.
   */
  bool compare(const SearchPath &other) const;

 public:
  /**
   * Append a node to the end of the path.
   * @param node
   */
  void push_back(SearchNode *node);

  /**
   * Remove the last node from the end of the path.
   */
  void pop_back();

  /**
   * Clear and reset the entire path.
   */
  void clear();

  std::vector<SearchNode *>::const_iterator begin() const noexcept;
  std::vector<SearchNode *>::const_iterator end() const noexcept;

  std::vector<SearchNode *>::const_reverse_iterator crbegin() const noexcept;
  std::vector<SearchNode *>::const_reverse_iterator crend() const noexcept;

  bool operator==(const SearchPath &other) const;
  bool operator!=(const SearchPath &other) const;

  /**
   * Get the size of the path.
   * @return Number of nodes in the path.
   */
  std::size_t size() const;

  /**
   * Generate a string from the path.
   * @return String.
   */
  t9_symbol_sequence to_string() const;

  /**
   * Get the probability of the path.
   * @return Probability.
   */
  float get_probability() const;

  inline bool operator<(const SearchPath &other) {
    return probability < other.probability;
  }

  inline bool operator>(const SearchPath &other) {
    return probability > other.probability;
  }

  inline bool operator<=(const SearchPath &other) {
    return probability <= other.probability;
  }

  inline bool operator>=(const SearchPath &other) {
    return probability >= other.probability;
  }
};

}  // namespace t9

#endif //CPP_T9_PATH_HPP
