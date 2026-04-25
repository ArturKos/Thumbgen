//---------------------------------------------------------------------------
// VCL form glue for Thumbgen.
//
// Walks a directory tree, filters out unsupported files using the portable
// thumbgen::is_supported_image_extension helper, and delegates each thumbnail
// generation to thumbgen::generate_jpeg_thumbnail. The form itself owns only
// UI concerns: GDI+ lifecycle, status text, preview rendering, button events.
//---------------------------------------------------------------------------
#define STRICT
#include <windows.h>
#include <gdiplus.h>
#include <vcl.h>
#pragma hdrstop

#include <string>
#include <vector>

#include "main.h"
#include "image_filter.h"
#include "thumbnail_engine.h"

#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"

TForm1* Form1;

namespace {

bool is_self_or_parent(const AnsiString& name) {
    return name == "." || name == "..";
}

bool is_image_file(const TSearchRec& entry) {
    if ((entry.Attr & faDirectory) == faDirectory) {
        return false;
    }
    return thumbgen::is_supported_image_extension(
        std::string(entry.Name.c_str()));
}

bool is_real_subdirectory(const TSearchRec& entry,
                          const AnsiString& output_subfolder) {
    if ((entry.Attr & faDirectory) != faDirectory) {
        return false;
    }
    if (is_self_or_parent(entry.Name)) {
        return false;
    }
    return entry.Name != output_subfolder;
}

void update_preview(const AnsiString& thumbnail_path) {
    if (!FileExists(thumbnail_path)) {
        return;
    }
    Gdiplus::Bitmap thumbnail(WideString(thumbnail_path).c_bstr());
    Gdiplus::Graphics canvas(Form1->previewImage->Canvas->Handle);
    canvas.DrawImage(&thumbnail, 0, 0,
                     thumbnail.GetWidth(), thumbnail.GetHeight());
    Form1->previewImage->Refresh();
}

void process_image_file(const AnsiString& parent_dir,
                        const AnsiString& filename) {
    Form1->statusBar->SimpleText = AnsiString("Processing: ") + filename;

    const AnsiString output_subfolder = Form1->outputFolderName->Text;
    const AnsiString output_dir = parent_dir + "\\" + output_subfolder;
    if (!DirectoryExists(output_dir)) {
        CreateDir(output_dir);
    }

    const AnsiString thumbnail_filename =
        StringReplace(filename, ExtractFileExt(filename), ".jpg",
                      TReplaceFlags() << rfReplaceAll);
    const AnsiString thumbnail_path = output_dir + "\\" + thumbnail_filename;
    const AnsiString source_path = parent_dir + "\\" + filename;

    if (FileExists(thumbnail_path) &&
        !Form1->replaceExistingCheckBox->Checked) {
        return;
    }

    const bool ok = thumbgen::generate_jpeg_thumbnail(
        WideString(source_path).c_bstr(),
        WideString(thumbnail_path).c_bstr(),
        static_cast<unsigned int>(Form1->thumbnailWidth->Value),
        static_cast<unsigned int>(Form1->thumbnailHeight->Value));

    if (ok) {
        update_preview(thumbnail_path);
    }
    Application->ProcessMessages();
}

void process_files_in_directory(const AnsiString& parent_dir) {
    TSearchRec entry;
    if (FindFirst(parent_dir + "\\*.*", faDirectory, entry) != 0) {
        return;
    }
    do {
        if (is_image_file(entry)) {
            process_image_file(parent_dir, entry.Name);
        }
    } while (FindNext(entry) == 0);
    FindClose(entry);
}

void collect_subdirectories(const AnsiString& parent_dir,
                            const AnsiString& output_subfolder,
                            std::vector<AnsiString>& out) {
    TSearchRec entry;
    if (FindFirst(parent_dir + "\\*.*", faDirectory, entry) != 0) {
        return;
    }
    do {
        if (is_real_subdirectory(entry, output_subfolder)) {
            out.push_back(parent_dir + "\\" + entry.Name);
            Form1->statusBar->SimpleText =
                AnsiString("Scanning: ") + entry.Name;
            Application->ProcessMessages();
        }
    } while (FindNext(entry) == 0);
    FindClose(entry);
}

void walk_directory_tree(const AnsiString& root) {
    const AnsiString output_subfolder = Form1->outputFolderName->Text;
    std::vector<AnsiString> directories;
    directories.push_back(root);

    // Index-based iteration: collect_subdirectories appends to the same
    // vector, which would invalidate iterators but not size-based indexing.
    for (std::size_t i = 0; i < directories.size(); ++i) {
        collect_subdirectories(directories[i], output_subfolder, directories);
    }
    for (std::size_t i = 0; i < directories.size(); ++i) {
        process_files_in_directory(directories[i]);
    }
    Form1->statusBar->SimpleText = "Done.";
}

}  // namespace

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {}

void __fastcall TForm1::FormCreate(TObject* Sender) {
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

void __fastcall TForm1::FormDestroy(TObject* Sender) {
    Gdiplus::GdiplusShutdown(gdiplusToken);
}

void __fastcall TForm1::generateButtonClick(TObject* Sender) {
    walk_directory_tree(directoryList->Directory);
}
