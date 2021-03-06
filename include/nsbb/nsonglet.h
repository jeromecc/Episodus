#ifndef __NSONGLET_H#define __NSONGLET_H

// #include <owl\owlpch.h>
#include <owl\applicat.h>
#include <owl\tabctrl.h>
//#include <vbxct1.h>
//#include <\bvsp\include\saxtabs1.h> TTabControl   TTabItem

#ifdef _ENTERPRISE_DLL
  #include "enterpriseLus/nsglobalLus.h"
#else
  #include "partage/nsglobal.h"
#endif

#include "nsbb\nsdlg.h"
#include "nsbb\nsbb_dlg.h"

class NSOnglet : public TTabControl, public NSRoot
{
  public:

  	NSOnglet(NSContexte *pCtx, TWindow* parent, int resId) ;    NSOnglet(NSContexte *pCtx, TWindow* parent, int resId, int x, int y, int w, int h, TModule* module = 0) ;
    ~NSOnglet();
    void InitialiseTabs(NSDialogOnglet* pConfigOnglet);
    void SetupWindow() ;
	  void activeControle(int activation, Message* pMessage = 0 );
	  WNDTYPE donneType() { return(isOnglet); }
	  // child id notification handled at the child	  //
    void TabSelChange(TNotify far&);
    void TabSelChanging(TNotify far&);
    void EvLButtonDown(uint modKeys, NS_CLASSLIB::TPoint& point);
	  //void EvClick(VBXEVENT FAR*);
	  //void BNClicked(VBXEVENT FAR *event);  // BN_CLICKED

    NSControle* getControl()                  { return _pControle ; }
    void        setControl(NSControle* pCtrl) { _pControle = pCtrl ; }

    int         getLevel()                    { return _iLevel ; }
    void        setLevel(int iL)              { _iLevel = iL ; }

  protected:

    NSControle* _pControle ;
	  int         _iOngletActif ;
    int         _iLevel ;

	DECLARE_RESPONSE_TABLE(NSOnglet) ;} ;

#endif

