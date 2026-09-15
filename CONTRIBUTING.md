# Contributing

Thank you for adding to cpp-toolbox. The constitution is [BLUEPRINT.md](BLUEPRINT.md). This page is the **recipe for one catalog entry**. Agents follow the same recipe via the `add-catalog-entry` skill.

## What we accept

One change should be either:

- a slice of the **build/docs spine** (CMake, Sphinx, formatters), or
- **one catalog entry** of a single `kind`, complete enough to mark `status: complete`.

Do not open a PR that only adds a `.cpp` with a promise to document it later.

## Add an entry (about ten minutes of structure)

1. **Pick the kind and slug.** Kinds: `tutorial`, `how-to`, `example`, `exercise`, `project`, `template`. The folder slug is kebab-case and equal to `id` (tutorials also get a `NN-` prefix for order).
2. **Copy** [`templates/catalog-entry/`](templates/catalog-entry/) into the path from the table below. For exercises, copy it twice: once to `starter/` and once to `solution/`, and add `prompt.md`.
3. **Write the code** (C++20, see [docs/style.md](docs/style.md)). Mark include regions:

   ```cpp
   // start <id>
   // ...
   // end <id>
   ```

4. **Write the leaf `README.md`**: what, when to use it, how to build, see-also. This is the lab card, not the chapter.
5. **Append a row to [`catalog.yaml`](catalog.yaml).** Use an existing topic from that file, or add a topic in the same change and say why. Set `prose: draft` until the Sphinx page meets [docs/style.md](docs/style.md).
6. **Add a Sphinx page** under `docs/tutorials/`, `docs/how-to/`, `docs/examples/`, `docs/exercises/`, `docs/projects/`, or `docs/templates/` (filename = `id`) that `literalinclude`s the marked region (see [docs/style.md](docs/style.md)). Cite with `{cite}` from [docs/refs.bib](docs/refs.bib). Rebuild with `./scripts/build-docs.sh` and, when TeX is available, `./scripts/build-docs.sh --pdf`.
7. **Build and sanity-check:** `cmake --preset dev --target <id>` then `ctest --preset dev` if you added tests. Repeat with the `sanitize` preset. The leaf must still compile by hand as `c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror main.cpp`.

### Where it goes

| Kind | Path |
|---|---|
| Tutorial | `tutorials/NN-slug/` |
| How-to | `how-to/slug/` |
| Example | `examples/<topic>/slug/` |
| Exercise | `exercises/<topic>/slug/{prompt.md,starter/,solution/}` |
| Project | `projects/slug/` |
| Template | `templates/slug/` (copy-out; not built in-tree) |

`starter/` must compile. Solutions stay out of the prompt.

## Style

[docs/style.md](docs/style.md) covers C++ and narrative voice. The leaf README
is a lab card; the Sphinx page is the chapter. Spine tutorials need a numbered
equation or figure and `{cite}` keys from [docs/refs.bib](docs/refs.bib).
Format C++ with clang-format; `pre-commit install` after cloning.

## Catalog status

| Field | Values | Meaning |
|---|---|---|
| `status` | `planned` | Row only; no folder required. Backlog. |
| `status` | `draft` | Folder exists; slice not finished. Avoid merging. |
| `status` | `complete` | Code, README, catalog, docs page all present. |
| `prose` | `draft` | Chapter does not yet meet `docs/style.md`. Omit on `planned`. |
| `prose` | `complete` | Voice, numbered math or figure, and `{cite}` are green. |

## Cursor

Slash commands. Layout of rules/skills/commands: [.cursor/README.md](.cursor/README.md).

- `/onboard` — intention, layout, catalog status, and next work
- `/add-tutorial`, `/add-howto`, `/add-example`, `/add-exercise`, `/add-project`, `/add-template` (pin the kind, then follow `add-catalog-entry`)
- `/review-entry` — completeness checklist
- `/extract-toolbox` — promote a helper after repeated copies

## Pull requests

Use the repository PR template. Title the PR with the kind and id, for example `Add tutorial 02-floating-point`. Do not change [BLUEPRINT.md](BLUEPRINT.md) in the same PR as a content entry unless the change *is* a constitutional one.

## Commits

[Conventional Commits](https://www.conventionalcommits.org/): type and imperative subject on one line (≤50 characters), body wrapped at 72 columns. See `.cursor/rules/conventional-commits.mdc`.
