# Build, sanitizers, and what UB looks like

```{index} undefined behavior
```

```{index} AddressSanitizer
```

```{index} UndefinedBehaviorSanitizer
```

This is chapter 1 of the [contents](../learning-path.md). It assumes no
prior catalog entry. The next spine chapter is
[raii-and-ownership](raii-and-ownership.md). `cmake-app` remains planned.

Undefined behavior withdraws the language's guarantee that the
executable remains a semantics for the program text
{cite}`iso14882-2020`. Once an evaluation is undefined, the
International Standard imposes no requirement on the observable
behavior of the execution, so a finite voltage may still be written to
the output stream. The rest of the book is compiled under
warnings-as-errors and under `AddressSanitizer` together with
`UndefinedBehaviorSanitizer` {cite}`serebryany2012,llvm-ubsan`, which
is why this chapter comes first: later numerical claims are only as
trustworthy as the build that produced them.

## Two presets

The `dev` and `sanitize` configure presets {cite}`cmake-presets` are
the two instruments used throughout. From the repository root:

```bash
cmake --preset dev
cmake --build --preset dev --target build-and-ub
./build/dev/build-and-ub

cmake --preset sanitize
cmake --build --preset sanitize --target build-and-ub
./build/sanitize/build-and-ub
```

| Preset | Role |
|---|---|
| `dev` | Debug build, warnings as errors, `compile_commands.json`. |
| `sanitize` | Inherits `dev`, plus ASan and UBSan (`-fsanitize=address,undefined`). |

The leaf still compiles without CMake, which is the copy-out test of
the catalog:

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  tutorials/01-build-and-ub/main.cpp -o /tmp/build-and-ub
```

`-Werror` treats a warning as a failed run. A warning is a hypothesis
that the source does not mean what it appears to say; leaving it in
the log is the same habit as ignoring a conservation drift because the
plot still looks smooth.

## The program

Four DC voltages in volts, dtype `double`, form a manufactured
calibration. The values 2.0, 2.5, 3.0, and 2.5 are exactly
representable in IEEE-754 binary64, so their arithmetic mean is the
scalar in {eq}`mean-volts`.

```{math}
:label: mean-volts
\bar{v} = \frac{1}{n}\sum_{i=0}^{n-1} v_i = 2.5\,\mathrm{V}.
```

The default path computes that mean with a range-for over a
`std::span` of the `std::vector` that owns the buffer, then checks
$|\bar{v}-2.5\,\mathrm{V}|\le 10^{-15}\,\mathrm{V}$ and
`std::isfinite`. Passing `--broken` selects a 1-based index loop
instead. That branch is opt-in so that the `sanitize` preset remains a
usable default: continuous integration and the default invocation
stay defined and sanitizer-clean.

```{literalinclude} ../../tutorials/01-build-and-ub/main.cpp
:language: cpp
:start-after: // start build-and-ub
:end-before: // end build-and-ub
```

## When this fails

Laboratory notebooks, MATLAB, and Fortran number the first sample as
1, whereas a C++ container is indexed from 0. The broken loop therefore
forms {eq}`one-based-mean`.

```{math}
:label: one-based-mean
\frac{1}{n}\left(\sum_{i=1}^{n-1} v_i + v_n\right).
```

Index $n$ addresses storage beyond the record of length $n$; the value
loaded there is whatever occupies that address, not an element of
$\{v_i\}_{i=0}^{n-1}$. Without sanitizers the load is undefined, so the
printed mean may lie near $2.5\,\mathrm{V}$, may be wild, or may crash
in a caller that did not contain the index. Under high optimization the
compiler may delete later checks, because it is allowed to assume the
out-of-range index never occurs. A plausible printed voltage is
therefore not evidence that {eq}`mean-volts` was formed.

`std::span::at` and `std::vector::at` throw `std::out_of_range`. That
evaluation is defined and still a failed experiment. The lesson uses
unchecked `operator[]` because that is the default for those types, and
because it is the path that contaminates a result without a language-level
diagnostic {cite}`cppcoreguidelines`.

## Interpreting the sanitizer report

Reproduce the finding from a `sanitize` build, or by hand with the same
flags the preset uses:

```bash
./build/sanitize/build-and-ub --broken
```

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  tutorials/01-build-and-ub/main.cpp -o /tmp/build-and-ub
/tmp/build-and-ub --broken
```

`AddressSanitizer` intercepts the out-of-range load by poisoning a
redzone adjacent to the four-element heap allocation
{cite}`serebryany2012`. A report looks like the excerpt below. Process
ids, addresses, and C++ name mangling differ by platform and standard
library; the structure of the message does not.

```text
ERROR: AddressSanitizer: heap-buffer-overflow on address ...
READ of size 8 at ... thread T0
    #0 ... mean_volts_one_based(...) main.cpp:35
    #1 ... main main.cpp:60
    [...]

... is located 0 bytes after 32-byte region [...]
allocated by thread T0 here:
    [...]
    ... vector ... main.cpp:48
    [...]

SUMMARY: AddressSanitizer: heap-buffer-overflow main.cpp:35
    in ... mean_volts_one_based(...)

Shadow bytes around the buggy address:
  ...
=>...:[fa]...
  [...]
```

Read it as a measurement of the program, not as compiler noise:

- `heap-buffer-overflow` names a spatial error: the access left the
  allocation that holds the samples.
- `READ of size 8` is one object of type `double` on the platforms
  considered here.
- Frame `#0` is the load in `mean_volts_one_based`; `#1` is the caller
  in `main`.
- `0 bytes after 32-byte region` is the first byte past four
  `double`s, which is index $n$ on a record of length $n$.
- The allocation stack points at the `std::vector` constructed in
  `main`.
- `[fa]` in the shadow map is the heap redzone (eight application
  bytes per shadow byte). The rest of the map can be ignored on a
  first reading.

Non-zero termination is the intended outcome of the demonstration: the
tool is operating within its specification.

The defect is spatial, so `AddressSanitizer` is the instrument that
fires. `UndefinedBehaviorSanitizer` in the same preset catches a
different class of silent wrongness (signed overflow, invalid shifts,
misaligned access) {cite}`llvm-ubsan`. The `dev` preset will compile
`--broken` and may even run it, leaving the out-of-range load
uninstrumented. Build with `sanitize` when the number matters.

## Alternatives

Bounds-checked access (`.at()`, or a checked span) converts the mistake
into an exception: defined, loud, and still a failed experiment.
Valgrind Memcheck is complementary and slower; in this repository the
`sanitize` preset remains the required instrument. A default `main`
that always triggers undefined behavior would make
`cmake --preset sanitize` unusable, which is why the poisonous path
stays behind `--broken`.

Turning sanitizers off in order to clear a log removes the measurement
rather than the defect.

Cited works are collected in {doc}`/references`.
