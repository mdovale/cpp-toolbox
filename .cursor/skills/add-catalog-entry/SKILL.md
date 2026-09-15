---
name: add-catalog-entry
description: >-
  Adds a complete cpp-toolbox catalog entry (tutorial, how-to, example,
  exercise, project, or template) as a vertical slice. Use when creating a new
  lesson, filling a planned catalog.yaml row, or when the user runs
  /add-tutorial, /add-howto, /add-example, /add-exercise, /add-project, or
  /add-template.
---

# Add a catalog entry

Constitution: [BLUEPRINT.md](../../../BLUEPRINT.md). Human recipe: [CONTRIBUTING.md](../../../CONTRIBUTING.md). File templates: [reference.md](reference.md).

## Kind and path

| Kind | Path | Notes |
|---|---|---|
| `tutorial` | `tutorials/NN-slug/` | `id` = slug without `NN-`. Prefer the spine in `docs/learning-path.md`. |
| `how-to` | `how-to/slug/` | README title is an action. |
| `example` | `examples/<topic>/slug/` | `topic` from `catalog.yaml`. |
| `exercise` | `exercises/<topic>/slug/` | `prompt.md` + compiling `starter/` + `solution/`. |
| `project` | `projects/slug/` | Several sources OK. |
| `template` | `templates/slug/` | Copy-out; not in the superbuild. |

If kind is missing, ask. Do not guess a new **topic**; use the vocabulary in `catalog.yaml` or add one on purpose in the same change.

If `id` already exists as `planned`, fill that row (keep `id`, `path`, `kind`) and move `status` to `complete` only at the end.

## Procedure

1. Copy `templates/catalog-entry/` to the path above. For exercises, copy it to `starter/` and `solution/`; add `prompt.md` with no spoilers.
2. Replace `CHANGE_ME` with `id`. Write C++20 per `docs/style.md` and `.cursor/rules/cpp-standards.mdc`. Keep `// start <id>` / `// end <id>` around the lesson.
3. Leaf `README.md`: what, when to use it, how to build, see-also (other catalog ids).
4. Upsert the `catalog.yaml` row (`difficulty` 1–5, `std` 20 or 23, tags, title, path, `status`, and `prose` once the folder exists).
5. Add a docs page under the matching book section (`docs/tutorials/<id>.md`, `docs/how-to/<id>.md`, `docs/examples/<id>.md`, `docs/exercises/<id>.md`, `docs/projects/<id>.md`, or `docs/templates/<id>.md`). See [reference.md](reference.md). Follow skill `write-scientific-docs`. `literalinclude` the marked region. Do not paste the program.
6. Numeric work: units, dtype, correctness check. Spine tutorials: numbered `{math}` or a numbered figure; `{cite}` from `docs/refs.bib`.
7. Run skill `review-catalog-entry`. Fix gaps before you stop. Set `status: complete` only if the slice checklist is green. Set `prose: complete` only if the voice checklist is green.

Until CMake exists, `main.cpp` must still compile as `c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror main.cpp`.

## Do not

- Put a tutorial under `examples/` or an exercise under `projects/`.
- Add `toolbox/` APIs as part of the first use of a helper.
- `add_subdirectory` a template.
- Mark `complete` with a stub `main` or a README that says “TODO.”
