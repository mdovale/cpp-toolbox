---
name: review-catalog-entry
description: >-
  Reviews a cpp-toolbox catalog entry for completeness, C++ practice, numerical
  honesty, and docs/code sync. Use before marking catalog status complete, when
  reviewing a tutorial/example/exercise/project, or when the user runs
  /review-entry.
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

**Slice**

- [ ] Compiling C++20 (exercise: `starter/` and `solution/` both compile)
- [ ] `// start <id>` / `// end <id>` present
- [ ] Leaf `README.md`: what, when, build, see-also
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

**Docs voice**

- [ ] Scientific/engineering tone
- [ ] Exercise prompt has no spoilers

## Output format

```text
Entry: <id> (<kind>) at <path>
Verdict: complete | draft | blocked
Gaps:
- ...
```
