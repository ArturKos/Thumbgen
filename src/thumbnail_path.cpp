#include "thumbnail_path.h"

#include <string>

namespace thumbgen {

namespace {

#ifdef _WIN32
constexpr char kPathSeparator = '\\';
#else
constexpr char kPathSeparator = '/';
#endif

std::string::size_type find_last_separator(const std::string& path) {
    return path.find_last_of("/\\");
}

std::string replace_extension_with_jpg(const std::string& filename) {
    const std::string::size_type dot = filename.find_last_of('.');
    if (dot == std::string::npos) {
        return filename + ".jpg";
    }
    return filename.substr(0, dot) + ".jpg";
}

}  // namespace

std::string derive_thumbnail_path(const std::string& source_path,
                                  const std::string& output_subfolder) {
    const std::string::size_type sep = find_last_separator(source_path);
    const std::string parent =
        (sep == std::string::npos) ? std::string() : source_path.substr(0, sep);
    const std::string filename =
        (sep == std::string::npos) ? source_path : source_path.substr(sep + 1);

    const std::string thumbnail_name = replace_extension_with_jpg(filename);

    if (parent.empty()) {
        return output_subfolder + kPathSeparator + thumbnail_name;
    }
    return parent + kPathSeparator + output_subfolder + kPathSeparator +
           thumbnail_name;
}

}  // namespace thumbgen
