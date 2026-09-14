# Learning path

Fill **this spine** before a large set of disconnected examples. How-tos, examples, and projects should link back here. These ten rows are already `status: planned` in [`catalog.yaml`](../catalog.yaml); adding a tutorial means filling that row as a vertical slice, not inventing a parallel sequence.

Assume calculus, linear algebra, and some numerical methods. Do not assume CS coursework. Ownership, undefined behavior, and lifetime are taught the way we explain stiffness and conditioning: they make answers silently wrong.

| # | Planned `id` | Title | Topic | Why it is on the spine |
|---|---|---|---|---|
| 01 | `build-and-ub` | Build, sanitizers, and what UB looks like | `build` | The rest of the book is unsafe without this. |
| 02 | `raii-and-ownership` | RAII, ownership, and views (`span`) | `language` | Resource and lifetime model for lab code. |
| 03 | `error-handling` | Errors: exceptions, `expected`, and what labs actually do | `language` | Failure is normal in scientific programs. |
| 04 | `floating-point` | Floating point and numerical honesty | `numerics` | Rounding, cancellation, and when results lie. |
| 05 | `ranges-for-data` | Containers, algorithms, and ranges for scientific data | `language` | Data layout before clever numerics. |
| 06 | `parallel-stl` | Parallel STL and practical threading | `parallelism` | Speed without a framework. |
| 07 | `engineering-io` | I/O for engineering data | `io` | Files are part of the experiment. |
| 08 | `testing-numerics` | How to test numerical code | `testing` | Residuals, tolerances, and property checks. |
| 09 | `cmake-app` | Structure a small CMake app | `build` | The build system is a lesson, not magic. |
| 10 | `read-a-profile` | How to read a profiler output | `performance` | Measure before rewriting the kernel. |

When you add tutorial *N*, use folder `tutorials/NN-<id>/`, set `kind: tutorial`, and mark `status: complete` only as a vertical slice ([CONTRIBUTING.md](../CONTRIBUTING.md)).
