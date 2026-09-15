# Notation

Symbols below are frozen for the spine through chapter 4
(`floating-point`). Later chapters may add names; they should not
redefine these.

## Units and dtypes

SI units appear in the text and in identifier suffixes (`samples_v` for
voltages in volts). The default floating type is IEEE-754 binary64
(`double`), chosen because laboratory scalars and 3-vectors fit
comfortably in a 53-bit mantissa. Use `float` only when the lesson is
the dtype, and say so at the data model. Do not hide either behind an
uncommented `typedef`.

A correctness check states the quantity, the unit, and the tolerance
(absolute or relative) against a manufactured value, a residual, or a
property such as `std::isfinite`.

## Indices

C++ containers are 0-based. In displayed mathematics, $i$ runs through
$0,\ldots,n-1$ unless the surrounding sentence says otherwise. A
1-based index, as in MATLAB or Fortran, is written $i=1,\ldots,n$ and
called out as such, because it is a common source of an out-of-range
load.

## Linear algebra (from chapter 6)

Column vectors are lowercase bold in prose when needed, and plain $x$
in inline math for a 3-vector of `double`. Matrices are $A$, $R$. A
$3\times 3$ map stored in a length-9 `std::array` is column-major:
entry $a_{ij}$ lives at index $i+3j$ with $i,j\in\{0,1,2\}$.

## Frames and rotations (from chapter 7)

A named frame is a label on a 3-vector or on $R$, written in
identifiers (`x_lab_m`, `r_lab_from_body`), not a C++ type.
$x_{\mathrm{lab}} = R x_{\mathrm{body}}$ with $R$ column-major as in
chapter 6. Euler angles in this book are ZYX (yaw $\psi$, pitch
$\theta$, roll $\phi$) in radians. Do not write $\dot{x}$ for a time
derivative until chapter 8; the contents table uses that symbol only
to name the ODE lesson.

## Typography in this book

Print is `pdflatex`. Write ASCII or math (`$\dot{x}$`, `$3\times 3$`),
not raw Unicode letters. Catalog `id`s and CMake targets stay
kebab-case in code font.
