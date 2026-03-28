# Thumbgen

A Windows desktop application for **batch thumbnail generation** built with **C++ Builder 6** and **GDI+**, supporting recursive directory traversal and JPEG output.

![C++](https://img.shields.io/badge/C%2B%2B-Builder%206-blue)
![GDI+](https://img.shields.io/badge/GDI%2B-Graphics-purple)
![Windows](https://img.shields.io/badge/Platform-Windows-0078D6)

## Features

- **Batch thumbnail generation** -- processes entire directory trees of images in one operation
- **Recursive directory traversal** -- scans all subdirectories using an iterative BFS approach with a `std::vector` queue
- **Configurable thumbnail size** -- user-adjustable width and height via spin controls
- **Multiple input formats** -- supports BMP, JPG, JPEG, GIF, TIFF, TIF, PNG, and EMF source images
- **JPEG output** -- all thumbnails are saved as JPEG files using GDI+ image encoders
- **Dedicated output folder** -- creates a named subfolder (default "miniatury") in each processed directory
- **Overwrite control** -- optional checkbox to replace existing thumbnails or skip already-generated files
- **Live preview** -- displays each thumbnail in real-time on the form as it is generated
- **Directory and drive selection** -- built-in `TDirectoryListBox` and `TDriveComboBox` for source selection
- **Status bar feedback** -- shows the currently processed filename during generation

## Dependencies

| Component | Purpose |
|-----------|---------|
| C++ Builder 6 | IDE, VCL framework, and compiler |
| GDI+ | Image loading, resizing, and JPEG encoding |
| Windows SDK | GDI+ headers and libraries |

## Building

1. Open `Thumbgen.bpr` in **C++ Builder 6**.
2. Ensure the GDI+ headers (`gdiplus.h`) are accessible via the include path.
3. Press **F9** to build and run.

## Usage

1. Select the **drive** and **directory** containing images.
2. Set the desired **thumbnail width** and **height** (default: 100x100 pixels).
3. Optionally set a custom **output folder name** (default: `miniatury`).
4. Check **"Replace existing thumbnails"** if you want to regenerate all.
5. Click **"Generuj"** (Generate) to start batch processing.

Thumbnails are saved into a subfolder within each processed directory. The application processes all subdirectories recursively.

## Supported Input Formats

| Extension | Format |
|-----------|--------|
| `.bmp` | Windows Bitmap |
| `.jpg` / `.jpeg` | JPEG |
| `.gif` | GIF |
| `.png` | Portable Network Graphics |
| `.tiff` / `.tif` | Tagged Image File Format |
| `.emf` | Enhanced Metafile |

## Project Structure

```
Thumbgen/
├── Thumbgen.cpp      # Application entry point (WinMain)
├── Thumbgen.bpr      # C++ Builder 6 project file
├── Thumbgen.res      # Compiled resource file
├── main.cpp          # Core logic: GDI+ thumbnail generation, recursive traversal
├── main.h            # TForm1 class declaration with UI components
├── main.dfm          # Form layout (directory browser, spin edits, preview)
└── main.ddp          # Diagram file
```

## License

This project is provided as-is for educational purposes.
