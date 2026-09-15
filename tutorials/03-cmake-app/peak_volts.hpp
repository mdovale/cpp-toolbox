// start cmake-app
#pragma once

#include <span>

// Invariant: samples_v names a non-empty contiguous record of voltages in
// volts. The caller owns the buffer and keeps that storage alive for this
// call. Return value is the maximum in volts.
double peak_volts(std::span<const double> samples_v);
// end cmake-app
