# Named frames and rotations

A one-file C++20 lesson in labeling a 3-vector with a frame and mapping
it with a ZYX (yaw-pitch-roll) rotation stored column-major. Use it
after `small-linear-algebra`, when body and lab coordinates share a
type, and whenever a printed position might still be in the wrong
frame.

## Build

From the repository root:

```bash
cmake --preset dev
cmake --build --preset dev --target frames-and-rotations
./build/dev/frames-and-rotations

cmake --preset sanitize
cmake --build --preset sanitize --target frames-and-rotations
./build/sanitize/frames-and-rotations
```

The default run prints `x_lab = [0, 1, 0] m` and exits 0. Units are
meters for the positions; R is dimensionless; Euler angles are yaw =
90 deg, pitch = 0, roll = 0, with exact cos/sin (0 and 1), dtype
`double`. The check is 1e-15 m against the manufactured lab vector.

Hand-compile the leaf (warnings as errors, no sanitizers):

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  main.cpp -o /tmp/frames-and-rotations
```

From the repository root the same line is
`c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror tutorials/07-frames-and-rotations/main.cpp -o /tmp/frames-and-rotations`.

## Reproduce the mixed-frame copy

The in-tree binary is defined and sanitizer-clean even with `--broken`.
That flag writes the body components as `x_lab` without applying R and
prints `x_lab = [1, 0, 0] m`. AddressSanitizer does not fire: the
evaluation is defined, and the coordinates still look like a position.

```bash
# Expected: x_lab = [1, 0, 0] m; exit 0. Sanitizers stay quiet.
./build/sanitize/frames-and-rotations --broken
```

If you copied only this folder:

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  main.cpp -o /tmp/frames-and-rotations
/tmp/frames-and-rotations --broken
```

ZYX Euler is singular at pitch = +/-90 deg; this leaf does not extract
angles. Time integration is the next spine item.

## See also

- `small-linear-algebra`: prior spine item; column-major 3-by-3 maps.
  This chapter names the frames that those maps connect.
- `ode-rk4`: next spine item; time integration with RK4.
