// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

#if !defined(__NSDOCVIEW_H)

#include "nsbb\docViewMgr.h"
/**
* Helper class for doc/view management
*/
class _NSBBCLASSE NSDocViewManager : public NSDocViewRootManager

		// Constructeur - Destructeur
		~NSDocViewManager() ;

		TView* 				createView(TDocument* pDoc, string sDescription = "", TView* pView = 0) ;
};

#endif		// __NSDOCVIEW_H
