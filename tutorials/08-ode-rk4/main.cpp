#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string_view>

// start ode-rk4
namespace {

// Linear decay: dv/dt = -v/tau. tau is seconds; v is volts (dtype double).
constexpr double k_tau_s = 1.0;   // s
constexpr double k_v0_v = 1.0;    // V
constexpr double k_t_end_s = 3.0; // s
constexpr double k_dt_s = 0.125;  // s; 1/8, exact in binary64
constexpr std::size_t k_n_steps = 24;
constexpr double k_dt_broken_s = 3.0; // s; one step equal to t_end
constexpr double k_abs_tol_v = 1e-6;  // V; RK4 global error at dt=0.125 s

// Invariant: f(v,t) = -v/tau. Return value is V/s. Autonomous: t unused.
double f_decay_vps(const double v_v, [[maybe_unused]] const double t_s) {
  return -v_v / k_tau_s;
}

// Classical RK4, one step. k_i have units V/s; dt_s * k_i is volts.
double rk4_step_v(const double v_v, const double t_s, const double dt_s) {
  const double k1_vps = f_decay_vps(v_v, t_s);
  const double k2_vps =
      f_decay_vps(v_v + 0.5 * dt_s * k1_vps, t_s + 0.5 * dt_s);
  const double k3_vps =
      f_decay_vps(v_v + 0.5 * dt_s * k2_vps, t_s + 0.5 * dt_s);
  const double k4_vps = f_decay_vps(v_v + dt_s * k3_vps, t_s + dt_s);
  return v_v + (dt_s / 6.0) * (k1_vps + 2.0 * k2_vps + 2.0 * k3_vps + k4_vps);
}

bool v_is_correct_v(const double v_v, const double v_expected_v) {
  return std::isfinite(v_v) && std::abs(v_v - v_expected_v) <= k_abs_tol_v;
}

} // namespace

int main(int argc, char* argv[]) {
  const bool broken = argc == 2 && std::string_view{argv[1]} == "--broken";
  if (argc > 1 && !broken) {
    std::cerr << "usage: ode-rk4 [--broken]\n";
    return EXIT_FAILURE;
  }

  const double v_expected_v = k_v0_v * std::exp(-k_t_end_s / k_tau_s); // V

  if (broken) {
    // Opt-in large step: RK4 remains a defined map. dt = 3 s is 3 tau, so
    // the stability polynomial grows; the printed voltage is not e^{-3}.
    const double v_v = rk4_step_v(k_v0_v, 0.0, k_dt_broken_s);
    std::cout << "v(" << k_t_end_s << " s) = " << v_v << " V\n";
    return EXIT_SUCCESS;
  }

  double v_v = k_v0_v; // V
  double t_s = 0.0;    // s
  for (std::size_t i = 0; i < k_n_steps; ++i) {
    v_v = rk4_step_v(v_v, t_s, k_dt_s);
    t_s += k_dt_s;
  }
  std::cout << "v(" << k_t_end_s << " s) = " << v_v << " V\n";
  if (!v_is_correct_v(v_v, v_expected_v)) {
    std::cerr << "correctness check failed: expected " << v_expected_v
              << " V (dtype double, abs tol " << k_abs_tol_v << " V)\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
// end ode-rk4
