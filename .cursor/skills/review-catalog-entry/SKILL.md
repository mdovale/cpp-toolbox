---
name: review-catalog-entry
description: >-
  Reviews a cpp-toolbox catalog entry for completeness, C++ practice, numerical
  honesty, docs/code sync, and book prose. Use before marking catalog status
  complete, when reviewing a tutorial/example/exercise/project, or when the
  user runs /review-entry.
---

# Review a catalog entry

Report gaps; fix them if you are in Agent mode and the user asked to add or finish the entry. Otherwise list them.

Identify the entry (`id`, path, kind) from the user, the open files, or `catalog.yaml`.

## Checklist

**Placement**

- [ ] Path matches kind (table in `CONTRIBUTING.md`)
- [ ] `catalog.yaml` row exists; `id` equals folder slug (tutorials: slug without `NN-`)
- [ ] `topic` is in the controlled vocabulary
- [ ] `templates/` not referenced from CMake

**Slice** (`status: complete`)

- [ ] Compiling C++20 (exercise: `starter/` and `solution/` both compile)
- [ ] `// start <id>` / `// end <id>` present
- [ ] Leaf `README.md`: what, when, build, see-also (lab card, not the chapter)
- [ ] `docs/` page `literalinclude`s the marked region (no pasted program)
- [ ] `status: complete` only if every box above is true

**C++**

- [ ] No bare `new`/`delete`; RAII; `span`/`string_view` for non-owning views
- [ ] No `using namespace std;` in headers
- [ ] Lesson is understandable copied as a folder (`toolbox/` optional)

**Numerics** (if numbers)

- [ ] Units and dtype stated
- [ ] Correctness check present
- [ ] Failure mode named when the method is fragile

**Prose** (`prose: complete`; spec in `docs/style.md`)

- [ ] Scientific/engineering tone; hypotaxis; affirmative definition
- [ ] Analogies scoped; UB/lifetime not equated with an unstable time step
- [ ] Spine tutorial: numbered `{math}` or numbered figure
- [ ] Citations are `{cite}` from `docs/refs.bib`, not a pasted list
- [ ] Exercise prompt has no spoilers
- [ ] `prose: complete` only if every box in this section is true; otherwise `prose: draft`

A slice may be `status: complete` with `prose: draft`. Spine tutorials should not ship that way.

## Output format

```text
Entry: <id> (<kind>) at <path>
Verdict: complete | draft | blocked
Prose: complete | draft
Gaps:
- ...
```
