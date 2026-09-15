# Floating point and numerical honesty

A one-file C++20 lesson in IEEE-754 binary64 rounding and in
cancellation of (1-cos x)/x^2 for a small angle. Use it after
`cmake-app`, when a printed voltage looks exact, and whenever two close
values are subtracted.

## Build

From the repository root:

```bash
cmake --preset dev
cmake --build --preset dev --target floating-point
./build/dev/floating-point

cmake --preset sanitize
cmake --build --preset sanitize --target floating-point
./build/sanitize/floating-point
```

The default run prints a 0.3 V sum (stream rounding), a residual of
about 5.55e-17 V versus the decimal 0.3 V, and `f stable = 0.5`, then
exits 0. Dtype is `double`. The rounding check is 1e-15 V; the
cancellation check is 1e-12 against the manufactured limit 1/2.

Hand-compile the leaf (warnings as errors, no sanitizers):

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  main.cpp -o /tmp/floating-point
```

From the repository root the same line is
`c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror tutorials/04-floating-point/main.cpp -o /tmp/floating-point`.

## Reproduce the cancellation

The in-tree binary is defined and sanitizer-clean even with `--broken`.
That flag evaluates (1-cos x)/x^2 at x = 1e-8 rad and prints `0`
instead of `0.5`. AddressSanitizer does not fire: the evaluation is
defined, and the result is still wrong.

```bash
# Expected: f naive ... = 0; exit 0. Sanitizers stay quiet.
./build/sanitize/floating-point --broken
```

If you copied only this folder:

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  main.cpp -o /tmp/floating-point
/tmp/floating-point --broken
```

## See also

- `cmake-app`: prior spine item; multi-file layout. This leaf is one
  translation unit again.
- `error-handling` (planned): next spine item; failure is normal in
  laboratory programs.
