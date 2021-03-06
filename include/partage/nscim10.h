//---------------------------------------------------------------------------//     NSCIM10.H
//     PA   juillet 95
//  Contient les d�finitions des objets Mat�riel
//---------------------------------------------------------------------------
#ifndef __NSCIM10_H
#define __NSCIM10_H

#include <classlib\arrays.h>
#include "partage\ns_vector.h"

class NSPatPathoArray ;

#ifndef _ENTERPRISE_DLL
  #include <owl\dialog.h>
  #include <owl\listbox.h>
  #include <owl\groupbox.h>
  #include <owl\button.h>
  #include <owl\listwind.h>

  #include <ns_sgbd\nsfiche.h>
#else
  #include "enterpriseLus\superLus.h"
#endif

// #include "nssavoir\ns_medic.h"
#include "partage\ntarray.h"

#if defined(_DKD_DLL)
	#define _NSDKDCLASSE __export
#else
	#define _NSDKDCLASSE __import
#endif

//
// Taille des champs du fichier CIM10
//
#define CIM_CODE_LEN 				4
#define CIM_LIBELLE_LEN 	  65
#define CIM_MODULE_LEN 	 		5
//
// Ordre des champs du fichier CIM10
//
#define CIM_CODE_FIELD 			1
#define CIM_LIBELLE_FIELD		2
#define CIM_MODULE_FIELD		3

//---------------------------------------------------------------------------
//  Classe NSCIM10
//      ANCETRE : NSFiche
//---------------------------------------------------------------------------
//
// Objet donn�es des Objets Materiel
//
class _NSDKDCLASSE NSCim10Data
{
	public :

		//
		// Variables de stockage des valeurs
		//
		char code[CIM_CODE_LEN + 1];
		char libelle[CIM_LIBELLE_LEN + 1];
		char module[CIM_MODULE_LEN + 1];

		void metAZero();

		NSCim10Data() { metAZero(); }
		NSCim10Data(NSCim10Data& rv);

		NSCim10Data& operator=(const NSCim10Data& src);
		int   		   operator==(const NSCim10Data& o);
};

#ifndef _ENTERPRISE_DLL
class _NSDKDCLASSE NSCim10 : public NSFiche
{
	public :

		NSCim10Data* pDonnees;	  // Donn�es de la fiche PARADOX

		NSCim10(NSSuper* pSuper);
		~NSCim10();

		DBIResult open();
		void alimenteFiche();
		void videFiche();
};
#endif

//
// Objet "Info" correspondant � NSCim10
// (destin� � �tre utilis� dans les containers)
//
class _NSDKDCLASSE NSCim10Info
{
	public:

		NSCim10Data Donnees ;

		NSCim10Info();
#ifndef _ENTERPRISE_DLL
		NSCim10Info(NSCim10* pCim);
#endif
		NSCim10Info(const NSCim10Info& rv);

		NSCim10Info& operator=(const NSCim10Info& src);
		int operator == ( const NSCim10Info& o );
};

//
// D�finition de NSMaterielArray (Array de NSMateriel(s))
//
typedef vector<NSCim10Info*> NSCimInfoArray ;
typedef NSCimInfoArray::iterator CimIter ;
typedef NTArray<NSCim10Info> NSCim10Array ;

/* class NSCim10Array : public NSCimInfoArray
{
	public :

		// Constructeurs
		NSCim10Array() : NSCimInfoArray() {}
		NSCim10Array(NSCim10Array& rv);
      //
		// Destructeur
		virtual ~NSCim10Array();
   	void vider();
}; */

//
// Objet "Boite de dialogue" utilis� pour s�lectionner un code CIM10
//
#ifndef _ENTERPRISE_DLL
class _NSDKDCLASSE ChoixCIM10Dialog : public TDialog, public NSRoot
{
	public:

		string*			 pModule;

		NSCim10Info* 	 pCodeChoisi;

		OWL::TListBox* 	 pMatBox;
		NSCim10Array*    pMatArray;
        int              nbMat;

		UINT				 CodeChoisi;

		ChoixCIM10Dialog(TWindow*, NSContexte* pCtx, string* pModu,
                         NSCim10Info* pCodeChoisi);
		~ChoixCIM10Dialog();

		void SetupWindow();

        void EvKeyDown(uint key, uint repeatCount, uint flags);
		void CmSelectMateriel(WPARAM Cmd);
		void CmCancel();
		void CmMaterielDblClk(WPARAM Cmd);

		void OuvreDocument(int NumDoc);

	DECLARE_RESPONSE_TABLE(ChoixCIM10Dialog);
};
#endif

//
// Taille des champs du fichier CCAM
//
#define CCAM_CODE_LEN          10
#define CCAM_LIBELLE_LEN      150
#define CCAM_MODULE_LEN         6
#define CCAM_PRIX_LEN           7
#define CCAM_FREQ_LEN           2
//
// Ordre des champs du fichier CCAM
//
#define CCAM_CODE_FIELD         1
#define CCAM_LIBELLE_FIELD	    2
#define CCAM_MODULE_FIELD       3
#define CCAM_PRIX_FIELD         4
#define CCAM_FREQ_FIELD         5

//---------------------------------------------------------------------------
//  Classe NSCCAM
//      ANCETRE : NSFiche
//---------------------------------------------------------------------------
//
// Objet donn�es des Objets CCAM
//
class _NSDKDCLASSE NSCcamData
{
	public :

		//
		// Variables de stockage des valeurs
		//
		char code[CCAM_CODE_LEN + 1] ;
		char libelle[CCAM_LIBELLE_LEN + 1] ;
		char module[CCAM_MODULE_LEN + 1] ;
    char prix[CCAM_PRIX_LEN + 1] ;
    char frequence[CCAM_FREQ_LEN + 1] ;

		void metAZero() ;

		NSCcamData() { metAZero() ; }
		NSCcamData(const NSCcamData& rv) ;

		NSCcamData& operator=(const NSCcamData& src) ;
		int   		 operator==(const NSCcamData& o) ;
};

class NSCcamInfo ;

#ifndef _ENTERPRISE_DLL
class _NSDKDCLASSE NSCcam : public NSFiche
{
	public :

		NSCcamData _Donnees ; // Donn�es de la fiche PARADOX

		NSCcam(NSSuper* pSuper) ;
		~NSCcam() ;

    string getCode()      { return string(_Donnees.code) ; }
		string getLibelle()   { return string(_Donnees.libelle) ; }
		string getModule()    { return string(_Donnees.module) ; }
    string getPrix()      { return string(_Donnees.prix) ; }
    string getFrequence() { return string(_Donnees.frequence) ; }

		DBIResult open() ;
		void alimenteFiche() ;
		void videFiche() ;

    DBIResult getRecordByCode(string sCode, NSCcamInfo* pResult, bool bOpenClose, bool bVerbose = true) ;
};
#endif

//
// Objet "Info" correspondant � NSCim10
// (destin� � �tre utilis� dans les containers)
//
class _NSDKDCLASSE NSCcamInfo
{
	public:

		NSCcamData _Donnees ;

		NSCcamInfo() ;
#ifndef _ENTERPRISE_DLL
		NSCcamInfo(const NSCcam* pCim) ;
#endif
		NSCcamInfo(const NSCcamInfo& rv) ;
    ~NSCcamInfo() {}

    string getCode()      const { return string(_Donnees.code) ; }
		string getLibelle()   const { return string(_Donnees.libelle) ; }
		string getModule()    const { return string(_Donnees.module) ; }
    string getPrix()      const { return string(_Donnees.prix) ; }
    string getFrequence() const { return string(_Donnees.frequence) ; }

    int    getPrice()     const { return atoi(_Donnees.prix) ;      }
    int    getFrequency() const { return atoi(_Donnees.frequence) ; }

		NSCcamInfo& operator=(const NSCcamInfo& src) ;
		int         operator==(const NSCcamInfo& o) ;

    void metAZero() { _Donnees.metAZero() ; }
};

//
// D�finition de NSMaterielArray (Array de NSMateriel(s))
//
typedef vector<NSCcamInfo*> NSCcamInfoArray ;
typedef NSCcamInfoArray::iterator         CcamIter ;
typedef NSCcamInfoArray::const_iterator   CcamConstIter ;
typedef NSCcamInfoArray::reverse_iterator CcamReverseIter ;
typedef NTArray<NSCcamInfo> NSCcamArray ;

/* class NSCim10Array : public NSCimInfoArray
{
	public :

		// Constructeurs
		NSCim10Array() : NSCimInfoArray() {}
		NSCim10Array(NSCim10Array& rv);
      //
		// Destructeur
		virtual ~NSCim10Array();
   	void vider();
}; */

class NSListeCCAMWindow ;

//
// Objet "Boite de dialogue" utilis� pour s�lectionner un code CCAM
//
#ifndef _ENTERPRISE_DLL
class _NSDKDCLASSE ChoixCcamDialog : public TDialog, public NSRoot
{
	public:

		string			 		   _sExam ;
    bool               _bGlobalList ;

		NSCcamInfo* 	 	   _pCodeChoisi ;

		NSListeCCAMWindow* _pMatBox ;
		NSCcamArray        _aMatArray ;

		UINT				 		   _iCodeChoisi ;

    OWL::TGroupBox*    _mainShade ;
    OWL::TGroupBox*    _separatorShade ;
    OWL::TButton*      _okButton ;
    OWL::TButton*      _cancelButton ;
    OWL::TButton*      _helpButton ;
    OWL::TButton*      _pChoiceButton ;

		ChoixCcamDialog(TWindow*, NSContexte* pCtx, string* pModu,
                         NSCcamInfo* pCodeChoisi) ;
		~ChoixCcamDialog() ;

		void SetupWindow() ;

    void EvSize(uint sizeType, ClassLib::TSize& size) ;
		void EvKeyDown(uint key, uint repeatCount, uint flags) ;
		void CmSelectMateriel(WPARAM Cmd) ;
		void CmCancel() ;
    void CmOk() ;
		void CmMaterielDblClk(WPARAM Cmd) ;
    void CmElargir() ;

    bool InitCCAMArray() ;
    bool InitCCAMArrayForCode() ;
    bool InitGlobalCCAMArray() ;
		void InitListe() ;
		void AfficheListe() ;		void LvnGetDispInfo(TLwDispInfoNotify& dispInfo) ;
    void LVNColumnclick(TLwNotify& lwn) ;

		void OuvreDocument(int NumDoc) ;

    void sortByCode() ;
    void sortByLibelle() ;
    void sortByPrice() ;
    void sortByFreq() ;

	protected :

		bool _bNaturallySorted ;
		int  _iSortedColumn ;

    void swapSortOrder(int iColumn) ;

	DECLARE_RESPONSE_TABLE(ChoixCcamDialog) ;
};

//
// Objet "ListWindow" avec gestion du double-click (pour les codes CCAM)
//
class _NSDKDCLASSE NSListeCCAMWindow : public TListWindow
{
	public:

		ChoixCcamDialog* pDlg ;

		NSListeCCAMWindow(ChoixCcamDialog* pere, int resId) : TListWindow(pere, resId)
		{
			pDlg = pere ;
    }
		~NSListeCCAMWindow() {}

    void SetupWindow() ;

		void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
    int  IndexItemSelect() ;

	DECLARE_RESPONSE_TABLE(NSListeCCAMWindow) ;
};
#endif // #ifndef _ENTERPRISE_DLL

string _NSDKDCLASSE getBestCcamCodeForExam(string sExam, NSContexte* pCtx, NSPatPathoArray* pPatho) ;

#endif    // __NSCIM10_H

