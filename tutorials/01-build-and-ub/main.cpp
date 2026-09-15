#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <span>
#include <string_view>
#include <vector>

// start build-and-ub
namespace {

// Manufactured DC calibration: four voltages in volts (dtype double).
// 2.0, 2.5, 3.0, and 2.5 are exactly representable in IEEE-754 binary64, and
// their arithmetic mean is exactly 2.5 V. That is the correctness check.
constexpr double k_expected_mean_v = 2.5; // V
constexpr double k_abs_tol_v = 1e-15;     // V; a few ulps around 2.5 V

// Invariant: samples_v is a contiguous record of voltages in volts. Valid
// indices are 0 .. size()-1. The return value is the arithmetic mean in volts.
double mean_volts(std::span<const double> samples_v) {
  double sum_v = 0.0;
  for (const double sample_v : samples_v) {
    sum_v += sample_v;
  }
  return sum_v / static_cast<double>(samples_v.size());
}

// Pitfall: a 1-based loop (MATLAB / Fortran habit) reads samples_v[n], which
// is not a sample. operator[] is unchecked; this is undefined behavior, not
// a guaranteed crash. .at(n) would throw instead -- defined, still wrong.
// Default execution never calls this function.
double mean_volts_one_based(std::span<const double> samples_v) {
  double sum_v = 0.0;
  for (std::size_t i = 1; i <= samples_v.size(); ++i) {
    sum_v += samples_v[i];
  }
  return sum_v / static_cast<double>(samples_v.size());
}

bool mean_is_correct_v(const double mean_v) {
  return std::isfinite(mean_v) &&
         std::abs(mean_v - k_expected_mean_v) <= k_abs_tol_v;
}

} // namespace

int main(int argc, char* argv[]) {
  const std::vector<double> samples_v{2.0, 2.5, 3.0, 2.5}; // V
  const std::span<const double> view{samples_v};

  const bool broken = argc == 2 && std::string_view{argv[1]} == "--broken";
  if (argc > 1 && !broken) {
    std::cerr << "usage: build-and-ub [--broken]\n";
    return EXIT_FAILURE;
  }

  if (broken) {
    // Opt-in undefined behavior. Do not take this branch in CI or the default
    // run; the sanitize preset would then be a landmine.
    const double mean_v = mean_volts_one_based(view);
    std::cout << "mean (broken, 1-based) = " << mean_v << " V\n";
    return EXIT_SUCCESS;
  }

  const double mean_v = mean_volts(view);
  std::cout << "mean = " << mean_v << " V\n";
  if (!mean_is_correct_v(mean_v)) {
    std::cerr << "correctness check failed: expected " << k_expected_mean_v
              << " V (dtype double, abs tol " << k_abs_tol_v << " V)\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
// end build-and-ub
