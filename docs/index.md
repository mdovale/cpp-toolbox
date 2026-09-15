# cpp-toolbox

This book teaches laboratory C++ as a sequence of worked programs. Each
chapter is a catalog entry you can copy, compile, and run; the narrative
is the argument that those programs are the right ones to run first.
Calculus, linear algebra, and some numerical methods are assumed. A
degree in compilers is not.

The claim of the sequence is that ownership, undefined behavior, and
lifetime fail the way an ill-conditioned computation fails: a small
perturbation of the data or of an assumption can change the printed
result while the run still looks successful. Warnings-as-errors and
AddressSanitizer plus UndefinedBehaviorSanitizer belong in the
experiment because they are the instruments that make those failures
visible. The companion repository is a catalog of independently
compilable artifacts (`catalog.yaml` at the repository root), not an
umbrella library and not a package-manager mirror of scientific C++.

```{toctree}
:maxdepth: 2
:caption: Front matter

learning-path
notation
style
build
```

```{toctree}
:maxdepth: 2
:caption: Spine

tutorials/README
```

```{toctree}
:maxdepth: 2
:caption: Apparatus

api
references
```

```{toctree}
:maxdepth: 2
:caption: Catalog around the spine

how-to/README
examples/README
exercises/README
projects/README
templates/README
```

How-tos, examples, exercises, projects, and templates link back to the
[contents](learning-path.md). They are recipes around the spine, not a
substitute for it. Narrative pages include real source with
`literalinclude`; they do not paste a second copy of the program.
How to build the code and the book: [build.md](build.md). Terms marked
in the chapters appear in the {ref}`genindex`.
