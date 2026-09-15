# Time integration with RK4

A one-file C++20 lesson in classical RK4 on a linear voltage decay
dv/dt = -v/tau. Use it after `frames-and-rotations`, when a laboratory
state evolves in time, and whenever a timestep that is large compared
with tau might still print a plausible voltage.

## Build

From the repository root:

```bash
cmake --preset dev
cmake --build --preset dev --target ode-rk4
./build/dev/ode-rk4

cmake --preset sanitize
cmake --build --preset sanitize --target ode-rk4
./build/sanitize/ode-rk4
```

The default run prints `v(3 s)` near `0.0497874 V` and exits 0. Units
are volts and seconds; tau = 1 s; dtype is `double`. Twenty-four RK4
steps of 0.125 s (exact in binary64) check to 1e-6 V against the
manufactured exp(-3) V.

Hand-compile the leaf (warnings as errors, no sanitizers):

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  main.cpp -o /tmp/ode-rk4
```

From the repository root the same line is
`c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror tutorials/08-ode-rk4/main.cpp -o /tmp/ode-rk4`.

## Reproduce the large step

The in-tree binary is defined and sanitizer-clean even with `--broken`.
That flag takes one RK4 step of 3 s and prints `v(3 s) = 1.375 V`
instead of exp(-3) V. AddressSanitizer does not fire: the recurrence
is defined, and the result still looks like a voltage.

```bash
# Expected: v(3 s) = 1.375 V; exit 0. Sanitizers stay quiet.
./build/sanitize/ode-rk4 --broken
```

If you copied only this folder:

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  main.cpp -o /tmp/ode-rk4
/tmp/ode-rk4 --broken
```

Files as laboratory records are the next spine item.

## See also

- `frames-and-rotations`: prior spine item; named frames and rotations.
  This chapter evolves a scalar in time.
- `engineering-io` (planned): next spine item; files are part of the
  experiment.
