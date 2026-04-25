#include "image_filter.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <string>

namespace thumbgen {

namespace {

constexpr std::array<const char*, 8> kSupportedExtensions = {
    "bmp", "jpg", "jpeg", "gif", "png", "tif", "tiff", "emf",
};

std::string extension_of(const std::string& filename) {
    const std::string::size_type dot = filename.find_last_of('.');
    if (dot == std::string::npos || dot + 1 >= filename.size()) {
        return {};
    }
    std::string ext = filename.substr(dot + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return ext;
}

}  // namespace

bool is_supported_image_extension(const std::string& filename) {
    const std::string ext = extension_of(filename);
    if (ext.empty()) {
        return false;
    }
    return std::find(kSupportedExtensions.begin(), kSupportedExtensions.end(),
                     ext) != kSupportedExtensions.end();
}

}  // namespace thumbgen
