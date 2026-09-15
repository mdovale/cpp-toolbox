#pragma once

#include <cmath>

namespace toolbox {

/// Returns true iff @p x is a finite IEEE-754 value (not inf, not NaN).
///
/// Use before a reduction or a residual check when a non-finite input would
/// make the rest of the algorithm meaningless rather than "slightly wrong".
[[nodiscard]] inline bool is_finite(double x) noexcept {
  return std::isfinite(x);
}

}  // namespace toolbox
