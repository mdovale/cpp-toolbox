# Documentation

This directory becomes the **Sphinx book** (HTML and PDF). Until the build spine exists ([build.md](build.md)), these pages are the narrative source we will wire up.

| File | Role |
|---|---|
| [index.md](index.md) | Book landing page (future Sphinx root) |
| [learning-path.md](learning-path.md) | Order we fill tutorials first |
| [style.md](style.md) | C++ and prose conventions |
| [build.md](build.md) | CMake, Sphinx, Doxygen, presets |

## Catalog pages

One Markdown file per catalog `id`. They `literalinclude` the matching sources. Do not paste programs here.

| Kind | Directory |
|---|---|
| Tutorial | [tutorials/](tutorials/) |
| How-to | [how-to/](how-to/) |
| Example | [examples/](examples/) |
| Exercise | [exercises/](exercises/) |
| Project | [projects/](projects/) |
| Template | [templates/](templates/) |

Leaf `README.md` files next to code are also part of the book.

Constitution: [../BLUEPRINT.md](../BLUEPRINT.md). How to add a page as part of an entry: [../CONTRIBUTING.md](../CONTRIBUTING.md).
