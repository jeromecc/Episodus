#ifndef __NSDN_DLG_H#define __NSDN_DLG_H

#ifdef _ENTERPRISE_DLL  #include "enterpriseLus/nsglobalLus.h"
#else
  #include "partage/nsglobal.h"
#endif
#include <string.stl>
#include <classlib\arrays.h>
#include <owl\dialog.h>#include <owl\groupbox.h>
#include <owl\checkbox.h>
#include <owl\edit.h>
#include <owl\gauge.h>

#include "nsbb\nsutidlg.h"

#if defined(_DANSNSDNDLL)
	#define _CLASSENSDN __export
#else
	#define _CLASSENSDN __import
#endif
//
// Objet "Boite de dialogue" utilis� pour montrer la progression de
// l'enregistrement
//
class _CLASSENSDN NSEnregProgressDlg : public NSUtilDialog
{
  public:

    OWL::TGauge* pDataProgressBar ;
    OWL::TGauge* pLocProgressBar ;

    NSEnregProgressDlg(TWindow* pere, NSContexte* pCtx, TModule* module = 0) ;
    ~NSEnregProgressDlg() ;

    void SetupWindow() ;

    void resetDataGauge() ;
    void resetLocGauge() ;

    void fixePositionData(int iPos) { pDataProgressBar->SetValue(iPos) ; }
    void fixePositionLoc(int iPos)  { pLocProgressBar->SetValue(iPos) ; }

	DECLARE_RESPONSE_TABLE(NSEnregProgressDlg) ;
};

#endif // __NSDN_DLG_H
