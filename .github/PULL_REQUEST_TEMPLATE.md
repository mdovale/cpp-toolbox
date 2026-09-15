## Kind of change

- [ ] Build/docs spine (CMake, Sphinx, formatters) — no incomplete catalog entry mixed in
- [ ] One catalog entry (vertical slice)
- [ ] Constitutional (`BLUEPRINT.md`, catalog schema, layout) — described below

**Catalog `id` / kind** (if an entry):

## Slice checklist (entries)

- [ ] Folder lives under the correct kind (`tutorials/`, `how-to/`, `examples/`, `exercises/`, `projects/`, `templates/`)
- [ ] `catalog.yaml` row; `status: complete` only if the rest of this list is true
- [ ] `prose: complete` only if the Sphinx page meets `docs/style.md` (hypotaxis, numbered math or figure on spine tutorials, `{cite}`)
- [ ] Compiling C++20 (exercise: `starter/` and `solution/` both compile)
- [ ] `// start <id>` / `// end <id>` markers for docs includes
- [ ] Leaf `README.md` (what, when, build, see-also)
- [ ] Docs page that `literalinclude`s the code (not a pasted copy)
- [ ] Numerics: units, dtype, correctness check (if applicable)
- [ ] No new `toolbox/` API unless this is the third extraction (see BLUEPRINT)

## Notes
