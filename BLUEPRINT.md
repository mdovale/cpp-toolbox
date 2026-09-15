# Blueprint

This file is the constitution of **cpp-toolbox**. If another document disagrees with it, this one wins. Update it when we change intention, layout, or tooling — not to record day-to-day content.

## Intention

cpp-toolbox is a **catalog of independently compilable C++ artifacts** plus a **small shared toolkit** and a **book-quality documentation set**.

It holds:

- **Tutorials** — a taught sequence. Read in order.
- **How-tos** — task-oriented recipes. Not sequential.
- **Examples** — complete, commented programs that illustrate a technique.
- **Exercises** — a problem first; a starter that compiles; a solution apart from the prompt.
- **Mini-projects** — small end-to-end programs a working engineer could extend.
- **Reusable templates** — starters you copy *out* of this repo to begin a real project.

The code is **modern C++**, follows established best practice, and is documented well enough to build into **HTML and PDF**. The audience is **general engineering and scientific**: calculus, linear algebra, and some numerical methods are assumed; a computer-science degree is not.

## What this is not

- Not a single umbrella library that examples must link against.
- Not a package-manager mirror of scientific C++ (Eigen, PETSc, Kokkos, …).
- Not a contest dump of clever snippets without a learning path.
- Not a framework. If `toolbox/` starts to dictate how examples are written, it has grown too large.

## Design principles

1. **A reader can copy one folder and understand it.** Shared code is a convenience, not a requirement.
2. **One catalog, one book.** If it is not in `catalog.yaml`, it is not a first-class entry.
3. **Docs and code cannot drift.** Narrative pages include real source with Sphinx `literalinclude` (or the equivalent). Do not paste a second copy of the program into Markdown.
4. **Vertical slices.** An entry ships as code + comments + leaf `README.md` + catalog row + docs page in the same change. “I’ll document it later” is not acceptable.
5. **Teach by existing.** Sanitizers, tests, `span`/`string_view`, and honest numerics are part of the lesson, not an appendix.
6. **Extract under pressure.** Start examples self-contained. Promote a helper into `toolbox/` only after it has been copied about three times.
7. **C++20 is the floor.** Opt into C++23 per entry when the lesson needs it. Do not require C++26.

## Layout

```text
cpp-toolbox/
  BLUEPRINT.md                 # this file — constitution
  README.md                  # people arriving at the repo
  AGENTS.md                  # map for coding agents
  CONTRIBUTING.md            # how to add an entry
  LICENSE                    # BSD 3-Clause
  catalog.yaml               # single source of truth for the index
  .gitignore
  cmake/                     # CMake modules (warnings, sanitizers, helpers)
  toolbox/                   # small header-only core + its tests
  tutorials/                 # NN-slug/ — taught sequence
  how-to/                    # kebab-case/ — task recipes
  examples/<topic>/<slug>/  # complete programs
  exercises/<topic>/<slug>/ # prompt + starter/ + solution/
  projects/<slug>/           # mini-projects
  templates/                 # copy-out starters; not built in-tree
    catalog-entry/           # shape used when adding a new entry
  docs/
    conf.py                    # planned Sphinx config
    index.md
    tutorials/                # one page per tutorial id
    how-to/
    examples/
    exercises/
    projects/
    templates/
  .cursor/                   # rules, skills, slash commands
  .github/                   # PR template (vertical-slice checklist)
```

**First-level split is pedagogical role, not C++ feature.** Topic (`numerics`, `io`, …) lives one level down. Engineers looking for “how do I time a kernel?” should not hunt through a `std::chrono` tutorial.

| Kind | Path | Folder name | Built in-tree? |
|---|---|---|---|
| Tutorial | `tutorials/NN-slug/` | two-digit order prefix | yes |
| How-to | `how-to/slug/` | kebab-case | yes |
| Example | `examples/<topic>/slug/` | kebab-case | yes |
| Exercise | `exercises/<topic>/slug/` | kebab-case | yes (starter and solution) |
| Project | `projects/slug/` | kebab-case | yes |
| Template | `templates/slug/` | kebab-case | **no** — copy out |
| Toolkit | `toolbox/` | headers under `include/toolbox/` | yes |

Leaf folders that compile in-tree contain at least:

| File | Role |
|---|---|
| `main.cpp` and/or headers | The thing people copy |
| `README.md` | One page: what, when, how to build, see-also. Sphinx includes this. |
| `CMakeLists.txt` | Only if the entry has extra dependencies; otherwise the root helper registers it |

Exercises additionally contain `prompt.md` (or the prompt in `README.md`), `starter/`, and `solution/`. `starter/` must compile.

Templates (`templates/app`, `templates/header-only-lib`, …) are **not** `add_subdirectory`’d into the superbuild.

## Catalog

`catalog.yaml` is the index that CMake, Sphinx, and the README table all follow.

Required fields per entry:

| Field | Meaning |
|---|---|
| `id` | Unique kebab-case id; matches the folder slug (not the `NN-` prefix) |
| `kind` | `tutorial` \| `how-to` \| `example` \| `exercise` \| `project` \| `template` |
| `topic` | Controlled vocabulary in `catalog.yaml` |
| `difficulty` | Integer 1–5 (1 = intro, 3 = needs numerical care, 5 = project-scale) |
| `std` | `20` or `23` |
| `tags` | List of lowercase kebab-case tags |
| `title` | Human title, sentence case |
| `path` | Repo-relative directory |
| `status` | `planned` \| `draft` \| `complete` |

An entry is `complete` only when code, comments, leaf README, catalog row, and docs page all exist. Planned rows may exist without a folder; they are the backlog.

## Documentation

**Sphinx + MyST** is the narrative system (tutorials, how-tos, math, citations). **Doxygen** extracts APIs from `toolbox/` and from reusable headers. **Breathe** (optionally Exhale) joins the two. **sphinxcontrib-bibtex** covers papers. HTML and PDF come from the same tree (`sphinx-build -b html` and `-b latex` + `latexmk`).

Contract:

- **Comments in code** explain this line, this invariant, this numerical pitfall.
- **Leaf README + Sphinx pages** explain why, when to use it, alternatives, complexity, and caveats.
- **Doxygen** is for `toolbox/` and reusable headers, not for dumping a tutorial into `/** */`.

Mark regions for inclusion:

```cpp
// start kahan
// ... the lesson ...
// end kahan
```

Sphinx pages use `literalinclude` with `:start-after:` / `:end-before:`. Solutions may be a Sphinx dropdown in HTML and a “Solutions” appendix in PDF — never HTML-only.

Audience tone: explain ownership, UB, and lifetime the way we explain stiffness or conditioning: as things that make results silently wrong.

## C++ bar

- C++ Core Guidelines as the north star: RAII, no bare `new`/`delete`, non-owning views are `std::span` / `std::string_view`.
- Warnings as errors in the `dev` preset; ASan/UBSan in the `sanitize` preset.
- clang-format and clang-tidy in pre-commit and CI, once those files exist.
- Numeric examples state **units, dtype, and a correctness check** (residual, invariant, or property).
- Prefer the standard library. Add a dependency only when it teaches a real workflow, pin it, and document *why* it is here.
- Tests: Catch2 (or doctest) for `toolbox/` and for exercise solutions. Tutorials may `assert` in `main`.

## Tooling

### Now (this revision)

Constitution, catalog, directory tree, Cursor rules/skills/commands, a **CMake spine**, **Sphinx HTML and PDF**, and Doxygen/Breathe for `toolbox/`. Do not invent a second layout or a second docs stack.

### Next (formatters, then content)

1. clang-format and clang-tidy.
2. Content along `docs/learning-path.md` (start with `build-and-ub`).

Presets: `dev` (warnings as errors, `compile_commands.json`), `sanitize` (ASan/UBSan), `docs`.

Dependencies stay tiny and pinned (CPM or FetchContent): `{fmt}`, Catch2, Eigen only when an entry needs it. We are not a vcpkg catalog.

Default configure builds `toolbox` tests and the `tutorials` group. Examples and projects are `-DTOOLBOX_BUILD_EXAMPLES=ON` so day-to-day iteration stays fast.

### Cursor

| Mechanism | Role |
|---|---|
| `AGENTS.md` | Map: where things live, what “done” means |
| `.cursor/rules/` | Persistent constraints (C++, docs, numerics, CMake) |
| `.cursor/skills/` | Procedures (add an entry, extract to toolbox, write docs, review) |
| `.cursor/commands/` | Explicit `/` shortcuts that pin a kind and call the matching skill |

## How the repo grows

- Grow along the **learning-path spine** (`docs/learning-path.md`) before filling a zoo of disconnected examples.
- One PR or session = one complete catalog entry (or a slice of the build/docs spine).
- Batch by topic (a week of numerics, a week of I/O), not by mixing “move semantics” with “HDF5 layout”.
- Third copy of a helper → `toolbox/`, then update the older copies.
- Topics are a **controlled vocabulary** listed in `catalog.yaml`. Propose a new topic in the same change that needs it; do not silently invent one.

## Decision log

| Decision | Choice | Why |
|---|---|---|
| Docs stack | Sphinx + MyST + Doxygen + Breathe | HTML and PDF, math, citations, `literalinclude` |
| C++ floor | C++20 | Ranges, `span`, concepts; still realistic in labs |
| Catalog | `catalog.yaml` | One index for CMake, Sphinx, and humans |
| Shared code | Tiny header-only `toolbox/` | Copyable folders; extract under pressure |
| Templates | Copy-out, not in the superbuild | Starters are not examples |
| First-level dirs | Pedagogical kind | Matches how engineers look things up |
