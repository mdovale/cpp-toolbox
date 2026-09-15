#include <cmath>
#include <cstdlib>
#include <iostream>
#include <span>
#include <string_view>
#include <vector>

// start raii-and-ownership
namespace {

// Manufactured DC record: four voltages in volts (dtype double).
// 2.0, 2.5, 3.0, and 2.5 are exactly representable in IEEE-754 binary64, and
// their maximum is exactly 3.0 V. That is the correctness check.
constexpr double k_expected_peak_v = 3.0; // V
constexpr double k_abs_tol_v = 1e-15;     // V; a few ulps around 3.0 V

// Invariant: samples_v names a non-empty contiguous record of voltages in
// volts. The caller owns the buffer and keeps that storage alive for this
// call; the span does not copy it and does not extend its lifetime. Return
// value is the maximum in volts.
double peak_volts(std::span<const double> samples_v) {
  double peak_v = samples_v.front();
  for (const double sample_v : samples_v) {
    if (sample_v > peak_v) {
      peak_v = sample_v;
    }
  }
  return peak_v;
}

bool peak_is_correct_v(const double peak_v) {
  return std::isfinite(peak_v) &&
         std::abs(peak_v - k_expected_peak_v) <= k_abs_tol_v;
}

} // namespace

int main(int argc, char* argv[]) {
  const bool broken = argc == 2 && std::string_view{argv[1]} == "--broken";
  if (argc > 1 && !broken) {
    std::cerr << "usage: raii-and-ownership [--broken]\n";
    return EXIT_FAILURE;
  }

  if (broken) {
    // Opt-in undefined behavior. view still holds a pointer and length 4
    // after the vector destructor has released the buffer. Do not take this
    // branch in CI or the default run; the sanitize preset would then fail.
    std::span<const double> view;
    {
      const std::vector<double> samples_v{2.0, 2.5, 3.0, 2.5}; // V
      view = samples_v;
    }
    const double peak_v = peak_volts(view);
    std::cout << "peak (broken, dangling view) = " << peak_v << " V\n";
    return EXIT_SUCCESS;
  }

  // Owner: vector acquires the heap buffer and releases it in its destructor.
  const std::vector<double> samples_v{2.0, 2.5, 3.0, 2.5}; // V
  // View: pointer and length; no copy of the voltages.
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
// end raii-and-ownership
