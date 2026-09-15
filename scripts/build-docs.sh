#!/usr/bin/env bash
# Build the Sphinx book. Doxygen runs from docs/conf.py.
set -euo pipefail
root="$(cd "$(dirname "$0")/.." && pwd)"
cd "$root"

python="${PYTHON:-${root}/.venv/bin/python}"
if [[ ! -x "$python" ]]; then
  python="$(command -v python3)"
fi

"$python" -m sphinx -W -b html docs docs/_build/html

if [[ "${1:-}" == "--pdf" ]]; then
  "$python" -m sphinx -W -b latex docs docs/_build/latex
  (cd docs/_build/latex && latexmk -pdf -interaction=nonstopmode cpp-toolbox.tex)
fi
