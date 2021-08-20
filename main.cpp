//---------------------------------------------------------------------------
#define STRICT
#include <windows.h>
#include <algorithm>
#include <Jpeg.hpp>
#include <vector>
using std::min;
using std::max;
#include <gdiplus.h>
#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
using namespace Gdiplus;
TForm1 *Form1;

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
  unsigned int  num = 0;    // number of image encoders
  unsigned int  size = 0;   // size of the image encoder array in bytes
  
  Gdiplus::GetImageEncodersSize(&num, &size);
  if(size == 0)return -1;
  
  Gdiplus::ImageCodecInfo* imageCodecInfo = new Gdiplus::ImageCodecInfo[size];
  Gdiplus::GetImageEncoders(num, size, imageCodecInfo);
  
  for(unsigned int i = 0; i < num; ++i)
  {
    if( wcscmp(imageCodecInfo[i].MimeType, format) == 0 )
    {
       *pClsid = imageCodecInfo[i].Clsid;
       delete[] imageCodecInfo;
       return i;
    }    
  }
  delete[] imageCodecInfo;
  return -1;
}

void oPliki(AnsiString Nazwa_Katalogu)
{
  TSearchRec sr;
         if(FindFirst(Nazwa_Katalogu+"\\*.*",faDirectory, sr)==0)
           {
              if(((sr.Attr & faDirectory) != faDirectory)&&(sr.Name!=".")&&(sr.Name!="..")&&
                 ((UpperCase (ExtractFileExt (sr. Name))==".BMP")||
                  (UpperCase (ExtractFileExt (sr. Name))==".JPG")||
                  (UpperCase (ExtractFileExt (sr. Name))==".JPEG")||
                  (UpperCase (ExtractFileExt (sr. Name))==".GIF")||
                  (UpperCase (ExtractFileExt (sr. Name))==".BMP")||
                  (UpperCase (ExtractFileExt (sr. Name))==".TIFF")||
                  (UpperCase (ExtractFileExt (sr. Name))==".PNG")||
                  (UpperCase (ExtractFileExt (sr. Name))==".EMF")||
                  (UpperCase (ExtractFileExt (sr. Name))==".TIF")) )
               {
           if(Form1->CheckBox2->Checked)
            {
             /*AnsiString buf = sr.Name;
             fixname(&sr.Name);
             if(buf!=sr.Name)
             RenameFile(Nazwa_Katalogu+"\\"+buf,Nazwa_Katalogu+"\\"+sr.Name);  */
            }
            Form1->status->SimpleText = "Przetwarzam: "+sr.Name;
            if (!DirectoryExists(Nazwa_Katalogu+"\\"+Form1->m->Text))
             CreateDir(Nazwa_Katalogu+"\\"+Form1->m->Text);

            if(!FileExists(Nazwa_Katalogu+"\\"+Form1->m->Text+"\\"+sr.Name)||(Form1->CheckBox1->Checked)){
             Gdiplus::Bitmap image(WideString(Nazwa_Katalogu+"\\"+sr.Name).c_bstr());
             Gdiplus::Image* Thumbnail = image.GetThumbnailImage(Form1->szerokosc->Value, Form1->wysokosc->Value, NULL, NULL);
             Gdiplus::Graphics grphx(Form1->Image1->Canvas->Handle);
             grphx.DrawImage(Thumbnail, 0, 0,Thumbnail->GetWidth(), Thumbnail->GetHeight());
             Form1->Image1->Refresh();
             CLSID gifClsid;
             GetEncoderClsid(L"image/jpeg", &gifClsid);
             sr.Name = StringReplace(sr.Name, ExtractFileExt(sr.Name), ".jpg",TReplaceFlags() << rfReplaceAll);
             Thumbnail->Save(WideString(Nazwa_Katalogu+"\\"+Form1->m->Text+"\\"+sr.Name), &gifClsid, NULL);
             delete Thumbnail;
             Application->ProcessMessages();
            }
           }
             while(FindNext(sr) == 0)
               if(((sr.Attr & faDirectory) != faDirectory)&&(sr.Name!=".")&&(sr.Name!="..")&&
                  ((UpperCase (ExtractFileExt (sr. Name))==".BMP")||
                  (UpperCase (ExtractFileExt (sr. Name))==".JPG")||
                  (UpperCase (ExtractFileExt (sr. Name))==".JPEG")||
                  (UpperCase (ExtractFileExt (sr. Name))==".GIF")||
                  (UpperCase (ExtractFileExt (sr. Name))==".BMP")||
                  (UpperCase (ExtractFileExt (sr. Name))==".TIFF")||
                  (UpperCase (ExtractFileExt (sr. Name))==".PNG")||
                  (UpperCase (ExtractFileExt (sr. Name))==".EMF")||
                  (UpperCase (ExtractFileExt (sr. Name))==".TIF")) )
                {
                  Form1->status->SimpleText = "Przetwarzam: "+sr.Name;
             if(Form1->CheckBox2->Checked){
            /* AnsiString buf = sr.Name;
             fixname(&sr.Name);
             if(buf!=sr.Name)
             RenameFile(Nazwa_Katalogu+"\\"+buf,Nazwa_Katalogu+"\\"+sr.Name);       */
             }
             if (!DirectoryExists(Nazwa_Katalogu+"\\"+Form1->m->Text))
              CreateDir(Nazwa_Katalogu+"\\"+Form1->m->Text);

             if(!FileExists(Nazwa_Katalogu+"\\"+Form1->m->Text+"\\"+sr.Name)||(Form1->CheckBox1->Checked)){
              Gdiplus::Bitmap image(WideString(Nazwa_Katalogu+"\\"+sr.Name).c_bstr());
              Gdiplus::Image* Thumbnail = image.GetThumbnailImage(Form1->szerokosc->Value, Form1->wysokosc->Value, NULL, NULL);
              Gdiplus::Graphics grphx(Form1->Image1->Canvas->Handle);
              grphx.DrawImage(Thumbnail, 0, 0,Thumbnail->GetWidth(), Thumbnail->GetHeight());
              Form1->Image1->Refresh();
              CLSID gifClsid;
              GetEncoderClsid(L"image/jpeg", &gifClsid);
              sr.Name = StringReplace(sr.Name, ExtractFileExt(sr.Name), ".jpg", TReplaceFlags() << rfReplaceAll);
              Thumbnail->Save(WideString(Nazwa_Katalogu+"\\"+Form1->m->Text+"\\"+sr.Name), &gifClsid, NULL);
              delete Thumbnail;
             }
            }
         Application->ProcessMessages();
         FindClose(sr);
        }
}

void oKatalogi(AnsiString gdzie)
{
std::vector<AnsiString*> directory;
TSearchRec sr;
directory.push_back(new AnsiString(gdzie));
oPliki(gdzie);
for (int i = 0; i < directory.size(); ++i){
        if(FindFirst(*directory[i]+"\\*.*",faDirectory, sr)==0){
          if(((sr.Attr & faDirectory) == faDirectory)&&(sr.Name!=".")&&(sr.Name!="..")&&(sr.Name!=Form1->m->Text)) {
           if(Form1->CheckBox2->Checked)
            { /*
             AnsiString buf = sr.Name;
             fixname(&sr.Name);
             if(buf!=sr.Name)
             RenameFile(k->NazwaKatalogu()+"\\"+buf,k->NazwaKatalogu()+"\\"+sr.Name);   */
            }
           directory.push_back(new AnsiString(*directory[i]+"\\"+sr.Name));    
           Form1->status->SimpleText = "Przetwarzam: "+sr.Name;
           Application->ProcessMessages();
            } //  if(((sr.Attr & faDirectory) == faDirectory)&&(sr.Name!=".")&&(sr.Name!="..")&&(sr.Name!=Form1->m->Text))
           while(FindNext(sr) == 0){
            if(((sr.Attr & faDirectory) == faDirectory)&&(sr.Name!=".")&&(sr.Name!="..")&&(sr.Name!=Form1->m->Text)) {
            if(Form1->CheckBox2->Checked)
             { /*
              AnsiString buf = sr.Name;
              fixname(&sr.Name);
              if(buf!=sr.Name)
              RenameFile(k->NazwaKatalogu()+"\\"+buf,k->NazwaKatalogu()+"\\"+sr.Name);   */
             }
            directory.push_back(new AnsiString(*directory[i]+"\\"+sr.Name));
            Form1->status->SimpleText = "Przetwarzam: "+sr.Name;
            Application->ProcessMessages();
            }  //if(((sr.Attr & faDirectory) == faDirectory)&&(sr.Name!=".")&&(sr.Name!="..")&&(sr.Name!=Form1->m->Text))
           }   //while
          FindClose(sr);
          } //if(FindFirst(*directory[i]+"\\*.*",faDirectory, sr)==0){

} //for
for (int i = 0; i < directory.size(); ++i)
 oPliki(*directory[i]);
//free memory
Form1->status->SimpleText = "Zakoñczono tworzenie miniatur. ";
for (int i = 0; i < directory.size(); ++i) delete directory[i];
};





//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
Gdiplus::GdiplusShutdown(gdiplusToken);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
oKatalogi(dir->Directory);

}
//---------------------------------------------------------------------------


