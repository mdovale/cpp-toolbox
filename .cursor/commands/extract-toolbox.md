---
name: extract-toolbox
description: Promote a repeated helper into toolbox/ and update callers
---

Extract a repeated helper into `toolbox/`.

1. Read and follow skill `extract-to-toolbox`.
2. If the user named a helper or files after this command, start there; otherwise search for the duplicated utility in the conversation or working tree.
3. Do not extract if the helper *is* the lesson or has fewer than about three copies unless the user insisted.
4. Keep entries readable without toolbox (document the include as optional).
