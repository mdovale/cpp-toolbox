#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string_view>

// start floating-point
namespace {

// Angle in radians (dtype double). 1e-8 rad is small enough that 1 and
// cos(x) agree to more than the 53-bit significand can separate.
constexpr double k_x_rad = 1e-8;     // rad
constexpr double k_expected_f = 0.5; // dimensionless; lim x->0 (1-cos x)/x^2
constexpr double k_abs_tol_f =
    1e-12; // dimensionless; stable form matches 1/2 to this tol
constexpr double k_round_tol_v = 1e-15; // V; a few ulps around 0.3 V

// Pitfall: 1 and cos(x) share leading bits, so 1-cos(x) is rounding noise
// (often 0) and the quotient is not 1/2. Default execution never calls this.
double f_naive(const double x_rad) {
  return (1.0 - std::cos(x_rad)) / (x_rad * x_rad);
}

// Invariant: uses 1-cos x = 2 sin^2(x/2), so the cancellation is gone.
// Return value is dimensionless and equals 1/2 in the limit x -> 0.
double f_stable(const double x_rad) {
  const double half_x_rad = 0.5 * x_rad;
  const double sinc = std::sin(half_x_rad) / half_x_rad;
  return 0.5 * sinc * sinc;
}

bool f_is_correct(const double f) {
  return std::isfinite(f) && std::abs(f - k_expected_f) <= k_abs_tol_f;
}

bool sum_is_close_v(const double sum_v, const double target_v) {
  return std::isfinite(sum_v) && std::abs(sum_v - target_v) <= k_round_tol_v;
}

} // namespace

int main(int argc, char* argv[]) {
  const bool broken = argc == 2 && std::string_view{argv[1]} == "--broken";
  if (argc > 1 && !broken) {
    std::cerr << "usage: floating-point [--broken]\n";
    return EXIT_FAILURE;
  }

  // Rounding on entry: 0.1 V and 0.2 V are not binary64 values, so their
  // sum is not the binary64 value of the decimal 0.3 V. == is the wrong
  // check; a few ulps is the honest one.
  const double tenth_v = 0.1; // V
  const double fifth_v = 0.2; // V
  const double sum_v = tenth_v + fifth_v;
  const double three_tenths_v = 0.3; // V
  std::cout << "0.1 V + 0.2 V = " << sum_v << " V\n";
  std::cout << "residual vs 0.3 V = " << (sum_v - three_tenths_v) << " V\n";
  if (!sum_is_close_v(sum_v, three_tenths_v)) {
    std::cerr << "rounding check failed: expected " << three_tenths_v
              << " V within " << k_round_tol_v << " V (dtype double)\n";
    return EXIT_FAILURE;
  }

  if (broken) {
    // Opt-in defined, sanitizer-clean, numerically wrong. Do not take this
    // branch as evidence that f is 1/2; AddressSanitizer will stay quiet.
    const double f = f_naive(k_x_rad);
    std::cout << "f naive (1-cos x)/x^2 at x = " << k_x_rad << " rad = " << f
              << "\n";
    return EXIT_SUCCESS;
  }

  const double f = f_stable(k_x_rad);
  std::cout << "f stable at x = " << k_x_rad << " rad = " << f << "\n";
  if (!f_is_correct(f)) {
    std::cerr << "correctness check failed: expected " << k_expected_f
              << " (dtype double, abs tol " << k_abs_tol_f << ")\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
// end floating-point
