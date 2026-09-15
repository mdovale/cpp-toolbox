# RAII, ownership, and views

```{index} RAII
```

```{index} std::span
```

```{index} lifetime
```

This is chapter 2 of the [contents](../learning-path.md). It depends on
[build-and-ub](build-and-ub.md). The next spine chapter is
[cmake-app](cmake-app.md). `floating-point` remains planned.

A laboratory buffer is a resource: a region of storage that must be
released exactly once. RAII (Resource Acquisition Is Initialization)
makes that release the destructor of a C++ object, so leaving a scope,
including by an exception, frees the buffer
{cite}`stroustrup2013,cppcoreguidelines-raii`. `std::vector<double>` is
the owner in this chapter: construction acquires a heap allocation for
$n$ voltages, and the destructor releases it. `std::unique_ptr<T>` is
the same contract for a single heap object.

`std::span<const double>` is a view: a pointer and a length that name
existing objects without extending their lifetime
{cite}`iso14882-2020-life`. Passing the span into a helper copies those
two words rather than the voltages, so the helper can read the record
without a second allocation. Defined use of the view requires that the
owner remain alive and retain the same storage for the whole call. In
the sense of conditioning, dropping that assumption is a small
perturbation: the printed peak may still look like a voltage while the
objects the span names have already ended their lifetime. Chapter 1
already passed a `std::span` of a `std::vector` that remained in `main`
until after the mean; this chapter is that contract, including the case
where it is broken.

## The program

Four DC voltages in volts, dtype `double`, form a manufactured record
whose maximum is the scalar in {eq}`peak-volts`. The values 2.0, 2.5,
3.0, and 2.5 V are exactly representable in IEEE-754 binary64, so the
peak 3.0 V is exact. `double` is the dtype because a laboratory scalar
fits in a 53-bit mantissa, as in [notation](../notation.md).

```{math}
:label: peak-volts
v_{\max} = \max_{0 \le i < n} v_i = 3.0\,\mathrm{V}.
```

The default path constructs a `std::vector` that owns the four samples,
forms a `std::span` of that vector, and passes the span to
`peak_volts`, which does not copy the buffer. The check is
$|v_{\max}-3.0\,\mathrm{V}|\le 10^{-15}\,\mathrm{V}$ and
`std::isfinite`. Passing `--broken` lets the vector's destructor run
while a span that named its buffer is still in scope, then reads through
that span. That branch is opt-in so that the `sanitize` preset remains a
usable default, as in [build-and-ub](build-and-ub.md).

```{literalinclude} ../../tutorials/02-raii-and-ownership/main.cpp
:language: cpp
:start-after: // start raii-and-ownership
:end-before: // end raii-and-ownership
```

## When this fails

The inner block in the `--broken` path constructs the owner, binds a
span to its buffer, and then ends. The destructor of `std::vector`
releases the allocation, which ends the lifetime of the four `double`
objects {cite}`iso14882-2020-life`. The span still holds a pointer and
the length 4; those two words are ordinary copies and do not keep the
buffer alive. `peak_volts` then loads through a pointer to storage the
program has already given back to the allocator.

Without sanitizers the loads are undefined, so the printed peak may
equal 3.0 V (the freed bytes have not yet been reused), may be wild, or
may crash in a caller that did not contain the span. A plausible printed
voltage is therefore not evidence that {eq}`peak-volts` was formed.

The same class of defect occurs when the owner object is still in
scope but replaces its buffer: `push_back` or `resize` past
`capacity()` allocates a new region and frees the old one. A
`std::vector` that remains in scope after that relocation is a
different allocation, so every span into the previous storage dangles.
Defined use keeps the owner alive without reallocating for the duration
of the view.

`std::string_view` is the analogous non-owning type for text. Returning
a `string_view` into a function-local `std::string` is the same
lifetime mistake as returning a span into a function-local vector.

## Interpreting the sanitizer report

Reproduce the finding from a `sanitize` build, or by hand with the same
flags the preset uses:

```bash
./build/sanitize/raii-and-ownership --broken
```

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  tutorials/02-raii-and-ownership/main.cpp -o /tmp/raii-and-ownership
/tmp/raii-and-ownership --broken
```

`AddressSanitizer` intercepts the load by poisoning the freed heap
region {cite}`serebryany2012`. A report looks like the excerpt below.
Process ids, addresses, and C++ name mangling differ by platform and
standard library; the structure of the message does not.

```text
ERROR: AddressSanitizer: heap-use-after-free on address ...
READ of size 8 at ... thread T0
    #0 ... peak_volts(...) main.cpp:22
    #1 ... main main.cpp:54
    [...]

freed by thread T0 here:
    [...]
    ... vector ... main.cpp:53
    [...]

previously allocated by thread T0 here:
    [...]
    ... vector ... main.cpp:51
    [...]

SUMMARY: AddressSanitizer: heap-use-after-free main.cpp:22
    in ... peak_volts(...)
```

Read it as a measurement of the program:

- `heap-use-after-free` names a temporal error: the access used storage
  after it was released.
- `READ of size 8` is one object of type `double` on the platforms
  considered here.
- Frame `#0` is the load in `peak_volts`; `#1` is the caller in
  `main`.
- The free stack is the `std::vector` destructor at the closing brace
  of the inner block; the allocation stack is the constructor of that
  same vector.

Non-zero termination is the intended outcome of the demonstration: the
tool is operating within its specification. Chapter 1's `--broken` path
was a spatial overflow (`heap-buffer-overflow`); this one is temporal.
The `dev` preset will compile `--broken` and may even run it, leaving
the dangling load uninstrumented.

## Alternatives

Returning the vector by value transfers ownership; the caller then
forms a span of a live object. Returning a span of a local vector
compiles and dangles. Passing a temporary vector into a helper that
returns `std::span` is the same defect in one line, because the
temporary is destroyed at the end of the full expression. A
`std::unique_ptr<double[]>` can own a buffer but does not carry a
length; `std::vector` remains the default owner for a contiguous
record {cite}`cppcoreguidelines-raii`.

A default `main` that always dangles would make
`cmake --preset sanitize` unusable, which is why the poisonous path
stays behind `--broken`.

Cited works are collected in {doc}`/references`.
