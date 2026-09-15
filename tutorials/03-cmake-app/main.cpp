#include <cmath>
#include <cstdlib>
#include <iostream>
#include <span>
#include <vector>

// start cmake-app
#include "peak_volts.hpp"

namespace {

// Manufactured DC record: four voltages in volts (dtype double).
// 2.0, 2.5, 3.0, and 2.5 are exactly representable in IEEE-754 binary64, and
// their maximum is exactly 3.0 V. That is the correctness check: splitting
// the helper into its own translation unit must not change the peak.
constexpr double k_expected_peak_v = 3.0; // V
constexpr double k_abs_tol_v = 1e-15;     // V; a few ulps around 3.0 V

bool peak_is_correct_v(const double peak_v) {
  return std::isfinite(peak_v) &&
         std::abs(peak_v - k_expected_peak_v) <= k_abs_tol_v;
}

} // namespace

int main() {
  const std::vector<double> samples_v{2.0, 2.5, 3.0, 2.5}; // V
  const std::span<const double> view{samples_v};

  const double peak_v = peak_volts(view);
  std::cout << "peak = " << peak_v << " V\n";
  if (!peak_is_correct_v(peak_v)) {
    std::cerr << "correctness check failed: expected " << k_expected_peak_v
              << " V (dtype double, abs tol " << k_abs_tol_v << " V)\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
// end cmake-app
