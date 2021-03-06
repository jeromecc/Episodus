//---------------------------------------------------------------------------//      NSDLG.H
//
//  D�finitions des bo�tes de dialogue NAUTILUS,
//   Bo�te de dialogue g�n�rique NSDialog, anc�tre dont d�rivent :
//   - bo�te de dialogue modale       : NSDialogModal
//   - bo�te de dialogue non modale   : NSDialog
//
//   Une NSDialog configure au chargement de la ressource ses contr�les,
//   - cr�e les objets OWL correspondants pour chacun d'eux
//   - met en place le m�canisme de transfert
//   - configure les contr�les Edit � l'aide de validateurs appropri�s gr�ce
//     � l'information contenue dans szConfigStr qui est d�coup�e et plac�e
//     dans pConfigCache
//
//  Auteur: KRZISCH Ph.
// Date de cr�ation : mars 93   Derni�re mise � jour : mai 94
//---------------------------------------------------------------------------

#ifndef __NSDLG_H__
# define __NSDLG_H__

# ifndef __NSBBITEC_H
  class BBPhraseItem ;
# endif
# ifndef __NSONGLET_H
	class NSOnglet ;
# endif
# ifndef __NSBBSMAL_H
	class NSSmallBrother ;
# endif
# ifndef __NSTRNODE_H
	class NSTreeWindow ;
  class NSTreeNode ;
# endif

class NsMultiDialog ;
class NSPatPathoArray ;
class NSButton ;
class NSToolTip ;

# include "partage\nsdebug.h"
# include <classlib/arrays.h>
# include <owl/dialog.h>
# include <owl/groupbox.h>
# include <owl/docview.h>

# include "nsutil\nscache.h"
//# include "nsbb\nsbitmap.h"
// # include "nsbb\nsbbtran.h"
// # include "nsbb\nstrnode.h"
# include "nsbb\nsbb_dlg.h"            // for iterNSControle
// # include "nsbb\nsbbitem.h"
# include "partage\ns_vector.h"
# include "partage\NTArray.h"

# define NSFCT_REF	 	  0
# define NSFCT_INIT 	  1
# define NSFCT_ACTIVE   2
# define NSFCT_AIGUILLE 3
# define NSFCT_PHRASE   4

// Nom du type de ressource pour  la configuration d'une NSDialog//const char szTypeResName[] = "MYRESSOURCE";

/***********************************************************************/
class NSDialogCtrl
{
	public :

		NSDialogCtrl() ;
		NSDialogCtrl(const NSDialogCtrl& rv) ;
		~NSDialogCtrl() ;
		NSDialogCtrl& operator=(const NSDialogCtrl& src) ;
		int operator == (const NSDialogCtrl& o) ;
		int operator != (const NSDialogCtrl& o) { return !(*this==o) ; }

    string getIdentite()             { return _sIdentite ; }
    void   setIdentite(string sI)    { _sIdentite = sI ; }

		string getControle()             { return _sControle ; }
    void   setControle(string sC)    { _sControle = sC ; }

		string getDlgFonction()          { return _sDlgFonction ; }
    void   setDlgFonction(string sF) { _sDlgFonction = sF ; }

    string getHelpText()             { return _sHelpText ; }
    void   setHelpText(string sH)    { _sHelpText = sH ; }

  protected :

		string _sIdentite ;
		string _sControle ;
		string _sDlgFonction ;
    string _sHelpText ;
};

typedef vector<NSDialogCtrl*>              NSDialogCtrlVector ;
typedef NSDialogCtrlVector::iterator       iterNSDialogCtrlVector ;
typedef NSDialogCtrlVector::const_iterator constIterNSDialogCtrlVector ;

class _NSBBCLASSE NSDialogVector : public NSDialogCtrlVector
{
	public :

		// Constructeurs
		NSDialogVector() : NSDialogCtrlVector() {}
		NSDialogVector(const NSDialogVector& rv) ;

		// Destructeur
		~NSDialogVector() ;
		NSDialogVector& NSDialogVector::operator=(const NSDialogVector& src) ;
    void vider() ;

    NSDialogCtrl* getDialogCtrl(string sIdentite) ;
};
/***********************************************************************/

class NSDialogEdit
{
	public :

		char szType[25];
		UINT nMaxInput;

		NSDialogEdit();
		NSDialogEdit(const NSDialogEdit& rv);
		~NSDialogEdit();
		NSDialogEdit& operator=(const NSDialogEdit& src);
		int operator == (const NSDialogEdit& o);
		int operator != (const NSDialogEdit& o) {return !(*this==o);}
};

class _NSBBCLASSE NSDialogOnglet
{
  public :

		int 	  nNbOnglets ;
    string	sOngletActif ;
    string*	pTexteOnglets[20] ;

		NSDialogOnglet() ;
		NSDialogOnglet(const NSDialogOnglet& rv) ;
		~NSDialogOnglet() ;

    void vider() ;
    void addTabText(const string& sLabel) ;

		NSDialogOnglet& operator=(const NSDialogOnglet& src) ;
		int             operator==(const NSDialogOnglet& o) ;
		int             operator!=(const NSDialogOnglet& o) { return !(*this==o) ; }
};

typedef vector<NSDialogOnglet*>  NSOngletVector ;
typedef NSOngletVector::iterator NSOngletIter ;
typedef NTArray<NSDialogOnglet>  NSOngletArray ;
//---------------------------------------------------------------------------
//  Classe des dialogues NAUTILUS
//       ANCETRE   : TDialog
//       SURCHARGE : SetupWindow()  (h�rit� de TWindowObject)
//  Cette classe sert � mettre en place les dialogues complexes.
//  (Contenant des EDIT � configurer).
//  C'est une classe ANCETRE
//----------------------------------------------------------------------------
class _NSBBCLASSE NSDialog : public TDialog, public NSRoot
{
	public:

    enum ACTIONTYPE { actionOther = 0, actionOk, actionCancel, actionFreeText, actionHelp, actionControl} ;

    BBItem                  *_pBBItem ;		    // BBItem cr�ateur de la boite de dialogue
#ifndef __OB1__
    bool                    _bInitFromBbk ;   // Dialogue � initialiser � partir du blackboard (oui/non)
#endif
		string                  _sControleur ;    // Cha�ne de contr�le
		string                  _sConfigEdit ;    // Cha�ne de configuration des EDIT
    string                  _sConfigOnglet ;  // Cha�ne de configuration de l'onglet
    string                  _sConfigHelp ;    // Cha�ne de configuration de l'aide
    string                  _sConfigTips ;    // Cha�ne de configuration des Tooltips
		int                     BitmapID ;        // ID du bitmap
    string                  _sResInfo ;       // Cha�ne d'informations de configuration

		int				              _iIndexCtrl ;	    // Index du contr�le � configurer
		int				              _iIndexEdit ;	    // Index de l'Edit � configurer
		int 			              _iIndexGroupe ;	  // Index des groupes

    NsMultiDialog           *_pControleurMulti ;

		int				              _iNbrCtrl ;		    // Nombre d'objets contr�le cr��s
		NSControleVector        _aNSCtrls ;	      // Pointeurs sur ces objets

		NSDialogVector          _aConfigCtrls ;	    // Controls config information
		NSDialogEdit            *_pConfigCache[20] ;	// Pointeur sur une matrice dynamique
    NSOngletArray           _aConfigTabs ;

    vector<OWL::TGroupBox*> _aGroups ;
		OWL::TGroupBox          *_pGroupCurr ;       // Groupe actif

		TResId 			            _ResID, _ConfigResID ;
    TModule                 *_pNSResModule ;
		bool			              _bActif ;

    TWindowView             *_pView ;            // Vue (au sens document/vue)
    bool                    _bActivateMUEView ;

    string                  _sHelpBodyUrl ;
    string                  _sHelpIndexUrl ;

    bool                    _bPOMRDialog ;
    bool                    _bMereMUEView ;     //savoir si le dialog est dans une MUEView
    bool                    _bCanMove ;

    bool                    _bOkActivated ;

    bool                    _bBlackboardStillAtWork ;

    TTooltip               *_pToolTip ;

		// Constructeurs
#ifdef __OB1__
		NSDialog(NSContexte* pCtx, TWindow *AParent, TResId ResourceID, TResId ConfigRes = 0, BBItem *pItem = 0, TModule *pNSResModule = 0, NsMultiDialog *pControl = 0) ;
    NSDialog(NSContexte* pCtx, TWindow *AParent, BBItem *pItem = 0, TModule *pNSResModule = 0, NsMultiDialog *pControl = 0) ;
#else
		NSDialog(NSContexte* pCtx, TWindow *AParent, TResId ResourceID, TResId ConfigRes = 0, BBItem *pItem = 0, TModule *pNSResModule = 0, NsMultiDialog *pControl = 0, bool initFromBbk = false) ;
    NSDialog(NSContexte* pCtx, TWindow *AParent, BBItem *pItem = 0, TModule *pNSResModule = 0, NsMultiDialog *pControl = 0, bool initFromBbk = false) ;
#endif

		// Destructeur
		virtual ~NSDialog() ;

    void         init(BBItem *pItem, NsMultiDialog *pControl) ;
    bool         Create() ;

    void 	       Desactive() ;

		// Fonctions d'int�r�t g�n�ral
		void         BlankDisplay(int id) ;

		// Fonctions de transfert
		void         rafraichitControles() ;
		void         initialiseControles() ;
    //si les controles � cocher sont remplis onStart initOnStart=true.
    void         initControlesFromBbk(string filling = "SetupWindow") ;    void         initControlFromBbkAnswer(NSControle* pControl, NSPatPathoArray* pPatPathoArray, string* psDate = NULL) ;    void         ActiveControlSuivant(NSControle *pControle) ;
    void         ActiveControlPrecedent(NSControle *pControle) ;

    void         initControlesFromCapture() ;

		void         CmOkMessage(int iMessage) ;

		//$$ Temporaire pour test
		int          CountChild() ;
		void         ConfigShow() ;

  	// M�thodes de r�ponse aux messages
		void         CmOk() ;
		void         CmSuite() ;
		void         CmRetour() ;
		void         CmConclusion() ;
    void         CmBbkCalcul() ;    void         CmBbkEvent() ;    void         CmBbkUpdate() ;		void         CmCancel() ;
    void         CmHelp() ;
    void         CmTreePaste() ;
    void         CmOkFermer() ;
    void         CmCancelFermer() ;
    void         CmWarnForNoFreeText() ;
    void         EvKillFocus(THandle hWndGetFocus) ;
    void         EvSetFocus(THandle hWndLostFocus) ;
    void         EvWindowPosChanging(WINDOWPOS far& windowPos) ;
    HBRUSH       EvCtlColor(HDC hdc, HWND hWndCtl, uint ctlType) ;
    // void      EvMove(ClassLib::TPoint& clientOrigin);
    // void      EvWindowPosChanged(WINDOWPOS far& windowPos);
    void         ForceCanClose() ;
    void         activateParent() ;

    // Overrides functions in order to process tooltips
    virtual void Destroy(int retVal = 0) ;
    virtual int  Execute() ;
    bool         PreProcessMsg(MSG &msg) ;

    void         checkFreeText() ;
    void         uncheckFreeText() ;
    void         getFreeTextButtons(NSButton** ppStandardButton, NSButton** ppCheckedButton) ;

    int          getIncrementedOngletsLevel() { return ++_iOngletLevel ; }

    ACTIONTYPE   getLastAction()                   { return _iLastAction ; }
    void         setLastAction(ACTIONTYPE iAction) { _iLastAction = iAction ; }

 protected:

    NSToolTip    *_pNSToolTip ;
    int          _iOngletLevel ;

    ACTIONTYPE   _iLastAction ;

    // Fonctions d'ouverture et de fermeture
		virtual void SetupWindow() ;
		bool         initialiseRessources(TResId ResourceID, TResId ConfigResID) ;
    bool         initialiseRessourcesArchetype() ;
		string       *LoadConfigResource(TResId resId, const char far *resType = RT_RCDATA) ;
    bool         canCloseOk;
    void         insertLeavesOnBlackBoard(string sCheminPere, NSPatPathoArray* pPatPathoArray);

		bool         AnalyseRes() ;
		void         AnalyseCtrl(const char *input, const char *separateurs) ;
		void         AnalyseEdit(const char *input, const char *separateurs) ;
    void         AnalyseOnglet(const string &sInput, const string &sSeparateurs) ;
    void         AnalyseHelp(const char *input, const char *separateurs) ;
    void         AnalyseTips(const char *input, const char *separateurs) ;
		static void  DlgConfigCtrl2(TWindow *pWnd, void *) ;

    void         CreerControles() ;
    void         CreerControlesArchetype() ;

    void         SetDynamicCaption() ;

		void         referenceControle(NSControle *pNSControle) ;
		void         detruitControles() ;

		//DefRegionArray* defRegions() { return pDefRegions; }
		bool         CanClose() ;

    LRESULT      EvCorrect(WPARAM, LPARAM) ;
		LRESULT      EvContinue(WPARAM, LPARAM) ;
		void	       TestClick(WPARAM) ;
    void 	       EvActivate(uint active, bool minimized, HWND hwnd) ;
    bool         EvNCActivate(bool active) ;
    void         EvLButtonDown(uint modKeys, NS_CLASSLIB::TPoint& point) ;

 		void         closeEditDico() ;
    void         executeClosingFunctions() ;
    void         executePreClosingFunctions() ;

#ifdef __OB1__
    void         EvTimer(uint id) ;
    void         resetOB1PrecocheTimer() ;
    void         checkPrecocheOnTimer() ;
    void         checkResultOnTimer() ;
#endif
		string       getPathForBbkQuestion(iterNSControle iterCtrl) ;
    void         waitForKS() ;

//wrappers public:

    void         GetWindowClass(WNDCLASS& wndClass) ;
    void         CloseWindow(int retVal = 0) ;

 private:

    bool _IsModalDialog ;

	DECLARE_RESPONSE_TABLE(NSDialog) ;

	// Fonction de cr�ation des objets OWL et leurs transfert buffer
	static bool FAR PASCAL _export DlgConfigCtrl(HWND hWnd, LPARAM lParam) ;
} ;

//---------------------------------------------------------------------------
//  Classe des fonctions Big Brother
//
//  Cette classe sert � mettre en place les fonctions qui interviennent au
//  sein de l'arborescence Big Brother
//  Elle est homog�ne � NSDialog
//----------------------------------------------------------------------------
class _NSBBCLASSE NSBBFonction : public NSRoot
{
  public :

    BBItem*       pBBItem;         // BBItem cr�ateur de la fonction    BBPhraseItem* pBBPhraseItem ;  // BBPhraseItem cr�ateur de la fonction

    string        sNomFonction ;
    bool (FAR *pAdresseFct) (NSBBFonction far *, NSSmallBrother far*, int, int far*) ;

    int           iNbrCtrl ;		   // Nombre d'objets contr�le cr��s
    NSControle*   pNSCtrl[100] ;	 // Pointeurs sur ces objets

    // Constructeurs
    NSBBFonction(NSContexte* pCtx, string sNomFonct, BBItem* pBBItemPere) ;
    NSBBFonction(NSContexte* pCtx, string sNomFonct, BBPhraseItem* pBBItemPere) ;

    // Destructeur
    virtual ~NSBBFonction() ;

    int  referenceTransfert() ;
    int  nouveauCtrl(string sIdentite, string sDlgFct) ;
    bool execute(int iParam, int* piValeur, string sEtiquette = "", NSControle* pNSCtrl = 0) ;

    string getFonction() { return sNomFonction ; }
};

// WIN32
int ajouteBBFonctionCtrl(NSBBFonction* pBBFct, /*char cGroupe,*/ char sIdentite, string sDlgFct) ;

#endif // __NSDLG_H__

