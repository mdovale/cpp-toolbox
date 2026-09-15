# Agent map — docs/

You are in the Sphinx book source. `catalog.yaml` is the machine index;
these pages are the monograph.

- [index.md](index.md) is the preface. Do not paste programs here;
  `literalinclude` marked regions from the matching leaf sources.
- Spine tutorials follow skill `write-scientific-docs` and [style.md](style.md).
  Specimen: [tutorials/build-and-ub.md](tutorials/build-and-ub.md).
- Notation is frozen in [notation.md](notation.md). Citations go in
  [refs.bib](refs.bib); the list is [references.md](references.md).
- A new catalog entry needs a page in the same change. Set `prose: complete`
  only when the voice checklist is green.
- Build HTML with `./scripts/build-docs.sh` or `/build-docs`. PDF:
  `./scripts/build-docs.sh --pdf` or `/build-docs --pdf` (required for
  spine chapters; `pdflatex` needs ASCII or math, not raw Unicode).
  Generated output belongs in `_build/` (gitignored).
