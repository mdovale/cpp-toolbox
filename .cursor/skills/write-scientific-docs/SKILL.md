---
name: write-scientific-docs
description: >-
  Writes Sphinx/MyST pages for cpp-toolbox that literalinclude real C++ and
  speak to an engineering and scientific audience. Use when adding or editing
  docs/, leaf README.md files, catalog documentation, HTML/PDF book pages, or
  Doxygen comments on toolbox/ headers.
paths:
  - "docs/**"
  - "**/README.md"
  - "**/prompt.md"
  - "catalog.yaml"
---

# Write scientific docs

Spec: [docs/style.md](../../../docs/style.md). Book root: [docs/index.md](../../../docs/index.md).

## Contract

| Location | Content |
|---|---|
| Code comments | This invariant, this pitfall, this tolerance |
| Leaf README | What, when, build, see-also |
| `docs/` page | Why, alternatives, math, citations, `literalinclude` |
| Doxygen | `toolbox/` and reusable headers only |

Never paste a full program into Markdown. Use MyST `literalinclude` with the entry’s `// start <id>` markers. Paths are relative to the docs page, not the repo root.

If markers are missing, add them in the source in the same change.

## Voice

- Engineering/scientific. Assume calculus and linear algebra; do not assume CS coursework.
- Ownership, UB, races: say how the **result** goes wrong.
- Math: `$...$` / `$$...$$`. Citations: bibliographic list until bibtex is enabled.
- Exercises: no spoilers in `prompt.md`. Solution = dropdown in HTML, appendix in PDF.

## Page checklist

- Title matches `catalog.yaml` `title`
- Depends-on tutorials linked by `id`
- `literalinclude` path is correct from the new file
- Numeric entries state units, dtype, correctness check
- No “click here” as the only way to see a solution
