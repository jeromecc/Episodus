// -----------------------------------------------------------------------------
// ns_vidal.h
// -----------------------------------------------------------------------------
// $Revision: 1.1 $
// $Author: pameline $
// $Date: 2015/02/07 14:46:18 $
// -----------------------------------------------------------------------------
// R�cup�ration des donn�es concernant les bases VIDAL
// -----------------------------------------------------------------------------
// FLP - juillet 2003
// -----------------------------------------------------------------------------

#ifndef __NS_TESTS_H__
#define __NS_TESTS_H__

#include <bwcc.h>

class NSTestControler ;

#include "nautilus\nssuper.h"

void _export nsmtoolsInformation(string far *psToolName, string far *psDescription) ;
void _export nsmToolsAction(TWindow far *pere, NSContexte far *pCtx) ;

void startUnitTest(NSTestControler* pControl) ;
void executeUnitTestsForNsmUtil(NSTestControler* pControl) ;
void executeUnitTestsForPatpatho(NSTestControler* pControl) ;
void executeUnitTestsForTreeView(NSTestControler* pControl) ;
void executeUnitTestsForTextGenerator(NSTestControler* pControl) ;
void executeUnitTestsForEdits(NSTestControler* pControl) ;
void executeUnitTestsForOb1(NSTestControler* pControl) ;

#ifdef _MAIN
    #ifndef __MAIN
        extern TModule    *pNSResModule ;
    #else   // __MAIN
        static TModule    *pResMod ;
        TModule           *pNSResModule ;
    #endif  // __MAIN
#else    // _MAIN
    extern TModule    *pNSResModule ;
#endif   // _MAIN

#endif    // __NS_ARCHEDIT_H__

