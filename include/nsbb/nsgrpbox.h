#ifndef __NSGRPBOX_H
#define __NSGRPBOX_H

// #include <owl\owlpch.h>
#include <owl\applicat.h>
#include <owl\groupbox.h>

#ifdef _ENTERPRISE_DLL  #include "enterpriseLus/nsglobalLus.h"
#else
  #include "partage/nsglobal.h"
#endif
#include "nsbb\nsbb_dlg.h"

class NSGroupBox : public TGroupBox {
  public:

	NSControle* pControle;

	NSGroupBox(TWindow* parent, int resId);    
	~NSGroupBox();
    void SetupWindow();
	void activeControle(int activation, string message) {}

	WNDTYPE donneType() { return(isBtn); }

	void EvSetFocus(HWND hWndLostFocus);
   void EvKillFocus(HWND hWndGetFocus);

	DECLARE_RESPONSE_TABLE(NSGroupBox);
};

#endif
