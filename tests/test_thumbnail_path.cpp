#include "thumbnail_path.h"

#include <gtest/gtest.h>

using thumbgen::derive_thumbnail_path;

#ifdef _WIN32
constexpr const char* kSep = "\\";
#else
constexpr const char* kSep = "/";
#endif

namespace {
std::string join(std::initializer_list<const char*> parts) {
    std::string out;
    bool first = true;
    for (const char* p : parts) {
        if (!first) {
            out += kSep;
        }
        out += p;
        first = false;
    }
    return out;
}
}  // namespace

TEST(ThumbnailPath, PlacesThumbnailInSubfolderOfSourceParent) {
    const std::string source = join({"C:", "images", "vacation.jpg"});
    const std::string expected = join({"C:", "images", "thumbs", "vacation.jpg"});
    EXPECT_EQ(derive_thumbnail_path(source, "thumbs"), expected);
}

TEST(ThumbnailPath, RewritesAnyExtensionToJpg) {
    const std::string source = join({"photos", "image.png"});
    const std::string expected = join({"photos", "thumbs", "image.jpg"});
    EXPECT_EQ(derive_thumbnail_path(source, "thumbs"), expected);
}

TEST(ThumbnailPath, RewritesUppercaseExtension) {
    const std::string source = join({"photos", "image.BMP"});
    const std::string expected = join({"photos", "thumbs", "image.jpg"});
    EXPECT_EQ(derive_thumbnail_path(source, "thumbs"), expected);
}

TEST(ThumbnailPath, AppendsJpgWhenSourceHasNoExtension) {
    const std::string source = join({"photos", "image"});
    const std::string expected = join({"photos", "thumbs", "image.jpg"});
    EXPECT_EQ(derive_thumbnail_path(source, "thumbs"), expected);
}

TEST(ThumbnailPath, HandlesBareFilenameWithoutDirectory) {
    const std::string expected = join({"thumbs", "image.jpg"});
    EXPECT_EQ(derive_thumbnail_path("image.png", "thumbs"), expected);
}

TEST(ThumbnailPath, AcceptsForwardOrBackSlashesInSource) {
    EXPECT_EQ(derive_thumbnail_path("a/b/c.jpg", "t"),
              std::string("a/b") + kSep + "t" + kSep + "c.jpg");
    EXPECT_EQ(derive_thumbnail_path("a\\b\\c.jpg", "t"),
              std::string("a\\b") + kSep + "t" + kSep + "c.jpg");
}

TEST(ThumbnailPath, PreservesMultipleDotsInFilename) {
    const std::string source = join({"dir", "my.photo.jpeg"});
    const std::string expected = join({"dir", "thumbs", "my.photo.jpg"});
    EXPECT_EQ(derive_thumbnail_path(source, "thumbs"), expected);
}
