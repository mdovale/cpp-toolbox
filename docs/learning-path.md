# Contents

The table is the order of the book. Chapter numbers are the reading
order. Catalog `id`s are the machine names in `catalog.yaml`, in CMake
target names, and in folder slugs (`tutorials/NN-<id>/`). Fill this
spine as vertical slices before a large set of disconnected examples.

Chapters 1 through 5 (`build-and-ub`, `raii-and-ownership`,
`cmake-app`, `floating-point`, `error-handling`) are written. Later
chapters remain planned until they exist as the same kind of slice,
including `prose: complete`.

The audience is the working engineer or scientist. Ownership, undefined
behavior, and lifetime are taught in the sense of conditioning: they
make answers silently wrong.

| Ch. | Catalog `id` | Title | Topic | Role in the book |
|---|---|---|---|---|
| 1 | `build-and-ub` | Build, sanitizers, and what UB looks like | `build` | The rest of the book is unsafe without this. |
| 2 | `raii-and-ownership` | RAII, ownership, and views (`span`) | `language` | Resource and lifetime model for lab code. |
| 3 | `cmake-app` | Structure a small CMake app | `build` | Multi-file layout from the start; the build system is a lesson. |
| 4 | `floating-point` | Floating point and numerical honesty | `numerics` | Rounding, cancellation, and when results lie. |
| 5 | `error-handling` | Errors in laboratory C++ | `language` | Failure is normal in scientific programs. |
| 6 | `small-linear-algebra` | Small vectors and matrices | `linear-algebra` | 3-vectors and $3\times 3$ maps without a library; later rotations depend on this. |
| 7 | `frames-and-rotations` | Named frames and rotations | `linear-algebra` | Mixed frames and Euler singularities make answers silently wrong. |
| 8 | `ode-rk4` | Time integration with RK4 | `numerics` | $\dot{x} = f(x, t)$, timestep, and a correctness check on a toy ODE. |
| 9 | `engineering-io` | I/O for engineering data | `io` | Files are part of the experiment. |
| 10 | `testing-numerics` | How to test numerical code | `testing` | Residuals, tolerances, and property checks. |
| 11 | `ranges-for-data` | Containers, algorithms, and ranges for scientific data | `language` | Data layout after there is something to store. |

Planned how-tos (around the spine, not numbered with it): `parallel-stl`
and `read-a-profile`. Speed and measurement come after a working serial
program.

When you add chapter $N$, use folder `tutorials/NN-<id>/`, set
`kind: tutorial`, and mark `status: complete` and `prose: complete` only
as a vertical slice (`CONTRIBUTING.md` at the repository root).
