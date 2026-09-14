# File templates for a catalog entry

## catalog.yaml row

```yaml
  - id: the-id
    kind: tutorial   # tutorial | how-to | example | exercise | project | template
    topic: numerics  # must be in catalog.yaml topics
    difficulty: 2
    std: 20
    tags: [floating-point]
    title: Sentence-case title
    path: tutorials/04-the-id
    status: complete
```

## Leaf README.md

Use this shape (fence the build command as a bash block in the real file):

- Title, then one paragraph: what this is and **when to use it**.
- **Build**: once CMake exists, `cmake --preset dev --target the-id`. Until then: `c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror main.cpp -o the-id`
- **Notes**: units, dtype, correctness check (numeric entries). Pitfalls.
- **See also**: other catalog ids and why the reader would open them.

## docs page

Create `docs/tutorials/<id>.md`, `docs/how-to/<id>.md`, `docs/examples/<id>.md`, `docs/exercises/<id>.md`, `docs/projects/<id>.md`, or `docs/templates/<id>.md`.

Relative `literalinclude` from `docs/tutorials/the-id.md` to a spine tutorial:

```text
{literalinclude} ../../tutorials/04-the-id/main.cpp
:language: cpp
:start-after: // start the-id
:end-before: // end the-id
```

Wrap that in a MyST code fence (triple backticks, then `{literalinclude} ...`). Add **When this fails** and **References** (full bibliographic entries until bibtex is enabled).

## Exercise prompt.md

- **Problem**: what to implement. No solution text.
- **Constraints**: C++20, stated units, a correctness check.
- **Starter**: build `starter/`. Do not look at `solution/` until they have tried.

## main.cpp markers

```cpp
#include <cstdlib>

// start the-id
int main() {
  return EXIT_SUCCESS;
}
// end the-id
```
