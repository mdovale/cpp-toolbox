# Named frames and rotations

```{index} Euler angles
```

```{index} rotation
```

```{index} reference frame
```

This is chapter 7 of the [contents](../learning-path.md). It depends on
[small-linear-algebra](small-linear-algebra.md). The next spine id is
`ode-rk4`; that chapter is not yet written.

The three components of a laboratory 3-vector are coordinates in a
named frame. A rotation $R$ maps those coordinates from one frame into
another, so that $x_{\mathrm{lab}}$ in {eq}`lab-from-body` is a
different triple from $x_{\mathrm{body}}$ whenever $R$ is not the
identity {cite}`shuster1993`. Copying the body components into a
variable whose name says lab is a small change in an assumption, in
the sense of conditioning: the evaluation remains defined,
`AddressSanitizer` stays quiet, and the printed meters still look like
a position. Frames in this chapter are labels on identifiers
(`x_body_m`, `x_lab_m`, `r_lab_from_body`), as in
[notation](../notation.md), not a C++ type that the compiler can check.

## The program

$R$ is the ZYX (yaw-pitch-roll) product in {eq}`zyx-euler`, stored
column-major as in chapter 6. Yaw $\psi = 90^{\circ}$, pitch
$\theta = 0$, and roll $\phi = 0$ have exact binary64 cosines and
sines $(0,1)$, $(1,0)$, and $(1,0)$, which the program passes directly
rather than as `std::cos` of $\pi/2$, a rounding residual from
[floating-point](floating-point.md). The body vector is
$x_{\mathrm{body}} = (1,0,0)^{\top}\,\mathrm{m}$, dtype `double`, so
{eq}`lab-from-body` manufactures $x_{\mathrm{lab}} =
(0,1,0)^{\top}\,\mathrm{m}$.

```{math}
:label: lab-from-body
x_{\mathrm{lab}} = R x_{\mathrm{body}}.
```

```{math}
:label: zyx-euler
R = R_z(\psi)\,R_y(\theta)\,R_x(\phi).
```

The default path forms $R$, applies it with the chapter 6 product, and
checks each lab component to $10^{-15}\,\mathrm{m}$ together with
`std::isfinite`. Passing `--broken` writes $x_{\mathrm{body}}$ under
the name `x_lab`. That branch is opt-in and defined, so a quiet
`sanitize` run is not evidence that {eq}`lab-from-body` was formed.

```{literalinclude} ../../tutorials/07-frames-and-rotations/main.cpp
:language: cpp
:start-after: // start frames-and-rotations
:end-before: // end frames-and-rotations
```

## When this fails

The mixed-frame copy leaves the components in the body basis and
prints them as lab meters, so a unit vector along body $x$ appears
along lab $x$. Both triples are finite positions; the diagnostic is
that they are not the same list of numbers
{cite}`shuster1993,diebel2006`. Length is preserved either way, so
$\|x\|$ does not catch the mistake.

The ZYX chart is singular at $\theta = \pm 90^{\circ}$: the yaw and
roll axes coincide, and a recovery of $(\psi,\phi)$ from $R$ is
underdetermined {cite}`shuster1993`. A naive `atan2` then prints a
pair of degrees that still looks like an attitude. That failure is a
defined trigonometric evaluation, in the sense of an ill-conditioned
chart on $\mathrm{SO}(3)$, which remains a well-defined map of
matrices. This leaf's `--broken` path is the mixed-frame copy, which
is the defect that shows up when body and lab share `Vec3`.

## Interpreting a quiet sanitizer

Reproduce the mixed-frame copy from a `sanitize` build:

```bash
./build/sanitize/frames-and-rotations --broken
```

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  tutorials/07-frames-and-rotations/main.cpp -o /tmp/frames-and-rotations
/tmp/frames-and-rotations --broken
```

The process exits 0. There is no `heap-buffer-overflow` and no
`heap-use-after-free`, because the failure is not a bounds or lifetime
error. The diagnostic is the printed `[1, 0, 0] m` beside the
manufactured `[0, 1, 0] m` of {eq}`lab-from-body`.

## Alternatives

A quaternion or a rotation vector charts $\mathrm{SO}(3)$ without the
ZYX singularity {cite}`shuster1993,diebel2006`. They still require a
named product into the destination frame; a quaternion copied into
`x_lab` is the same mixed-frame habit. Compile-time frame tags (a
`Vec3` parameterized by a frame type) catch some swaps that comments
miss; this leaf keeps the labels in the identifier. Eigen's
`AngleAxis` and `Quaternion` belong when the rotation is no longer
nine entries and two labels.

The next spine item, `ode-rk4`, integrates a toy ODE in time. This
chapter is the named $R$ that a later attitude or mechanics model will
apply at a sample.

Cited works are collected in {doc}`/references`.
