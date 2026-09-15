---
name: build-docs
description: Build the Sphinx HTML book; add --pdf for HTML plus PDF
---

Build the cpp-toolbox Sphinx book from the repository root.

1. Do **not** invent a second docs stack. The only entry point is
   `./scripts/build-docs.sh` (Doxygen runs from `docs/conf.py`; Sphinx
   `-W`). Spec: `docs/build.md`.
2. Default (HTML):

   ```bash
   ./scripts/build-docs.sh
   ```

   If the user typed `--pdf` or asked for PDF after this command:

   ```bash
   ./scripts/build-docs.sh --pdf
   ```

3. PDF is a gate for spine chapters when `latexmk` and `pdflatex` are
   on `PATH`. If TeX is missing, say so; HTML `-W` must still succeed.
4. Stop with the outcome: success or the first Sphinx/LaTeX error.
   Paths: `docs/_build/html/index.html`, and
   `docs/_build/latex/cpp-toolbox.pdf` when PDF was requested and built.
   Do not commit `_build/`.
