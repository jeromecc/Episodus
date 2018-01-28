// nsv_badlist : personnes non transf�r�es// PA D�cembre 2012
//////////////////////////////////////////////////////

#ifndef __NSV_BADLIST_H
#define __NSV_BADLIST_H

#include <owl/listbox.h>
#include <owl/listwind.h>

class NSVUpgrade ;

#include <partage/NTArray>

class NSBadElement
{
  public :

    string _sOldNss ;
    string _sOldFamillyName ;
    string _sOldChristianName ;
    string _sOldBirthDate ;

    string _sNewChristianName ;

    NSBadElement(string sNss, string sFamillyName, string sChristianName, string sBirthDate) ;
    NSBadElement() ;
    NSBadElement(NSBadElement& rv) ;

    ~NSBadElement() ;

    string getNss()           { return _sOldNss ; }
    string getFamillyName()   { return _sOldFamillyName ; }
    string getChristianName() { return _sOldChristianName ; }
    string getBirthdate()     { return _sOldBirthDate ; }

    NSBadElement& operator=(NSBadElement src) ;
};

//// NSBadElementArray (Array of NSBadElement(s))
//
typedef vector<NSBadElement*> NSBadElementVector ;
typedef NSBadElementVector::iterator         NSBadElementIter ;
typedef NSBadElementVector::reverse_iterator NSBadElementReverseIter ;
typedef NTArray<NSBadElement> NSBadElementArray ;

class NSBadListWindow ;

class NSBadListDialog : public NSUtilDialog
{
	public:

		NSBadListDialog(TWindow* pere, NSContexte* pCtx, NSVUpgrade* pNSVUpgrade) ;
   	~NSBadListDialog() ;

   	void 		SetupWindow() ;

		void 		InitBadElementsList() ;
    void 		InitBadElementsDisplay() ;
   	void 		DisplayBadElementsList() ;
   	void 		DispInfoBadElementsList(TLwDispInfoNotify& dispInfo) ;

   	void 		CmOk() ;
   	void 		CmCancel() ;

    void    transfertDoublon() ;
    void    showDoublons() ;
    void    transfertAll() ;

    void    refresh() ;
    void    buildCsvFile() ;

    bool    addBadElementFromNss(string sOldNss) ;

  protected:

    NSBadElementArray _aBadElements ;
   	NSBadListWindow*  _pBadElementsList ;

    NSVUpgrade*       _pNSVUpgrade ;

    OWL::TButton*     _pRefresh ;
    OWL::TButton*     _pCsvFile ;

	DECLARE_RESPONSE_TABLE(NSBadListDialog) ;
};

//
// Objet "ListWindow" avec gestion du double-click (pour les fiches Imp � modifier)
//
class NSBadListWindow : public TListWindow
{
	public:

		NSBadListWindow(NSBadListDialog* pere, int resId) ;
   	~NSBadListWindow() {}

    void SetupWindow() ;

		void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
    void EvRButtonDown(uint modkeys, NS_CLASSLIB::TPoint& point) ;
   	int  IndexItemSelect() ;

  protected:

    NSBadListDialog* _pDlg ;

    void transfertDoublon() ;
    void showDoublons() ;
    void transfertAll() ;

	DECLARE_RESPONSE_TABLE(NSBadListWindow) ;
};

#endif

// fin de Nsv_badlist.h/////////////////////////////////////////////////////////

