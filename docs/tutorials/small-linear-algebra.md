# Small vectors and matrices

```{index} column-major
```

```{index} matrix-vector product
```

```{index} std::array
```

This is chapter 6 of the [contents](../learning-path.md). It depends on
[error-handling](error-handling.md). The next spine id is
`frames-and-rotations`; that chapter is not yet written.

A laboratory 3-vector is three objects of type `double` with a layout,
and a $3\times 3$ map is nine more. Forming $y=Ax$ is a sum over a
stated index convention {cite}`golub2013`. Swapping the row stride with
the column stride applies $A^{\top}$ instead of $A$, which is a small
change in an assumption, in the sense of conditioning: the evaluation
remains defined, `AddressSanitizer` stays quiet, and the printed
coordinates still look like a position in meters. Named frames stay
labels until chapter 7; this chapter is the map those frames will use,
as in [notation](../notation.md).

## The program

The position $x$ is in meters, dtype `double`. The map $A$ is
dimensionless and nonsymmetric, so $A^{\top}x$ is a different vector
from $Ax$. The entries of {eq}`ax-map` are integers, hence exact in
IEEE-754 binary64. `std::array<double, 3>` is the 3-vector;
`std::array<double, 9>` holds $A$ in column-major order, which is the
BLAS and Fortran convention and the default in Eigen
{cite}`golub2013,trefethen1997`. Entry $a_{ij}$ lives at the index in
{eq}`col-major`.

```{math}
:label: ax-map
A = \begin{pmatrix} 1 & 2 & 0 \\ 0 & 1 & 2 \\ 0 & 0 & 1 \end{pmatrix},
\quad
x = \begin{pmatrix} 1 \\ 2 \\ 3 \end{pmatrix}\,\mathrm{m},
\quad
y = Ax = \begin{pmatrix} 5 \\ 8 \\ 3 \end{pmatrix}\,\mathrm{m}.
```

```{math}
:label: col-major
a_{ij}\ \text{at index}\ i + 3j,
\qquad i,j \in \{0,1,2\}.
```

The default path stores the columns of $A$ in that order, forms $Ax$,
and checks each component of $y$ to $10^{-15}\,\mathrm{m}$ together
with `std::isfinite`. Passing `--broken` uses index $j+3i$, which reads
$a_{ji}$ and therefore forms $A^{\top}x$. That branch is opt-in and
defined, so a quiet `sanitize` run is not evidence that {eq}`ax-map`
was formed.

```{literalinclude} ../../tutorials/06-small-linear-algebra/main.cpp
:language: cpp
:start-after: // start small-linear-algebra
:end-before: // end small-linear-algebra
```

## When this fails

Column-major storage lists $a_{00}, a_{10}, a_{20}$ first, then the
next column. Index $j+3i$ walks rows as if they were columns, which is
the expansion of $A^{\top}x$ on the same buffer. For the manufactured
$A$ that product is $(1,4,7)^{\top}\,\mathrm{m}$, a finite 3-vector of
meters other than the $y$ of {eq}`ax-map` {cite}`golub2013`. The
evaluation is nine multiplies and six adds of `double`.

A symmetric $A$ hides the same layout mistake, because then
$A^{\top}=A$. The lesson uses a nonsymmetric map so that the wrong
index is visible in the printed coordinates. Nested C++ arrays
`a[i][j]` already mean row $i$, column $j$; flattening them into a
length-9 buffer without stating {eq}`col-major` is the same class of
defect when the buffer is later passed to BLAS.

## Interpreting a quiet sanitizer

Reproduce the transposed layout from a `sanitize` build:

```bash
./build/sanitize/small-linear-algebra --broken
```

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  tutorials/06-small-linear-algebra/main.cpp -o /tmp/small-linear-algebra
/tmp/small-linear-algebra --broken
```

The process exits 0. There is no `heap-buffer-overflow` and no
`heap-use-after-free`, because every index stays in $0,\ldots,8$. The
diagnostic is the printed `[1, 4, 7] m` beside the manufactured
$[5, 8, 3]$ m of {eq}`ax-map`.

## Alternatives

A nested `std::array<std::array<double, 3>, 3>` with `a[i][j] = a_{ij}`
matches the mathematics without a stride formula; it is row-major in
the C++ sense and is the wrong layout to pass into a column-major
kernel. Eigen or a BLAS `dgemv` belong when the map is no longer nine
entries {cite}`trefethen1997`. This leaf stays on `std::array` so the
folder compiles by itself.

The next spine item, `frames-and-rotations`, names the frames that $x$
and $Ax$ occupy. This chapter is the product that those names will
require to be unambiguous.

Cited works are collected in {doc}`/references`.
