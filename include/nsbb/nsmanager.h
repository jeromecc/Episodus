// -----------------------------------------------------------------------------
// nsmanager.h
// -----------------------------------------------------------------------------
// Gestion des graphes
// -----------------------------------------------------------------------------
// $Revision: 1.15 $
// $Author: pameline $
// $Date: 2016/12/29 16:36:44 $
// -----------------------------------------------------------------------------
// FLP - 31-08-2004
// adding sort by localisation in NSDataTree, allow to not call to getPatPatho
// in graphPrepare of NSDataArray.
// --
// ajout du sort par localisation dans NSDataTree, permet de ne pas faire de
// getPatPatho dans graphPrepare de NSDataTreeArray.
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Copyright Nautilus, 2004
// http://www.nautilus-info.com
// -----------------------------------------------------------------------------
// Ce logiciel est un programme informatique servant � g�rer et traiter les
// informations de sant� d'une personne.
//
// Ce logiciel est r�gi par la licence CeCILL soumise au droit fran�ais et
// respectant les principes de diffusion des logiciels libres. Vous pouvez
// utiliser, modifier et/ou redistribuer ce programme sous les conditions de la
// licence CeCILL telle que diffus�e par le CEA, le CNRS et l'INRIA sur le site
// "http://www.cecill.info".
//
// En contrepartie de l'accessibilit� au code source et des droits de copie, de
// modification et de redistribution accord�s par cette licence, il n'est offert
// aux utilisateurs qu'une garantie limit�e. Pour les m�mes raisons, seule une
// responsabilit� restreinte p�se sur l'auteur du programme, le titulaire des
// droits patrimoniaux et les conc�dants successifs.
//
// A cet �gard  l'attention de l'utilisateur est attir�e sur les risques
// associ�s au chargement, � l'utilisation, � la modification et/ou au
// d�veloppement et � la reproduction du logiciel par l'utilisateur �tant donn�
// sa sp�cificit� de logiciel libre, qui peut le rendre complexe � manipuler et
// qui le r�serve donc � des d�veloppeurs et des professionnels avertis
// poss�dant des connaissances informatiques approfondies. Les utilisateurs sont
// donc invit�s � charger et tester l'ad�quation du logiciel � leurs besoins
// dans des conditions permettant d'assurer la s�curit� de leurs syst�mes et ou
// de leurs donn�es et, plus g�n�ralement, � l'utiliser et l'exploiter dans les
// m�mes conditions de s�curit�.
//
// Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez pris
// connaissance de la licence CeCILL, et que vous en avez accept� les termes.
// -----------------------------------------------------------------------------
// This software is a computer program whose purpose is to manage and process
// a person's health data.
//
// This software is governed by the CeCILL  license under French law and abiding
// by the rules of distribution of free software. You can use, modify and/ or
// redistribute the software under the terms of the CeCILL license as circulated
// by CEA, CNRS and INRIA at the following URL "http://www.cecill.info".
//
// As a counterpart to the access to the source code and  rights to copy, modify
// and redistribute granted by the license, users are provided only with a
// limited warranty and the software's author, the holder of the economic
// rights, and the successive licensors have only limited liability.
//
// In this respect, the user's attention is drawn to the risks associated with
// loading, using, modifying and/or developing or reproducing the software by
// the user in light of its specific status of free software, that may mean that
// it is complicated to manipulate, and that also therefore means that it is
// reserved for developers and experienced professionals having in-depth
// computer knowledge. Users are therefore encouraged to load and test the
// software's suitability as regards their requirements in conditions enabling
// the security of their systems and/or data to be ensured and, more generally,
// to use and operate it in the same conditions as regards security.
//
// The fact that you are presently reading this means that you have had
// knowledge of the CeCILL license and that you accept its terms.
// -----------------------------------------------------------------------------

#ifndef __NSMANAGER_H__
# define __NSMANAGER_H__

class NSPatPathoArray ;
class NSVectPatPathoArray ;
class NSPatLinkInfo ;
class NSMoralPerson ;

#ifdef _ENTERPRISE_DLL
  #include "enterpriseLus/nsglobalLus.h"
#else
  #include "partage/nsglobal.h"
#endif

# include "partage/ns_vector.h"
# include "nsbb/nsexport.h"
# include "nsbb/nspatpat.h"
# include "nssavoir/nsRootLink.h"
# include "nssavoir/nspatlnk.h"

/**************************************
# ifdef N_TIERS
#  define INMEMORY_CHAR    	"#"
#  define OBJECTINMEMORY		"#$___________"
# else
#  define INMEMORY_CHAR    	"_"
# endif
**************************************/

// -----------------------------------------------------------------------------
// NSDataTree class : to push / get patpathoArray into / from Graphs
// -----------------------------------------------------------------------------
class _NSBBCLASSE NSDataTree : public NSSuperRoot
{
  private:

	  static long _lObjectCount ;

  protected:

 	  NSPatPathoArray  _PatPathoArray ;

    GRAPHTYPE        _iTypeTree ;
    string           _sTreeID ;

    // protocol management data (archetypes, r�f�rentiels)
    //
    string           _sModelName ;
    string           _sModelFileName ;

  public:

    // constructors/destructor
    NSDataTree(NSSuper* pSuper, string treeID, GRAPHTYPE iType) ;
    NSDataTree(const NSDataTree& rv) ;
    ~NSDataTree() ;

    NSDataTree& operator=(const NSDataTree& src) ;
    int 		    operator==(const NSDataTree& o) ;

    static long getNbInstance()  { return _lObjectCount ; }
    static void initNbInstance() { _lObjectCount = 0 ; }

    string  getPerson() { return string(_sTreeID, 0, PIDS_NSS_LEN) ; }
    string  getDocum()  { return string(_sTreeID, PIDS_NSS_LEN, DOC_CODE_DOCUM_LEN) ; }
    string  getTreeID() { return _sTreeID ; }
    void    setTreeID(string treeID) ;

    // m�thode d'acc�s � la patpatho
    void    developpePatPatho(NSPatPathoArray* pPatPatho) ;
    void    contractePatPatho(NSPatPathoArray* pPatPatho) ;
    void    getRawPatPatho(NSPatPathoArray* pPatPatho, bool bModePilot = false) ;
    void    setPatPatho(NSPatPathoArray* pPatPatho, bool bModePilot = false) ;
    string  genereXML() ;
    size_t  size() ;

    NSPatPathoArray* getPatPathoPointer() { return &_PatPathoArray ; }

    // m�thodes g�n�riques pour charger ou enregistrer la patpatho

    void	  sortPPTByLocalisation()	;

    bool    readParadoxTree() ;

    // m�thodes pour cr�er un nouvel objet tree
    bool    writeParadoxTree(NSPatPathoArray* pPatPathoTree = 0) ;

    string getModelName()     { return _sModelName ; }
    string getModelFileName() { return _sModelFileName ; }

    void   setModelName(string sVal)     { _sModelName = sVal ; }
    void   setModelFileName(string sVal) { _sModelFileName = sVal ; }
} ;

// -----------------------------------------------------------------------------
// D�finition de NSDataTreeArray (Array de NSDataTree(s))
// -----------------------------------------------------------------------------
typedef vector<NSDataTree*>					      NSDataTreeVector ;
typedef NSDataTreeVector::iterator	      NSDataTreeIter ;
typedef NSDataTreeVector::const_iterator	ConstNSDataTreeIter ;

class _NSBBCLASSE NSDataTreeArray : public NSDataTreeVector
{
  private:

    static long _lObjectCount ;

  public:

    // Constructeurs
    NSDataTreeArray() ;
    NSDataTreeArray(const NSDataTreeArray& rv) ;
    // Destructeur
    virtual ~NSDataTreeArray() ;
    void 		vider() ;

    NSDataTreeArray& operator=(const NSDataTreeArray& src) ;
    int 	           operator==(const NSDataTreeArray& o) ;

    static long getNbInstance()  { return _lObjectCount ; }
    static void initNbInstance() { _lObjectCount = 0 ; }

    bool   ExisteTreeID(string sObjectID, NSDataTreeIter* pIter = 0) ;
    bool   ExisteTree(string sTypeLex, NSSuper* pSuper, NSDataTreeIter* pIter = 0) ;
    bool   DetruireTree(string sTypeLex, NSSuper* pSuper) ;
} ;

// -----------------------------------------------------------------------------
// class NSArcLink
// -----------------------------------------------------------------------------
class _NSBBCLASSE NSArcLink : public NSSuperRoot
{
  protected:

    string _sObject ;
    string _sNode ;
    string _sType ;
    string _sModel_object_id ;

    static long _lObjectCount ;

  public:

    // constrcutors/destructor
    NSArcLink(NSSuper* pSuper) ;
    NSArcLink(NSSuper* pSuper, NSPatLinkInfo* pLinkInfo) ;
    NSArcLink(NSSuper* pSuper, string sObject, string sNode, string sType, string sModelID) ;
    NSArcLink(const NSArcLink& rv) ;
    ~NSArcLink() ;

    // operators
    NSArcLink& operator=(const NSArcLink& src) ;
    int        operator==(const NSArcLink& o) ;

    void       setFullNode(string sNode) ;
    string     getFullNode() ;

    string getObject() { return _sObject ; }
    string getNode()   { return _sNode ; }
    string getType()   { return _sType ; }
    string getMOId()   { return _sModel_object_id ; }

    void   setObject(string sVal) { _sObject = sVal ; }
    void   setNode(string sVal)   { _sNode = sVal ; }
    void   setType(string sVal)   { _sType = sVal ; }
    void   setMOId(string sVal)   { _sModel_object_id = sVal ; }

    static long getNbInstance()	  { return _lObjectCount ; }
    static void initNbInstance() 	{ _lObjectCount = 0 ; }
} ;

// -----------------------------------------------------------------------------
// D�finition de NSArcLinkArray (Array de NSArcLink(s))
// -----------------------------------------------------------------------------
typedef vector<NSArcLink*> NSArcLinkVector ;
typedef NSArcLinkVector::iterator       NSArcLinkIter ;
typedef NSArcLinkVector::const_iterator NSArcLinkConstIter ;

class _NSBBCLASSE NSArcLinkArray : public NSArcLinkVector
{
  protected:

    static long _lObjectCount ;

  public:

    // constructors/destructor
    NSArcLinkArray() ;
    NSArcLinkArray(const NSArcLinkArray& rv) ;
    virtual ~NSArcLinkArray() ;

    void vider() ;

    // operators
    NSArcLinkArray& operator=(const NSArcLinkArray& src) ;
    int 	          operator==(const NSArcLinkArray& o) ;

    static long getNbInstance()	 { return _lObjectCount ; }
    static void initNbInstance() { _lObjectCount = 0 ; }
} ;

// -----------------------------------------------------------------------------
// class NSNodeRight
// -----------------------------------------------------------------------------
// Class wich define the right of a node or a document
// A Right is pair of string :
// 		- The id of the element (pathpahto or document)
//    - The Right
// -----------------------------------------------------------------------------
class _NSBBCLASSE NSNodeRight
{
  protected:

    string _sNode ;
    string _sRight ;

    static long _lObjectCount ;

  public:

    NSNodeRight() ;
    NSNodeRight(string nod, string rig) ;
    NSNodeRight(const NSNodeRight& rig) ;
    ~NSNodeRight() ;

    NSNodeRight& operator=(const NSNodeRight& rig) ;
    bool         operator==(const NSNodeRight& rig) ;

    string getNode()  { return _sNode ; }
    string getRight() { return _sRight ; }

    void   setNode(string sVal)  { _sNode = sVal ; }
    void   setRight(string sVal) { _sRight = sVal ; }

    static long getNbInstance()	 { return _lObjectCount ; }
    static void initNbInstance() { _lObjectCount = 0 ; }
} ;

typedef std::vector<NSNodeRight*> NSNodeRightVector ;
typedef NSNodeRightVector::iterator       NSNodeRightIter ;
typedef NSNodeRightVector::const_iterator NSNodeRightConstIter ;

//! Abstract predicat classe for find_if
template <class T, class T2>
class Tester
{
  public:

    Tester(T * p) : _data(p) {}
    virtual bool operator()(T2* p2) = 0 ;

  protected:

    T* _data ;
} ;

class RightTester : public Tester<NSNodeRight, NSNodeRight>
{
  public:

    RightTester(NSNodeRight* p) : Tester<NSNodeRight, NSNodeRight>(p) {}
    bool operator()(NSNodeRight* p2) { return _data->getNode() == p2->getNode() ; }
} ;

class RightStringPredicat : public Tester<std::string, NSNodeRight>
{
  public:

    RightStringPredicat(string* p) : Tester<string, NSNodeRight>(p) {}
    bool operator()(NSNodeRight* p2) { return *_data == p2->getNode() ; }
} ;

//! Class wich contains the Right of the node and document
//! This class provides mechanims to find and element ..
class _NSBBCLASSE NSNodeRightArray : public NSNodeRightVector
{
  protected:

    static long _lObjectCount ;

  public:

    // Constructeurs
    NSNodeRightArray() ;
    NSNodeRightArray(const NSNodeRightArray& rv) ;

    // Destructeur
    virtual ~NSNodeRightArray() ;
    void vider() ;

    NSNodeRightArray&	operator=(const NSNodeRightArray& src) ;
    int 	         		operator==(const NSNodeRightArray& o) ;

    //! Function that search a right for a node
    //! \return If the node is found, we return the right else we return an empty string ""
    string     				find(string temp) ;

    //! Function that search a NSRight Struct
    string    				operator[](string temp) ;

    //! Add an element in the NSRightArray. If the element exist the function
    //! modify the right Else only add element
    void 							set(string node, string right) ;

    //! Remove all the document excepted the right of the document itself
    void 							RemoveAllTreeNodeOfDocument(string doc) ;

    //! Remove a document
    void 							RemoveDocument(string doc) ;

    static long getNbInstance()	 { return _lObjectCount ; }
    static void initNbInstance() { _lObjectCount = 0 ; }
} ;

// -----------------------------------------------------------------------------
// Classe NSDataGraph : GraphManager's Data storage object
// -----------------------------------------------------------------------------
class _NSBBCLASSE NSDataGraph : public NSSuperRoot
{
  private:

 	  static long _lObjectCount ;

  protected:

    string    _sGraphID ;
    GRAPHTYPE _iTypeGraph ;
    string    _sLastTree ;

    NSDataTreeArray  _aTrees ;
    NSPatLinkArray   _aLinks ;
    NSArcLinkArray   _aArchs ;
    NSNodeRightArray _aRights ;

  public :

    NSDataGraph(NSSuper* pSuper, GRAPHTYPE typeGraph) ;
    NSDataGraph(const NSDataGraph& rv) ;

    ~NSDataGraph() ;

    NSDataGraph&    operator=(const NSDataGraph& src) ;
    int							operator==(const NSDataGraph& o) ;

    static long getNbInstance()							{ return _lObjectCount ; }
    static void initNbInstance() 						{ _lObjectCount = 0 ; }

    void      setGraphID(string sGrID) 				  { _sGraphID = sGrID ; }
    string    getGraphID()										  { return _sGraphID ; }
    void      setGraphType(GRAPHTYPE typeGraph) { _iTypeGraph = typeGraph ; }
    GRAPHTYPE getGraphType() 									  { return _iTypeGraph ; }
    void      setLastTree(string sLast = "") ;
    string    getLastContribution() ;
    string    getLastTree()										  { return _sLastTree ; }
    string    getNextTreeID() ;

    string    getDocumentRight(string id)       { return _aRights[id] ; }

    bool    getTree(string sTreeID, NSPatPathoArray* pPatPatho, string* psDocRosace, bool bVerbose = true) ;
    string  setTree(NSPatPathoArray* pPatPatho, string sDocRosace, string sCode = "") ;
    bool    updateNodesTL(NSPatPathoArray* pPatPatho, string sCode) ;
    bool    removeTree(string sTreeID) ;
    bool    replaceTree(string sTreeID, string sNewTreeID, NSPatPathoArray* pNewPatPatho, string sNewDocRosace) ;
    bool    signChanges(string sTreeID, string sContributionID) ;

    void    graphReset() ;
    string  genereXML() ;
    bool    incrementeCode(string& sCompteur) ;

    NSDataTreeArray*  getTrees()  { return &_aTrees ; }
    NSPatLinkArray*   getLinks()  { return &_aLinks ; }
    NSArcLinkArray*   getArchs()  { return &_aArchs ; }
    NSNodeRightArray* getRights() { return &_aRights ; }
} ;

class NSLinkManager ;
class NSBasicAttributeArray ;

// -----------------------------------------------------------------------------
// NSObjectGraphManager
// object manager
// -----------------------------------------------------------------------------
class _NSBBCLASSE NSObjectGraphManager : public NSSuperRoot
{
  private:

    static long _lObjectCount ;

  protected:

    bool					_bReadOnly ;
    bool					_bNeedUnlock ;

    // Data management
    NSDataGraph		*_pDataGraph ;
    NSLinkManager	*_pLinkManager ;

  public:

    // Informations from OIDS

    // constructors/destructor
    NSObjectGraphManager(NSSuper* pSuper) ;
    NSObjectGraphManager(const NSObjectGraphManager& rv) ;
    virtual ~NSObjectGraphManager() ;

    NSObjectGraphManager&	operator=(const NSObjectGraphManager& src) ;

    static long getNbInstance()							{ return _lObjectCount ; }
    static void initNbInstance() 						{ _lObjectCount = 0 ; }

	  void   setRootObject(string sID) { _pDataGraph->setGraphID(sID) ; }
    string getRootObject() 					 { return _pDataGraph->getGraphID() ; }

    bool   getTree(string sID, NSPatPathoArray *pPPT, string *psRosace)			{ return (_pDataGraph->getTree(sID, pPPT, psRosace)) ; }
    string setTree(NSPatPathoArray *pPPT, string sRosace, string sCode = "")	{ return (_pDataGraph->setTree(pPPT, sRosace, sCode)) ; }

    bool   getGraph() ;
    bool   setGraph() ;
    void   graphReset()	{ _pDataGraph->graphReset() ; }
    bool   exportXML(string sFichier = "objgraphtest.xml") ;

    // Fonction de parsing des objets template
    void ParseTemplate(NSPatPathoArray* pPatPathoArray, NSBasicAttributeArray *pTmplArray) ;

    NSDataGraph*   getDataGraph()   { return _pDataGraph ; }
    NSLinkManager* getLinkManager() { return _pLinkManager ; }

    bool					 getReadOnly()    { return _bReadOnly ; }
    bool					 getNeedUnlock()  { return _bNeedUnlock ; }

    void	 setReadOnly(bool bVal)   { _bReadOnly = bVal ; }
    void	 setNeedUnlock(bool bVal) { _bNeedUnlock = bVal ; }
} ;


// -----------------------------------------------------------------------------
// NSAddressGraphManager
// object manager avec les fonctions sp�cifiques aux adresses.
// -----------------------------------------------------------------------------
class _NSBBCLASSE NSAddressGraphManager : public NSObjectGraphManager
{
  public:

    NSAddressGraphManager(NSSuper* pSuper)					 : NSObjectGraphManager(pSuper)	{}
    NSAddressGraphManager(const NSAddressGraphManager& rv) : NSObjectGraphManager(rv)		{}
    ~NSAddressGraphManager() {}

    string  CalculeClefLieu(NSContexte *pContexte, NSPatPathoArray *pPatPathoObject, string sLang) ;
    string  CalculeClefSite(NSPatPathoArray *pPatPathoObject) ;
    string  CalculeClefVoie(NSContexte *pContexte, NSPatPathoArray *pPatPathoObject, string sLang) ;
    string  CalculeClefVille(NSPatPathoArray *pPatPathoObject) ;

    bool    getGraphAdr(string sObjID, NSPatPathoArray *pPatPathoArray = 0) ;
    bool    setGraphAdr(NSContexte *pContexte, NSPatPathoArray *pPatPathoArray, string sLang, string sOperatorID = "") ;
    bool    trouveInfoLieuAdr(string& sNomEspace, string& sTele1, string& sTele2, string& sFax) ;
    bool    trouveInfoSiteAdr(string& sNomSite, string& sNumVoie, string& sBat, string& sEsc, string& sBP, string& sLieuDit) ;
    bool    trouveInfoVoieAdr(NSContexte *pContexte, string& sVoie, string sLang);
    bool    trouveInfoVilleAdr(string& sVille, string& sPays, string& sZip, string& sCedex) ;
    string  trouveLibCourtAdr(NSContexte *pContexte, string sLang) ;
    string  trouveLibLongAdr(NSContexte *pContexte, string sLang) ;
    string  trouveTelAdr() ;
} ;


// -----------------------------------------------------------------------------
// NSTeamGraphManager
// object manager avec les fonctions sp�cifiques aux �quipes (personne morale).
// -----------------------------------------------------------------------------
class _NSBBCLASSE NSTeamGraphManager : public NSObjectGraphManager
{
  public:

    NSTeamGraphManager(NSSuper* pSuper) 			 : NSObjectGraphManager(pSuper) {}
    NSTeamGraphManager(const NSTeamGraphManager& rv) : NSObjectGraphManager(rv)	{}
    ~NSTeamGraphManager() {}

    bool    					getTeamGraph(string sObjID, NSPatPathoArray *pPPT = 0) ;
    bool    					setTeamGraph(NSPatPathoArray *pPPT, string sOperatorID = "", bool bLocalTeam = false) ;
    NSMoralPerson *   createTeam(NSContexte *pCtx) ;

    string						getTeamName(NSPatPathoArray *pPPT) ;
} ;

class NSBasicAttributeArray ;
class NSSejourInfo ;

class _NSBBCLASSE NSPersonGraphManager : public NSSuperRoot
{
  private:

    static long _lObjectCount ;

  protected:

    // Informations from PIDS
    bool _bReadOnly ;
    bool _bNeedUnlock ;

    // Data management
    NSDataGraph*           _pDataGraph ;
    NSLinkManager*         _pLinkManager ;
    NSBasicAttributeArray* _pAttrArray ;

  public:

    NSPersonGraphManager(NSSuper* pSuper) ;
    NSPersonGraphManager(const NSPersonGraphManager& rv) ;
    ~NSPersonGraphManager() ;

    NSPersonGraphManager& operator=(const NSPersonGraphManager& src) ;

    static long getNbInstance()  { return _lObjectCount ; }
    static void initNbInstance() { _lObjectCount = 0 ; }

	  // Fonctions de base
    void    setRootTree(string sTrID) ;
    string  getRootTree() ;
    bool    getTree(string sObjectID, NSPatPathoArray* pPatPatho, string* psDocRosace, bool bVerbose = true) ;
    string  setTree(NSPatPathoArray* pPatPatho, string sDocRosace, string sCode = "") ;
    bool    updateTrees(NSContexte *pContexte, NSVectPatPathoArray* pVectTrees, string* psNewDataTreeId, string* psNewMetaTreeId = 0, PIDSTYPE iTypePids = pidsPatient, bool bInterface = true) ;
    bool    commitGraphTree(NSContexte *pContexte, string& sTreeID, PIDSTYPE iTypePids = pidsPatient) ;
    bool    signChanges(NSContexte *pContexte, string sTreeID) ;
    string  getPersonID() ;

    bool    getGraph() ;
    bool    setGraph() ;
    bool    writeGraph(NSContexte *pContexte, PIDSTYPE iTypePids, NSDataGraph* pGraph = 0) ;
    void    graphReset() ;
    bool	  graphPrepare() ;
    bool    mergeGraph(NSContexte *pContexte, string sPersonID, string sNewRole, string sOldRole);
    bool    mergeTrees(NSContexte *pContexte, NSPatPathoArray* pSource, NSPatPathoArray* pDest);

    string  getDataIdFromMetaId(string sMetaId) ;
    string  getMetaIdFromDataId(string sDataId) ;

    // Administratif
    bool    getGraphAdmin(string sID, bool bVerbose, PIDSTYPE iTypePids = pidsPatient, NSPatPathoArray* pPatPathoArray = 0) ;
    bool    setGraphAdmin(NSContexte *pContexte, NSPatPathoArray* pPatPathoArray, PIDSTYPE iTypePids = pidsPatient) ;
    bool    createGraphAdmin(string sUserID, NSPatPathoArray* pPPTAdmin, NSPatPathoArray* pPPTPDS, PIDSTYPE iTypePids = pidsPatient);
    bool    createPPTAdmin(NSPatPathoArray* pPPTAdmin, string sUserID);
    bool    createPPTPDS(NSPatPathoArray* pPPTPDS, string sUserID);
    bool    modifyGraphAdmin(string sUserID, NSPatPathoArray* pPPTAdmin, NSPatPathoArray* pPPTPDS, PIDSTYPE iTypePids = pidsPatient);
    void    setInfoPids(NSBasicAttributeArray *pAttr) ;
    void    changeInfoPids(NSContexte *pContexte) ;
    bool    validAttributes(PIDSTYPE iTypePids) ;
    void    initAttributesToCore() ;
    string  getAttributeValue(string sBalise) ;
    void    setAttributeValue(string sBalise, string sValue) ;

    bool    trouveNomCorresp(NSContexte *pContexte, string& sInfo) ;
    bool    trouveCivilite(NSContexte *pContexte, string& sInfo, string sLang = "") ;
    bool    trouveObjectAdrPrinc(PIDSTYPE iTypePids, string& sObject, string& sChez) ;
    string  trouveLibLongForInGraphAdr(PIDSTYPE iTypePids) ;
    string  getAddressLabel(NSPatPathoArray* pPPT, PIDSTYPE iTypePids) ;
    bool    trouveEMail(PIDSTYPE iTypePids, string& sInfo) ;
    bool    exportXML(string sFichier = "graphtest.xml") ;
    bool    incrementeCode(string& sCompteur) ;

    // Administratif mode N_TIERS
    bool    createPerson(NSPatPathoArray* pPatPathoArray, int iTypePerson = asPatient) ;
    bool    createKernelGraph(NSPatPathoArray* pPatPathoAdmin) ;
    int     parseMainAttributes(NSContexte *pContexte) ;

    enum    ATTRIB_UPDATER { attribsInit = 0, attribsUpdate, attribsChange } ;

    bool    setAdminAttributes(NSContexte *pContexte, NSPatPathoArray* pPatPathoAdmin, ATTRIB_UPDATER iSettingType) ;
    bool    setPDSAttributes(NSContexte *pContexte, NSPatPathoArray* pPatPathoPDS, ATTRIB_UPDATER iSettingType) ;
    bool    setBothAttributes(NSContexte *pContexte, NSPatPathoArray* pPatPathoDual, ATTRIB_UPDATER iSettingType) ;

    // Gestion des donn�es
    void    ChargePatPathoMeta(NSPatPathoArray* pPatPathoMeta, string sUserId, string typeDoc, string nomDoc, string codeDoc, string sTypeContenu, bool bVisible = true) ;
    void    ChargeDonneesAdmin(NSContexte* pContexte, NSPatPathoArray* pPatPathoArray, string& sNom, string& sPrenom, string& sCode, string& sSexe, string& sNaissance, string& sCivilite, string& sPhone, string& sMobile, string& sMail, string sLang = "fr") ;
    void    setAdminAttrArray(ATTRIB_UPDATER iSettingType, string& sNom, string& sPrenom, string& sSexe, string& sNaissance) ;
    void    ChargeDonneesPDS(NSContexte *pContexte, NSPatPathoArray* pPatPathoArray, string& sMetier, string& sSpec, string& sActiveJob, string& sOrient, string& sCivilite, string& sTitre, string& sVille, string &sAdeli, string &sRpps, string sLang = "fr") ;
    void    setPDSAttrArray(ATTRIB_UPDATER iSettingType, string& sMetier, string& sSpec, string& sActiveJob, string& sOrient, string& sTitre, string& sVille, string& sAdeli) ;
    void    ChargeContacts(NSPatPathoArray* pPatPathoArray, PIDSTYPE iTypePids, string& sTelp, string& sEmail) ;

    void    buildDualPatho(NSPatPathoArray* pDualPatho, NSPatPathoArray* pAdminPatho, NSPatPathoArray* pPDSPatho) ;
    void    partDualPatho(NSPatPathoArray* pDualPatho, NSPatPathoArray* pAdminPatho, NSPatPathoArray* pPDSPatho) ;

    string  getTreeDocId(string sMasterDocId) ;
    string  getStructuredDocId(string sMasterDocId) ;
    string  getExternalDocId(string sMasterDocId) ;
    string  getLinkedDocId(string sMasterDocId, NSRootLink::NODELINKTYPES masterLink) ;

    // Composition
    bool	  setTemplatePres(NSContexte *pContexte, string sCodeDocPres, string sTemplate, string sEnTete);
    bool    getTemplatePres(string sCodeDocPres, string& sTemplate, string& sEnTete);

    // Groupe
    bool    getLibIDsPpt(NSPatPathoArray* pPPTIdent) const ;
    bool    IPPEnCours(NSPatPathoArray* pPPTIdent, string sSite, string* psIpp = (string*) 0, string* psOuvre = (string*) 0, string* psFerme = (string*) 0) const ;
    bool    ClotureIPP(NSPatPathoArray* pPPTIdent, string sSite, string sIpp, NSPatPathoArray* pPPTIpp = (NSPatPathoArray*) 0) ;
    bool    InsereIPPFusion(NSPatPathoArray* pPPTIdent, string sSite, NSPatPathoArray* pPPTIpp) ;

    // S�jours
    bool    LastOpenStay(NSContexte *pContexte, string sDateTime, NSSejourInfo* pStayInfo) ;
    bool    GetStayArray(NSContexte *pContexte, vector<NSSejourInfo*> *pStayArray) ;

    // Gestion du PIDS en MUE
    bool    GetTreesWithLink(string sCodeDocOrigine, NSRootLink::NODELINKTYPES typeLink, bool& bNoLink) ;

    // Gestion des donn�es de suivi
    void    ConnectRootTreeToGoal(NSContexte *pContexte, string sTree, string sGoalNode, NSRootLink::NODELINKTYPES iLink) ;
    void    ConnectNodeToGoal(NSContexte *pContexte, string sTreeNode, string sGoalNode, NSPatPathoArray* pData, NSRootLink::NODELINKTYPES iLink) ;

    NSDataGraph*           getDataGraph()   { return _pDataGraph ; }
    NSLinkManager*         getLinkManager() { return _pLinkManager ; }
    NSBasicAttributeArray* getAttrArray()   { return _pAttrArray ; }

    bool					 getReadOnly()    { return _bReadOnly ; }
    bool					 getNeedUnlock()  { return _bNeedUnlock ; }

    void   setDataGraph(NSDataGraph* pDG) { _pDataGraph = pDG ; }

    void	 setReadOnly(bool bVal)   { _bReadOnly = bVal ; }
    void	 setNeedUnlock(bool bVal) { _bNeedUnlock = bVal ; }
} ;

#endif // !__NSMANAGER_H__

