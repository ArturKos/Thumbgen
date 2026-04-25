# Thumbgen

A small Windows utility that walks a directory tree and generates JPEG
thumbnails for every recognized image file it finds, dropping each one into a
per-directory output folder. The original UI is implemented in Borland C++
Builder 6 (VCL); this repository pairs that legacy Windows shell with a
portable, unit-tested C++ core.

![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)
![CMake](https://img.shields.io/badge/build-CMake%203.14%2B-064F8C)
![GoogleTest](https://img.shields.io/badge/tests-GoogleTest-yellow)
![Doxygen](https://img.shields.io/badge/docs-Doxygen-2C4AA8)

## Why this is interesting

- **Clean separation of concerns.** The pure logic (extension whitelist,
  output-path derivation) lives in a portable static library that has no
  dependency on Windows, GDI+, or the VCL framework. The Windows UI is a
  thin shell on top of it.
- **Two parallel build paths.** The portable core builds and tests with
  CMake on any platform, while the Windows executable is still buildable
  with the original Borland C++ Builder 6 project file (`Thumbgen.bpr`).
- **Hermetic unit tests.** The portable core is exercised by GoogleTest
  cases that cover extension matching, case-insensitivity, multi-dot
  filenames, mixed separators, and missing extensions — none of which
  require a filesystem or a Windows runtime.
- **Small, deliberate Doxygen surface.** Only the public API (`include/`)
  is documented; internal helpers stay anonymous and self-named.

## Building and running

### Portable core + tests (Linux, macOS, Windows)

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

This builds the `thumbgen_core` static library and the `thumbgen_tests`
GoogleTest executable. On Windows it additionally builds the
`thumbgen_engine` static library that links against GDI+.

### Windows GUI executable (Borland C++ Builder 6)

1. Open `Thumbgen.bpr` in C++ Builder 6.
2. The project's include path is configured for `include/` and `form/`.
3. Press **F9** to build and run.

The resulting `Thumbgen.exe` is the GUI shell: drive picker, directory
list, width/height spinners, output-folder name, and a *Generate* button.

### API documentation

```sh
doxygen docs/Doxyfile
# Output: docs/build/html/index.html
```

## Project layout

```
Thumbgen/
├── CMakeLists.txt              CMake build for portable core and tests
├── include/                    Public headers (Doxygen-annotated)
│   ├── image_filter.h          Supported-extension predicate
│   ├── thumbnail_path.h        Output-path derivation
│   └── thumbnail_engine.h      GDI+ JPEG encoder wrapper (Windows-only)
├── src/                        Implementations
│   ├── image_filter.cpp        Portable
│   ├── thumbnail_path.cpp      Portable
│   ├── thumbnail_engine.cpp    Windows / GDI+
│   └── main.cpp                VCL form glue (Windows-only)
├── tests/                      GoogleTest suites for the portable core
│   ├── test_image_filter.cpp
│   └── test_thumbnail_path.cpp
├── form/                       VCL form artifacts (Windows-only)
│   ├── main.h                  TForm1 declaration
│   ├── main.dfm                Form layout
│   └── main.ddp                C++ Builder diagram metadata
├── docs/Doxyfile               Doxygen configuration
├── Thumbgen.bpr                C++ Builder 6 project file
├── Thumbgen.cpp                WinMain entry point
└── Thumbgen.res                Compiled Win32 resources
```

## Supported input formats

`bmp`, `jpg`, `jpeg`, `gif`, `png`, `tif`, `tiff`, `emf` (case-insensitive).
Output is always JPEG.

## License

Provided as-is for educational and portfolio purposes.
