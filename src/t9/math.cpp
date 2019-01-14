// T9 math helper functions -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#include "t9/math.hpp"

namespace t9 {
float
ln(float x) {
  double tmp;

  tmp = x + DBL_MIN;
  if (tmp > 1.0) {
    tmp = 1.0;
  }
  return static_cast<float>(log(tmp));
}
}   // namespace t9
