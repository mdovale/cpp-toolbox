# Structure a small CMake app

```{index} CMake
```

```{index} translation unit
```

```{index} add_executable
```

This is chapter 3 of the [contents](../learning-path.md). It depends on
[raii-and-ownership](raii-and-ownership.md). The next spine id is
`floating-point`; that chapter is not yet written.

A laboratory program outgrows one translation unit as soon as a helper
is worth a name. The declaration lives in a header, the definition in
its own `.cpp`, and `main` in a third file
{cite}`cppcoreguidelines-sf`. CMake is the list of those files plus the
compile features they require {cite}`cmake-buildsystem`. The target
`cmake-app` is that list. Omitting a `.cpp` is a link error, so the
program never prints a voltage. In the sense of conditioning, a missing
object file is a perturbation the toolchain refuses to ignore, unlike
the dangling view in chapter 2, which can still produce a plausible
peak.

Chapter 2's `peak_volts` is the helper that moves. The four-sample
record and the manufactured peak in {eq}`peak-volts-app` are unchanged,
so a successful split is a successful experiment: the layout did not
alter the result. Units are volts; dtype is `double`, as in
[notation](../notation.md).

```{math}
:label: peak-volts-app
v_{\max} = \max_{0 \le i < n} v_i = 3.0\,\mathrm{V}.
```

## Two translation units

A translation unit is a source file after preprocessing: `main.cpp`
includes `peak_volts.hpp` and becomes one unit; `peak_volts.cpp`
includes the same header and becomes another. The header is
self-contained (`#pragma once`, `#include <span>`) so that either unit
can see the declaration without depending on a previous include
{cite}`cppcoreguidelines-sf`. The definition has external linkage in
`peak_volts.cpp`; the anonymous namespace in `main.cpp` stays local to
that unit, which is why the manufactured constants and the correctness
check do not leak into the helper.

The copy-out `CMakeLists.txt` names both units. In this repository the
superbuild does not `add_subdirectory` that file:
`toolbox_add_lesson_tree` compiles every `*.cpp` next to `main.cpp`
into the same target, and the `dev` and `sanitize` presets still apply
warnings and sanitizers as in [build-and-ub](build-and-ub.md)
{cite}`cmake-presets`. When you copy the folder out, the leaf
`CMakeLists.txt` is the build.

```{literalinclude} ../../tutorials/03-cmake-app/CMakeLists.txt
:language: cmake
```

## The program

The default path constructs a `std::vector` that owns the four samples,
forms a `std::span` of that vector, and passes the span to
`peak_volts` in the other translation unit. The check is
$|v_{\max}-3.0\,\mathrm{V}|\le 10^{-15}\,\mathrm{V}$ and
`std::isfinite`. There is no opt-in undefined branch: a missing source
fails at link time, before any voltage is written.

```{literalinclude} ../../tutorials/03-cmake-app/peak_volts.hpp
:language: cpp
:start-after: // start cmake-app
:end-before: // end cmake-app
```

```{literalinclude} ../../tutorials/03-cmake-app/peak_volts.cpp
:language: cpp
:start-after: // start cmake-app
:end-before: // end cmake-app
```

```{literalinclude} ../../tutorials/03-cmake-app/main.cpp
:language: cpp
:start-after: // start cmake-app
:end-before: // end cmake-app
```

## When this fails

Compiling only `main.cpp` leaves `peak_volts` undefined. The compiler
accepts the call because the header declared it; the linker then
searches the objects you named, does not find a definition, and stops
{cite}`iso14882-2020-odr`. Reproduce it from this folder:

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  main.cpp -o /tmp/cmake-app
```

A report looks like the excerpt below. The mangled name and the linker
(`ld`, `lld`, `ld64`) differ by platform; the structure does not.

```text
Undefined symbols for architecture ...:
  "peak_volts(std::span<double const, ...>)", referenced from:
      _main in main-....o
ld: symbol(s) not found for architecture ...
clang++: error: linker command failed with exit code 1
```

Read it as a missing translation unit, not as a defect in the voltage
record:

- The undefined symbol is `peak_volts`, the helper declared in the
  header.
- `referenced from: _main` is the call in `main.cpp`.
- The objects named on the command line did not include
  `peak_volts.cpp`.

The same class of error occurs when the copy-out `add_executable` lists
only `main.cpp`. Adding the file to disk is not sufficient; CMake
compiles the sources the target names {cite}`cmake-buildsystem`. The
in-tree glob of `*.cpp` is the catalog's way of keeping that list in
sync with the folder. The leaf `CMakeLists.txt` is the list you
maintain when the folder is no longer next to `toolbox_add_lesson_tree`.

Defining `peak_volts` in the header and compiling both `.cpp` files
produces the complementary link error: two definitions of one function,
which violates the one-definition rule {cite}`iso14882-2020-odr`. Keep
the declaration in the header and the definition in a single `.cpp`.

Without the helper object, the program does not run, so it cannot print
a plausible 3.0 V. That is the intended diagnostic.

## Alternatives

A unity build (`#include "peak_volts.cpp"` from `main.cpp`) restores a
single translation unit, so the linker never has to resolve
`peak_volts` in a second object. Header-only helpers belong where every
caller should see the definition. This chapter's `add_executable` lists
two `.cpp` files because that is the layout a small app grows into.

Cited works are collected in {doc}`/references`.
