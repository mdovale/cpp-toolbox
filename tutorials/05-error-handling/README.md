# Errors in laboratory C++

A one-file C++20 lesson in reporting a failed experiment in the control
flow (`std::invalid_argument`) instead of printing a warning and still
returning a voltage. Use it after `floating-point`, when a helper cannot
form its result (empty record, violated precondition), and whenever a
`catch` might hide that failure.

## Build

From the repository root:

```bash
cmake --preset dev
cmake --build --preset dev --target error-handling
./build/dev/error-handling

cmake --preset sanitize
cmake --build --preset sanitize --target error-handling
./build/sanitize/error-handling
```

The default run prints `mean = 2.5 V` and exits 0. Units are volts;
dtype is `double`. The samples `{2.0, 2.5, 3.0, 2.5}` V have an exactly
representable mean of 2.5 V, which the program checks to 1e-15 V.
`mean_volts` throws `std::invalid_argument` on an empty record; the
default path never takes that branch.

Hand-compile the leaf (warnings as errors, no sanitizers):

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  main.cpp -o /tmp/error-handling
```

From the repository root the same line is
`c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror tutorials/05-error-handling/main.cpp -o /tmp/error-handling`.

## Reproduce the swallowed error

The in-tree binary is defined and sanitizer-clean even with `--broken`.
That flag passes an empty record into `mean_volts`, catches
`std::invalid_argument`, and prints `mean = 3 V` (a dummy equal to the
peak of the four-sample record). AddressSanitizer does not fire: the
evaluation is defined, and a plausible voltage is still written.

```bash
# Expected: mean = 3 V; exit 0. Sanitizers stay quiet.
./build/sanitize/error-handling --broken
```

If you copied only this folder:

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  main.cpp -o /tmp/error-handling
/tmp/error-handling --broken
```

C++23 `std::expected` is the type-level alternative; this leaf stays on
C++20 and names it in the chapter.

## See also

- `floating-point`: prior spine item; a defined evaluation can still
  print the wrong number. This chapter is a detected error that is then
  swallowed.
- `small-linear-algebra`: next spine item; 3-vectors and 3-by-3 maps.
