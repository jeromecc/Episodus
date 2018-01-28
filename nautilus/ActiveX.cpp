//---------------------------------------------------------------------------
#pragma hdrstop

#include "ActiveX.h"

//---------------------------------------------------------------------------
// #pragma link "SHDocVw_TLB"
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"

TWebProxy *WebProxy ;
//---------------------------------------------------------------------------
                     :TForm(Owner)
{
  pView = 0 ;
}

// Constructeur Nautilus
{
	pView = View ;

	// CoInitialize(NULL);
	// Control = new TWebBrowser(Parent);
	// Control->Align = alClient;
}

//---------------------------------------------------------------------------
{
	wchar_t buff[100] ;

	// SetStatusText("Retrieving document " + URL + "...");
{
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, URL.c_str(), -1, buff, sizeof(buff)) ;
  Control->Navigate(buff, 0, 0, 0, 0) ;
}
catch (EOleException* e)
{
	ShowMessage(e->Message) ;
}
}
//---------------------------------------------------------------------------

void __fastcall TWebProxy::FormMouseDown(TObject *Sender,
{
	if (Button == mbRight)
    {
    }
}
//---------------------------------------------------------------------------

void __fastcall TWebProxy::ControlNavigateComplete2(TObject* Sender,
{
  if (pView)
    pView->NavigateComplete() ;
}
//---------------------------------------------------------------------------


void __fastcall TWebProxy::NavigateError(TObject *Sender, LPDISPATCH pDisp,
      TVariant *URL, TVariant *Frame, TVariant *StatusCode,
      TOLEBOOL *Cancel)
{
  int iStatusCode = int(*StatusCode) ;
  AnsiString sUrl = AnsiString(*URL) ;

  if (pView)
    pView->NavigateErrorEvent(iStatusCode, string(sUrl.c_str())) ;
}
//---------------------------------------------------------------------------
