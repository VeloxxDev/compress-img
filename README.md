Image Compression — ENSICAEN
=============================

Overview
--------

This project implements RGB histogram computation, popularity-based color quantification, and pixel mapping to a reduced color palette. It demonstrates algorithmic rigor, memory-safe C programming, and clear documentation practices.

Main Objectives:
- Compute RGB histograms from PPM images
- Perform color quantification using the popularity algorithm
- Map image pixels to the most frequent colors
- Generate quantified output images with statistics

Key Features:
- 256×256 histogram structure for 2D color tracking (Red-Green channels)
- Linked-list based color frequency tracking
- Euclidean distance color mapping
- Unit tests with minunit framework
- Full Doxygen documentation support

Project tree
```
compress-img/
├── README.md
├── Doxyfile
├── Makefile
├── include/
│   ├── histo.h
│   ├── image.h
│   ├── minunit.h
│   └── quantification.h
├── src/
│   ├── main.c
│   ├── histo.c
│   ├── image.c
│   ├── quantification.c
│   └── ppmhist.c
└── tests/
    └── test_histo.c
```

Getting Started
===============

Build the project
-----------------

To compile all binaries (main program and utilities):

```bash
make main
make ppmhist
```

The compiled binaries will be in the current directory: `main` and `ppmhist`.

Usage
-----

### Main program - Image compression with quantification

```bash
./main K input.ppm
```

This will:
1. Load the image from `input.ppm` (PPM/PGM format)
2. Compute RGB histograms
3. Perform color quantification (K most frequent colors)
4. Map pixels to the reduced palette
5. Save the output as `output.ppm`

### PPM histogram viewer

```bash
./ppmhist input.ppm
```

Displays histogram statistics for the input image.

Generate and view documentation
-------------------------------

Generate Doxygen documentation (requires Doxygen):

```bash
make doc
```

This creates HTML documentation in the `doc/` directory. Open the documentation in your browser:

```bash
cd doc/html
open index.html    # macOS
xdg-open index.html  # Linux
start index.html   # Windows
```

Clean up build artifacts
------------------------

Clean object files and executables:

```bash
make clean
```

Clean everything including generated documentation:

```bash
make docclean
```

Or clean both:

```bash
make clean
make docclean
```

Unit tests
----------

Build and run unit tests:

```bash
make tests
```

This compiles and runs histogram tests using the minunit framework.

Dependencies
-------------

- **C Standard Library** (stdio, stdlib, string)
- **Doxygen** (optional, for documentation generation)
- **Make** (build system)

Requirements
-----------

- GCC or Clang compiler with C99 support
- POSIX-compatible environment (Linux, macOS, WSL)
- PPM/PGM image files in 8-bit format

Contact & Support
-----------------

For questions or issues, contact the project authors or review the Doxygen documentation.

Authors
-------

- **Yann Moulin** — ENSICAEN, Class of 2028
- **Iwan Clemente** — ENSICAEN, Class of 2028

License
-------

Academic project — not intended for public distribution without written permission from the authors.

