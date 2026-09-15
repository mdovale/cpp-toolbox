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

4. **Write the leaf `README.md`**: what, when to use it, how to build, see-also. This page is included in the book.
5. **Append a row to [`catalog.yaml`](catalog.yaml).** Use an existing topic from that file, or add a topic in the same change and say why.
6. **Add a Sphinx page** under `docs/tutorials/`, `docs/how-to/`, `docs/examples/`, `docs/exercises/`, `docs/projects/`, or `docs/templates/` (filename = `id`) that `literalinclude`s the marked region (see [docs/style.md](docs/style.md)). Rebuild HTML with `sphinx-build -W -b html docs docs/_build/html`.
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

[docs/style.md](docs/style.md) covers C++ and narrative voice. Short version: RAII, no raw `new`, scientific tone, units and a correctness check on numeric work, comments for invariants and pitfalls, README for *why*.

## Catalog status

| Status | Meaning |
|---|---|
| `planned` | Row only; no folder required. Backlog. |
| `draft` | Folder exists; slice not finished. Avoid merging. |
| `complete` | Code, README, catalog, docs page all present. |

## Cursor

Slash commands (pin the kind, then follow `add-catalog-entry`). Layout of rules/skills/commands: [.cursor/README.md](.cursor/README.md).

- `/add-tutorial`, `/add-howto`, `/add-example`, `/add-exercise`, `/add-project`, `/add-template`
- `/review-entry` — completeness checklist
- `/extract-toolbox` — promote a helper after repeated copies

## Pull requests

Use the repository PR template. Title the PR with the kind and id, for example `Add tutorial 02-floating-point`. Do not change [BLUEPRINT.md](BLUEPRINT.md) in the same PR as a content entry unless the change *is* a constitutional one.

## Commits

[Conventional Commits](https://www.conventionalcommits.org/): type and imperative subject on one line (≤50 characters), body wrapped at 72 columns. See `.cursor/rules/conventional-commits.mdc`.

