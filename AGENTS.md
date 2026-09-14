# Agent instructions

This repository is a **catalog of C++ teaching artifacts**, not a single library. Read [BLUEPRINT.md](BLUEPRINT.md) before changing layout, tooling, or the meaning of “done”. [catalog.yaml](catalog.yaml) is the index of record.

## Non-negotiables

- Put work in the directory for its **kind**: `tutorials/`, `how-to/`, `examples/`, `exercises/`, `projects/`, `templates/`, `toolbox/`.
- Do not merge an entry that is missing any of: compiling code (starter + solution for exercises), comments, leaf `README.md`, `catalog.yaml` row, docs page that will `literalinclude` the code.
- Do not paste a second copy of a program into Markdown. Use `// start <id>` / `// end <id>` markers and `literalinclude`.
- Do not grow `toolbox/` into a framework. Promote a helper only after ~three copies. Entries must remain understandable if copied alone.
- C++20 floor, C++ Core Guidelines, no bare `new`/`delete`. Numeric examples state units, dtype, and a correctness check.
- Do not add a new top-level directory, docs stack, or build system. The planned spine is CMake + Sphinx + Doxygen ([docs/build.md](docs/build.md)).
- `templates/` are copy-out starters. Never `add_subdirectory` them into the superbuild.
- Topics are the controlled list in `catalog.yaml`. A new topic is a conscious change, not a side effect.
- Git commits are Conventional Commits: 50-character subject, 72-column body. See `.cursor/rules/conventional-commits.mdc`.

## Where to look

| Task | Start here |
|---|---|
| Intention, layout, tooling | `BLUEPRINT.md` |
| Add an entry | Skill `add-catalog-entry`; commands `/add-tutorial` etc. |
| C++ style | `.cursor/rules/cpp-standards.mdc`, `docs/style.md` |
| Docs / Sphinx | Skill `write-scientific-docs`, `docs/style.md` |
| Promote shared code | Skill `extract-to-toolbox` |
| Completeness check | Skill `review-catalog-entry` or `/review-entry` |
| Human recipe | `CONTRIBUTING.md` |
| Spine of tutorials to fill first | `docs/learning-path.md` |

## Nested maps

Subdirectories have their own `AGENTS.md`. Those win for files under that tree.

## Done means

The catalog row is `status: complete` only when the review skill’s checklist is green. Prefer one complete entry per change over many stubs.
