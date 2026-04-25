#ifndef THUMBGEN_THUMBNAIL_PATH_H
#define THUMBGEN_THUMBNAIL_PATH_H

#include <string>

namespace thumbgen {

/**
 * @brief Build the output path for a thumbnail derived from a source image.
 *
 * The thumbnail file is placed in @p output_subfolder under the directory of
 * @p source_path, and its extension is rewritten to ".jpg" because all
 * thumbnails are JPEG-encoded.
 *
 * @param source_path        Full path to the original image, with native
 *                           separators ('\\' on Windows, '/' elsewhere).
 * @param output_subfolder   Name of the per-directory output folder
 *                           (e.g. "thumbnails"). Must not contain separators.
 * @return Full path to the would-be thumbnail file.
 */
std::string derive_thumbnail_path(const std::string& source_path,
                                  const std::string& output_subfolder);

}  // namespace thumbgen

#endif  // THUMBGEN_THUMBNAIL_PATH_H
