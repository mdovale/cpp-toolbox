---
name: extract-to-toolbox
description: >-
  Promotes a repeated helper into the header-only toolbox/ core and updates
  callers. Use when the same utility appears in about three catalog entries, when
  the user asks to share code across examples, or when they run /extract-toolbox.
---

# Extract to toolbox

`toolbox/` is a convenience, not a framework. Constitution: [BLUEPRINT.md](../../../BLUEPRINT.md).

## When to extract

Extract only if **all** are true:

- The same helper (timer, `require_finite`, table printer, …) exists in about **three** entries, or the user explicitly wants the extraction.
- The helper is generic (not the lesson itself).
- An entry still makes sense if a reader copies the folder **without** toolbox.

If the helper *is* the lesson, leave it in the entry.

## Procedure

1. Find every copy. Read callers so the public API matches real use.
2. Add `toolbox/include/toolbox/<name>.hpp`:
   - `#pragma once`, `#include <toolbox/name.hpp>`
   - Doxygen on every public entity
   - Inline / constexpr / header-only; no `src/` unless there is already a compiled toolbox (there is not)
3. Add a Catch2 test under `toolbox/tests/` once Catch2 exists. Until then, add a `toolbox/tests/<name>_test.cpp` that a future `add_test` can pick up, or a comment in the header’s README if a test cannot yet compile.
4. Replace copies in catalog entries with `#include <toolbox/name.hpp>`. Mention the dependency in each leaf README (“optional toolkit”).
5. Do not change catalog `id`s. Do not pull new third-party libraries into toolbox without a BLUEPRINT-level reason.

## API shape

```cpp
#pragma once

/// @file
/// @brief One-line purpose.

namespace toolbox {

/// One sentence. Units in the parameter names or in this comment.
[[nodiscard]] constexpr bool is_finite(double x) noexcept;

}  // namespace toolbox
```

Namespace is `toolbox`. No macros except include guards if `pragma once` is insufficient (it is enough).
