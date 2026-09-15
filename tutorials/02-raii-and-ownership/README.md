# RAII, ownership, and views

A one-file C++20 lesson in who owns a voltage buffer (`std::vector`) and
who only observes it (`std::span`). Use it after `build-and-ub`, when
you pass records into helpers without copying, and whenever a view might
outlive the owner or survive a reallocation.

## Build

From the repository root:

```bash
cmake --preset dev
cmake --build --preset dev --target raii-and-ownership
./build/dev/raii-and-ownership

cmake --preset sanitize
cmake --build --preset sanitize --target raii-and-ownership
./build/sanitize/raii-and-ownership
```

The default run prints `peak = 3 V` and exits 0. Units are volts; dtype
is `double`. The samples `{2.0, 2.5, 3.0, 2.5}` V have an exactly
representable maximum of 3.0 V, which the program checks to 1e-15 V.

Hand-compile the leaf (warnings as errors, no sanitizers):

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  main.cpp -o /tmp/raii-and-ownership
```

From the repository root the same line is
`c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror tutorials/02-raii-and-ownership/main.cpp -o /tmp/raii-and-ownership`.

## Reproduce the sanitizer finding

The in-tree binary is sanitizer-clean unless you pass `--broken`. That
flag binds a `std::span` to a `std::vector` and then lets the vector's
destructor run before the span is read (use-after-free). Default `main`
never takes that branch.

```bash
# Expected: AddressSanitizer reports heap-use-after-free; non-zero exit.
./build/sanitize/raii-and-ownership --broken
```

If you copied only this folder:

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  main.cpp -o /tmp/raii-and-ownership
/tmp/raii-and-ownership --broken
```

Without sanitizers, `--broken` may print a number that looks like a
peak, print a wild value, or crash. A quiet run is not evidence that the
peak is correct. `push_back` or `resize` past `capacity()` is the same
class of bug while the vector object is still in scope.

## See also

- `build-and-ub`: prior spine item; sanitizers and a defined default
  `main`.
- `cmake-app`: next spine item; more than one source file.
