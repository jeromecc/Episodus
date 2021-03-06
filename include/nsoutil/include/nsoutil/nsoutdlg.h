#ifndef __NSOUTDLG_H#define __NSOUTDLG_H

class NSTemplateInfo ;
class NSTemplateArray ;
class NSComboBox ;
class NSUtilEdit ;
class NSUtilLexique ;

#include <classlib\arrays.h>

#include <owl\dialog.h>
#include <owl\groupbox.h>
#include <owl\checkbox.h>
#include <owl\edit.h>
#include <owl\listwind.h>
#include <owl\radiobut.h>

#include "nsbb\nsutidlg.h"
// #include "nsbb\nsednum.h"
#include "nsoutil\nsexport.h"
// #include "nsoutil\nssavary.h"
// #include "nsepisod\flechiesDB.h"
// #include "nsbb\nsarc.h"
// #include "nsbb\nsattval.h"
// #include "nsbb\nscomboutil.h"

//
// Objet "Boite de dialogue" utilis� pour s�lectionner l'utilitaire
//
class _NSOUTILCLASSE NsOutilDialog : public NSUtilDialog
{
	public:

    OWL::TListBox* 	pFunctionsBox ;

    map<string, string> aFunctions ;

    string* psSelectedModuleName ;

	  NsOutilDialog(TWindow* pere, NSContexte* pCtx, string* psModuleName) ;
	  ~NsOutilDialog() ;

	  void SetupWindow() ;
    void CmOk() ;

    void initFunctionsList() ;
    void CmFunctionDblClk(WPARAM Cmd) ;

	DECLARE_RESPONSE_TABLE(NsOutilDialog) ;
};

class _NSOUTILCLASSE NSEditTemplateDialog : public NSUtilDialog
{
	public :

  	NSComboBox*         pTypeDoc ;
    OWL::TGroupBox*     pUtil ;
    OWL::TRadioButton*  pUtil1 ;
    OWL::TRadioButton*  pUtil2 ;
    NSUtilEdit*         pConsole ;
    NSUtilLexique*      pRoot ;
    NSUtilEdit*         pLibelle ;
    OWL::TButton*       pEnTete ;
    OWL::TButton*       pFichier ;
    OWL::TGroupBox*     pTypeTpl ;
    OWL::TRadioButton*  pCompo ;
    OWL::TRadioButton*  pDefaut ;

    string  sLibelle ;
    string  sEnTete ;
    string  sFichier ;
    string  sTypeDoc ;
    string  sOper ;
    string  sCompo ;
    string  sDefaut ;
    string  sNoConsole ;
    string  sLexiqueRoot ;

    // patpatho r�sultat
    NSPatPathoArray* pPatPatho ;
    NSTemplateInfo*  pTplInfo ;

    NSEditTemplateDialog(TWindow* pere, NSContexte* pCtx, NSTemplateInfo* pTpl = 0) ;
    ~NSEditTemplateDialog() ;

    void    SetupWindow() ;
    string  TrouveNomFichier() ;
    void    CmEnTete() ;
    void    CmFichier() ;
    void    CmOk() ;
    void    CmCancel() ;

    void    setHeaderInfo() ;
    void    setFileInfo() ;
    void    setDocInfo() ;
    void    setuserInfo() ;
    void    setCompoInfo() ;
    void    setDefaultInfo() ;
    void    setRootInfo() ;
    void    setConsoleInfo() ;
    void    setLibelleInfo() ;

    void    fillPatPatho() ;
    void    fillTplInfo() ;

	DECLARE_RESPONSE_TABLE(NSEditTemplateDialog) ;
};

class _NSOUTILCLASSE NSTemplateManager : public NSRoot
{
	public :

    NSTemplateArray* pTplArray ;

    NSTemplateManager(NSContexte* pCtx) ;
    NSTemplateManager(const NSTemplateManager& rv) ;

    ~NSTemplateManager();
    NSTemplateManager& operator=(const NSTemplateManager& src) ;

    bool LoadTemplateList(string sTypeDoc) ;
    void initInfo(NSPatPathoArray* pPPT) ;

    void LoadAllTemplates() ;
    void LoadTemplatesByType(string sDefaultAttribute) ;
    void initTemplateFromOids(string sTplOids) ;
};

class NSTemplateListWindow ;

class _NSOUTILCLASSE NSTemplateWindow : public TWindow, public NSRoot{ public:

	NSTemplateManager* pTemplates ;

	// Constructeur - Destructeur
  NSTemplateWindow(NSContexte* pCtx, TWindow* parent, const char far* title = 0) ;
  ~NSTemplateWindow() ;

  void CmNouveau() ;
  void CmModifier() ;
  void CmSupprimer() ;

  void SetupColumns() ;
  void AfficheListe() ;

  // Fonctions de r�ponse aux evts
  void   EvSize(uint sizeType, ClassLib::TSize &size) ;
  void   EvRButtonDown(uint modkeys, NS_CLASSLIB::TPoint& point) ;
  void   EvRButtonDownOut(uint modkeys, NS_CLASSLIB::TPoint& point) ;
  void   EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
  void   EvChar(uint key, uint repeatCount, uint flags) ;
  void   EvSetFocus(HWND hWndLostFocus) ;
  void   focusFct() ;

  string donneContexte(string sContexte) ;
  void   initCurentDrugs() ;

  void   reloadView(string sReason) ;

  // void						autoAddInDrugView(string sConcern, NSPatPathoArray *pPPT);
  void   autoAddInDrugView(string sConcern);

 protected:

	// Remplissage de la vue
  void SetupWindow() ;
  void SetupTxtBar() ;
  void InitFormatFont() ;
  void SetupToolBar() ;

  void DispInfoListe(TLwDispInfoNotify& dispInfo) ;
  void LVNColumnclick(TLwNotify& lwn) ;

  void sortAgain() ;

  void changeSortOrder(int iOrder) ;

  void sortByLibelle() ;
  void sortByUser() ;
  void sortByType() ;
  void sortByRoot() ;
  void sortByHeader() ;
  void sortByTpl() ;
  void sortByCompo() ;
  void sortByDefault() ;

  string getDrugRefToModify(string sWarningMsg = string("")) ;

  // Variables
  NSTemplateListWindow* pListeWindow ;
  bool                  bNaturallySorted ;
  int                   iSortedColumn ;

	DECLARE_RESPONSE_TABLE(NSTemplateWindow) ;
};

//
// Objet "ListWindow" avec gestion du double-click (pour les m�dicaments � modifier)
//
class _NSOUTILCLASSE NSTemplateListWindow : public TListWindow
{
	public:

		NSTemplateWindow* pView ;		int               iRes ;
		NSTemplateListWindow(NSTemplateWindow* pere, int resId, int x, int y, int w,                                                int h, TModule* module = 0) ;

    ~NSTemplateListWindow() {}    void SetupWindow() ;
    void EvRButtonDown(uint modkeys, NS_CLASSLIB::TPoint& point) ;
    void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;    void EvKeyDown(uint key, uint repeatCount, uint flags) ;    void EvLButtonUp(uint modKeys, NS_CLASSLIB::TPoint& pt) ;    int  IndexItemSelect() ;

    void EvSetFocus(HWND hWndLostFocus) ;
    void EvKillFocus(HWND hWndGetFocus) ;

	DECLARE_RESPONSE_TABLE(NSTemplateListWindow) ;};

//
//  Objets de l'�diteur d'en-tetes
//

class NSVarTag
{
	public:

  	string name ;
    string value ;

    NSVarTag(string sName, string sValue) ;
    ~NSVarTag() ;
    NSVarTag(const NSVarTag& rv) ;
    NSVarTag& operator=(const NSVarTag& src) ;
};

typedef vector<NSVarTag*> NSVarTagVector ;
typedef NSVarTagVector::iterator NSVarTagIter ;

class NSVarTagArray : public NSVarTagVector
{	public :
		// Constructeurs		NSVarTagArray() : NSVarTagVector() {}		NSVarTagArray(const NSVarTagArray& rv) ;    NSVarTagArray& operator=(const NSVarTagArray& src) ;
		// Destructeur		virtual ~NSVarTagArray() ;    void vider() ;};

class NSEnTeteEditWindow ;

class _NSOUTILCLASSE NSEnTeteEditDialog : public NSUtilDialog
{
	public:

  	NSVarTagArray*      pVarArray ;
    int                 nbVar ;
    string              sFileName ;
    string              html_string ;
    NSEnTeteEditWindow* pListeVar ;
    bool                bParseOK ;

    NSEnTeteEditDialog(TWindow* pere, NSContexte* pCtx, string filename) ;
    ~NSEnTeteEditDialog() ;

    void SetupWindow() ;
    bool ParseModele() ;
    void InitListeVar() ;
    void AfficheListeVar() ;
    void DispInfoListeVar(TLwDispInfoNotify& dispInfo) ;

    void CmEditVarTag() ;
    void CmOk() ;
    void CmCancel() ;
    void CmHelp() ;

	DECLARE_RESPONSE_TABLE(NSEnTeteEditDialog) ;
};

//
// Objet "ListWindow" avec gestion du double-click (pour les variables � modifier)
//

class NSEnTeteEditWindow : public TListWindow{
	public:

		NSEnTeteEditDialog* pDlg ;
		NSEnTeteEditWindow(NSEnTeteEditDialog* pere, int resId) ;    ~NSEnTeteEditWindow() {}

    void SetupWindow() ;
		void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;    int  IndexItemSelect() ;

	DECLARE_RESPONSE_TABLE(NSEnTeteEditWindow) ;};

class NSVarTagEditDialog : public NSUtilDialog
{
	public:

		NSVarTag*   pVarTag ;
  	OWL::TEdit* pEditName ;
    OWL::TEdit* pEditValue ;

    NSVarTagEditDialog(TWindow* pere, NSContexte* pCtx, NSVarTag* pVar) ;
    ~NSVarTagEditDialog() ;

    void SetupWindow() ;
    void CmOk() ;
    void CmCancel() ;

  DECLARE_RESPONSE_TABLE(NSVarTagEditDialog) ;
};


#endif

