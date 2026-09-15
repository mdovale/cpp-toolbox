#include <array>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string_view>

// start small-linear-algebra
namespace {

// 3-vector and 3x3 map, dtype double. Positions are meters; A is
// dimensionless. Column-major: a_ij lives at index i + 3*j (i row, j col).
using Vec3 = std::array<double, 3>;
using Mat3 = std::array<double, 9>;

constexpr std::size_t k_n = 3;
constexpr double k_abs_tol_m = 1e-15;         // m; a few ulps around Ax
constexpr Vec3 k_expected_y_m{5.0, 8.0, 3.0}; // m; manufactured A x

// Invariant: a is column-major with a_ij at i + k_n*j. Return value is A x
// in the same unit as x_m (meters).
Vec3 apply_map(const Mat3& a, const Vec3& x_m) {
  Vec3 y_m{};
  for (std::size_t i = 0; i < k_n; ++i) {
    double sum_m = 0.0;
    for (std::size_t j = 0; j < k_n; ++j) {
      sum_m += a[i + k_n * j] * x_m[j];
    }
    y_m[i] = sum_m;
  }
  return y_m;
}

// Pitfall: j + k_n*i reads a_ji, so this forms A^T x. Default never calls it.
Vec3 apply_map_transposed_layout(const Mat3& a, const Vec3& x_m) {
  Vec3 y_m{};
  for (std::size_t i = 0; i < k_n; ++i) {
    double sum_m = 0.0;
    for (std::size_t j = 0; j < k_n; ++j) {
      sum_m += a[j + k_n * i] * x_m[j];
    }
    y_m[i] = sum_m;
  }
  return y_m;
}

bool y_is_correct_m(const Vec3& y_m) {
  for (std::size_t i = 0; i < k_n; ++i) {
    if (!std::isfinite(y_m[i]) ||
        std::abs(y_m[i] - k_expected_y_m[i]) > k_abs_tol_m) {
      return false;
    }
  }
  return true;
}

void write_vec_m(const Vec3& y_m) {
  std::cout << "y = [" << y_m[0] << ", " << y_m[1] << ", " << y_m[2] << "] m\n";
}

} // namespace

int main(int argc, char* argv[]) {
  const bool broken = argc == 2 && std::string_view{argv[1]} == "--broken";
  if (argc > 1 && !broken) {
    std::cerr << "usage: small-linear-algebra [--broken]\n";
    return EXIT_FAILURE;
  }

  // Columns of A: (1,0,0), (2,1,0), (0,2,1). Integers, exact in binary64.
  const Mat3 a{1.0, 0.0, 0.0, 2.0, 1.0, 0.0, 0.0, 2.0, 1.0};
  const Vec3 x_m{1.0, 2.0, 3.0}; // m

  if (broken) {
    // Opt-in defined, sanitizer-clean, wrong map: A^T x, not A x.
    const Vec3 y_m = apply_map_transposed_layout(a, x_m);
    write_vec_m(y_m);
    return EXIT_SUCCESS;
  }

  const Vec3 y_m = apply_map(a, x_m);
  write_vec_m(y_m);
  if (!y_is_correct_m(y_m)) {
    std::cerr << "correctness check failed: expected [5, 8, 3] m "
              << "(dtype double, abs tol " << k_abs_tol_m << " m)\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
// end small-linear-algebra
