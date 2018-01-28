// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
// Fabrice LE PERRU - Aout 2001
// source : R�mi SPAAK - Mai 1997
// --------------------------------------------------------------------------

#if !defined(__NS_SOAPVIEW_H)

#include <owl\docmanag.h>
#include <owl\mdichild.h>
#include <owl\decframe.h>
#include <owl\statusba.h>
#include <owl\controlb.h>
#include <owl\buttonga.h>
#include <owl\applicat.h>
#include <owl\richedpr.h>
#include <owl\choosefo.h>
#include <owl\listwind.h>

#include "nautilus\nsepicap.h"
#include "nsepisod\eptables.h"
#include "nsepisod\nssoapdiv.h"

#include "nssavoir\nspatho.h"

#include "nautilus\nsdocref.h"
#include "nautilus\richedap.h"
#include "nsbb\nsednum.h"

#define _NSSOAPVIEWCLASS _USERCLASS

#define NS_EV_TLISTWIND_NOTIFY_BOOL(notifyCode, method)\
  (TMyPMF)b_LISTWIND_NOTIFY_Sig(&TMyClass::method)}
#define NS_LVN_BEGINDRAG(method) NS_EV_TLISTWIND_NOTIFY_BOOL(LVN_BEGINDRAG, method)

// enum category_type {subjective = 0, objective, assesment, plan} ;
class NSSOAPListWindow;        // classe g�n�rique de documents texte nautilus
#define CLASSIF_PRINCIPLE_NBMAXSLOT 8
class  NSSOAPDocument : public TDocument, public NSRoot
  public:

    NSEpisodus*       pEpisodus ;
    NSDocumentInfo*   pDocInfo ;

    PrinciplesArray*  pPrincipes ;
    OWL::TImageList*  pMainImgList ;

    // Drag And Drop
    OWL::TImageList*  ImgDragDrop ;    // ImageList of the drag-and-drop
    NSSOAPListWindow* pSrcDragDrop ;   // ListWindow source
    NSSOAPListWindow* pDstDragDrop ;   // ListWindow destination
    SOAPObject*       pObject2Drop ;   // object to drop;

    NSSOAPDocument(TDocument *parent, NSContexte *pCtx = (NSContexte*) 0, NSDocumentInfo* pDocInf = (NSDocumentInfo*) 0) ;
    ~NSSOAPDocument();
    bool    enregistrer();

    void    addToTank(SOAPObject* pObject);
    void    removeBasket(SOAPBasket* pBasket);
    void    donneChamp(SOAPObject* pObject);
    string  donneCaseLexique(int index);
    int     donneIconIndex(string sCode);
    bool    acceptDragDrop(SOAPObject *pObject2Drop);
    bool    deleteItemDragDrop(SOAPObject *pObject2Drag);
    bool    floculer();
    void    creerChroniques();

    // M�thodes virtuelles de TDocument
    bool    Close()                                    {return true;}

    bool    IsOpen()                                   {return true;}
    bool    SetNProblems(int i) { nProblems = i ; return true ;};

    int     GetNProblems()  { return nProblems ; };

    NSRefDocument* getDocument() { return pDocument ; }
    bool           setDocument(NSRefDocument* pDoc) ;

//        NSCutPaste* pBufCopie;

  protected:
    int            nProblems ;

    NSRefDocument* pDocument ;
};
class NSSOAPView;

class NSSOAPListWindow : public TListWindow
  public:

    OWL::TWindow*            pParentWindow;
    NSSOAPDocument*          pDocSOAP;
    SOAPBasket*              pBasket;

    ClassificationPrinciple* pPrincipe;

    int                      iColumn;

    OWL::TImageList*         pLgImageList;

    NSSOAPListWindow();
    NSSOAPListWindow(NSSOAPTankView* parent, int id, int x, int y, int w, int h, TModule* module = 0);

    ~NSSOAPListWindow() ;
    // r�ponse aux �v�nements
//        void    EvLButtonDown(uint modKeys, NS_CLASSLIB::TPoint& point);
    void    EvSetFocus(HWND hWndLostFocus);
    void    DispInfoSOAP(TLwDispInfoNotify& dispInfo);

    void    SetupWindow();
    bool    LvnBeginDrag(TLwNotify& nmHdr);
    void    EvMouseMove(uint modKeys, NS_CLASSLIB::TPoint& point);
    void    EvLButtonDown( uint modKeys, NS_CLASSLIB::TPoint& pt);
    void    EvLButtonUp(uint modKeys, NS_CLASSLIB::TPoint& pt);
    void    EvRButtonDown(uint modkeys, NS_CLASSLIB::TPoint& point);
    void    EvLButtonDblClk(uint modkeys, NS_CLASSLIB::TPoint& point);
    void    EvMove(ClassLib::TPoint& clientOrigin);
    void    EvWindowPosChanged(WINDOWPOS far& windowPos);

    void    EvCode();
    void    EvDupliquer();
    void    EvCloner();
    void    EvLibelle();

    void    EvPosit(int iPosit);
    void    EvPosit2() { EvPosit(2); }
    void    EvPosit3() { EvPosit(3); }
    void    EvPosit4() { EvPosit(4); }
    void    EvPosit5() { EvPosit(5); }
    void    EvPosit6() { EvPosit(6); }
    void    EvPosit7() { EvPosit(7); }
    void    EvPosit8() { EvPosit(8); }
    void    EvPosit9() { EvPosit(9); }

    void    EvDupli(int iPosit);
    void    EvDupli2() { EvDupli(2); }
    void    EvDupli3() { EvDupli(3); }
    void    EvDupli4() { EvDupli(4); }
    void    EvDupli5() { EvDupli(5); }
    void    EvDupli6() { EvDupli(6); }
    void    EvDupli7() { EvDupli(7); }
    void    EvDupli8() { EvDupli(8); }
    void    EvDupli9() { EvDupli(9); }

    int     getFocusedItem();

    bool    DeleteItemDragDrop(SOAPObject *pObject2Drag);      // efface la donn�e de sa liste

    void    addObject(SOAPObject* pObject);

  DECLARE_RESPONSE_TABLE(NSSOAPListWindow);
};

typedef vector<NSSOAPListWindow*>   ArraySOAPLW ;
typedef ArraySOAPLW::const_iterator ArraySOAPListWindowConstIter ;

class SOAPListWinArray : public ArraySOAPLW
  public:

    SOAPListWinArray() ;
    ~SOAPListWinArray() ;

    NSSOAPListWindow* trouveList(SOAPBasket* pBasket, ClassificationPrinciple* pPrincipe) ;
    void vider() ;
    SOAPListWinArray& operator=(const SOAPListWinArray& src) ;
  protected:
    bool bOwner ; // L'array est-elle propri�taire des objets r�f�renc�s

class NSSOAPView : public NSMUEView
  public:

    // Constructeur - Destructeur
    ~NSSOAPView();

    void CmOk() {}
    void CmCancel() {}

    // Red�finiton des fonctions virtuelles de TView
    const char      *GetViewName() {return StaticName();}
    TWindow         *GetWindow();
    bool            CanClose();           // de TEditFile
    // bool         CanClear();           // de TEditFile
    bool            SetDocTitle(const char far* docname, int index)
    {
        return OWL::TWindow::SetDocTitle(docname, index);
    }
    void            setViewName() ;

    void            EvDestroy();
    void            RecordWindowPosit();

    void            SetupColumns();
    void            EvSetFocus(HWND hWndLostFocus);
    void            EvMouseMove(uint modKeys, NS_CLASSLIB::TPoint& point);
                    // Fonctions de r�ponse aux evts
    void            EvSize(uint sizeType, ClassLib::TSize &size);
    void            EvMove(ClassLib::TPoint& clientOrigin);
    void            EvWindowPosChanged(WINDOWPOS far& windowPos);
    void            EvPaint();
    void            gotMoved();

    void            addColumn(SOAPBasket* pBasket = 0);
    bool            noItem(int iCol);

    void            transmit();
    // void            addButton();
    void            logMessage(string sLogMessage);
    NSSOAPDocument*     getDoc()    { return pDocSOAP; }

  protected:
    // Variables
    bool                bFirstSetup;
    NSSOAPDocument*     pDocSOAP;	            // Pointeur sur document soap
    int                 nSOAPWindowList;

    bool	            bSetupToolBar;
    // Remplissage de la vue
    void SetupWindow() ;
    void SetupToolBar() ;
    void SetupTxtBar() ;
    void InitFormatFont() ;

    // view event handlers

    void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;

  DECLARE_RESPONSE_TABLE(NSSOAPView) ;

class NSSOAPTankView : public NSMUEView
  public:

    // Constructeur - Destructeur
    NSSOAPTankView(NSSOAPDocument& doc, TWindow *parent = 0, string sPreoccu = "");
    ~NSSOAPTankView();

    void addObject(SOAPObject* pObjectSOAP);
    void reposit();

    void CmOk() {}
    void CmCancel() {}

    // Red�finiton des fonctions virtuelles de TView
    const char      *GetViewName() {return StaticName();}
    TWindow         *GetWindow();
    bool            CanClose();           // de TEditFile
    // bool         CanClear();           // de TEditFile
    bool            SetDocTitle(const char far* docname, int index)
    {
        return OWL::TWindow::SetDocTitle(docname, index);
    }
    void            setViewName() ;

    void            EvDestroy();
    void            RecordWindowPosit();

    // view event handlers

    void            DispInfoTank(TLwDispInfoNotify& dispInfo);
    void            EvMouseMove(uint modKeys, NS_CLASSLIB::TPoint& point);

    NSSOAPListWindow  *pMyListWindow; // ListWindow
    NSSOAPDocument* getDoc() { return pDocSOAP; }
  protected:
    // Remplissage de la vue
    void 	SetupWindow();
    void    SetupToolBar();

    // Fonctions de r�ponse aux evts

    // variables

    bool	       bSetupToolBar ;
  DECLARE_RESPONSE_TABLE(NSSOAPTankView) ;

class NSSOAPLibelleDlg : public TDialog, public NSRoot
  public:

    // Constructeur - Destructeur
    ~NSSOAPLibelleDlg() ;

    void    CmOk() ;

    void    SetupWindow() ;
  protected:
    OWL::TEdit* pLibelEdit ;

  DECLARE_RESPONSE_TABLE(NSSOAPLibelleDlg) ;

class NSSOAPDlg : public TDialog, public NSRoot
  public:

    // Constructeur - Destructeur
    NSSOAPDlg(TWindow *parent, NSContexte *pCtx, string *psdlg);
    ~NSSOAPDlg() ;

    void    CmOk();
    void    CmConvert() ;

//        bool    newFicheClasser(NSEpiClasserData *pData) ;
    bool    newFicheClasserC2(string sCode, string sRelation) ;

  protected:
    OWL::TEdit *pSOAPEdit1 ;
    OWL::TEdit *pSOAPEdit3 ;
    string     *psSOAPEdit ;

  DECLARE_RESPONSE_TABLE(NSSOAPDlg) ;

#endif		// __NS_SOAPVIEW_H