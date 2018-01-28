#ifndef __NSCOMBO_H#define __NSCOMB0_H

// #include <owl\owlpch.h>
#include <owl\applicat.h>
#include <owl\combobox.h>
#include "owl\validate.h"
#include <string.h>
#include <cstring.h>

#include "nsbb\nsbbtran.h"
#include "nsbb\nsbb_dlg.h"
#include "nsepisod\eptables.h"
#include "nssavoir\nspathor.h"

#ifdef _ENTERPRISE_DLL
  #include "enterpriseLus/nsglobalLus.h"
#else
  #include "partage/nsglobal.h"
#endif

#include "nsbb\nsedilex.h"

class NSComboSemantique : public OWL::TComboBox, public NSRoot
{
	public:

		NSControle* pControle ;
		string 	    sConcept ; // Classification en cours
    string      sContenuPere ;
		string      sContenuTransfert, Type, sContenuAncien ;
    NSEditLexiqueDerive*    pNSEdit ;   //fils fictif
		bool        ActiveToi ;
		bool        bWinStd ;       // Gestion standard windows

		// Constructeur et destructeur
		NSComboSemantique(NSContexte *pCtx, TWindow* parent, int resId) ;

		NSComboSemantique(NSContexte *pCtx, TWindow* parent, int resId, int x, int y, int w, int h,
                    uint32 style, uint textLimit = 0, TModule* module = 0) ;
		~NSComboSemantique() ;

		uint    Transferer(TTransferDirection direction, CTRL_ACTIVITY* pActif, Message* pMessage = 0) ;
		uint    TempTransferer(CTRL_ACTIVITY* pActif, Message* pMessage = 0) ;
		void    activeControle(int activation, Message* pMessage = 0) ;
		bool    canWeClose() ;
		void    SetupWindow() ;
		void    donneTransfert() ;
		void    CBSelChange() ;
    void    CreerBBItem();

		WNDTYPE     donneType() { return(isComboSemantique) ; }

	private:

		NSPathoArray aTermList ;

		void searchList(string sConcept) ;

	DECLARE_RESPONSE_TABLE(NSComboSemantique) ;
};

class NSComboClassif : public OWL::TComboBox, public NSRoot
{
	public:

		NSControle* pControle ;
		string 	    sClassification ; // Classification en cours
		string      sContenuTransfert, Type, sContenuAncien ;
		bool        ActiveToi ;
		bool        bWinStd ;       // Gestion standard windows

		// Constructeur et destructeur
		NSComboClassif(NSContexte *pCtx, TWindow* parent, int resId) ;

		NSComboClassif(NSContexte *pCtx, TWindow* parent, int resId, int x, int y, int w, int h,
                    uint32 style, uint textLimit = 0, TModule* module = 0) ;
		~NSComboClassif() ;

		uint    Transferer(TTransferDirection direction, CTRL_ACTIVITY* pActif, Message* pMessage = 0) ;
		uint    TempTransferer(CTRL_ACTIVITY* pActif, Message* pMessage = 0) ;
		void    activeControle(int activation, Message* pMessage = 0) ;
		bool    canWeClose() ;
		void    SetupWindow() ;
		void    donneTransfert() ;
		void    CBSelChange() ;

		WNDTYPE     donneType() { return(isComboClassif) ; }

	private:

		NSEpiClassifInfoVector aClassifList ;

		void searchList(string sClassif) ;

	DECLARE_RESPONSE_TABLE(NSComboClassif) ;
};

#endif  // __NSCOMB0_H

