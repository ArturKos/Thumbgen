//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabeledEdit *m;
        TCSpinEdit *szerokosc;
        TCSpinEdit *wysokosc;
        TLabel *Label1;
        TLabel *Label2;
        TDirectoryListBox *dir;
        TDriveComboBox *DriveComboBox1;
        TStatusBar *status;
        TSpeedButton *SpeedButton1;
        TCheckBox *CheckBox1;
        TImage *Image1;
        TLabel *Label3;
        TCheckBox *CheckBox2;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR  gdiplusToken;
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
