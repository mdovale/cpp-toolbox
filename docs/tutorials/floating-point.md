# Floating point and numerical honesty

```{index} floating-point
```

```{index} cancellation
```

```{index} rounding
```

This is chapter 4 of the [contents](../learning-path.md). It depends on
[cmake-app](cmake-app.md). The next spine chapter is
[error-handling](error-handling.md).

IEEE-754 binary64 (`double`) is a finite set of numbers with a 53-bit
significand {cite}`ieee754-2019`. Rounding maps a real voltage or a real
angle onto that set, so most decimal constants in the source are already
perturbed on entry {cite}`goldberg1991`. Subtracting two close rounded
values then cancels the bits they share, which leaves rounding noise in
the difference {cite}`higham2002`. In the sense of conditioning, a one-ulp
change in $\cos x$ is amplified by $1/x^2$ when $x$ is small, so a
defined evaluation can print a plausible 0 while the manufactured value
is $1/2$. AddressSanitizer stays quiet because nothing is undefined.

Chapters 1, 2, and 3 used voltages that are exact in binary64 (2.0, 2.5,
3.0) on purpose. This chapter uses decimals and a trigonometric identity
that are not.

## The program

The decimal 0.1 V is not an element of binary64. Adding the binary64
values of 0.1 V and 0.2 V therefore does not yield the binary64 value of
the decimal 0.3 V. The six-digit stream still prints `0.3 V`; the
residual against that decimal is about $5.55\times 10^{-17}\,\mathrm{V}$,
which the program checks to $10^{-15}\,\mathrm{V}$. A laboratory check
tests a tolerance; `==` tests bit patterns.

The second quantity is {eq}`one-minus-cos`. For $x$ in radians, dtype
`double`, the limit is the manufactured $1/2$.

```{math}
:label: one-minus-cos
\lim_{x \to 0}\frac{1-\cos x}{x^2} = \frac{1}{2}.
```

The default path evaluates the algebraically equivalent form
{eq}`half-sinc-sq`, which does not subtract two values near 1, and
checks $|f-1/2|\le 10^{-12}$. Passing `--broken` evaluates
$(1-\cos x)/x^2$ at $x=10^{-8}\,\mathrm{rad}$. That branch
is defined and sanitizer-clean, so a quiet `sanitize` run is not
evidence that $f=1/2$.

```{math}
:label: half-sinc-sq
\frac{1-\cos x}{x^2}
  = \frac{1}{2}\left(\frac{\sin(x/2)}{x/2}\right)^2.
```

```{literalinclude} ../../tutorials/04-floating-point/main.cpp
:language: cpp
:start-after: // start floating-point
:end-before: // end floating-point
```

## When this fails

At $x=10^{-8}\,\mathrm{rad}$, $\cos x$ and $1$ agree to more digits than
binary64 stores, so $1-\cos x$ rounds to 0 and the naive quotient is 0.
The evaluation is a finite sequence of floating-point operations with a
defined result {cite}`ieee754-2019`. That 0 is not the limit in
{eq}`one-minus-cos`. The stable form computes $\sin(x/2)/(x/2)$, whose
argument is not cancelled, and recovers $1/2$ to the stated tolerance
{cite}`higham2002`.

The same class of defect appears when two close laboratory readings are
subtracted to form a small offset: the leading digits of the readings
cancel, and the offset is rounding noise. Keep the difference in a
formula that does not discard those digits, or keep the offset as its
own measurement.

`float` (binary32, 24-bit significand) produces the same cancellation
at a larger $x$. This book uses `double` unless the lesson is the dtype,
as in [notation](../notation.md).

## Interpreting a quiet sanitizer

Reproduce the naive evaluation from a `sanitize` build:

```bash
./build/sanitize/floating-point --broken
```

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  tutorials/04-floating-point/main.cpp -o /tmp/floating-point
/tmp/floating-point --broken
```

The process exits 0. There is no `heap-use-after-free` and no
`heap-buffer-overflow`, because the failure is not a lifetime or bounds
error. The diagnostic is the printed `0` beside a manufactured $1/2$,
together with the rounding residual that the six-digit voltage line
conceals.

## Alternatives

A correctly rounded library routine for a particular expression, or a
compensated summation, can reduce that expression's error. Laboratory
scalars in this book stay in binary64 with a stated tolerance. The next
spine chapter, [error-handling](error-handling.md), is about failures
the program can report. This chapter is about results the program
reports with full confidence and the wrong value.

Cited works are collected in {doc}`/references`.
