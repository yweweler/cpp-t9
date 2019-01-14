// T9 performance profiling timers -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#include "t9/timer.hpp"

namespace t9 {
void
timer::start() {
  start_time = high_resolution_clock::now();
}

void
timer::stop() {
  stop_time = high_resolution_clock::now();
}

void
timer::restart() {
  stop_time = high_resolution_clock::time_point();
  start();
}

double
timer::duration_ms() const {
  double duration = static_cast<double>(duration_cast<nanoseconds>(stop_time - start_time).count());
  return duration / 1000000.0;
}
}