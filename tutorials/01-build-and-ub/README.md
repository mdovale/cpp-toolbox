# Build, sanitizers, and what UB looks like

A one-file C++20 lesson in configuring this repository and in running
AddressSanitizer on a 1-based mean that reads past a four-sample voltage
record. Use it when you first clone cpp-toolbox, before any later
tutorial, and whenever a result looks reasonable but you have not yet
run the `sanitize` preset.

## Build

Warnings-as-errors (`dev`) and ASan/UBSan (`sanitize`) are part of the
experiment. From the repository root:

```bash
cmake --preset dev
cmake --build --preset dev --target build-and-ub
./build/dev/build-and-ub

cmake --preset sanitize
cmake --build --preset sanitize --target build-and-ub
./build/sanitize/build-and-ub
```

The default run prints `mean = 2.5 V` and exits 0. Units are volts;
dtype is `double`. The samples `{2.0, 2.5, 3.0, 2.5}` V have an exactly
representable mean of 2.5 V, which the program checks to 1e-15 V.

Hand-compile the leaf (warnings as errors, no sanitizers):

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  main.cpp -o /tmp/build-and-ub
```

From the repository root the same line is
`c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror tutorials/01-build-and-ub/main.cpp -o /tmp/build-and-ub`.

`dev` is for day-to-day iteration: `-Wall -Wextra -Wpedantic -Werror`
and `compile_commands.json`. `sanitize` inherits that and adds
`-fsanitize=address,undefined`. Neither preset executes the broken path
below.

## Reproduce the sanitizer finding

The in-tree binary is sanitizer-clean unless you pass `--broken`. That
flag runs a 1-based mean that reads one past the last sample (undefined
behavior). Default `main` never takes that branch.

```bash
# Expected: AddressSanitizer reports heap-buffer-overflow; non-zero exit.
./build/sanitize/build-and-ub --broken
```

If you copied only this folder:

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  main.cpp -o /tmp/build-and-ub
/tmp/build-and-ub --broken
```

Without sanitizers, `--broken` may print a number that looks like a
voltage, print a wild value, or crash. A quiet run is not evidence that
the mean is correct.

## See also

- `raii-and-ownership`: next spine item; lifetime and views.
- `cmake-app` (planned): next build lesson; more than one source file.
