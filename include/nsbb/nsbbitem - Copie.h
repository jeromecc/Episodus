// -----------------------------------------------------------------------------// nsbbitem.h
// -----------------------------------------------------------------------------
// $Revision: 1.4 $
// $Author: pameline $
// $Date: 2011/03/04 13:55:03 $
// -----------------------------------------------------------------------------
// Ligne de vie - Arrays d'objets de type Vue (au sens Document/Vue)
// Ligne de vie - Arrays of View objects (for Document/View model)
// -----------------------------------------------------------------------------
// FLP - aout 2003
// ...
// KP  - mars 1994
// KP  - septembre 1993
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------// NSBigBro.H
//
// Contient la d�claration de NSBigBrother, gestionnaire g�n�ral des
// applications NAUTILUS.
// KP
// Cr�ation : sept 93         Derni�re mise � jour : mars 94
// -----------------------------------------------------------------------------
#ifndef __NSBBITEM_H
# define __NSBBITEM_H

class NSBBFonction ;
class NSTransferInfo ;
class NSDialog ;
class NsMultiDialog ;
class NSTreeNode ;
class nsGenericParseur ;
class nsarcParseur ;
class nsGuidelineParseur ;
class Citem ;
class Cdialogbox ;
class Creferences ;
class BBItemData ;
class NSVectFatheredPatPathoArray ;
class BBItem ;
class NSControle ;
class NSBBMUEView ;

# include <owl\window.h>

# include <classlib\arrays.h>
# include <cstring.h>

# include "partage\nsglobal.h"
# include "nsbb\nspatpat.h"              // for PatPathoIter

# ifdef __OB1__
#  include "ns_ob1\InterfaceForKs.h"
# endif

//---------------------------------------------------------------------------
//
// Structure de controle des exclusions entre �l�ments
//
//---------------------------------------------------------------------------
class BBFilsExclu
{
	public :

		//string sExclusion; // commentaire !!
    vector <string*> aExclusion ;

    // constructeurs
    BBFilsExclu() ;
    BBFilsExclu(const BBFilsExclu& src) ;

    BBFilsExclu& operator = (const BBFilsExclu src) ;
    int          operator == (BBFilsExclu& o) ;
};

typedef vector <BBFilsExclu*> BBFilsExcluArray ;
typedef BBFilsExcluArray::iterator BBExIter ;

class BBExcluArray : public BBFilsExcluArray
{
	public :
  	// Constructeurs
    BBExcluArray() : BBFilsExcluArray() {}
    BBExcluArray(BBExcluArray& rv) ;
    // Destructeur
    virtual ~BBExcluArray() ;
    void vider() ;
};

// class _NSBBCLASSE BBItem;
//---------------------------------------------------------------------------
// Matrice dynamique de BBFilspFils, objet de transfert correspondant
// � chaque objet BB
//---------------------------------------------------------------------------
typedef vector<BBItem*> BBFilsVecteur ;
typedef BBFilsVecteur::iterator BBiterFils ;

class _NSBBCLASSE VectorBBItem : public BBFilsVecteur
{
	public :

		// Constructeurs
    VectorBBItem() : BBFilsVecteur() {}
    VectorBBItem(VectorBBItem& rv) ;
    // Destructeur
    virtual ~VectorBBItem() ;

    void vider() ;
};
//---------------------------------------------------------------------------
//
// Structure de classement des BBItem fils d'un BBItem donn�
//
//---------------------------------------------------------------------------
class _NSBBCLASSE BBFilsItem : public NSRoot
{
  protected:

    string 			    _sEtiquette ;    // Etiquette de la branche dans l'arbre

    BBItem*			    _pPere ;
    BBItemData* 	  _pDonnees ;		// Donn�es de la fiche GUIDES

    NSTransferInfo*	_pTransfert ; 	// Pointeur sur la structure de transfert

    string			    _sNom ; // Code de la fiche Paradox

	public :

		NSSmallBrother*	pBigBoss ;
		// char			      szNom[CH_CODE_LEN + 1] ; // Code de la fiche Paradox

		bool			      FilsProlongeable ;		// savoir si ce BBFilsItem est
                                                // une feuille ou non
		Citem*          pCitem ;                // Citem d'archetype associ� au BBFilsItem

		bool			      DialogueMultiple ;		//multidialogue ou non

		VectorBBItem	  VectorFils ;    // Objet sur le BBItem s'il existe
                                        // cad si l'�l�ment est non terminal et
                                        // int�resse une fen�tre ouverte

		bool			      estActif ;	    //actif ou non cas des TreeView par exp
		NsMultiDialog*	pNsMultiDialog ;


    bool			      bCorriger ;     //correction du  CR



    BBFilsExclu		  Exclusion ;

    // constructeurs
    BBFilsItem(NSContexte* pCtx, BBItem* pPere, NSSmallBrother* pBig = 0, string Avant = "", string Apres = "") ;
    BBFilsItem(BBFilsItem& src) ;
    ~BBFilsItem() ;

		bool okFermerDialogue(bool rapatrier, bool bDetacheControle = true) ;
    void detacheControle() ;
    void rapatrieTmpPpt(NSPatPathoArray *pTempPatPatho, size_t iLevel) ;

    int Initialiser(string sCodon = "", int iActif = 0) ;

    void creerFils(int indexFils = -1) ;    // Demande aux fils (ou au seul fils indexFils)
                                                // de cr�er leur BBItem s'il appartient au dialogue
    void Desactive() ;
    void Active() ;
    void RemetAZero() ;
    void Redeveloppe() ;
    void Redispatche() ;

    void CreerFilsManuel(NSControle* pControle, NSControle* pControlePetitFrere/*, BBItemData* pDonnees*/) ;
    void tuerFils() ;
    void creerNouveauFils() ;
    void lancerMultiDialogue() ;
    bool ouvreDialog() ;
    int  Actif() ;

    bool actifVide() ;
    void ActiveControle(string sVal) ;      //activer un champ �dit
    void ActiveBouton(string sEtiquette) ;
    void DesactiveControle() ;              //d�sactiver un champ �dit

    NSVectFatheredPatPathoArray* getPatPatho() ;
    NSVectFatheredPatPathoArray* getTmpPatho() ;

    string          getItemLabel()                 { return _sEtiquette ; }
    void            setItemLabel(string sLabel)    { _sEtiquette = sLabel ; }

    string          getFilGuideName()              { return _sNom ; }
    void            setFilGuideName(string sName)  { _sNom = sName ; }

    BBItem*         getItemFather()                { return _pPere ; }
    void            setItemFather(BBItem* pFather) { _pPere = pFather ; }

    BBItemData*     getItemData()                  { return _pDonnees ; }
    void            setItemData(BBItemData* pData) { _pDonnees = pData ; }

    NSTransferInfo* getItemTransfertData()                       { return _pTransfert ; }
    void            setItemTransfertData(NSTransferInfo* pTrans) { _pTransfert = pTrans ; }

    Message*        getItemTransfertMsg() ;

    bool PatPtahovide() ;		        //NSVectPatPathoArray vide  ou non
    bool TmpPptvide() ;		            //NSVectPatPathoArray vide  ou non
    void DestructionManuelle(Message* pMessage) ;
    void DesactiveFils() ;
    bool estPlusZero() ;                // Indique si pDonnees->decalageNiveau == "+00+00"

    NSPatPathoArray* getPatpathoActive(NSPatPathoArray* pPatpathoActuelle,
                                            PatPathoIter pere) ;

    void RemplirPatpatho(NSPatPathoArray* pPatpathoActuelle, PatPathoIter pere) ;
    string getLocalisation() ;

    void cutBadDialogBranches(NSDialog* pDlg) ;
    bool isBadDialogBranch(NSDialog* pDlg) ;

    BBFilsItem& operator=(BBFilsItem src) ;
    int operator == (BBFilsItem& o ) ;
};

//---------------------------------------------------------------------------// Matrice dynamique de BBFilsItem, objet de transfert correspondant
// � chaque objet BB
//---------------------------------------------------------------------------
typedef vector<BBFilsItem*> BBFilsItemArray;
typedef BBFilsItemArray::iterator BBiter;

class _NSBBCLASSE BBFilsArray : public BBFilsItemArray
{
	public :

  	// Constructeurs
    BBFilsArray() : BBFilsItemArray() { gestionVecteur = true ; }
    BBFilsArray(BBFilsArray& rv) ;
    // Destructeur
    virtual ~BBFilsArray() ;

    bool gestionVecteur ;

    BBFilsItem* donneNieme(int indice) ;
    BBFilsItem* donneEtiqu(string* sEtiquette) ;
    void vider() ;
};

// -----------------------------------------------------------------------------
// Classe BBItem
//
// Cette structure sert � m�moriser dans Big-Brother
//    - Les informations de codage et configuration d'un contr�le ou bo�te de
//      dialogue contenus dans le fichier BigBrother PARADOX
//    - les saisies dans la partie de l'objet d'interface correspondant �
//      l'objet BB.
// REMARQUE : Ce type d'objet ne peut �tre cr�� que par un objet BBObj.
// -----------------------------------------------------------------------------
class _NSBBCLASSE BBItem : public NSRoot
{
 protected:

  string			          _sNomDlg ;   // Code de la fiche Paradox

  NSDialog              *_pNSDialog ; // Pointeur sur la NSDialog pour les
                                      // BBItem qui ouvrent une fen�tre

  NSBBMUEView           *_pView ;     // BBItem attach� � une vue
  nsarcParseur          *_pParseur ;  // pointeur sur le parseur d'archetype ou de decisionTree
  BBItemData            *_pDonnees ;	// Donn�es de la fiche GUIDES

 public:

  NSSmallBrother        *pBigBoss ;

  NSPatPathoInfo        *pPatPatho ;
  string                sLocalisation ; 	        // Position dans l'arbre

  BBFilsItem            *pBBFilsPere ;		        // Pointeur sur le BBFilsItem cr�ateur de ce BBItem
  NSPatPathoArray       *pPPTEnCours ;		        // Pointeur sur la PatPatho attribu�e par le pBBFilsPere
  // NSPatPathoArray       *pTempPPT ;		            // Pointeur sur la PatPatho temporaire
  NSPatPathoArray       *pPPTMerge ;                // Pointeur sur la PatPatho de "merge"

  BBFilsArray		        aBBItemFils ;   	        // Pointeurs sur les fils

  // char			            szNomDlg[BB_NOM_DIALOGUE_LEN + 1] ;
  string                sIdArchetype ;
#ifdef __OB1__
  BB1BBInterfaceForKs   KsInterface ;
#endif

  bool                  bModalDialog ;            // Boite modale ou non

  NSBBFonction          *pNSFonction ;	 	        // Pointeur sur l'�ventuelle NSFonction
                                                    // qui remplace ou compl�te la NSDialog
  bool                  bCreateParseur;             // bool�en pour le cas o� on transmet le parseur

  int				            iFilsActif ;	 		        // Num�ro du BBFilsItem qui a la main

  bool                  bActif ;     	 	          // Indicateur d'activation d'un contr�le

  bool                  bMiseAJour ;	 		        // Faut-il tenir compte des modifs ?
  int                   iRetourDlg ;	 		        // Code de retour de la boite de dialogue
  int                   iStatusDlg ;                    // Code pour les r�initialisations d'archetypes

  int                   ID ;         		          // ID de l'�l�ment d'interface qui correspond au fils
                                                  // de l'objet BigBrother en cours

  bool			            bConclusion ;             // savoir si le BBItem sert � la conclusion
  bool			            ConclusionAutomatique ;   // pr�-existence de conclusion automatique
  string			          sPositionConclusion ;     // Avant A La place ou Apr�s conclusion
  bool			            bCacher ;				          // cacher la NSdialog lanc�e par ce BBItem

  int                   iProfondeur ;             // Niveau de profondeur dans l'arbre

  // ---------------------------------------------------------------------------
  // ---------------------------------------------------------------------------
  // Constructeurs et destructeur
  // ---------------------------------------------------------------------------
  // ---------------------------------------------------------------------------

  BBItem(NSContexte* pCtx, BBFilsItem *pere, NSSmallBrother *pBig, NSPatPathoArray *pPPTEnCoursActif, NSPatPathoArray *pPPTEnCoursTMP) ;
  BBItem(NSContexte* pCtx, NSSmallBrother *pBig, bool actif = false, int Id = 0) ;
  BBItem(BBItem& src) ;
  ~BBItem() ;


  // ---------------------------------------------------------------------------
  // ---------------------------------------------------------------------------
  // Surcharge de l'op�rateur d'affectation
  // ---------------------------------------------------------------------------
  // ---------------------------------------------------------------------------

  BBItem&       operator=(BBItem src) ;

  // ---------------------------------------------------------------------------
  // Getters and Setters
  // ---------------------------------------------------------------------------

  string  getDialogName()              { return _sNomDlg ; }
  void    setDialogName(string sName)  { _sNomDlg = sName ; }

  nsarcParseur*     getParseur()       { return _pParseur ; }
  void              setParseur(nsarcParseur *pArc) ;

  // ---------------------------------------------------------------------------
  // ---------------------------------------------------------------------------
  // Fonctions de mise en place de l'arborescence des BBItems
  // ---------------------------------------------------------------------------
  // ---------------------------------------------------------------------------

  int           creer(bool Consultation = false);  // Cr�e les fils, rempli aBBItemFils
  int           createFromArchetype(bool Consultation, string sArchetypeFile) ;
  int           createFromDecisionTree(bool Consultation, string sDecisionTreeFile) ;

  // ---------------------------------------------------------------------------
  // creerFils() demande aux fils de cr�er leur BBItem s'il appartient au
  // dialogue le bool�en consultation sert � emp�cher l'appel de
  // DispatcherPatpatho fait dans creer dans le cas de la consultation car cette
  // fonction est appel�e dans NStreNode.cpp
  // ---------------------------------------------------------------------------
  int           creerFils() ;


  int           creerArchetype(Citem *pItem, bool Consultation = false) ;   // ----------> idem creer pour archetype
  int           creerFilsArchetype() ;                                      // ----------> idem creerFils pour archetype


  // add fab -- 2003/08/07 - fonction that controls if constraint are ok in RC archetype when it is closed
  bool          verifConstraintItem(string* psMessage) ;
  bool          verifConstraintItemForArchetype(string* psMessage, nsarcParseur *pArcParseur) ;
  bool          verifConstraintItemForDecisionTree(string* psMessage, nsGuidelineParseur *pDecisionTreeParseur) ;

  void          CreerFilsManuel(NSControle *pControle, NSControle *pControlePetitFrere /*, BBItemData* pDonnees*/) ;

  int           creerExclus() ;
  int           activer() ;   						                      // Lance la BBItem
  int           developper(string sEtiquette);	                // Demande � une branche de se prolonger
  int           developper(BBFilsItem *pFilsIt, NSPatPathoArray *pPPT = 0, int indexFils = -1) ;
  int           developperConsultation(BBFilsItem *pFilsIt);    // consultation
  int           Initialiser() ;						                      // Initialise les BBItem et BBFilsItem � partir d'une NSLesion
  int           InitialiserSeparateur() ;
  int           InitialiserNumerique() ;
  void          InitFromBBItem(BBItem src) ;

  // ---------------------------------------------------------------------------
  // ---------------------------------------------------------------------------
  // Fonctions de contr�le des boites de dialogue
  // ---------------------------------------------------------------------------
  // ---------------------------------------------------------------------------

  int           creerDialogue() ;
  int           gereRien() ;
  //int           creerDialogueMulti() ;
  bool          okFermerDialogue(bool rapatrier, bool bDetacheControle = true) ;
  void          detacheControle() ;
  void          mergePPTEnCours(bool bKillMerge) ;
  void          rapatrieTmpPpt(NSPatPathoArray *pTempPatPatho, size_t iLevel, bool bRootRecursivity = true) ;

  void          AjouteEtiquette(BBFilsItem *pFils, string sArc = "", NSPatPathoInfo* pPreviousNode = 0, bool bForceEmptyId = false) ;
  void          AjouteTmpEtiquette(NSPatPathoArray *pTempPatPatho, BBFilsItem *pFils, NSPatPathoInfo* pPreviousNode = 0) ;

  // Gestion de l'activation d'un controle Windows
  void          ctrlNotification( BBFilsItem  *pFilsItem,
                                  string      *sIdentite,
                                  int         etatInitial,
                                  int         etatSouhaite,
                                  Message     *pMessage,
                                  int         indexFils) ;

  void          DetruireExclus(BBFilsItem *pFilsIt) ;
  bool          isExcluded(BBFilsItem *pFilsIt1, BBFilsItem *pFilsIt2) ;
  void          arbitrateExcluded(BBFilsItem *pFilsIt1, BBFilsItem *pFilsIt2) ;

  // Recherche du fils qui correspond � un groupe et � une �tiquette donn�e
  BBFilsItem    *ChercheFils(string sIdentite, string sCheminParcouru = "") ;

  TWindow       *donneFenetre() ; 	                // Donne le pointeur de la premi�re fen�tre anc�tre
  bool          actifVide() ; 	   		            // Indique si le BBItem est ou non activ� si vide
  bool          uniciteLesion() ;  	                // Indique si la Lesion est unique ou non
  bool          lienDialogue() ;	  	            // Indique si le BBItem est rattach� � une boite de dialogue
  bool          lienFonction() ;	  	            // Indique si le BBItem est rattach� � une fonction
  bool          ouvreDialog() ;	  	                // Indique si le BBItem est ouvreur de boite de dialogue
  bool          ouvreArchetype() ;                  // Indique si le BBItem est ouvreur d'archetype
  bool          dansDialogue() ;	  	            // Indique si le BBItem est dans une boite de dialogue OUVERTE
  bool          dansMemeDialogue(BBItem *pAutre) ;  // Indique si le BBItem est dans le m�me dialogue que l'autre BBItem
  bool          estPlusZero() ;                     // Indique si pDonnees->decalageNiveau == "+00+00"

  void          donneGenetique(BBItem *pNewFils, string sEtiquette) ;  // Initialise le BBItem
  BBFilsItem    *TrouverFilsAyantBonneEtiquette(string sEtiquette, string sComplement) ;
  string        AjusteEtiquetteAvecDollar(string sComplement) ;
  void          donneRetourDlg(int i) { iRetourDlg = i ; }
  int           getRetourDlg()        { return iRetourDlg ; }
  void          donneStatusDlg(int i) { iStatusDlg = i ; }
  int           getStatusDlg()        { return iStatusDlg ; }
  void          Corriger() ;

  // ---------------------------------------------------------------------------
  // ---------------------------------------------------------------------------
  // M�thodes de r�cup�ration et de positionnement des donn�es
  // ---------------------------------------------------------------------------
  // ---------------------------------------------------------------------------

  bool          state()              { return bActif ; }
  void          state(int i)         { bActif = i ; }
  int           id()    const        { return ID ; }
  void          id(int src)          { ID = src ; }

  // ---------------------------------------------------------------------------
  // ---------------------------------------------------------------------------
  // M.A.J du patpatho
  // ---------------------------------------------------------------------------
  // ---------------------------------------------------------------------------

  // M.A.J du patptho de pFilsItem si on est � la racine
  void	        CreerPatPathoSmallBrother(BBFilsItem *pFilsItem) ;

  BBItem        *CreerBBitem( NSSmallBrother  *pBigBoss,
                              string          sItem,
						                  NSPatPathoArray *pPPT,
                              string          sSens,
                              BBItem          *pBBItemCree) ;

  // M.A.J du patptho de pFilsItem
  void          CreerPatPatho(BBFilsItem *pFilsItemPere, BBFilsItem *pFilsItem) ;
  void          DispatcherPatPatho() ;
  void          DispatcherPatPathoArbitrateExcluded() ;
  void          MiseAjourPatPatho(NSPatPathoArray *pPatpathoFils, NSPatPathoInfo *pPatPatho, int ligneNonNulle) ;
  void          MiseAjourPatPathoZero(NSPatPathoArray *pPatpathoFils, NSPatPathoInfo *pPatPatho, int ligneNonNulle) ;
  void          MiseAjourPatpatho() ;
  void          DestructionManuelle(Message *pMessage) ;
  void          DesactiveFils() ;
  void          RemetAZero() ;
  void          Redeveloppe() ;
  void          Redispatche() ;
  void          ActivePere(BBFilsItem *pFilsIt) ;
  string        EnleveZeo(string *pDollar) ;
  void          CmOkFermer(NSDialog *pDialog) ;
  void          CmCancelFermer(NSDialog *pDialog) ;
  void          DesactivePereFictif(BBFilsItem *pFilsIt) ;
  string        donneVraiChemin() ;
  void          cutBadDialogBranches(NSDialog* pDlg) ;
  bool          isBadDialogBranch(NSDialog* pDlg) ;

  Cdialogbox*   getArchetypeDialog(string sLang) ;
  bool          existArchetypeDialog(string sLang) ;
  string        getArchetypeFunction() ;
  Creferences*  getArchetypeReference() ;
  string        getArchetypeName() ;
  Citem*        getArchetypeRootItem() ;

  //
  //
  NSDialog*     getDialog()               { return _pNSDialog ; }
  NSBBMUEView*  getView()                 { return _pView ;     }
  TWindow*      getVindow()               { return (NULL == _pNSDialog) ? (TWindow*) _pView : (TWindow*) _pNSDialog ; }

  void          setDialog(NSDialog* pDlg) { _pNSDialog = pDlg ; }
  void          setView(NSBBMUEView* pV)  { _pView     = pV ;   }

  NSPatPathoArray* getPPTEncours()        { return pPPTEnCours ; }

  void          setItemData(BBItemData* pIt) ;
  BBItemData*   getItemData()             { return _pDonnees ; }

  string        getItemID() ;
  string        getItemGroupID() ;
  string        getItemSemanticPath() ;
  string        getItemValidityCase() ;
  string        getItemLabel() ;
  string        getItemDialogFile() ;
  string        getItemDialogName() ;
  string        getItemFctFile() ;
  string        getItemFctName() ;
  string        getItemLevelShift() ;
  string        getItemSonsList() ;
  string        getItemSonsRules() ;
  string        getItemSortRules() ;

  void          setItemLabel(string sLabel) ;
  void          setItemDialogFile(string sDlgF) ;
  void          setItemDialogName(string sDlgN) ;
  void          setItemFctFile(string sFctF) ;
  void          setItemFctName(string sFctN) ;
  void          setItemLevelShift(string sLevel) ;
  void          setItemSonsList(string sSons) ;
  void          setItemSonsRules(string sRules) ;
  void          setItemSortRules(string sSort) ;
  void          setItemAutomatic(bool bAuto) ;
  void          setItemEmptyActivation(bool bEA) ;
  void          setItemUnicity(bool bUniq) ;
  void          setItemOpenDialog(bool bOpen) ;
  void          setItemOpenArchetype(bool bOpen) ;
  void          setItemNeeded(bool bNeed) ;
} ;

#endif