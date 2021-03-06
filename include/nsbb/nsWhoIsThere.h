// NSBROWSE.H : Définition des objets dialogues contenant ie4/////////////////////////////////////////////////////////////
#if !defined(__NSWHOISTHERE_H)#define __NSWHOISTHERE_H
# include <owl/listwind.h># include <owl/panespli.h># include <owl/mdichild.h>
# include <owl/edit.h>

class NSProgressDlg ;
// class NSCsvRecord ;
// class NSCsvRecordArray ;

// #include "nautilus\nssuper.h"#include "partage\ns_vector.h"
#include "partage\NTArray.h"
#include "nsbb\nsutidlg.h"
#include "nsbb\nslistWind.h"
#include "nsbb\nscomboutil.h"
#include "nautilus\nsbrowseSvce.h"
#include "nsepisod\nsCsvParser.h"

#include "nsbb\nsexport.h"

class NSInsidePersonInformation{
  private:

    static long lObjectCount ;

  public:

    NSInsidePersonInformation() ;
    NSInsidePersonInformation(int iFieldIndex, string sRawData, string sPath, string sData, string sDisplayData, string sUnit = string("")) ;
    ~NSInsidePersonInformation() ;

    NSInsidePersonInformation(const NSInsidePersonInformation& rv) ;

    NSInsidePersonInformation& operator=(const NSInsidePersonInformation& src) ;
    int                        operator==(const NSInsidePersonInformation& o) ;

    string getPath()        { return _sPath ; }
    string getData()        { return _sData ; }
    string getRawData()     { return _sRawData ; }
    string getDisplayData() { return _sDisplayData ; }
    string getUnit()        { return _sUnit ; }

    void   setRawData(string sRD) { _sRawData = sRD ; }

    int    getFieldIndex() { return _iFieldIndex ; }

    static long getNbInstance()  { return lObjectCount ; }
    static void initNbInstance() { lObjectCount = 0 ; }

  protected:

    string _sPath ;
    string _sData ;
    string _sUnit ;

    string _sRawData ;
    string _sDisplayData ;

    int    _iFieldIndex ;
} ;

typedef vector<NSInsidePersonInformation*>          NSInPersonInformationVector ;
typedef NSInPersonInformationVector::iterator       NSInPersonInformationIter ;
typedef NSInPersonInformationVector::const_iterator NSInPersonInformationConstIter ;
typedef NTArray<NSInsidePersonInformation>          NSInPersonInformationArray ;

class NSInsidePerson
{
  private:

    static long lObjectCount ;

  public:

    NSInsidePerson() ;
    ~NSInsidePerson() ;

    NSInsidePerson(const NSInsidePerson& rv) ;

    NSInsidePerson& operator=(const NSInsidePerson& src) ;
    int             operator==(const NSInsidePerson& o) const ;
    int             operator!=(const NSInsidePerson& o) const { return !(o == (*this)) ; }

    string getName() { return _sName ; }

    NSInsidePersonInformation*  getInformation(const string sPath) const ;
    NSInsidePersonInformation*  getInformation(int iIndex) const ;
    NSInPersonInformationArray* getInformations() { return &_aInformation ; }

    string getInformationData(const string sPath) const ;
    string getInformationRawData(const string sPath) const ;
    string getInformationDisplayData(const string sPath) const ;

    void   addInformation(NSInsidePersonInformation* pInfo) { _aInformation.push_back(new NSInsidePersonInformation(*pInfo)) ; }

    bool   isEmpty() { return _aInformation.empty() ; }

    static long getNbInstance()  { return lObjectCount ; }
    static void initNbInstance() { lObjectCount = 0 ; }

  protected:

    NSInPersonInformationArray _aInformation ;
    string                     _sName ;
} ;

typedef vector<NSInsidePerson*>            NSInPersonVector ;
typedef NSInPersonVector::iterator         NSInPersonIter ;
typedef NSInPersonVector::const_iterator   NSInPersonConstIter ;
typedef NSInPersonVector::reverse_iterator NSInPersonReverseIter ;
typedef NTArray<NSInsidePerson>            NSInPersonArray ;

// A chapter from the description file
//
class _NSBBCLASSE NSInPersonField
{
  private:

    static long lObjectCount ;

  public:

    NSInPersonField() ;
    NSInPersonField(NSLocalisedChapter* pLocalisedChapter) ;
    NSInPersonField(int iNumber, string sTitle, string sPath, int iOrder,
                    string sFormat = string(""), string sDisplay = string(""),
                    int iWidth = 100, string sUnit = string(""),
                    string sLexi = string(""), bool bMustAskIfMissing = false) ;
    ~NSInPersonField() ;

    NSInPersonField(const NSInPersonField& rv) ;

    void init() ;

    NSInPersonField& operator=(const NSInPersonField& src) ;

    string getChapter() { return _sChapter ; }
    string getPath()    { return _sPath ; }
    string getFormat()  { return _sFormat ; }
    string getDisplay() { return _sDisplay ; }
    string getTitle()   { return _sTitle ; }
    string getUnit()    { return _sUnit ; }
    string getLexicon() { return _sLexicon ; }
    int    getNumber()  { return _iNumber ; }
    int    getOrder()   { return _iOrder ; }
    int    getWidth()   { return _iWidth ; }

    bool   isField()    { return string("") != _sPath ; }
    bool   isVisible()  { return _iOrder >= 0 ; }

    bool   mustAskIfMissing() { return _bAskIfMissing ; }

    static long getNbInstance()  { return lObjectCount ; }
    static void initNbInstance() { lObjectCount = 0 ; }

  protected:

    int    _iNumber ;  // Field number in CSV file
    int    _iOrder ;   // Diplay order on screen (not displayed if -1)
    int    _iWidth ;
    string _sChapter ;
    string _sTitle ;
    string _sPath ;
    string _sFormat ;
    string _sDisplay ;
    string _sLexicon ;
    string _sUnit ;
    bool   _bAskIfMissing ;
} ;

typedef vector<NSInPersonField*>              NSInPersonFieldVector ;
typedef NSInPersonFieldVector::iterator       NSInPersonFieldIter ;
typedef NSInPersonFieldVector::const_iterator NSInPersonFieldConstIter ;
typedef NTArray<NSInPersonField>              NSInPersonFieldArray ;

class NSInPersonsWindow ;

class NSInPersonsListWindow : public NSSkinableListWindow
{
  public:

    // constructors / destructor
    NSInPersonsListWindow() ;
    NSInPersonsListWindow(NSContexte* pCtx, NSInPersonsWindow *parent, int id, int x, int y, int w, int h, TModule* module = (TModule*) 0) ;
    ~NSInPersonsListWindow() ;

    // Loading mails list
    void    loadInPersons() ;
    void    initPersonsList() ;

    void    initPersonsListFromCsv() ;
    void    addPatientFromCsvEntry(NSCsvRecord* pCsvRecord) ;

    void    initPersonsListFromOdbc() ;

    void    initPersonsListFromHl7Siu() ;
    void    addPatientFromHl7SiuFile(const string sFileName, NSCsvRecordArray* pRecords, const VectString* paHl7Segments) ;
    void    getPatientInfoFromHl7SiuSegment(const string sSegmentName, const string &sSegmentContent, NSInsidePerson *pPerson, const char cSeparator, const string sSeparators) ;
    void    processHl7SiuSegment(const string sSegmentName, const string &sSegmentContent, ClasseStringVector* pSegmentsTank, const string sSeparators) ;

    // réponse aux événements
    bool    VnIsWindow(HWND hWnd) ;
    void    EvLButtonDown(uint modKeys, NS_CLASSLIB::TPoint& point) ;
    void    EvRButtonDown(uint modkeys, NS_CLASSLIB::TPoint& point) ;
    void    EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
    void    EvKeyDown(uint key, uint repeatCount, uint flags) ;
    void    EvSetFocus(HWND hWndLostFocus) ;
    void    EvLButtonUp(uint modKeys, NS_CLASSLIB::TPoint& pt) ;
    void    DispInfoListe(TLwDispInfoNotify& dispInfo) ;
    void    EvTimer(uint timerId) ;

    void    sortByName() ;
    void    sortAgain() ;
    void    LVNColumnclick(TLwNotify& lwn) ;
    void    changeSortOrder(int iCol) ;

    void    sortByFull(int iCol) ;
    void    sortBySelected(int iCol) ;

    int     IndexItemSelect() ;

    void    SetupToolBar() ;
    void    SetupWindow() ;
    void    SetupColumns() ;
    void    AfficheListe() ;
    void    EvKillFocus(HWND hWndGetFocus) ;

    void    seedChanged(string sSeed) ;
    void    refreshList() ;
    void    resetTimer() ;

    void    processSelectionChange() ;
    void    selectCurrentPatientInList() ;

    string  getPathForCol(int iCol) ;

    void    SelectLine(const int iLineIndex) ;
    void    SelectByName(const string sName) ;
    void    SelectByStayId(const string sStayId) ;
    void    SelectByDate(const string sDate) ;

    bool    IsStayPattern(const string &sName) ;
    bool    IsDatePattern(const string &sName) ;

    void    CmOpenPatient() ;
    void    openPatient(NSInsidePerson* pInPerson) ;

    bool    canAddToList() { return _bCanAddToList ; }
    void    addCurrentPatient() ;

    void    CmSetDocParams() ;

    NSInPersonsWindow* getInPersonsWindow() { return _pParentWindow ; }

    bool    bSetupToolBar ;

    string  getIcons() { return _sIcons ; }

  protected:

    string             _sDirectory ;

    // CSV file descriptors
    //
    string             _sCsvFileFullName ;
    bool               _bCsvHasHeader ;
    char               _cCvsSeparator ;

    // ODBC connection descriptors
    //
    string             _sOdbcConnectorName ;
    string             _sOdbcRequest ;

    // HL7 SIU descriptors
    //
    string             _sHl7SiuDir ;
    bool               _bExploreSubDir ;

    // Behavior options
    //
    int                _iRefreshInterval ;
    string             _sUserFilter ;
    bool               _bRemoveWhenOpening ;
    bool               _bCanAddToList ;
    bool               _bCloseAfterAdding ;
    string             _sIcons ;

    NSInPersonArray    _aInPersonsSelected ;
    NSInPersonArray    _aInPersonsFull ;

    int                _iPreviousSelection ;

    bool               _bNaturallySorted ;
    int                _iSortedColumn ;

    int                _iRes ;
    NSInPersonsWindow* _pParentWindow ;
    NSProgressDlg*     _pProgressDlg ;

    NSInPersonField*   _pNameField ;

    void   initNameField() ;

    void   refreshFromCsv() ;
    void   refreshFromOdbc() ;
    void   refreshFromHl7Siu() ;

    void   fillSelectedArray(string sSeed, size_t iRecordIndex = 0) ;
    int    getCutField(const string sSeed) ;
    int    getNewSelectedIndex(NSInsidePerson* pPreviouslySelected) ;

    void   removeFromList(NSInsidePerson* pPersonToRemove) ;
    void   addToList(NSInsidePerson* pPersonToAdd) ;
    bool   createLockFile() ;
    bool   deleteLockFile() ;
    string getLockFileName() ;
    string getTempFileName() ;
    bool   isCompatible(const string sLine, const NSInsidePerson* pPerson) ;

    void   fillInformationForPatient(NSInsidePerson* pPersonToFill) ;
    string getInformationForPath(const string sPath, const string sFormat) ;
    string reverseFormat(const NSPatPathoInfo* pPatPatho, const string sFormat) ;
    bool   areInformationToAsk(const NSInsidePerson* pInsidePerson) ;

    string getLine(size_t* piStart, const string* psContent) ;

  DECLARE_RESPONSE_TABLE(NSInPersonsListWindow) ;
} ;

class NSInPersonsWindow ;
class NSInPersonsGadgetWindow ;

class NSInPersonsRechNomEdit : public OWL::TEdit
{
	public:

		NSInPersonsWindow* pInPersonsWindow ;

		// on bloque le premier Return (booleen false dans NSUtilEdit)
		NSInPersonsRechNomEdit(NSInPersonsWindow* pIPW, NSInPersonsGadgetWindow* pere, int resId, const char far* text, int x, int y, int w, int h) ;
		~NSInPersonsRechNomEdit() {}

		void EvChar(uint key, uint repeatCount, uint flags) ;
		void EvKeyUp(uint key, uint repeatCount, uint flags) ;
    void EvSetFocus(HWND hWndLostFocus) ;

    string GetText() ;
    void   SelectTextInList() ;
    void   GoGetList() ;

	DECLARE_RESPONSE_TABLE(NSInPersonsRechNomEdit) ;
};

class NSInPersonsEditControlGadget : public TControlGadget
{
  public:

    NSInPersonsEditControlGadget(TWindow& control, NS_CLASSLIB::TRect innerRect, NS_CLASSLIB::TRect desiredRect, TBorderStyle bs = None)
                      :TControlGadget(control, bs), _innerRect(innerRect), _desiredRect(desiredRect) {}

  protected:

    void GetInnerRect(NS_CLASSLIB::TRect& innerRect) { innerRect = _innerRect ; }
    void GetDesiredSize(NS_CLASSLIB::TRect& desiredRect) { desiredRect = _desiredRect ; }

    NS_CLASSLIB::TRect _innerRect ;
    NS_CLASSLIB::TRect _desiredRect ;
} ;

class _NSBBCLASSE NSInPersonsGadgetWindow : public TGadgetWindow, public NSRoot
{
  public:

    NSInPersonsGadgetWindow(NSContexte* pCtx, TWindow* parent, bool bAddButtons = false, const char far* title = 0 ) ;
    ~NSInPersonsGadgetWindow() ;

    void EvSetFocus(HWND hWndLostFocus) ;
    void CmOpenPatient() ;
    void CmManual() ;
    void CmRefresh() ;
    void CmAddCurrentPatient() ;

    void activateParent() ;

    int  getGadgetsHeight() ;
    void setPaneSplitter(NSInPersonsWindow* pPS) { _pPaneSplitter = pPS ; }

    NSInPersonsRechNomEdit* getRechNomEdit() { return _pRechNomEdit ; }

  protected:

    void               SetupWindow() ;

    NSInPersonsWindow*      _pPaneSplitter ;
    NSInPersonsRechNomEdit* _pRechNomEdit ;

	DECLARE_RESPONSE_TABLE(NSInPersonsGadgetWindow) ;
} ;

class _NSBBCLASSE NSInPersonsWindow : public TPaneSplitter, public NSRoot
{
  public:

    // NSClientWindow(TWindow* parent, TSplitDirection splitDir, float percent = .50);
    NSInPersonsWindow(NSContexte* pCtx, TWindow* parent, string sDescFile, const char far* title = 0, TModule* module = 0) ;
    ~NSInPersonsWindow() ;

    void  CmOk() ;
    void  CmHelp() ;
    void  CmCancel() ;
    void  CmManual() ;

    void SetFocusForInit() ;

    void seedChanged(string sSeed) ;
    void goGetList(string sSeed) ;
    void refreshList() ;
    void addCurrentPatient() ;

    NSInPersonsListWindow* getList() { return _pListWindow ; }

    void  SelectByName(string sName) { _pListWindow->SelectByName(sName) ; }
    void  openPatient(NSInsidePerson* pPerson) ;

    void  setGadgetWindow(NSInPersonsGadgetWindow* pGW) { _pGadgetPanelWindow = pGW ; }

    NSInPersonFieldArray* getFields()         { return &_aFields ; }
    NSInPersonFieldArray* getVisibleFields()  { return &_aVisibleFields ; }
    NSLocalChapterArray*  getFileDescriptor() { return _pFileDescriptor ; }

    NSInPersonField*      getField(int iNumber) ;
    NSInPersonField*      getFieldForOrder(int iOrder) ;
    NSInPersonField*      getFieldForPath(string sPath) ;
    NSInPersonField*      getFieldForChapter(string sTitle) ;

    NSInPersonsRechNomEdit* getRechNomEdit() { return _pGadgetPanelWindow->getRechNomEdit() ; }
    string                  getSeed() ;
    void                    resetSeed() ;

    bool                  isStaticList()     { return _bStaticList ; }
    bool                  isFromHl7Siu()     { return _bFromHl7Siu ; }

    bool                  hasPractitioner()  { return _bIncludesPractitioner ; }

    void                  SetWindowPosit() ;

    string                getIcons()         { return _pListWindow->getIcons() ; }

  protected:

    void  EvClose() ;
    void  SetupWindow() ;
    void  EvSize(uint sizeType, ClassLib::TSize& size) ;
    void  setGadgetWindowLayout() ;

    void  initFields() ;

    bool                     _bStaticList ;
    bool                     _bFromHl7Siu ;

    TMDIChild*               _pMDIChild ;

    NSInPersonsGadgetWindow* _pGadgetPanelWindow ;
    NSInPersonsListWindow*   _pListWindow ;

    NSLocalChapterArray*     _pFileDescriptor ;
    bool                     _bIncludesPractitioner ;

    NSInPersonFieldArray     _aFields ;
    NSInPersonFieldArray     _aVisibleFields ;

  DECLARE_RESPONSE_TABLE(NSInPersonsWindow) ;
};

// Classe TMDIChild pour la redéfinition de EvClose
/////////////////////////////////////////////////////////
class _NSBBCLASSE NSInPersonsChild : public TMDIChild, public NSRoot
{
	public :

		NSInPersonsChild(NSContexte* pCtx, TMDIClient& parent, const char far* title = 0, TWindow *clientWnd = (TWindow*) 0) ;
		~NSInPersonsChild() ;

		void EvClose() ;

	DECLARE_RESPONSE_TABLE(NSInPersonsChild) ;
} ;

class MissingInformationControl
{
  public :

    MissingInformationControl(int iInformationIndex) ;
    ~MissingInformationControl() ;

    int getInformationIndex() { return _iInformationIndex ; }

    NTComboBox<string>* getCombo() { return _pCombo ; }
    void setCombo(NTComboBox<string>* pCombo) { _pCombo = pCombo ; }

    NSUtilEdit*         getEdit()  { return _pEdit ; }
    void setEdit(NSUtilEdit* pEdit) { _pEdit = pEdit ; }

  protected :

    int _iInformationIndex ;

    NSUtilEdit*         _pEdit ;
    NTComboBox<string>* _pCombo ;
} ;

typedef vector<MissingInformationControl*>              MissingInformationControlVector ;
typedef MissingInformationControlVector::iterator       MissingInformationControlIter ;
typedef MissingInformationControlVector::const_iterator MissingInformationControlConstIter ;
typedef NTArray<MissingInformationControl>              MissingInformationControlArray ;

class MissingInformationDialog : public NSUtilDialog
{
  public :

    MissingInformationDialog(NSContexte* pCtx, NSInPersonsListWindow *AParent, NSInsidePerson* pPersonInfo, TModule *pNSResModule = 0) ;

    ~MissingInformationDialog() ;

  protected :

    NSInPersonsListWindow* _pParent ;
    NSInsidePerson*        _pPersonInfo ;

    MissingInformationControlArray aControls ;

    int _iNextCtrlId ;
    int _iNextCtrlTop ;

    int _iCtrlInterval ;
    int _iLeftForStatic ;
    int _iStaticWidth ;
    int _iLeftForControl ;

    void CreateControls() ;
    void CreateButtons() ;

    void SetupWindow() ;
    void InitializeControls() ;
    void InitializeUserCombo(MissingInformationControl* pControl) ;
    void InitializeEdit(MissingInformationControl* pControl, NSInPersonField* pField) ;

    void CmOk() ;

    void CreateUserCombo(MissingInformationControl* pControl) ;
    void CreateEditFromUnit(MissingInformationControl* pControl, string sUnit) ;

    MissingInformationControl* getControlForField(int iField) ;
    NSInPersonFieldArray*      getFields() ;

  DECLARE_RESPONSE_TABLE(MissingInformationDialog) ;
} ;

#endif  // __NSWHOISTHERE_H

// fin de nsWhoIsThere.h///////////////////////////////////////////////////////////////

