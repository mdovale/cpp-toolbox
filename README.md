# cpp-toolbox

Modern C++ examples, tutorials, exercises, mini-projects, and copy-out templates for **engineers and scientists**.

The code follows current C++ practice (C++20 as the floor). Documentation is meant to become a **book**: HTML and PDF from the same sources, with math and citations. You do not need a computer-science degree; calculus, linear algebra, and some numerical methods are assumed.

This repository is in **skeleton** form: the layout, catalog, and contribution rules are in place. The CMake superbuild and the Sphinx site come next (see [docs/build.md](docs/build.md)). Until then, treat [BLUEPRINT.md](BLUEPRINT.md) as the constitution and [catalog.yaml](catalog.yaml) as the backlog.

## Who this is for

- Working engineers and scientists who write C++ for simulation, data, instruments, or analysis.
- People who want *why this is correct* (ownership, undefined behavior, floating-point) as well as *how to type it*.
- Instructors who need a starter / solution split for exercises.

## How the catalog is organized

| Kind | Directory | How to use it |
|---|---|---|
| Tutorials | [`tutorials/`](tutorials/) | Taught sequence. Follow [the learning path](docs/learning-path.md). |
| How-tos | [`how-to/`](how-to/) | One task, one recipe (“time a kernel”, “read a CSV”). |
| Examples | [`examples/`](examples/) | Complete programs, grouped by topic. |
| Exercises | [`exercises/`](exercises/) | Prompt + compiling starter + separate solution. |
| Mini-projects | [`projects/`](projects/) | Small end-to-end programs. |
| Templates | [`templates/`](templates/) | Copy *out* of this repo to start a real project. Not built here. |
| Toolkit | [`toolbox/`](toolbox/) | Tiny header-only helpers shared by several entries. Optional to copy. |

The index of record is [`catalog.yaml`](catalog.yaml). If an entry is not listed there, it is not part of the book.

## Learning path

Start with [docs/learning-path.md](docs/learning-path.md). That spine is the order we will fill first. How-tos, examples, and projects link back to it; they are not a substitute for it.

## Building

The build spine is not implemented yet. The intended flow is CMake presets (`dev`, `sanitize`, `docs`), C++20, warnings as errors, and sanitizers. Details: [docs/build.md](docs/build.md).

Documentation will be Sphinx (MyST) + Doxygen: `sphinx-build` for HTML, LaTeX + `latexmk` for PDF. Narrative pages include real source files so the book cannot rot.

## Contributing

New entries are **vertical slices**: code, comments, a leaf `README.md`, a `catalog.yaml` row, and a docs page in the same change.

- Humans: [CONTRIBUTING.md](CONTRIBUTING.md)
- Agents: [AGENTS.md](AGENTS.md)
- Constitution: [BLUEPRINT.md](BLUEPRINT.md)

In Cursor, `/add-tutorial`, `/add-howto`, `/add-example`, `/add-exercise`, `/add-project`, and `/add-template` run the add-entry workflow.

## License

[BSD 3-Clause](LICENSE). Copyright (c) 2026, Miguel Dovale.
