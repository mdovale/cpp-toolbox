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

Spec: [docs/style.md](../../../docs/style.md). Specimen: [docs/tutorials/build-and-ub.md](../../../docs/tutorials/build-and-ub.md). Book root: [docs/index.md](../../../docs/index.md). Notation: [docs/notation.md](../../../docs/notation.md).

## Contract

| Location | Content |
|---|---|
| Code comments | This invariant, this pitfall, this tolerance |
| Leaf README | Lab card: what, when, build, see-also |
| `docs/` spine page | Chapter: why, math, `{cite}`, failure modes, `literalinclude` |
| Doxygen | `toolbox/` and reusable headers only |

Never paste a full program into Markdown. Use MyST `literalinclude` with the entry’s `// start <id>` markers. Paths are relative to the docs page, not the repo root.

If markers are missing, add them in the source in the same change.

## Voice

- Engineering/scientific. Assume calculus and linear algebra; do not assume CS coursework.
- Ownership, UB, races: say how the **result** goes wrong. The apt analogue is conditioning, not an unstable time step; scope every analogy.
- Hypotaxis: a paragraph develops a claim; connectives carry the relation. Do not stack one-claim restatements.
- Define affirmatively. Negate once when a real confusion exists, not as a couplet habit.
- Math: numbered `{math}` (or a numbered figure) on every spine tutorial. `{cite}` keys from `docs/refs.bib`. ASCII or math in MyST (`pdflatex`).
- Exercises: no spoilers in `prompt.md`. Solution = dropdown in HTML, appendix in PDF.

## Chapter shape (spine tutorials)

1. Title matching `catalog.yaml` `title`.
2. What this chapter assumes (depends-on by catalog `id`; “none” if first).
3. The claim of the chapter, then the worked program (`literalinclude`).
4. Failure mode of the quantity (units, dtype, check).
5. At least one numbered displayed equation or numbered figure.
6. Alternatives, then running `{cite}` (bibliography lives in `docs/references.md`).

## Page checklist

- Title matches `catalog.yaml` `title`
- Depends-on tutorials linked by `id`
- `literalinclude` path is correct from the new file
- Numeric entries state units, dtype, correctness check
- Numbered `{math}` label or numbered figure on spine tutorials
- Citations are `{cite}` keys, not a pasted reference list
- Voice spec in `docs/style.md` is green (hypotaxis, affirmative definition)
- No “click here” as the only way to see a solution
- Set `prose: complete` in `catalog.yaml` only when this checklist is green
