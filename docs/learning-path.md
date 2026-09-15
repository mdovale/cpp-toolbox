# Learning path

Fill **this spine** before a large set of disconnected examples. How-tos, examples, and projects should link back here. These eleven tutorial rows are already `status: planned` in `catalog.yaml` at the repository root; adding a tutorial means filling that row as a vertical slice, not inventing a parallel sequence.

Assume calculus, linear algebra, and some numerical methods. Do not assume CS coursework. Ownership, undefined behavior, and lifetime are taught the way we explain stiffness and conditioning: they make answers silently wrong.

| # | Planned `id` | Title | Topic | Why it is on the spine |
|---|---|---|---|---|
| 01 | `build-and-ub` | Build, sanitizers, and what UB looks like | `build` | The rest of the book is unsafe without this. |
| 02 | `raii-and-ownership` | RAII, ownership, and views (`span`) | `language` | Resource and lifetime model for lab code. |
| 03 | `cmake-app` | Structure a small CMake app | `build` | Multi-file layout from the start; the build system is a lesson, not magic. |
| 04 | `floating-point` | Floating point and numerical honesty | `numerics` | Rounding, cancellation, and when results lie. |
| 05 | `error-handling` | Errors in laboratory C++ | `language` | Failure is normal in scientific programs. |
| 06 | `small-linear-algebra` | Small vectors and matrices | `linear-algebra` | 3-vectors and 3×3 maps without a library; later rotations depend on this. |
| 07 | `frames-and-rotations` | Named frames and rotations | `linear-algebra` | Mixed frames and Euler singularities make answers silently wrong. |
| 08 | `ode-rk4` | Time integration with RK4 | `numerics` | `ẋ = f(x, t)`, timestep, and a correctness check on a toy ODE. |
| 09 | `engineering-io` | I/O for engineering data | `io` | Files are part of the experiment. |
| 10 | `testing-numerics` | How to test numerical code | `testing` | Residuals, tolerances, and property checks. |
| 11 | `ranges-for-data` | Containers, algorithms, and ranges for scientific data | `language` | Data layout after there is something to store. |

Planned **how-tos** (not spine): `parallel-stl` and `read-a-profile`. Speed and measurement come after a working serial program.

When you add tutorial *N*, use folder `tutorials/NN-<id>/`, set `kind: tutorial`, and mark `status: complete` only as a vertical slice (`CONTRIBUTING.md` at the repository root).
