"""Sphinx configuration for the cpp-toolbox HTML book."""

project = "cpp-toolbox"
author = "Miguel Dovale"
copyright = "2026, Miguel Dovale"
release = "0.1.0"

extensions = [
    "myst_parser",
]

myst_enable_extensions = [
    "colon_fence",
    "deflist",
    "dollarmath",
    "amsmath",
    "fieldlist",
]

myst_heading_anchors = 3

exclude_patterns = [
    "_build",
    "AGENTS.md",
    "README.md",  # GitHub map; index.md is the book root
]

html_theme = "furo"
html_title = "cpp-toolbox"

nitpicky = True
