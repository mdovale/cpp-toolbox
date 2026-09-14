---
name: add-example
description: Add a complete example catalog entry (complete program under examples/topic/slug)
---

Add an **example** to cpp-toolbox.

1. Read and follow skill `add-catalog-entry` with `kind: example`.
2. Folder is `examples/<topic>/<slug>/`. `topic` must already be in `catalog.yaml` unless you add it on purpose in this change.
3. This is a complete program, not a prompt/solution pair and not a copy-out template.
4. Use any extra arguments the user typed after this command as the topic/`id`/title.
5. Finish with skill `review-catalog-entry`.
