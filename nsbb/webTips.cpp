//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "webTips.h"
#include "nsbb\nsTipBrowser.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"

TWebTip *WebTip ;

//---------------------------------------------------------------------------
    : TForm(Owner)
{
	BorderStyle = bsToolWindow ;
  FormStyle   = fsStayOnTop ;
}

//---------------------------------------------------------------------------
{
  pTip->CmFermer() ;
}

//---------------------------------------------------------------------------