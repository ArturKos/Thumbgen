#ifndef THUMBGEN_THUMBNAIL_ENGINE_H
#define THUMBGEN_THUMBNAIL_ENGINE_H

namespace thumbgen {

/**
 * @brief Decode an image file, resize it to a thumbnail, and save as JPEG.
 *
 * Wraps the GDI+ Bitmap loader and the JPEG encoder. Windows-only — the
 * caller must have initialized the GDI+ runtime via Gdiplus::GdiplusStartup
 * before the first call and shut it down with Gdiplus::GdiplusShutdown
 * before process exit.
 *
 * @param source_path Full UTF-16 path to the source image.
 * @param output_path Full UTF-16 path where the JPEG thumbnail is written.
 *                    The parent directory must already exist.
 * @param width       Target thumbnail width in pixels.
 * @param height      Target thumbnail height in pixels.
 * @return true on success, false on decode, encode, or I/O failure.
 */
bool generate_jpeg_thumbnail(const wchar_t* source_path,
                             const wchar_t* output_path,
                             unsigned int width,
                             unsigned int height);

}  // namespace thumbgen

#endif  // THUMBGEN_THUMBNAIL_ENGINE_H
