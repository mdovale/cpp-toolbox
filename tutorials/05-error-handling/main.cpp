#include <cmath>
#include <cstdlib>
#include <iostream>
#include <span>
#include <stdexcept>
#include <string_view>
#include <vector>

// start error-handling
namespace {

// Manufactured DC record: four voltages in volts (dtype double).
// 2.0, 2.5, 3.0, and 2.5 are exactly representable in IEEE-754 binary64, and
// their arithmetic mean is exactly 2.5 V when n >= 1. That is the check.
constexpr double k_expected_mean_v = 2.5; // V
constexpr double k_abs_tol_v = 1e-15;     // V; a few ulps around 2.5 V
// Pitfall: 3.0 V is the peak of this record, not a mean of an empty one.
constexpr double k_dummy_v = 3.0; // V; plausible, not the mean of n = 0

// Invariant: samples_v is a non-empty contiguous record of voltages in volts.
// Return value is the arithmetic mean in volts. Empty is a failed experiment:
// throw std::invalid_argument; do not divide by n = 0.
double mean_volts(std::span<const double> samples_v) {
  if (samples_v.empty()) {
    throw std::invalid_argument("mean_volts: empty voltage record");
  }
  double sum_v = 0.0;
  for (const double sample_v : samples_v) {
    sum_v += sample_v;
  }
  return sum_v / static_cast<double>(samples_v.size());
}

bool mean_is_correct_v(const double mean_v) {
  return std::isfinite(mean_v) &&
         std::abs(mean_v - k_expected_mean_v) <= k_abs_tol_v;
}

} // namespace

int main(int argc, char* argv[]) {
  const bool broken = argc == 2 && std::string_view{argv[1]} == "--broken";
  if (argc > 1 && !broken) {
    std::cerr << "usage: error-handling [--broken]\n";
    return EXIT_FAILURE;
  }

  if (broken) {
    // Opt-in swallow: the helper reports the empty record, then the catch
    // keeps a dummy voltage and exits 0. Defined; sanitizers stay quiet.
    const std::vector<double> empty_v{};
    const std::span<const double> view{empty_v};
    double mean_v = k_dummy_v; // V; used if the helper reports failure
    try {
      mean_v = mean_volts(view);
    } catch (const std::invalid_argument&) {
      // Swallow: mean_volts already detected the empty record.
    }
    std::cout << "mean = " << mean_v << " V\n";
    return EXIT_SUCCESS;
  }

  const std::vector<double> samples_v{2.0, 2.5, 3.0, 2.5}; // V
  const std::span<const double> view{samples_v};

  const double mean_v = mean_volts(view);
  std::cout << "mean = " << mean_v << " V\n";
  if (!mean_is_correct_v(mean_v)) {
    std::cerr << "correctness check failed: expected " << k_expected_mean_v
              << " V (dtype double, abs tol " << k_abs_tol_v << " V)\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
// end error-handling
