// T9 math helper functions -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#ifndef CPP_T9_MATH_HPP
#define CPP_T9_MATH_HPP

#include <cfloat>
#include <cmath>

namespace t9 {
/**
 * Wrapper around y = log(x), that calculates y = log(x + DBL_MIN) and limits x + DBL_MIN to 1.0.
 * @param x Value.
 * @return log( limit( x + DBL_MIN , 1.0 ) )
 */
float ln(float x);
}  // namespace t9

#endif //CPP_T9_MATH_HPP
