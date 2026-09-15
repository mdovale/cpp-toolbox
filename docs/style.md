# Style

C++ and prose conventions for cpp-toolbox. The constitution is `BLUEPRINT.md` at the repository root. This page is the working standard for code and the book.

## Audience

Write for a general **engineering and scientific** reader. Assume calculus, linear algebra, and some numerical methods. Do not assume a compilers course. When you mention undefined behavior, ownership, or data races, say what goes wrong in the result, not only that the standard forbids it.

## C++

- **C++20** unless the catalog row says `std: 23`.
- **C++ Core Guidelines**: RAII; no bare `new`/`delete`; non-owning views are `std::span` or `std::string_view`.
- Prefer the standard library. A third-party library is allowed when it teaches a real workflow; pin it and document *why* in the leaf README.
- `const` by default. Encode ownership in the type (`unique_ptr`, containers, views) rather than in comments alone.
- No `using namespace std;` in headers. In `main.cpp` of an example it is still discouraged.
- Headers under `toolbox/` are self-contained, `#pragma once`, and live in `include/toolbox/`.
- Name files and folders kebab-case on disk; C++ identifiers are `snake_case` functions/variables, `PascalCase` types, `kCamelCase` or `k_snake` for constexpr constants — pick `snake_case` for constexpr values unless matching a known formula (`R`, `kB`).
- Mark lesson regions for the book:

  ```cpp
  // start <id>
  // ...
  // end <id>
  ```

### Numerics

- State **units** and **dtype** (and why that dtype) in the README or in comments at the data model.
- Include a **correctness check**: residual, invariant, manufactured solution, or a property (`isfinite`, monotonicity, conservation to a stated tolerance).
- Say when a method is unstable and what the failure looks like.
- Do not hide `float` vs `double` behind a silent `typedef` without a comment.

### Comments vs README

| Put in comments | Put in README / Sphinx |
|---|---|
| This invariant, this pitfall, this line’s units | Why the method, when to use it, alternatives |
| Why a cast or a tolerance exists | Complexity, references, citations |
| Pre/postconditions on a helper | See-also links to other catalog ids |

Doxygen (`///` or `/** */`) is for `toolbox/` APIs and reusable headers, not for writing the tutorial inside a comment block.

## Prose

- American English, sentence case headings, short paragraphs.
- Use MyST in `docs/` (`{literalinclude}`, `{cite}`, math via `$$...$$` or `$...$`).
- Never paste a full program into Markdown. Include the source:

  ````markdown
  ```{literalinclude} ../../tutorials/04-the-id/main.cpp
  :language: cpp
  :start-after: // start the-id
  :end-before: // end the-id
  ```
  ````

- Cite papers with bibtex once that extension is enabled; until then, use a “References” list with full bibliographic entries.
- Solutions: Sphinx dropdown on HTML; a Solutions appendix in PDF. Do not make the solution HTML-only.

## Formatting (once the spine exists)

clang-format and clang-tidy are the mechanical style. Do not hand-format against them. Until those files exist, follow this document and keep includes ordered: corresponding header, then C++ library, then third-party, then project.
