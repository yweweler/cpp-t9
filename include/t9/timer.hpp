// T9 performance profiling timers -*- C++ -*-

// Copyright (C) 2019 Yves-Noel Weweler.
// All Rights Reserved.
//
// Licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#ifndef CPP_T9_TIMER_HPP
#define CPP_T9_TIMER_HPP

#include <iostream>
#include <chrono>

using namespace std::chrono;

namespace t9 {
class timer {
 public:
  /**
   * Start a timer.
   */
  void start();

  /**
   * Stop a timer.
   */
  void stop();

  /**
   * Restart a timer. The timer gets reinitialized and starts.
   */
  void restart();

  /**
   * Query the elapsed time in milliseconds.
   * @note The timer has to be stopped manually before querying the elapsed duration.
   * @return Elapsed duration in milliseconds.
   */
  double duration_ms() const;

 protected:
  high_resolution_clock::time_point start_time;
  high_resolution_clock::time_point stop_time;
};
}

#endif //CPP_T9_TIMER_HPP
