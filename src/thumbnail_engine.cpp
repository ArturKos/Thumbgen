#include "thumbnail_engine.h"

#include <windows.h>
#include <gdiplus.h>

#include <vector>

namespace thumbgen {

namespace {

bool find_encoder_clsid(const wchar_t* mime_type, CLSID& out) {
    UINT count = 0;
    UINT bytes = 0;
    Gdiplus::GetImageEncodersSize(&count, &bytes);
    if (bytes == 0) {
        return false;
    }

    std::vector<unsigned char> buffer(bytes);
    Gdiplus::ImageCodecInfo* encoders =
        reinterpret_cast<Gdiplus::ImageCodecInfo*>(buffer.data());
    Gdiplus::GetImageEncoders(count, bytes, encoders);

    for (UINT i = 0; i < count; ++i) {
        if (wcscmp(encoders[i].MimeType, mime_type) == 0) {
            out = encoders[i].Clsid;
            return true;
        }
    }
    return false;
}

}  // namespace

bool generate_jpeg_thumbnail(const wchar_t* source_path,
                             const wchar_t* output_path,
                             unsigned int width,
                             unsigned int height) {
    Gdiplus::Bitmap source(source_path);
    if (source.GetLastStatus() != Gdiplus::Ok) {
        return false;
    }

    Gdiplus::Image* thumbnail =
        source.GetThumbnailImage(width, height, NULL, NULL);
    if (thumbnail == NULL) {
        return false;
    }

    CLSID jpeg_clsid;
    if (!find_encoder_clsid(L"image/jpeg", jpeg_clsid)) {
        delete thumbnail;
        return false;
    }

    const Gdiplus::Status status =
        thumbnail->Save(output_path, &jpeg_clsid, NULL);
    delete thumbnail;
    return status == Gdiplus::Ok;
}

}  // namespace thumbgen
