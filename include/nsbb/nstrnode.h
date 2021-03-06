#ifndef __NSTRNODE_H#define __NSTRNODE_H

class NSEncyclo ;
class NSTreeNode ;
class NSTreeWindow ;
class NSCutPaste ;
class NSLinkedNode ;
class NSLinkedNodeArray ;
class Parametre ;
class NSPatPathoInfo ;
class NSControle ;
class Message ;
class NSTransferInfo ;
class BBFilsItem ;

#include <owl/treewind.h>
// #include "nsbb\nsedcon.h"
#include "partage\ns_vector.h"

#ifdef _ENTERPRISE_DLL
  #include "enterpriseLus/nsglobalLus.h"
#else
  #include "partage/nsglobal.h"
#endif

// #include "nssavoir\nsencycl.h"
#include "nssavoir\nsRootLink.h"
#include "nsbb\nsbb_glo.h"
#include "nsbb\nsexport.h"
#include "partage\nsdivfct.h"

//
//trier un vecteur selon la ligne de ses �l�ments
//
bool Tri(NSTreeNode* Node1, NSTreeNode* Node2);

//-------------------------------------------------------------------------
//		VecteurChaine est un vecteur de string
//-------------------------------------------------------------------------

// typedef vector<string*> EquiItem;
// typedef EquiItem::iterator IterString;

class _NSBBCLASSE VecteurChaine : public EquiItem
{
  public:

    VecteurChaine() ;
    ~VecteurChaine() ;
    VecteurChaine(const VecteurChaine& src) ;
    // Surcharge de l'op�rateur d'affectation
		VecteurChaine& operator=(const VecteurChaine& src) ;
    void vider() ;
};

//-------------------------------------------------------------------------
//		classe    NSTreeNode
//-------------------------------------------------------------------------

class	NSTreeNode ;

typedef vector<NSTreeNode*> NSNSTreeNodeArray ;
typedef NSNSTreeNodeArray::iterator       iterNSTreeNode ;
typedef NSNSTreeNodeArray::const_iterator iterNSTreeNodeConst ;

class _NSBBCLASSE NSTreeNodeArray : public  NSNSTreeNodeArray
{
  public :

    // Constructeurs
		NSTreeNodeArray(): NSNSTreeNodeArray() {}
		NSTreeNodeArray(const NSTreeNodeArray& rv) ;
		// Destructeur
		virtual ~NSTreeNodeArray() ;

		NSTreeNodeArray& NSTreeNodeArray::operator=(const NSTreeNodeArray& src) ;
    void vider() ;
    void eraseAll() ;

    void RemoveElement(NSTreeNode* pNSTreeNodeSuppr) ;
    void AddElement(NSTreeNode* pNSTreeNodeSuppr) ;

    bool Contains(string sEtiquette) ;
    bool Contains(int iLine) ;

    NSTreeNode* GetNode(int iLine) ;

    void ShiftLines(int iLineFrom, int iShiftCount, bool bSortAfter = true) ;

    void Sort() ;
};

class _NSBBCLASSE NSFilsTreeNodeArray : public NSTreeNodeArray
{
 	public :

        // Constructeurs
		NSFilsTreeNodeArray() : NSTreeNodeArray() {}
		NSFilsTreeNodeArray(const NSFilsTreeNodeArray& rv) ;

		// Destructeur		virtual ~NSFilsTreeNodeArray() ;
		NSFilsTreeNodeArray& NSFilsTreeNodeArray::operator=(const NSFilsTreeNodeArray& src) ;
    void Referencer(NSTreeNode* pNewNSTreeNode, NSTreeNode* pNSTreeNodeFrere = (NSTreeNode*) 0) ;
    void vider() ;

    void RemoveElement(NSTreeNode* pNSTreeNodeSuppr) ;
};

class _NSBBCLASSE NSFrereTreeNodeArray : public NSTreeNodeArray
{
  public :

    // Constructeurs		NSFrereTreeNodeArray(): NSTreeNodeArray() {}
		NSFrereTreeNodeArray(const NSFrereTreeNodeArray& rv) ;
		// Destructeur
		virtual ~NSFrereTreeNodeArray() ;
		NSFrereTreeNodeArray& NSFrereTreeNodeArray::operator=(const NSFrereTreeNodeArray& src) ;
    void vider() ;

    void RemoveElement(NSTreeNode* pNSTreeNodeSuppr) ;
};

class NSTlibre ;
class NSTreeWidow ;

class _NSBBCLASSE NSTreeNode : public OWL::TTreeNode, public NSRoot
{
  protected:

    string 			_sNoeud ;         // Noeud    string 			_sIdentite ;      // Etiquette
    string 			_sUnit ;          // Unit�
    string			_sInteret ;       // Champ inter�t patpatho
    string			_sPluriel ;       // Champ pluriel patpatho
    string			_sCertitude ;     // Champ certitude patpatho
    string 			_sLocalisation ;  // Position dans l'arbre
    string 			_sVisible ;       // Visible ou non
    string 			_sNodeRights ;    // Rosace

  public:

    NSControle*          _pControle ;

    bool                 _bEncyclop ;    // cet NStreeNode est ref�renc� dans
    bool                 _bCertif ;      // cet NStreeNode est ref�renc� dans
                                         // NSEncyclop.db ou non
    string               _sUrl ;         // Adresse URL (NSEncyclop.db)
    string               _sUrlCertif ;   // Adresse URL certificat (NSEncyclop.db)
    Parametre*           _pParametre ;   // Bo�te des param�tres
    // char                 _szType[25] ;   // Type de contr�le EDIT
    NSTreeNode*          _pere ;         // Pere cr�ateur du NSTreeNode
    NSFilsTreeNodeArray  _VectFils ;     // Vecteur des fils d'un NSTreeNode
    NSFrereTreeNodeArray _VectFrereLie ; // Vecteur des fr�res li�s � un NSTreeNode
    NSTreeNode*          _FrerePilote ;  // Fr�re contenant le texte libre
    bool                 _Absence ;      // Absence ou non de la pathologie
    bool                 _estPropose ;   // El�ment du fil guide propos�
                                            // mais non valid�

    bool   _CreateurChampEdit ; // �l�ment recevant une valeur chiffr�e
    bool   _bRecalcul ;         // recalcul ou non selon CONVERT.DB et autres param�tres

    bool   _DateHeure ;     // �l�ment recevant une date ou une heure
    string _sContenuBrut ;
    string _sContenuTransfert ;
    string _Type ;
    string _sLabel ;        // label du NSTreeNode : exp grippe
    string _code ;          // texte libre : code de la fiche contenant le texte dans ce noeud
    string _sTexteGlobal ;  // contient le texte libre global de ce NStreeNode

    //variable sp�cifiques � l'affichafge des documents dans l'historique
    void*  _pDocument ;     // document support� par le noeud
    bool   _bOuvert ;       // document ouvert ou ferm�

    // Liens entre ce noeud (pas encore enregistr�) et d'autres noeuds
    NSLinkedNodeArray* _pTemporaryLinks ;

    NSTreeNode(TTreeWindow& treeWind, NSContexte* pCtx, HTREEITEM hItem = TVI_ROOT) ;
    NSTreeNode(TTreeWindow& treeWind, NSContexte* pCtx, string text) ; // constructeur "private"
    NSTreeNode(const OWL::TTreeNode& treeNode, TNextCode nextCode, NSContexte* pCtx) ;
    NSTreeNode(const OWL::TTreeNode& treeNode, NSContexte* pCtx) ;
    //copie    NSTreeNode(const NSTreeNode& src) ;
    virtual ~NSTreeNode() ;
    // Surcharges des op�rateurs
		NSTreeNode& operator=(const NSTreeNode& src) ;
    // Mise � z�ro
    void   initialiser() ;
    //
    // methodes
    //
    void   activeControle(int activation, Message* pMessage = (Message*) 0)  ;
    uint   Transferer(TTransferDirection direction, CTRL_ACTIVITY* pActif, Message* pMessage = (Message*) 0) ;
    uint   TempTransferer(CTRL_ACTIVITY* pActif, Message* pMessage = (Message*) 0) ;
    uint   TransfererFinal(TTransferDirection direction, CTRL_ACTIVITY* pActif, Message* pMessage = (Message*) 0) ;

 		bool   MettreAjourLabel(NSTlibre* pNSTlibre, bool* pTexteRecupere,
                                int* pTailleVecteur, int ligne, int colonne,
                                string sTexteLibre, string sCodeTexteLibre,
                                string sIdentitepatho, NSTreeWindow* pTreeWindow,
                                string langue) ;

		WNDTYPE donneType() { return(isTreeNode) ; }
    void   DicoKillFocus(string* pContenu, string NewType) ;
    void   ctrlNotification() ;
    void   MettreAJourLigne(int Decalageligne) ; //decalage des lignes de Decalageligne
    bool   Descendant(NSTreeNode* pNSTreeNode) ;
    bool   estFictif() ;
    bool   estLie() ;
    void   Interet() ;
    string Certitude() ;
    void   PresenceLexique() ;
    void   AbsenceLexique() ;
    void   Encyclop() ;
    void   ExpandTousNoeud() ;
    void   CollapseTousNoeud() ;
    void   donneIneretMax(string* pInteretMax) ;
    void   InitialiseAffichage() ;
    void   InstancieUrl(NSEncyclo* pNSEncyclo) ;
    void   AfficheLabel(string sUnite) ;    bool   estFictifPur() ;
    bool   estUnDocument() ;
    void   activateFilsItem() ;

    void   RecupereParametre() ;

    void   fixeInteret(string sInteret) ;
    void   fixeCertitude(string sCertitude) ;
    void   fixePluriel(string sPluriel) ;

    string getNodeId() ;

    string getNoeud()       { return _sNoeud ; }    string getEtiquette()   { return _sIdentite ; }    string getUnit()        { return _sUnit ; }    string getInteret()     { return _sInteret ; }
    string getPluriel()     { return _sPluriel ; }
    string getCertitude()   { return _sCertitude ; }
    string getVisible()     { return _sVisible ; }
    string getPosition()    { return _sLocalisation ; }
    string getRights()    	{ return _sNodeRights ; }

    string      getLabelString()  { return _sLabel ; }
    string      getFreeTextCode() { return _code ; }
    string      getGlobalText()   { return _sTexteGlobal ; }
    string      getContenuTransfert() { return _sContenuTransfert ; }
    string      getType()         { return _Type ; }
    string      getUrl()          { return _sUrl ; }
    NSTreeNode* getFatherNode()   { return _pere ; }
    NSTreeNode* getPilotNode()    { return _FrerePilote ; }
    bool        isProposed()      { return _estPropose ; }
    bool        isCreateurChampEdit() { return _CreateurChampEdit ; }
    bool        isDateTime()          { return _DateHeure ; }
    bool        isRecalcul()          { return _bRecalcul ; }
    bool        isAbsent()            { return _Absence ; }
    bool        isEncyclop()          { return _bEncyclop ; }
    NSControle* getControl()      { return _pControle ; }
    void*       getDocument()     { return _pDocument ; }
    bool        isDocumentOpen()  { return _bOuvert ; }

    NSFilsTreeNodeArray*  getVectSons()       { return &_VectFils ; }
    NSFrereTreeNodeArray* getVectLinkedBros() { return &_VectFrereLie ; }

    void   SetNoeud(const string Noeud)           { _sNoeud = Noeud ; }
    void   SetLexique(const string Lexique)       { _sIdentite = Lexique ; }
    void   SetUnit(const string Unit)             { _sUnit = Unit ; }
    void   SetCertitude(const string Certitude)   { _sCertitude = Certitude ; }
    void   SetInteret(const string Interet)       { _sInteret = Interet ; }
    void   SetComplement(const string Complement) { _sContenuTransfert = Complement ; }
    void   SetPluriel(const string Pluriel)       { _sPluriel = Pluriel ; }
    void   SetVisible(const string Visible)       { _sVisible = Visible ; }
    void   SetPosition(const string Position)     { _sLocalisation = Position ; }
    void   SetRights(const string sRights)        { _sNodeRights = sRights ; }

    void   SetFatherNode(NSTreeNode *pNode)       { _pere = pNode ; }
    void   SetPilotNode(NSTreeNode *pNode)        { _FrerePilote = pNode ; }
    void   SetLabelString(const string sLabel)    { _sLabel = sLabel ; }
    void   SetGlobalText(const string sGT)        { _sTexteGlobal = sGT ; }
    void   SetFreeTextCode(const string sCode)    { _code = sCode ; }
    void   SetType(const string sType)            { _Type = sType ; }
    void   SetUrl(const string sUrl)              { _sUrl = sUrl ; }
    void   SetProposed(const bool bProp)          { _estPropose = bProp ; }
    void   SetCreateurChampEdit(const bool bCCE)  { _CreateurChampEdit = bCCE ; }
    void   SetDateTime(const bool bDT)            { _DateHeure = bDT ; }
    void   SetRecalcul(const bool bRec)           { _bRecalcul = bRec ; }
    void   SetAbsent(const bool bAbs)             { _Absence   = bAbs ; }
    void   SetEncyclop(const bool bEncy)          { _bEncyclop = bEncy ; }
    void   SetControl(NSControle *pCtrl)          { _pControle = pCtrl ; }
    void   SetDocument(void *pDoc)                { _pDocument = pDoc ; }
    void   SetDocumentOpen(const bool bOpen)      { _bOuvert   = bOpen ; }

    void   MettreMonEtiquetteAJour() ;
    void   setLibelle(string sEtiquette, string langue) ;

    int    InsererTexteLibre(Message* pMessage) ;
    void   CopyPatPatho(string sCopie) ;
    int    getLigne() 	 { return _ligne ; }
    int    getColonne()  { return _colonne ; }
    void   formerPatPatho(NSCutPaste* pBuffer) ;
    string getLabel() ;
    string getLabelSens() ;
    void   formerChemin(string* pChemin) ;
    void   formerCheminLocal(string* pChemin, bool bSens = true) ;

    void   trouveLabel(string langue) ;

    void   setLigne(int Ligne)     { _ligne = Ligne ; }
    void   setColonne(int Colonne) { _colonne = Colonne ; }

    void   addLinkedNode(NSLinkedNode* pLnkNode) ;

    bool   canWeClose() ;

    void   addTemporaryLink(string sNode, NSRootLink::NODELINKTYPES iLkType, NODELINKDIRECTION iLkDirection) ;
    void   addTemporaryLink(NSPatPathoInfo* pOtherTemporaryNode, NSRootLink::NODELINKTYPES iLkType, NODELINKDIRECTION iLkDirection) ;

    NSTransferInfo* getTransfert() ;
    BBFilsItem*     getBBFilsItem() ;

    Message*        getTransfertMessage() ;
    void            setTransfertMessage(const Message& message) ;

    void            setMessageIds(Message* pMessage) ;
    void            getMessageIds(Message* pMessage) ;

    static long getNbInstance()	 { return lObjectCount ; }
    static void initNbInstance() { lObjectCount = 0 ; }

  private:

    int    _ligne ;  	//num�ro de la ligne du NSTreeNode
    int    _colonne ; //num�ro de la colonne du NSTreeNode

    static long lObjectCount ;
};

#endif // __NSTRNODE_H

