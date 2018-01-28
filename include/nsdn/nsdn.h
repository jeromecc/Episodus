//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//#include <windows.h>

#ifndef __NSDN_H
#define __NSDN_H

#include <bwcc.h>

#ifdef _MAIN
	#ifndef __MAIN
		extern TModule *pNSResModule;
	#else
		static TModule *pResMod;
		TModule *pNSResModule;
	#endif
#else
	extern TModule *pNSResModule;
#endif

#endif