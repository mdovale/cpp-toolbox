# Build and documentation toolchain

**Status:** planned. The repo is a documented skeleton; this page is the spec the first CMake/Sphinx change must implement. Do not introduce a competing stack (Make-only, mdBook, Doxygen-only, Meson, …). Constitution: [BLUEPRINT.md](../BLUEPRINT.md).

## CMake (planned)

- C++20 as `CMAKE_CXX_STANDARD` at the root; an entry may request 23 via the catalog/`add_toolbox_example()` helper.
- Root `CMakeLists.txt` + `CMakePresets.json` + modules in [`cmake/`](../cmake/).
- Helper `add_toolbox_example()` registers one executable (or INTERFACE library) from a catalog row. Do not list dozens of targets by hand.
- Each in-tree artifact is its **own target**. No mega-binary of demos.
- `templates/` are never `add_subdirectory`’d.
- Fetch a **tiny, pinned** set (CPM or FetchContent): Catch2, `{fmt}`, other libraries only when an entry’s README explains why.
- `CMAKE_EXPORT_COMPILE_COMMANDS` on for clangd.

### Presets

| Preset | Purpose |
|---|---|
| `dev` | Warnings as errors (`-Wall -Wextra -Wpedantic -Werror`), `compile_commands.json` |
| `sanitize` | ASan + UBSan (and matching Clang/GCC flags) |
| `docs` | Configure only what the docs / Doxygen build needs |

Default build: `toolbox` tests + the `tutorials` group. Examples and projects behind `-DTOOLBOX_BUILD_EXAMPLES=ON`.

Until this exists, a leaf `main.cpp` must still be valid C++20 a reader can compile with a single-file command, for example:

```bash
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror main.cpp -o demo
```

## Documentation (planned)

| Tool | Role |
|---|---|
| Sphinx + MyST | Narrative book |
| Doxygen | API XML from `toolbox/` and reusable headers |
| Breathe (optionally Exhale) | API into Sphinx |
| sphinxcontrib-bibtex | Citations |
| `sphinx-build -b html` | HTML |
| `sphinx-build -b latex` + `latexmk` | PDF |

`docs/index.md` is the future Sphinx root. Generated output stays in `docs/_build/` (gitignored). CI should build HTML and PDF and fail on Sphinx warnings and on undocumented `toolbox/` parameters.

## Quality tools (planned)

- `.clang-format`, `.clang-tidy`, pre-commit
- Catch2 (or doctest) for `toolbox/` and exercise solutions
- GitHub Actions: `dev` + tests on PRs; full tree + docs on `main`

## What not to do while the spine is missing

- Do not add a second build entry point (`Makefile` at the root that becomes the real system, a `meson.build`, …).
- Do not check in generated HTML/PDF.
- Do not add heavy dependencies “to get started.”
