"""Sphinx configuration for the cpp-toolbox HTML and PDF book."""

from __future__ import annotations

import subprocess
import sys
from pathlib import Path

project = "cpp-toolbox"
author = "Miguel Dovale"
copyright = "2026, Miguel Dovale"
release = "0.1.0"

DOCS_DIR = Path(__file__).resolve().parent
DOXY_XML = DOCS_DIR / "_build" / "doxygen" / "xml"


def _run_doxygen() -> None:
    doxyfile = DOCS_DIR / "Doxyfile"
    (DOCS_DIR / "_build" / "doxygen").mkdir(parents=True, exist_ok=True)
    result = subprocess.run(
        ["doxygen", str(doxyfile)],
        cwd=DOCS_DIR,
        check=False,
        capture_output=True,
        text=True,
    )
    if result.stdout:
        print(result.stdout, end="")
    if result.stderr:
        print(result.stderr, file=sys.stderr, end="")
    if result.returncode != 0:
        sys.exit(f"doxygen failed with exit code {result.returncode}")
    if not (DOXY_XML / "index.xml").is_file():
        sys.exit(f"doxygen did not write {DOXY_XML / 'index.xml'}")


_run_doxygen()

extensions = [
    "myst_parser",
    "breathe",
    "sphinxcontrib.bibtex",
]

breathe_projects = {"toolbox": str(DOXY_XML)}
breathe_default_project = "toolbox"

bibtex_bibfiles = ["refs.bib"]
bibtex_default_style = "plain"
bibtex_reference_style = "author_year"

myst_enable_extensions = [
    "colon_fence",
    "deflist",
    "dollarmath",
    "amsmath",
    "fieldlist",
]

myst_heading_anchors = 3
myst_dmath_allow_labels = True

numfig = True
math_numfig = True
numfig_secnum_depth = 1

exclude_patterns = [
    "_build",
    "AGENTS.md",
    "README.md",
]

html_theme = "furo"
html_title = "cpp-toolbox"

latex_engine = "pdflatex"
latex_documents = [
    (
        "index",
        "cpp-toolbox.tex",
        "cpp-toolbox",
        "Miguel Dovale",
        "manual",
    ),
]
latex_elements = {
    "papersize": "letterpaper",
    "pointsize": "11pt",
    "preamble": r"\setlength{\headheight}{14pt}",
}

nitpicky = True
