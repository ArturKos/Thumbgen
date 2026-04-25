#include "image_filter.h"

#include <gtest/gtest.h>

using thumbgen::is_supported_image_extension;

TEST(ImageFilter, RecognizesAllSupportedExtensions) {
    EXPECT_TRUE(is_supported_image_extension("photo.bmp"));
    EXPECT_TRUE(is_supported_image_extension("photo.jpg"));
    EXPECT_TRUE(is_supported_image_extension("photo.jpeg"));
    EXPECT_TRUE(is_supported_image_extension("photo.gif"));
    EXPECT_TRUE(is_supported_image_extension("photo.png"));
    EXPECT_TRUE(is_supported_image_extension("photo.tif"));
    EXPECT_TRUE(is_supported_image_extension("photo.tiff"));
    EXPECT_TRUE(is_supported_image_extension("photo.emf"));
}

TEST(ImageFilter, IsCaseInsensitive) {
    EXPECT_TRUE(is_supported_image_extension("PHOTO.JPG"));
    EXPECT_TRUE(is_supported_image_extension("Photo.Jpeg"));
    EXPECT_TRUE(is_supported_image_extension("photo.PnG"));
}

TEST(ImageFilter, RejectsUnknownExtensions) {
    EXPECT_FALSE(is_supported_image_extension("song.mp3"));
    EXPECT_FALSE(is_supported_image_extension("doc.pdf"));
    EXPECT_FALSE(is_supported_image_extension("video.mp4"));
    EXPECT_FALSE(is_supported_image_extension("archive.zip"));
}

TEST(ImageFilter, RejectsFilesWithoutExtension) {
    EXPECT_FALSE(is_supported_image_extension("README"));
    EXPECT_FALSE(is_supported_image_extension(""));
}

TEST(ImageFilter, RejectsTrailingDot) {
    EXPECT_FALSE(is_supported_image_extension("photo."));
}

TEST(ImageFilter, HandlesPathsWithMultipleDots) {
    EXPECT_TRUE(is_supported_image_extension("my.photo.collection.jpg"));
    EXPECT_FALSE(is_supported_image_extension("my.photo.collection.bak"));
}

TEST(ImageFilter, HandlesFullPaths) {
    EXPECT_TRUE(is_supported_image_extension("C:\\images\\photo.jpg"));
    EXPECT_TRUE(is_supported_image_extension("/home/user/photo.png"));
}
