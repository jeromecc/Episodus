#ifndef __NSBOUTON_H#define __NSBOUTON_H

class Message ;

// #include <owl\owlpch.h>
#include <owl\applicat.h>
#include <owl\button.h>

#ifdef _ENTERPRISE_DLL
  #include "enterpriseLus/nsglobalLus.h"
#else
  #include "partage/nsglobal.h"
#endif

#include "nsbb\nsbb_glo.h"
// #include "nsbb\nsbbtran.h"

class _NSBBCLASSE NSButton : public OWL::TButton, public NSRoot
{
  public:

    NSControle* pControle ;
    bool        ActiveToi ;	// Activer physiquement le controle ou juste
                                // lui donner le focus
    string      sContenuBrut, sContenuTransfert, Type ;

    NSButton(NSContexte *pCtx, TWindow* parent, int resId) ;
    NSButton(NSContexte *pCtx, TWindow* parent, int resId, const char far* text,
                 int X, int Y, int W, int H, bool isDefault = false,
                 TModule* module = 0) ;
    ~NSButton() ;

    void activeControle(int activation, Message* pMessage = 0) ;

    WNDTYPE   donneType() { return(isBtn) ; }
    bool      canWeClose() ;
    char far* GetClassName() ;

    // child id notification handled at the child
    //
    void BNClicked() ;  // BN_CLICKED
    void SetupWindow() ;

	DECLARE_RESPONSE_TABLE(NSButton) ;
};

#endif

