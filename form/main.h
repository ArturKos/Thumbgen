//---------------------------------------------------------------------------
// VCL form declaration for the Thumbgen Windows UI.
// This header is consumed by the Borland C++ Builder 6 IDE; the field
// names match the components declared in main.dfm.
//---------------------------------------------------------------------------
#ifndef mainH
#define mainH

#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <StdCtrls.hpp>
#include <gdiplus.h>

#include "CSPIN.h"

class TForm1 : public TForm {
__published:  // IDE-managed components
    TLabeledEdit*       outputFolderName;
    TCSpinEdit*         thumbnailWidth;
    TCSpinEdit*         thumbnailHeight;
    TLabel*             widthLabel;
    TLabel*             heightLabel;
    TDirectoryListBox*  directoryList;
    TDriveComboBox*     driveCombo;
    TStatusBar*         statusBar;
    TSpeedButton*       generateButton;
    TCheckBox*          replaceExistingCheckBox;
    TImage*             previewImage;
    TLabel*             previewLabel;
    TCheckBox*          fixNamesCheckBox;

    void __fastcall FormCreate(TObject* Sender);
    void __fastcall FormDestroy(TObject* Sender);
    void __fastcall generateButtonClick(TObject* Sender);

private:
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR                    gdiplusToken;

public:
    __fastcall TForm1(TComponent* Owner);
};

extern PACKAGE TForm1* Form1;

#endif  // mainH
