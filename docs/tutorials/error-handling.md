# Errors in laboratory C++

```{index} exceptions
```

```{index} error handling
```

```{index} std::expected
```

This is chapter 5 of the [contents](../learning-path.md). It depends on
[floating-point](floating-point.md). The next spine chapter is
[small-linear-algebra](small-linear-algebra.md).

A helper that cannot form its assigned result has still produced a
result: the failure itself. Domain errors, empty records, and violated
preconditions occur in laboratory programs because an acquisition can
return no samples and a caller can pass a buffer that does not meet the
helper's contract {cite}`iso14882-2020-except,cppcoreguidelines-e`.
Reporting that failure in the control flow, by throwing
`std::invalid_argument`, makes the failed experiment visible, whereas
catching the exception and writing a voltage anyway is a small change
in an assumption, in the sense of conditioning: the evaluation remains
defined, `AddressSanitizer` stays quiet, and a plausible number is
still printed.

Chapters 1 and 2 taught undefined evaluation and dangling views, for
which the sanitizers fire. Chapter 4 taught a defined evaluation that
prints the wrong number, for which they stay quiet. This chapter is
the third kind of silent wrongness: the program detects the error and
then swallows it.

## The program

Four DC voltages in volts, dtype `double`, form a manufactured record
whose arithmetic mean is the scalar in {eq}`mean-n-ge-1` when the
length satisfies $n \ge 1$. The values 2.0, 2.5, 3.0, and 2.5 V are
exactly representable in IEEE-754 binary64, so the mean 2.5 V is exact,
as in [notation](../notation.md). `mean_volts` throws
`std::invalid_argument` when the record is empty, because the
right-hand side of {eq}`mean-n-ge-1` is then not a real number.

```{math}
:label: mean-n-ge-1
\bar{v} = \frac{1}{n}\sum_{i=0}^{n-1} v_i = 2.5\,\mathrm{V}, \qquad n \ge 1.
```

The default path constructs a `std::vector` of those four samples,
forms a `std::span` of that vector, and passes the span to
`mean_volts`. The check is
$|\bar{v}-2.5\,\mathrm{V}|\le 10^{-15}\,\mathrm{V}$ and
`std::isfinite`. Passing `--broken` constructs an empty record, catches
the exception, and writes $3.0\,\mathrm{V}$, which is the peak of the
four-sample record rather than a mean of $n=0$. That branch is opt-in
and defined, so a quiet `sanitize` run is not evidence that
{eq}`mean-n-ge-1` was formed.

```{literalinclude} ../../tutorials/05-error-handling/main.cpp
:language: cpp
:start-after: // start error-handling
:end-before: // end error-handling
```

## When this fails

The empty record is a failed experiment that `mean_volts` already
reported, so the `catch` clause that discards the
`std::invalid_argument` object and leaves a dummy of $3.0\,\mathrm{V}$
is a change of assumption rather than a recovery: the stream still
receives a number that looks like a calibration, and the process exits
0 {cite}`cppcoreguidelines-e`. The evaluation is a throw, a catch, and
an assignment of a finite `double` {cite}`iso14882-2020-except`.

The same class of defect occurs when a check for `empty()` returns a
sentinel without failing the run, or when a `catch` of
`std::exception` logs a line and continues, because the diagnostic was
available and the caller declined to fail the experiment.

## Interpreting a quiet sanitizer

Reproduce the swallow from a `sanitize` build:

```bash
./build/sanitize/error-handling --broken
```

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  tutorials/05-error-handling/main.cpp -o /tmp/error-handling
/tmp/error-handling --broken
```

The process exits 0. There is no `heap-buffer-overflow` and no
`heap-use-after-free`, because the failure is not a bounds or lifetime
error. The diagnostic is the printed `3` V beside a helper that
refused to form {eq}`mean-n-ge-1`.

## Alternatives

Leaving the exception uncaught terminates the process, so no voltage
is written as a successful measurement. Catching it in `main` and
returning `EXIT_FAILURE` without printing a mean is the same honesty
with a chance to log; RAII already runs destructors during stack
unwinding {cite}`stroustrup2013`.

C++23 puts the failure in the return type as
`std::expected<double, std::error_code>` {cite}`p0323r12,iso14882-2024`.
The caller inspects the object before using a voltage.
`value_or(3.0)` is the type-level analogue of the `catch` above: a
named swallow that still prints a plausible $3.0\,\mathrm{V}$. Error
codes and out-parameters are easy to ignore for the same reason the
dummy is easy to keep.

The next spine chapter, [small-linear-algebra](small-linear-algebra.md),
is about 3-vectors. This chapter is about failures the program can
report and then hide.

Cited works are collected in {doc}`/references`.
