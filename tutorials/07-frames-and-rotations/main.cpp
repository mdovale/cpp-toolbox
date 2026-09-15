#include <array>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string_view>

// start frames-and-rotations
namespace {

// 3-vector and 3x3 map, dtype double. Positions are meters; R is
// dimensionless. Column-major: a_ij at i + 3*j, as in chapter 6.
using Vec3 = std::array<double, 3>;
using Mat3 = std::array<double, 9>;

constexpr std::size_t k_n = 3;
constexpr double k_abs_tol_m = 1e-15;           // m
constexpr Vec3 k_expected_lab_m{0.0, 1.0, 0.0}; // m; R * e_1 after 90 deg yaw

// Invariant: r is column-major. Return value is r * x_m in the same unit
// as x_m (meters). Frames are labels on the callers' names, not a type.
Vec3 apply_map(const Mat3& r, const Vec3& x_m) {
  Vec3 y_m{};
  for (std::size_t i = 0; i < k_n; ++i) {
    double sum_m = 0.0;
    for (std::size_t j = 0; j < k_n; ++j) {
      sum_m += r[i + k_n * j] * x_m[j];
    }
    y_m[i] = sum_m;
  }
  return y_m;
}

// Invariant: ZYX yaw-pitch-roll, R = Rz(yaw) Ry(pitch) Rx(roll). Arguments
// are cos and sin of those angles (dimensionless), not the angles in
// radians, so 90 deg yaw can be the exact pair (0, 1) rather than
// std::cos(pi/2). Stored column-major.
Mat3 rotation_zyx(const double c_yaw, const double s_yaw, const double c_pitch,
                  const double s_pitch, const double c_roll,
                  const double s_roll) {
  const double r00 = c_pitch * c_yaw;
  const double r01 = s_roll * s_pitch * c_yaw - c_roll * s_yaw;
  const double r02 = c_roll * s_pitch * c_yaw + s_roll * s_yaw;
  const double r10 = c_pitch * s_yaw;
  const double r11 = s_roll * s_pitch * s_yaw + c_roll * c_yaw;
  const double r12 = c_roll * s_pitch * s_yaw - s_roll * c_yaw;
  const double r20 = -s_pitch;
  const double r21 = s_roll * c_pitch;
  const double r22 = c_roll * c_pitch;
  return Mat3{r00, r10, r20, r01, r11, r21, r02, r12, r22};
}

bool lab_is_correct_m(const Vec3& x_lab_m) {
  for (std::size_t i = 0; i < k_n; ++i) {
    if (!std::isfinite(x_lab_m[i]) ||
        std::abs(x_lab_m[i] - k_expected_lab_m[i]) > k_abs_tol_m) {
      return false;
    }
  }
  return true;
}

void write_lab_m(const Vec3& x_lab_m) {
  std::cout << "x_lab = [" << x_lab_m[0] << ", " << x_lab_m[1] << ", "
            << x_lab_m[2] << "] m\n";
}

} // namespace

int main(int argc, char* argv[]) {
  const bool broken = argc == 2 && std::string_view{argv[1]} == "--broken";
  if (argc > 1 && !broken) {
    std::cerr << "usage: frames-and-rotations [--broken]\n";
    return EXIT_FAILURE;
  }

  // Body x-axis, 1 m. Labels: x_body_m vs x_lab_m; R maps body to lab.
  const Vec3 x_body_m{1.0, 0.0, 0.0}; // m

  if (broken) {
    // Opt-in mixed frames: body components written as lab. Defined;
    // sanitizers stay quiet; the vector still looks like a position.
    write_lab_m(x_body_m);
    return EXIT_SUCCESS;
  }

  // Exact cos/sin of ZYX (yaw, pitch, roll) = (90 deg, 0, 0).
  const Mat3 r_lab_from_body = rotation_zyx(0.0, 1.0, 1.0, 0.0, 1.0, 0.0);
  const Vec3 x_lab_m = apply_map(r_lab_from_body, x_body_m);
  write_lab_m(x_lab_m);
  if (!lab_is_correct_m(x_lab_m)) {
    std::cerr << "correctness check failed: expected [0, 1, 0] m "
              << "(dtype double, abs tol " << k_abs_tol_m << " m)\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
// end frames-and-rotations
