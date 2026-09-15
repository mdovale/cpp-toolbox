# Time integration with RK4

```{index} Runge-Kutta
```

```{index} ordinary differential equation
```

```{index} timestep
```

This is chapter 8 of the [contents](../learning-path.md). It depends on
[frames-and-rotations](frames-and-rotations.md). The next spine id is
`engineering-io`; that chapter is not yet written.

A laboratory state that obeys $\dot{v}=f(v,t)$ is advanced by a
defined map from $(v_n,\Delta t)$ to $v_{n+1}$ {cite}`hairer1993`.
Classical RK4 is that map with four evaluations of $f$. The
manufactured solution of the linear decay in {eq}`decay-ode` is
{eq}`decay-exact`. A step $\Delta t$ that is no longer small compared
with $\tau$ is a change of assumption, in the sense of conditioning:
the recurrence remains defined, `AddressSanitizer` stays quiet, and
the printed volts still look like a decaying record. An unstable time
step is this defined recurrence, not an analogue for undefined
evaluation.

## The program

The voltage $v$ is in volts, time $t$ and the step $\Delta t$ are in
seconds, dtype `double`. $\tau=1\,\mathrm{s}$ and $v(0)=1\,\mathrm{V}$
make {eq}`decay-exact` at $t=3\,\mathrm{s}$ equal to
$e^{-3}\,\mathrm{V}$. The default path takes twenty-four RK4 steps of
$\Delta t=0.125\,\mathrm{s}$, which is $1/8$ and exact in IEEE-754
binary64, so $n\Delta t=3\,\mathrm{s}$ with no rounding of the clock.
The check is $|v-e^{-3}\,\mathrm{V}|\le 10^{-6}\,\mathrm{V}$ and
`std::isfinite`; the global RK4 error at this $\Delta t$ is about
$3\times 10^{-7}\,\mathrm{V}$. Passing `--broken` takes one RK4 step
of $\Delta t=3\,\mathrm{s}=3\tau$. That branch is opt-in and defined,
so a quiet `sanitize` run is not evidence that {eq}`decay-exact` was
formed.

```{math}
:label: decay-ode
\dot{v} = -\frac{v}{\tau}, \qquad \tau = 1\,\mathrm{s}.
```

```{math}
:label: decay-exact
v(t) = v(0)\,e^{-t/\tau}.
```

```{literalinclude} ../../tutorials/08-ode-rk4/main.cpp
:language: cpp
:start-after: // start ode-rk4
:end-before: // end ode-rk4
```

## When this fails

RK4 applied to {eq}`decay-ode` is the degree-four Taylor polynomial of
the exponential in the step $z=-\Delta t/\tau$ {cite}`hairer1993`. At
$\Delta t=3\tau$, that polynomial equals $1.375$, so one step from
$1\,\mathrm{V}$ yields $1.375\,\mathrm{V}$ while {eq}`decay-exact` is
$e^{-3}\,\mathrm{V}\approx 0.0498\,\mathrm{V}$. The four-stage map is
a finite sequence of multiplies and adds of `double`. Growth of the
linear test equation is the stability region of the method, which is a
property of the recurrence, not of the C++ abstract machine.

The same class of defect occurs when $\Delta t$ is a large fraction of
a faster time scale that $f$ still contains: the printed trajectory
looks smooth in $t$ and wrong in $v$. Reducing $\Delta t$ until the
manufactured check passes is the measurement; turning sanitizers off
does not change the truncation.

## Interpreting a quiet sanitizer

Reproduce the large step from a `sanitize` build:

```bash
./build/sanitize/ode-rk4 --broken
```

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  tutorials/08-ode-rk4/main.cpp -o /tmp/ode-rk4
/tmp/ode-rk4 --broken
```

The process exits 0. There is no `heap-buffer-overflow` and no
`heap-use-after-free`, because the failure is not a bounds or lifetime
error. The diagnostic is the printed `1.375` V beside the manufactured
$e^{-3}$ V of {eq}`decay-exact`.

## Alternatives

Forward Euler is the one-stage truncation of the same exponential; its
linear test equation is unstable for $\Delta t>2\tau$, so a large step
is visible even sooner {cite}`hairer1993`. Implicit and adaptive
methods belong when $f$ is stiff. This leaf is a scalar RK4 in one
translation unit. How residuals and tolerances are organized as tests
is `testing-numerics`; this chapter is one manufactured check in
`main`.

The next spine item, `engineering-io`, treats files as part of the
experiment. This chapter is the time stepping that those files will
later record.

Cited works are collected in {doc}`/references`.
