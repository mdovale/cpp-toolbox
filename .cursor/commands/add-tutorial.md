---
name: add-tutorial
description: Add a complete tutorial catalog entry (taught sequence, NN-slug folder)
---

Add a **tutorial** to cpp-toolbox.

1. Read and follow skill `add-catalog-entry` with `kind: tutorial`.
2. Prefer filling the next `status: planned` spine row in `docs/learning-path.md` / `catalog.yaml` unless the user named a different `id`.
3. Folder is `tutorials/NN-slug/` with `id` equal to `slug`.
4. Use any extra arguments the user typed after this command as the topic/`id`/title.
5. Finish with skill `review-catalog-entry`.
