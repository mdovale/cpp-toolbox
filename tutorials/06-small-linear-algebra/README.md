# Small vectors and matrices

A one-file C++20 lesson in 3-vectors and 3-by-3 maps as
`std::array<double, 3>` and a column-major `std::array<double, 9>`,
without a linear-algebra library. Use it after `error-handling`, when a
laboratory quantity is a 3-vector, and whenever a matrix-vector product
might be applying the transpose because the row and column strides were
swapped.

## Build

From the repository root:

```bash
cmake --preset dev
cmake --build --preset dev --target small-linear-algebra
./build/dev/small-linear-algebra

cmake --preset sanitize
cmake --build --preset sanitize --target small-linear-algebra
./build/sanitize/small-linear-algebra
```

The default run prints `y = [5, 8, 3] m` and exits 0. Units are meters
for x and y; A is dimensionless; dtype is `double`. The check is
1e-15 m against the manufactured A x.

Hand-compile the leaf (warnings as errors, no sanitizers):

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  main.cpp -o /tmp/small-linear-algebra
```

From the repository root the same line is
`c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror tutorials/06-small-linear-algebra/main.cpp -o /tmp/small-linear-algebra`.

## Reproduce the transposed layout

The in-tree binary is defined and sanitizer-clean even with `--broken`.
That flag forms A^T x by reading a_ji from the same column-major buffer,
and prints `y = [1, 4, 7] m`. AddressSanitizer does not fire: the
evaluation is defined, and the coordinates still look like a position.

```bash
# Expected: y = [1, 4, 7] m; exit 0. Sanitizers stay quiet.
./build/sanitize/small-linear-algebra --broken
```

If you copied only this folder:

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  main.cpp -o /tmp/small-linear-algebra
/tmp/small-linear-algebra --broken
```

Named frames and rotations are the next spine item.

## See also

- `error-handling`: prior spine item; a detected failure can still be
  swallowed. This chapter is a defined product with the wrong layout.
- `frames-and-rotations`: next spine item; named frames and Euler
  singularities.
