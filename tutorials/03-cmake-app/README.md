# Structure a small CMake app

A multi-file C++20 lesson in listing translation units: a header, a
`.cpp` for `peak_volts`, `main.cpp`, and a copy-out `CMakeLists.txt`.
Use it after `raii-and-ownership`, when a helper is worth its own file,
and whenever you copy a catalog folder out of the superbuild.

## Build

From the repository root:

```bash
cmake --preset dev
cmake --build --preset dev --target cmake-app
./build/dev/cmake-app

cmake --preset sanitize
cmake --build --preset sanitize --target cmake-app
./build/sanitize/cmake-app
```

The default run prints `peak = 3 V` and exits 0. Units are volts; dtype
is `double`. The samples `{2.0, 2.5, 3.0, 2.5}` V have an exactly
representable maximum of 3.0 V, which the program checks to 1e-15 V.

Hand-compile every translation unit (warnings as errors, no sanitizers):

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  main.cpp peak_volts.cpp -o /tmp/cmake-app
```

From the repository root the same line is
`c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror tutorials/03-cmake-app/main.cpp tutorials/03-cmake-app/peak_volts.cpp -o /tmp/cmake-app`.

Copy-out CMake, from this folder:

```bash
cmake -S . -B /tmp/cmake-app-build
cmake --build /tmp/cmake-app-build
/tmp/cmake-app-build/cmake-app
```

## Reproduce the link error

Compiling only `main.cpp` fails at link time: `peak_volts` is declared
in the header and defined in `peak_volts.cpp`. Default `main` is
sanitizer-clean; there is no `--broken` runtime path.

```bash
# Expected: undefined reference to peak_volts; non-zero exit.
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  main.cpp -o /tmp/cmake-app
```

## See also

- `raii-and-ownership`: prior spine item; the helper this folder splits
  out, and who owns the buffer the span names.
- `floating-point` (planned): next spine item; rounding and
  cancellation.
