---
name: onboard
description: >-
  Brief a new contributor or agent on cpp-toolbox intention, layout,
  tooling, catalog status, and the next spine item
---

Orient to cpp-toolbox. **Do not** add catalog entries, edit files, or
start `/add-tutorial` unless the user asked for that *after* the briefing.

1. Read in this order (do not skip; nested `AGENTS.md` files only if
   the user already named a kind):
   - `BLUEPRINT.md` — constitution (wins on layout and tooling)
   - `AGENTS.md` — agent map and non-negotiables
   - `CONTRIBUTING.md` — human recipe for one entry
   - `catalog.yaml` — index of record and topic vocabulary
   - `docs/learning-path.md` — tutorial spine to fill first
   - `.cursor/README.md` — rules, skills, slash commands
   - `docs/build.md` — CMake / Sphinx / CI snapshot

2. Inspect **live** state (do not hardcode counts from memory):
   - Tally `catalog.yaml` `entries` by `kind` and `status`
     (`planned` / `draft` / `complete`), and `prose` on complete rows.
   - Name the first learning-path tutorial that is not `complete`.
   - Note whether CMake, Sphinx, and CI already exist (`docs/build.md`).
   - List slash commands from `.cursor/commands/`.

3. Write a briefing with exactly these headings:

   **What this is** — catalog of copyable C++ artifacts + tiny
   `toolbox/` + Sphinx book. Audience: engineers/scientists (calculus
   and linear algebra assumed; CS degree not). Not an umbrella library,
   not a package-manager mirror, not a framework.

   **Where work goes** — kind → path table from `CONTRIBUTING.md`.
   First-level split is pedagogical role, not C++ feature. Topics are
   the controlled list in `catalog.yaml`.

   **Done means** — catalog slice: compiling C++20, comments,
   leaf `README.md`, `catalog.yaml` row (`status: complete`), docs page that
   `literalinclude`s `// start <id>` / `// end <id>`. Book chapter:
   `prose: complete` per `docs/style.md` (hypotaxis, numbered math or
   figure on spine tutorials, `{cite}`). Prefer one complete entry over
   many stubs. `templates/` are copy-out; never `add_subdirectory` them.

   **Catalog now** — counts by kind/status; tally `prose` on complete
   rows; next spine `id` and path.

   **How to work here** — `/add-tutorial` (and siblings) → skill
   `add-catalog-entry`; `/review-entry` before `status: complete` and
   before `prose: complete`; `/extract-toolbox` only after ~three copies.
   Conventional Commits (50-char subject, 72-column body). One entry
   (or one tooling slice) per change.

   **Tooling** — `cmake --preset dev` / `sanitize` / `docs`;
   `./scripts/build-docs.sh`; `pre-commit install`. Default build is
   toolbox tests + tutorials; how-tos/examples/projects need
   `-DTOOLBOX_BUILD_EXAMPLES=ON`.

   **Suggested next step** — fill the next planned spine tutorial
   unless the user named a different task. Extra arguments after this
   command are the user’s intended first task (kind, `id`, or question).

4. Stop. Ask what they want to do next. Offer the matching `/`
   command; do not run it unprompted.
