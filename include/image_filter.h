#ifndef THUMBGEN_IMAGE_FILTER_H
#define THUMBGEN_IMAGE_FILTER_H

#include <string>

namespace thumbgen {

/**
 * @brief Test whether a filename has an extension recognized as a supported
 *        raster image source.
 *
 * The comparison is case-insensitive and operates on the substring after the
 * final dot. Filenames without a dot, or with no characters after the final
 * dot, are not supported.
 *
 * Recognized extensions: bmp, jpg, jpeg, gif, png, tif, tiff, emf.
 *
 * @param filename Source filename or full path.
 * @return true if the extension matches a supported image format.
 */
bool is_supported_image_extension(const std::string& filename);

}  // namespace thumbgen

#endif  // THUMBGEN_IMAGE_FILTER_H
