---
name: add-template
description: Add a copy-out project template under templates/ (not built in-tree)
---

Add a **copy-out template** to cpp-toolbox.

1. Read and follow skill `add-catalog-entry` with `kind: template`.
2. Folder is `templates/<slug>/`. Do **not** wire it into the CMake superbuild.
3. Document how a reader copies it out and what they get (CMake, tests, sanitizers, …).
4. Do not overwrite `templates/catalog-entry/` unless the user is changing the in-tree cookie on purpose.
5. Use any extra arguments the user typed after this command as the `id`/title.
6. Finish with skill `review-catalog-entry`.
