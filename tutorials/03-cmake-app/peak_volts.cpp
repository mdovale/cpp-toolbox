// start cmake-app
#include "peak_volts.hpp"

// Definition lives in this translation unit. A second definition in the
// header would violate the one-definition rule once main.cpp is also
// compiled.
double peak_volts(std::span<const double> samples_v) {
  double peak_v = samples_v.front();
  for (const double sample_v : samples_v) {
    if (sample_v > peak_v) {
      peak_v = sample_v;
    }
  }
  return peak_v;
}
// end cmake-app
