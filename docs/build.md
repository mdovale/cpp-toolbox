# Build and documentation toolchain

**Status:** CMake spine and **Sphinx HTML** are in place. PDF (LaTeX) and Doxygen/Breathe are still planned. Do not introduce a competing stack (Make-only, mdBook, Doxygen-only, Meson, …). Constitution: `BLUEPRINT.md` at the repository root.

## CMake

C++20 at the root; an entry may request 23 via `add_toolbox_example(... STD 23)`. Root `CMakeLists.txt` + `CMakePresets.json` + modules in `cmake/`.

- `add_toolbox_example()` registers one executable per lesson. No mega-binary of demos.
- `templates/` are never in-tree targets.
- Catch2 is fetched pinned (`v3.8.1`) when `TOOLBOX_BUILD_TESTING` is ON. Other libraries only when an entry’s README explains why.
- `CMAKE_EXPORT_COMPILE_COMMANDS` is ON (`build/dev/compile_commands.json`).

### Presets

| Preset | Purpose |
|---|---|
| `dev` | Warnings as errors, `compile_commands.json`, toolbox tests |
| `sanitize` | Inherits `dev`, plus ASan + UBSan |
| `docs` | Configure only (Sphinx targets come later) |

```bash
cmake --preset dev
cmake --build --preset dev
ctest --preset dev

cmake --preset sanitize
cmake --build --preset sanitize
ctest --preset sanitize
```

Default build: `toolbox` tests + any `tutorials/*/main.cpp` that exist. How-tos, examples, exercises, and projects: `-DTOOLBOX_BUILD_EXAMPLES=ON`.

A leaf `main.cpp` must still be valid C++20 a reader can compile by hand:

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror main.cpp -o demo
```

## Documentation

HTML is built with Sphinx + MyST. Doxygen, Breathe, bibtex, and PDF are still planned.

| Tool | Role |
|---|---|
| Sphinx + MyST | Narrative book (HTML, wired) |
| Doxygen | API XML from `toolbox/` (planned) |
| Breathe (optionally Exhale) | API into Sphinx (planned) |
| sphinxcontrib-bibtex | Citations (planned) |
| `sphinx-build -b html` | HTML |
| `sphinx-build -b latex` + `latexmk` | PDF (planned) |

```bash
source .venv/bin/activate
pip install -r docs/requirements.txt
sphinx-build -W -b html docs docs/_build/html
```

Open `docs/_build/html/index.html`. Generated output stays in `docs/_build/` (gitignored).

### How the book includes code

Sphinx pulls marked regions from real sources. The cookie at `templates/catalog-entry/main.cpp` is the smoke test:

```{literalinclude} ../templates/catalog-entry/main.cpp
:language: cpp
:start-after: // start CHANGE_ME
:end-before: // end CHANGE_ME
```

If that block is empty or missing, the HTML build must fail. Lesson pages use the same `// start <id>` / `// end <id>` markers.

## Quality tools

- Catch2 for `toolbox/` tests (wired)
- `.clang-format`, `.clang-tidy`, pre-commit (planned)
- GitHub Actions: `dev` + tests on PRs; full tree + docs on `main` (planned)

## What not to do

- Do not add a second build entry point (`Makefile` at the root that becomes the real system, a `meson.build`, …).
- Do not check in generated HTML/PDF or `build/`.
- Do not add heavy dependencies “to get started.”
