//---------------------------------------------------------------------------//     NSFSE.H
//
//  Contient les d�finitions des objets de gestion des FSE
//
//  1ere version : PA juin 98   Derni�re modif : 17/06/98
//---------------------------------------------------------------------------
#ifndef __NSFSE16_H
#define __NSFSE16_H

#include <cstring.h>

#include <owl\combobox.h>

class NSFse16Array ;

#include "ns_sgbd\nsfiche.h"#include "partage\nsCIM10.h"#include "nscompta\nsCptaRef.h"
#if defined(_DANSCPTADLL)	#define _CLASSELEXI __export
#else
	#define _CLASSELEXI __import
#endif

#define FSE_NUMCOMPT_LEN 	  	9
#define FSE_NUMPREST_LEN 	  	4

//
// Taille des champs du fichier FSE1610
//
#define FSE1610_DATE_LEN 	  	 	 12
#define FSE1610_LIEU_LEN    		  1
#define FSE1610_CODE_LEN   			  4
#define FSE1610_COMPLMNT_LEN 		  1
#define FSE1610_MONTANT_F_LEN		  7
#define FSE1610_MONTANT_E_LEN  		7
#define FSE1610_QUALIF_LEN  	  	1
#define FSE1610_COEFF_LEN  	  		6
#define FSE1610_DIVIS_LEN			    2
#define FSE1610_QUANTITE_LEN  		2
#define FSE1610_DENOMBR_LEN  	  	2
#define FSE1610_PRIX_UNIT_F_LEN  	7
#define FSE1610_PRIX_UNIT_E_LEN  	7
#define FSE1610_BASE_RMB_LEN  		7
#define FSE1610_TAUX_LEN  	  		3
#define FSE1610_RMB_AMO_LEN  	  	7
#define FSE1610_RMB_AMC_LEN  	  	7
#define FSE1610_RMO_LEN  	  		  2
#define FSE1610_CODE_EXO_LEN  		1

//
// Indice des champs du fichier FSE1610
//
#define FSE1610_NUMCOMPT_FIELD  	1
#define FSE1610_NUMPREST_FIELD 	  2
#define FSE1610_DATE_FIELD 	  	 	3
#define FSE1610_LIEU_FIELD    		4
#define FSE1610_CODE_FIELD   		  5
#define FSE1610_COMPLMNT_FIELD 		6
#define FSE1610_MONTANT_F_FIELD		7
#define FSE1610_MONTANT_E_FIELD  	8
#define FSE1610_QUALIF_FIELD  	  9
#define FSE1610_COEFF_FIELD  	   10
#define FSE1610_DIVIS_FIELD			 11
#define FSE1610_QUANTITE_FIELD   12
#define FSE1610_DENOMBR_FIELD  	 13
#define FSE1610_PRIX_UNIT_F_FIELD 14
#define FSE1610_PRIX_UNIT_E_FIELD 15
#define FSE1610_BASE_RMB_FIELD  	16
#define FSE1610_TAUX_FIELD  	  	17
#define FSE1610_RMB_AMO_FIELD  	  18
#define FSE1610_RMB_AMC_FIELD  	  19
#define FSE1610_RMO_FIELD  	  		20
#define FSE1610_CODE_EXO_FIELD  	21

//
// Taille des champs du fichier FSE1620
//
#define FSE1620_DATE_DEPL_LEN  		12
#define FSE1620_CODE_IFD_LEN 	  	 4
#define FSE1620_MONTANT_IFD_F_LEN	 7
#define FSE1620_MONTANT_IFD_E_LEN  7
#define FSE1620_QUANTITE_LEN 		   2
#define FSE1620_PRIX_UNIT_F_LEN		 7
#define FSE1620_PRIX_UNIT_E_LEN		 7
#define FSE1620_BASE_RMB_LEN     	 7
#define FSE1620_TAUX_LEN     		   3
#define FSE1620_RMB_AMO_LEN     	 7
#define FSE1620_RMB_AMC_LEN     	 7

//
// Indice des champs du fichier FSE1620
//
#define FSE1620_NUMCOMPT_FIELD  		1
#define FSE1620_NUMPREST_FIELD 			2
#define FSE1620_DATE_DEPL_FIELD  		3
#define FSE1620_CODE_IFD_FIELD 	  	4
#define FSE1620_MONTANT_IFD_F_FIELD	5
#define FSE1620_MONTANT_IFD_E_FIELD 6
#define FSE1620_QUANTITE_FIELD 			7
#define FSE1620_PRIX_UNIT_F_FIELD		8
#define FSE1620_PRIX_UNIT_E_FIELD		9
#define FSE1620_BASE_RMB_FIELD     10
#define FSE1620_TAUX_FIELD     		 11
#define FSE1620_RMB_AMO_FIELD      12
#define FSE1620_RMB_AMC_FIELD      13

//
// Taille des champs du fichier FSE1630
//
#define FSE1630_DATE_DEPL_LEN  	 12
#define FSE1630_CODE_IK_LEN 	  	4
#define FSE1630_NBRE_KM_LEN       2
#define FSE1630_MONTANT_IK_F_LEN	7
#define FSE1630_MONTANT_IK_E_LEN  7
#define FSE1630_PRIX_UNIT_F_LEN		7
#define FSE1630_PRIX_UNIT_E_LEN		7
#define FSE1630_BASE_RMB_LEN     	7
#define FSE1630_TAUX_LEN     			3
#define FSE1630_RMB_AMO_LEN     	7
#define FSE1630_RMB_AMC_LEN     	7

//
// Indice des champs du fichier FSE1630
//
#define FSE1630_NUMCOMPT_FIELD  		1
#define FSE1630_NUMPREST_FIELD 			2
#define FSE1630_DATE_DEPL_FIELD  		3
#define FSE1630_CODE_IK_FIELD 	  	4
#define FSE1630_NBRE_KM_FIELD			  5
#define FSE1630_MONTANT_IK_F_FIELD	6
#define FSE1630_MONTANT_IK_E_FIELD  7
#define FSE1630_PRIX_UNIT_F_FIELD		8
#define FSE1630_PRIX_UNIT_E_FIELD		9
#define FSE1630_BASE_RMB_FIELD     10
#define FSE1630_TAUX_FIELD     		 11
#define FSE1630_RMB_AMO_FIELD      12
#define FSE1630_RMB_AMC_FIELD      13

//// Taille des champs du fichier FSECCAM
//
#define FSECCAM_DATE_LEN		       12
#define FSECCAM_CODE_LEN			     10
#define FSECCAM_POURCENT_LEN        2#define FSECCAM_MODIFICATEURS_LEN  10#define FSECCAM_MONTANT_E_LEN			  7

//
// Indice des champs du fichier FSECCAM
//
#define FSECCAM_NUMCOMPT_FIELD			1
#define FSECCAM_NUMPREST_FIELD		  2
#define FSECCAM_DATE_FIELD		      3
#define FSECCAM_CODE_FIELD			    4
#define FSECCAM_POURCENT_FIELD      5#define FSECCAM_MODIFICATEURS_FIELD 6#define FSECCAM_MONTANT_E_FIELD			7
//// Taille des champs du fichier FSELIBRE
//
#define FSELIBRE_DATE_LEN		       12
#define FSELIBRE_CODE_LEN			     10
#define FSELIBRE_POURCENT_LEN       2#define FSELIBRE_MONTANT_LEN        7//
// Indice des champs du fichier FSELIBRE
//
#define FSELIBRE_NUMCOMPT_FIELD			1
#define FSELIBRE_NUMPREST_FIELD		  2
#define FSELIBRE_DATE_FIELD		      3
#define FSELIBRE_CODE_FIELD			    4
#define FSELIBRE_POURCENT_FIELD     5#define FSELIBRE_MONTANT_E_FIELD		6#define FSELIBRE_MONTANT_F_FIELD		7//// Taille des champs du fichier FSEMAT
//
#define FSEMAT_CODE_LEN          10
#define FSEMAT_MONTANT_LEN		    7

//
// Indice des champs du fichier FSEMAT
//
#define FSEMAT_NUMCOMPT_FIELD     1
#define FSEMAT_NUMPREST_FIELD     2
#define FSEMAT_CODE_FIELD         3
#define FSEMAT_MONTANT_E_FIELD    4
#define FSEMAT_MONTANT_F_FIELD    5
//
// Taille des champs du fichier CODPREST
//
#define CODPREST_CODE_LEN			  4
#define CODPREST_LIBELLE_LEN	 80
#define CODPREST_FSE16XX_LEN		4
#define CODPREST_PRIX_F_LEN			7
#define CODPREST_PRIX_E_LEN			7

//
// Indice des champs du fichier CODPREST
//
#define CODPREST_CODE_FIELD			1
#define CODPREST_LIBELLE_FIELD	2
#define CODPREST_FSE16XX_FIELD	3
#define CODPREST_PRIX_F_FIELD		4
#define CODPREST_PRIX_E_FIELD		5

//------------------------------ Fse1610.db -------------------------------------
//
//---------------------------------------------------------------------------
//  Classe NSFse1610Data
//---------------------------------------------------------------------------
//
// Objet contenant les donn�es
//class _CLASSELEXI NSFse1610Data
{
  public :

    //    // Variables de stockage des valeurs
    //
    char numcompt[FSE_NUMCOMPT_LEN + 1];
    char numprest[FSE_NUMPREST_LEN + 1];
    char date[FSE1610_DATE_LEN + 1];
    char lieu[FSE1610_LIEU_LEN + 1];
    char code[FSE1610_CODE_LEN + 1];
    char complmnt[FSE1610_COMPLMNT_LEN + 1];
    char montant_f[FSE1610_MONTANT_F_LEN + 1];
    char montant_e[FSE1610_MONTANT_E_LEN + 1];    char qualif[FSE1610_QUALIF_LEN + 1];
    char coeff[FSE1610_COEFF_LEN + 1];
    char divis[FSE1610_DIVIS_LEN + 1];
    char quantite[FSE1610_QUANTITE_LEN + 1];
    char denombr[FSE1610_DENOMBR_LEN + 1];
    char prix_unit_f[FSE1610_PRIX_UNIT_F_LEN + 1];    char prix_unit_e[FSE1610_PRIX_UNIT_E_LEN + 1];
    char base_rmb[FSE1610_BASE_RMB_LEN + 1];
    char taux[FSE1610_TAUX_LEN + 1];
    char rmb_amo[FSE1610_RMB_AMO_LEN + 1];
    char rmb_amc[FSE1610_RMB_AMC_LEN + 1];
    char rmo[FSE1610_RMO_LEN + 1];
		char code_exo[FSE1610_CODE_EXO_LEN + 1];

    NSFse1610Data() ;
    NSFse1610Data(const NSFse1610Data& rv) ;
    ~NSFse1610Data() ;

    NSFse1610Data& operator=(const NSFse1610Data& src) ;
    int            operator==(const NSFse1610Data& o) ;

    void metAZero() ;

    string getNumCompt() const { return string(numcompt) ; }
    string getNumPrest() const { return string(numprest) ; }

    void setNumCompt(string sN) { strcpy(numcompt, sN.c_str()) ; }
    void setNumPrest(string sN) { strcpy(numprest, sN.c_str()) ; }
};

//---------------------------------------------------------------------------//  Classe NSFse1610
//---------------------------------------------------------------------------
//
// Objet d�riv� de NSFiche servant aux acc�s de base de donn�es
//
class _CLASSELEXI NSFse1610 : public NSFiche
{
  public :
    //
    // Objet qui contient les donn�es
    //
    NSFse1610Data _Donnees ;

    NSFse1610(NSSuper* pSuper) ;
    NSFse1610(const NSFse1610& rv) ;
    ~NSFse1610() ;

    void alimenteFiche() ;
    void videFiche() ;
    DBIResult open() ;

    virtual bool Create() ;
    virtual bool Modify() ;

    NSFse1610& operator=(const NSFse1610& src) ;
    int        operator==(const NSFse1610& o) ;

    string getNumCompt() { return _Donnees.getNumCompt() ; }
    string getNumPrest() { return _Donnees.getNumPrest() ; }

    void setNumCompt(string sN) { _Donnees.setNumCompt(sN) ; }
    void setNumPrest(string sN) { _Donnees.setNumPrest(sN) ; }
};

//---------------------------------------------------------------------------//  Classe NSFse1610Info  (destin�e � �tre stock�e dans une Array)
//---------------------------------------------------------------------------
class _CLASSELEXI NSFse1610Info
{
	public :

		//		// Objet qui contient les donn�es
		//
		NSFse1610Data _Donnees ;

		NSFse1610Info() ;
		NSFse1610Info(const NSFse1610*) ;
		NSFse1610Info(const NSFse1610Info& rv) ;
    ~NSFse1610Info() ;

		NSFse1610Info& operator=(const NSFse1610Info& src) ;
		int            operator==(const NSFse1610Info& o) ;

    string getNumCompt() { return _Donnees.getNumCompt() ; }
    string getNumPrest() { return _Donnees.getNumPrest() ; }

    void setNumCompt(string sN) { _Donnees.setNumCompt(sN) ; }
    void setNumPrest(string sN) { _Donnees.setNumPrest(sN) ; }

    string exportAsString() ;
    void   importFromString(string sModele) ;
};

//--------------------------- Fse1620.db ------------------------------------
//
//---------------------------------------------------------------------------
//  Classe NSFse1620Data
//---------------------------------------------------------------------------
//
// Objet contenant les donn�es
//
class _CLASSELEXI NSFse1620Data{
  public :
    //
    // Variables de stockage des valeurs
    //
    char numcompt[FSE_NUMCOMPT_LEN + 1];
    char numprest[FSE_NUMPREST_LEN + 1];
    char date_depl[FSE1620_DATE_DEPL_LEN + 1];
    char code_ifd[FSE1620_CODE_IFD_LEN + 1];
    char montant_ifd_f[FSE1620_MONTANT_IFD_F_LEN + 1];
    char montant_ifd_e[FSE1620_MONTANT_IFD_E_LEN + 1];
    char quantite[FSE1620_QUANTITE_LEN + 1];
    char prix_unit_f[FSE1620_PRIX_UNIT_F_LEN + 1];
    char prix_unit_e[FSE1620_PRIX_UNIT_E_LEN + 1];
    char base_rmb[FSE1620_BASE_RMB_LEN + 1];
    char taux[FSE1620_TAUX_LEN + 1];
    char rmb_amo[FSE1620_RMB_AMO_LEN + 1];
    char rmb_amc[FSE1620_RMB_AMC_LEN + 1];

    NSFse1620Data() ;
    NSFse1620Data(const NSFse1620Data& rv) ;
    ~NSFse1620Data() ;

    NSFse1620Data& operator=(const NSFse1620Data& src) ;
    int            operator==(const NSFse1620Data& o) ;

    void metAZero() ;    string getNumCompt() { return string(numcompt) ; }    string getNumPrest() { return string(numprest) ; }    void setNumCompt(string sN) { strcpy(numcompt, sN.c_str()) ; }    void setNumPrest(string sN) { strcpy(numprest, sN.c_str()) ; }};

//---------------------------------------------------------------------------//  Classe NSFse1620
//---------------------------------------------------------------------------
//
// Objet d�riv� de NSFiche servant aux acc�s de base de donn�es
//
class _CLASSELEXI NSFse1620 : public NSFiche
{
  public :

    //    // Objet qui contient les donn�es
    //
    NSFse1620Data _Donnees ;

    NSFse1620(NSSuper* pSuper) ;
    NSFse1620(const NSFse1620& rv) ;
    ~NSFse1620() ;

    void alimenteFiche();
    void videFiche();
    DBIResult open();

    virtual bool Create();
    virtual bool Modify();

    NSFse1620& operator=(const NSFse1620& src) ;
    int        operator==(const NSFse1620& o) ;

    string getNumCompt() { return _Donnees.getNumCompt() ; }
    string getNumPrest() { return _Donnees.getNumPrest() ; }

    void setNumCompt(string sN) { _Donnees.setNumCompt(sN) ; }
    void setNumPrest(string sN) { _Donnees.setNumPrest(sN) ; }
};

//---------------------------------------------------------------------------//  Classe NSFse1620Info  (destin�e � �tre stock�e dans une Array)
//---------------------------------------------------------------------------
class _CLASSELEXI NSFse1620Info
{
	public :

		//		// Objet qui contient les donn�es
		//
		NSFse1620Data _Donnees ;

		NSFse1620Info() ;
		NSFse1620Info(const NSFse1620*) ;
		NSFse1620Info(const NSFse1620Info& rv) ;
    ~NSFse1620Info() ;

		NSFse1620Info& operator=(const NSFse1620Info& src) ;
		int            operator==(const NSFse1620Info& o) ;

    string getNumCompt() { return _Donnees.getNumCompt() ; }
    string getNumPrest() { return _Donnees.getNumPrest() ; }

    void setNumCompt(string sN) { _Donnees.setNumCompt(sN) ; }
    void setNumPrest(string sN) { _Donnees.setNumPrest(sN) ; }

    string exportAsString() ;
    void   importFromString(string sModele) ;
};

//--------------------------- Fse1630.db ------------------------------------//
//---------------------------------------------------------------------------
//  Classe NSFse1630Data
//---------------------------------------------------------------------------
//
// Objet contenant les donn�es
//
class _CLASSELEXI NSFse1630Data
{
	public :

    //    // Variables de stockage des valeurs
    //
    char numcompt[FSE_NUMCOMPT_LEN + 1];
    char numprest[FSE_NUMPREST_LEN + 1];
    char date_depl[FSE1630_DATE_DEPL_LEN + 1];
    char code_ik[FSE1630_CODE_IK_LEN + 1];
    char nbre_km[FSE1630_NBRE_KM_LEN + 1];
    char montant_ik_f[FSE1630_MONTANT_IK_F_LEN + 1];
    char montant_ik_e[FSE1630_MONTANT_IK_E_LEN + 1];
    char prix_unit_f[FSE1630_PRIX_UNIT_F_LEN + 1];
    char prix_unit_e[FSE1630_PRIX_UNIT_E_LEN + 1];
    char base_rmb[FSE1630_BASE_RMB_LEN + 1];
    char taux[FSE1630_TAUX_LEN + 1];
    char rmb_amo[FSE1630_RMB_AMO_LEN + 1];
    char rmb_amc[FSE1630_RMB_AMC_LEN + 1];

    NSFse1630Data() ;
	  NSFse1630Data(const NSFse1630Data& rv) ;
    ~NSFse1630Data() ;

    NSFse1630Data& operator=(const NSFse1630Data& src) ;
    int            operator==(const NSFse1630Data& o) ;

    void metAZero() ;

    string getNumCompt() { return string(numcompt) ; }
    string getNumPrest() { return string(numprest) ; }

    void setNumCompt(string sN) { strcpy(numcompt, sN.c_str()) ; }
    void setNumPrest(string sN) { strcpy(numprest, sN.c_str()) ; }
};

//---------------------------------------------------------------------------//  Classe NSFse1630
//---------------------------------------------------------------------------
//
// Objet d�riv� de NSFiche servant aux acc�s de base de donn�es
//
class _CLASSELEXI NSFse1630 : public NSFiche
{
  public :

    //    // Objet qui contient les donn�es
    //
    NSFse1630Data _Donnees ;

    NSFse1630(NSSuper* pSuper) ;
    NSFse1630(const NSFse1630& rv) ;
    ~NSFse1630() ;

    void alimenteFiche();
    void videFiche();
    DBIResult open();

    virtual bool Create();
    virtual bool Modify();

    NSFse1630& operator=(const NSFse1630& src) ;
    int        operator==(const NSFse1630& o) ;

    string getNumCompt() { return _Donnees.getNumCompt() ; }
    string getNumPrest() { return _Donnees.getNumPrest() ; }

    void setNumCompt(string sN) { _Donnees.setNumCompt(sN) ; }
    void setNumPrest(string sN) { _Donnees.setNumPrest(sN) ; }
};

//---------------------------------------------------------------------------
//  Classe NSFse1630Info  (destin�e � �tre stock�e dans une Array)
//---------------------------------------------------------------------------
class _CLASSELEXI NSFse1630Info
{
	public :

		//
		// Objet qui contient les donn�es
		//
		NSFse1630Data _Donnees ;

		NSFse1630Info() ;
		NSFse1630Info(const NSFse1630*) ;
		NSFse1630Info(const NSFse1630Info& rv) ;
    ~NSFse1630Info() ;

		NSFse1630Info& operator=(const NSFse1630Info& src) ;
		int            operator==(const NSFse1630Info& o) ;

    string getNumCompt() { return _Donnees.getNumCompt() ; }
    string getNumPrest() { return _Donnees.getNumPrest() ; }

    void setNumCompt(string sN) { _Donnees.setNumCompt(sN) ; }
    void setNumPrest(string sN) { _Donnees.setNumPrest(sN) ; }

    string exportAsString() ;
    void   importFromString(string sModele) ;
};
//------------------------------ FseCCAM.db -------------------------------------//
//---------------------------------------------------------------------------
//  Classe NSFseCCAMData
//---------------------------------------------------------------------------
//
// Objet contenant les donn�es
//
class _CLASSELEXI NSFseCCAMData
{
	public :

		//
    // Variables de stockage des valeurs
    //
    char numcompt[FSE_NUMCOMPT_LEN + 1] ;
    char numprest[FSE_NUMPREST_LEN + 1] ;
    char date[FSECCAM_DATE_LEN + 1] ;
    char code[FSECCAM_CODE_LEN + 1] ;
    char pourcent[FSECCAM_POURCENT_LEN + 1] ;    char modificateurs[FSECCAM_MODIFICATEURS_LEN + 1] ;    char montant_e[FSECCAM_MONTANT_E_LEN + 1] ;

    NSFseCCAMData() ;    NSFseCCAMData(const NSFseCCAMData& rv) ;    ~NSFseCCAMData() ;

    NSFseCCAMData& operator=(const NSFseCCAMData& src) ;    int            operator==(const NSFseCCAMData& o) ;

    void metAZero() ;

    string getNumCompt() const { return string(numcompt) ; }
    string getNumPrest() const { return string(numprest) ; }

    void setNumCompt(string sN) { strcpy(numcompt, sN.c_str()) ; }
    void setNumPrest(string sN) { strcpy(numprest, sN.c_str()) ; }
};

//---------------------------------------------------------------------------//  Classe NSFseCCAM
//---------------------------------------------------------------------------
//
// Objet d�riv� de NSFiche servant aux acc�s de base de donn�es
//
class _CLASSELEXI NSFseCCAM : public NSFiche
{
  public :

		//
    // Objet qui contient les donn�es
    //
    NSFseCCAMData _Donnees ;

    NSFseCCAM(NSSuper* pSuper) ;
    NSFseCCAM(const NSFseCCAM& rv) ;
    ~NSFseCCAM() ;

    void      alimenteFiche() ;
    void      videFiche() ;
    DBIResult open() ;

    virtual bool Create() ;
    virtual bool Modify() ;

    bool      initArrayForCompt(string sNumCompt, NSFse16Array *paFseCCAM) ;

    NSFseCCAM& operator=(const NSFseCCAM& src) ;
    int        operator==(const NSFseCCAM& o) ;

    string getNumCompt() { return _Donnees.getNumCompt() ; }
    string getNumPrest() { return _Donnees.getNumPrest() ; }

    void setNumCompt(string sN) { _Donnees.setNumCompt(sN) ; }
    void setNumPrest(string sN) { _Donnees.setNumPrest(sN) ; }
};

//---------------------------------------------------------------------------//  Classe NSFseCCAMInfo  (destin�e � �tre stock�e dans une Array)
//---------------------------------------------------------------------------
class _CLASSELEXI NSFseCCAMInfo
{
	public :

		//
		// Objet qui contient les donn�es
		//
		NSFseCCAMData _Donnees ;

		NSFseCCAMInfo() ;
		NSFseCCAMInfo(const NSFseCCAM*) ;
		NSFseCCAMInfo(const NSFseCCAMInfo& rv) ;
    ~NSFseCCAMInfo() ;

		NSFseCCAMInfo& operator=(const NSFseCCAMInfo& src) ;
		int            operator==(const NSFseCCAMInfo& o) ;

    void initFromCCAMinfo(const NSCcamInfo* pCCAMInfo) ;

    string getNumCompt()      const { return _Donnees.getNumCompt() ; }
    string getNumPrest()      const { return _Donnees.getNumPrest() ; }
    string getDate()          const { return string(_Donnees.date) ; }
    string getCode()          const { return string(_Donnees.code) ; }
    string getPourcent()      const { return string(_Donnees.pourcent) ; }    string getModificateurs() const { return string(_Donnees.modificateurs) ; }    string getMontant_e()     const { return string(_Donnees.montant_e) ; }

    void setNumCompt(string sN) { _Donnees.setNumCompt(sN) ; }
    void setNumPrest(string sN) { _Donnees.setNumPrest(sN) ; }

    string exportAsString() ;
    void   importFromString(string sModele) ;
};

//---------------------------------------------------------------------------
//  Classe NSFseLibre
//---------------------------------------------------------------------------
//
// Objet contenant les donn�es
//
class _CLASSELEXI NSFseLibreData
{
	public :

    NSFseLibreData() ;    NSFseLibreData(const NSFseLibreData& rv) ;    ~NSFseLibreData() ;

    NSFseLibreData& operator=(const NSFseLibreData& src) ;    int             operator==(const NSFseLibreData& o) ;

    void metAZero() ;

    string getNumCompt() const { return string(numcompt) ;  }
    string getNumPrest() const { return string(numprest) ;  }
    string getDate()     const { return string(date) ;      }
    string getCode()     const { return string(code) ;      }
    string getPourcent() const { return string(pourcent) ;  }
    string getMontantE() const { return string(montant_e) ; }
    string getMontantF() const { return string(montant_f) ; }

    void setNumCompt(string sN) { strcpy(numcompt, sN.c_str()) ;  }
    void setNumPrest(string sN) { strcpy(numprest, sN.c_str()) ;  }
    void setDate(string sN)     { strcpy(date, sN.c_str()) ;      }
    void setCode(string sN)     { strcpy(code, sN.c_str()) ;      }
    void setPourcent(string sN) { strcpy(pourcent, sN.c_str()) ;  }
    void setMontantE(string sN) { strcpy(montant_e, sN.c_str()) ; }
    void setMontantF(string sN) { strcpy(montant_f, sN.c_str()) ; }

  // protected :

    char numcompt[FSE_NUMCOMPT_LEN + 1] ;
    char numprest[FSE_NUMPREST_LEN + 1] ;
    char date[FSELIBRE_DATE_LEN + 1] ;
    char code[FSELIBRE_CODE_LEN + 1] ;
    char pourcent[FSELIBRE_POURCENT_LEN + 1] ;    char montant_e[FSELIBRE_MONTANT_LEN + 1] ;    char montant_f[FSELIBRE_MONTANT_LEN + 1] ;};

//
// Objet d�riv� de NSFiche servant aux acc�s de base de donn�es
//
class _CLASSELEXI NSFseLibre : public NSFiche
{
  public :

		//
    // Objet qui contient les donn�es
    //
    NSFseLibreData _Donnees ;

    NSFseLibre(NSSuper* pSuper) ;
    NSFseLibre(const NSFseLibre& rv) ;
    ~NSFseLibre() ;

    void      alimenteFiche() ;
    void      videFiche() ;
    DBIResult open() ;

    virtual bool Create() ;
    virtual bool Modify() ;

    bool      initArrayForCompt(string sNumCompt, NSFse16Array *paFseLibre) ;

    NSFseLibre& operator=(const NSFseLibre& src) ;
    int         operator==(const NSFseLibre& o) ;

    string getNumCompt() const { return _Donnees.getNumCompt() ; }
    string getNumPrest() const { return _Donnees.getNumPrest() ; }
    string getDate()     const { return _Donnees.getDate() ;     }
    string getCode()     const { return _Donnees.getCode() ;     }
    string getPourcent() const { return _Donnees.getPourcent() ; }
    string getMontantE() const { return _Donnees.getMontantE() ; }
    string getMontantF() const { return _Donnees.getMontantF() ; }

    void setNumCompt(string sN) { _Donnees.setNumCompt(sN) ; }
    void setNumPrest(string sN) { _Donnees.setNumPrest(sN) ; }
};

//---------------------------------------------------------------------------
//  Classe NSFseCCAMInfo  (destin�e � �tre stock�e dans une Array)
//---------------------------------------------------------------------------
class _CLASSELEXI NSFseLibreInfo
{
	public :

		//
		// Objet qui contient les donn�es
		//
		NSFseLibreData _Donnees ;

		NSFseLibreInfo() ;
    NSFseLibreInfo(const NSFseLibre*) ;
		NSFseLibreInfo(const NSFseLibreInfo& rv) ;
    ~NSFseLibreInfo() ;

		NSFseLibreInfo& operator=(const NSFseLibreInfo& src) ;
		int             operator==(const NSFseLibreInfo& o) ;

    void initFromLibreInfo(const NSLibreInfo* pLibreInfo) ;

    string getNumCompt() const { return _Donnees.getNumCompt() ; }
    string getNumPrest() const { return _Donnees.getNumPrest() ; }
    string getDate()     const { return _Donnees.getDate() ;     }
    string getCode()     const { return _Donnees.getCode() ;     }
    string getPourcent() const { return _Donnees.getPourcent() ; }
    string getMontantE() const { return _Donnees.getMontantE() ; }
    string getMontantF() const { return _Donnees.getMontantF() ; }

    void setNumCompt(string sN) { _Donnees.setNumCompt(sN) ; }
    void setNumPrest(string sN) { _Donnees.setNumPrest(sN) ; }

    string exportAsString() ;
    void   importFromString(string sModele) ;
};

//------------------------------ FseMAT.db -------------------------------------
//
//---------------------------------------------------------------------------
//  Classe NSFseMatData
//---------------------------------------------------------------------------
//
// Objet contenant les donn�es
//
class _CLASSELEXI NSFseMatData
{
	public :

		//
    // Variables de stockage des valeurs
    //
    char _numcompt[FSE_NUMCOMPT_LEN + 1] ;
    char _numprest[FSE_NUMPREST_LEN + 1] ;
    char _code[FSEMAT_CODE_LEN + 1] ;
    char _montant_f[FSEMAT_MONTANT_LEN + 1] ;
    char _montant_e[FSEMAT_MONTANT_LEN + 1] ;

    NSFseMatData() ;    NSFseMatData(const NSFseMatData& rv) ;    ~NSFseMatData() ;

    NSFseMatData& operator=(const NSFseMatData& src) ;    int           operator==(const NSFseMatData& o) ;

    void metAZero() ;

    string getNumCompt()  const { return string(_numcompt) ;  }
    string getNumPrest()  const { return string(_numprest) ;  }
    string getCode()      const { return string(_code) ;      }
    string getMontant_f() const { return string(_montant_f) ; }
    string getMontant_e() const { return string(_montant_e) ; }

    void setNumCompt(string sN) { strcpy(_numcompt, sN.c_str()) ; }
    void setNumPrest(string sN) { strcpy(_numprest, sN.c_str()) ; }
};

//---------------------------------------------------------------------------//  Classe NSFseMat
//---------------------------------------------------------------------------
//
// Objet d�riv� de NSFiche servant aux acc�s de base de donn�es
//
class _CLASSELEXI NSFseMat : public NSFiche
{
  public :

		//
    // Objet qui contient les donn�es
    //
    NSFseMatData _Donnees ;

    NSFseMat(NSSuper* pSuper) ;
    NSFseMat(const NSFseMat& rv) ;
    ~NSFseMat() ;

    void      alimenteFiche() ;
    void      videFiche() ;
    DBIResult open() ;

    virtual bool Create() ;
    virtual bool Modify() ;

    bool      initArrayForCompt(string sNumCompt, NSFse16Array *paFseCCAM) ;

    NSFseMat& operator=(const NSFseMat& src) ;
    int       operator==(const NSFseMat& o) ;

    string getNumCompt() const { return _Donnees.getNumCompt() ; }
    string getNumPrest() const { return _Donnees.getNumPrest() ; }

    void setNumCompt(string sN) { _Donnees.setNumCompt(sN) ; }
    void setNumPrest(string sN) { _Donnees.setNumPrest(sN) ; }
};

//---------------------------------------------------------------------------//  Classe NSFseMatInfo  (destin�e � �tre stock�e dans une Array)
//---------------------------------------------------------------------------
class _CLASSELEXI NSFseMatInfo
{
	public :

		//
		// Objet qui contient les donn�es
		//
		NSFseMatData _Donnees ;

		NSFseMatInfo() ;
		NSFseMatInfo(const NSFseMat*) ;
		NSFseMatInfo(const NSFseMatInfo& rv) ;
    ~NSFseMatInfo() ;

		NSFseMatInfo& operator=(const NSFseMatInfo& src) ;
		int           operator==(const NSFseMatInfo& o) ;

    void initFromProduitInfo(const NSLotInfo* pLotInfo) ;

    string getNumCompt()  const { return _Donnees.getNumCompt() ;  }
    string getNumPrest()  const { return _Donnees.getNumPrest() ;  }
    string getCode()      const { return _Donnees.getCode() ;      }
    string getMontant_f() const { return _Donnees.getMontant_f() ; }
    string getMontant_e() const { return _Donnees.getMontant_e() ; }

    void setNumCompt(string sN) { _Donnees.setNumCompt(sN) ; }
    void setNumPrest(string sN) { _Donnees.setNumPrest(sN) ; }

    string exportAsString() ;
    void   importFromString(string sModele) ;
};

//--------------------------- CodPrest.db ------------------------------------//
//---------------------------------------------------------------------------
//  Classe NSCodPrestData
//---------------------------------------------------------------------------
//
// Objet contenant les donn�es
//
class _CLASSELEXI NSCodPrestData
{
	public :

    //
    // Variables de stockage des valeurs
    //
    char code[CODPREST_CODE_LEN + 1] ;
    char libelle[CODPREST_LIBELLE_LEN + 1] ;
    char fse16xx[CODPREST_FSE16XX_LEN + 1] ;
    char prix_f[CODPREST_PRIX_F_LEN + 1] ;
    char prix_e[CODPREST_PRIX_E_LEN + 1] ;

    NSCodPrestData() ;
    NSCodPrestData(const NSCodPrestData& rv) ;
    ~NSCodPrestData() ;

    NSCodPrestData& operator=(const NSCodPrestData& src) ;
    int             operator==(const NSCodPrestData& o) ;

    void metAZero() ;

    string getCode()    { return string(code) ;    }
    string getLabel()   { return string(libelle) ; }
    string getFse16xx() { return string(fse16xx) ; }
    string getPriceF()  { return string(prix_f) ;  }
    string getPriceE()  { return string(prix_e) ;  }

    void setCode(string sN)    { strcpy(code,    sN.c_str()) ; }
		void setLabel(string sN)   { strcpy(libelle, sN.c_str()) ; }
		void setFse16xx(string sN) { strcpy(fse16xx, sN.c_str()) ; }
    void setPriceF(string sN)  { strcpy(prix_f,  sN.c_str()) ; }
    void setPriceE(string sN)  { strcpy(prix_e,  sN.c_str()) ; }
};

//---------------------------------------------------------------------------//  Classe NSCodPrest
//---------------------------------------------------------------------------
//
// Objet d�riv� de NSFiche servant aux acc�s de base de donn�es
//
class _CLASSELEXI NSCodPrest : public NSFiche
{
  public :

    NSCodPrestData _Donnees ;

    NSCodPrest(NSSuper* pSuper) ;
    NSCodPrest(const NSCodPrest& rv) ;
    ~NSCodPrest() ;

    void alimenteFiche() ;
    void videFiche() ;
    DBIResult open() ;

    virtual bool Create();
    virtual bool Modify();

    NSCodPrest& operator=(const NSCodPrest& src) ;
    int 	      operator==(const NSCodPrest& o) ;

    string getCode()    { return _Donnees.getCode() ;    }
    string getLabel()   { return _Donnees.getLabel() ;   }
    string getFse16xx() { return _Donnees.getFse16xx() ; }
    string getPriceF()  { return _Donnees.getPriceF() ;  }
    string getPriceE()  { return _Donnees.getPriceE() ;  }

    void setCode(string sN)    { _Donnees.setCode(sN) ;    }
		void setLabel(string sN)   { _Donnees.setLabel(sN) ;   }
    void setFse16xx(string sN) { _Donnees.setFse16xx(sN) ; }
    void setPriceF(string sN)  { _Donnees.setPriceF(sN) ;  }
    void setPriceE(string sN)  { _Donnees.setPriceE(sN) ;  }
};

//---------------------------------------------------------------------------//  Classe NSCodPrestInfo  (destin�e � �tre stock�e dans une Array)
//---------------------------------------------------------------------------
class _CLASSELEXI NSCodPrestInfo
{
  protected :

    NSCodPrestData _Donnees ;

	public :

		NSCodPrestInfo() ;		NSCodPrestInfo(const NSCodPrest*) ;
		NSCodPrestInfo(const NSCodPrestInfo& rv) ;
    ~NSCodPrestInfo();

		NSCodPrestInfo& operator=(const NSCodPrestInfo& src) ;
		int             operator==(const NSCodPrestInfo& o) ;

    string getCode()    { return _Donnees.getCode() ;    }
    string getLabel()   { return _Donnees.getLabel() ;   }
    string getFse16xx() { return _Donnees.getFse16xx() ; }
    string getPriceF()  { return _Donnees.getPriceF() ;  }
    string getPriceE()  { return _Donnees.getPriceE() ;  }

    void setCode(string sN)    { _Donnees.setCode(sN) ;    }
		void setLabel(string sN)   { _Donnees.setLabel(sN) ;   }
    void setFse16xx(string sN) { _Donnees.setFse16xx(sN) ; }
    void setPriceF(string sN)  { _Donnees.setPriceF(sN) ;   }
    void setPriceE(string sN)  { _Donnees.setPriceE(sN) ;   }

    void initCodPrest(NSCodPrest& codePrest) { codePrest._Donnees = _Donnees ; }
};

//// D�finition de NSCodPrestArray (Array de NSCodPrestInfo(s))
//
typedef vector<NSCodPrestInfo*> NSFicheCodPrestArray ;
typedef NSFicheCodPrestArray::iterator         NSCodPrestIter ;
typedef NSFicheCodPrestArray::const_iterator   NSCodPrestConstIter ;
typedef NSFicheCodPrestArray::reverse_iterator NSCodPrestReverseIter ;
typedef NTArray<NSCodPrestInfo> NSCodPrestArray ;

//
// Gestion des codes actes
//

class NSMngtListeNgapActsWin ;

class _NSDKDCLASSE NgapActsManagementDialog : public TDialog, public NSRoot
{
	public:

		NSMngtListeNgapActsWin* _pMatBox ;
		NSCodPrestArray         _aActsArray ;

		UINT				 		        _iCodeChoisi ;

		NgapActsManagementDialog(TWindow*, NSContexte* pCtx) ;
		~NgapActsManagementDialog() ;

		void SetupWindow() ;

    void EvSize(uint sizeType, ClassLib::TSize& size) ;
		void EvKeyDown(uint key, uint repeatCount, uint flags) ;
    void CmOk() ;
    void CmNewAct() ;
    void CmNewActFrom() ;
		void CmMaterielDblClk(WPARAM Cmd) ;

    bool InitActsArray() ;
		void InitListe() ;
		void AfficheListe() ;		void LvnGetDispInfo(TLwDispInfoNotify& dispInfo) ;
    void LVNColumnclick(TLwNotify& lwn) ;

    void sortByCode() ;
    void sortByLibelle() ;

    bool createAct(NSCodPrestInfo* pActInfo) ;
    bool updateAct(NSCodPrestInfo* pActInfo) ;
    bool existAct(string sCode) ;

	protected :

		bool _bNaturallySorted ;
		int  _iSortedColumn ;

    void swapSortOrder(int iColumn) ;

	DECLARE_RESPONSE_TABLE(NgapActsManagementDialog) ;
};

//
// Objet "ListWindow" avec gestion du double-click (pour les codes NGAP)
//
class _NSDKDCLASSE NSMngtListeNgapActsWin : public TListWindow
{
	public:

		NgapActsManagementDialog* pDlg ;

		NSMngtListeNgapActsWin(NgapActsManagementDialog* pere, int resId) : TListWindow(pere, resId)
		{
			pDlg = pere ;
    }
		~NSMngtListeNgapActsWin() {}

    void SetupWindow() ;
    void EvRButtonDown(uint modkeys, NS_CLASSLIB::TPoint& point) ;

    void CmNewAct() ;
    void CmNewActFrom() ;
    void CmEditAct() ;

		void EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
    int  IndexItemSelect() ;

	DECLARE_RESPONSE_TABLE(NSMngtListeNgapActsWin) ;
};

class _CLASSELEXI EditNgapDialog : public NSUtilDialog
{
	public :

  	NSCodPrestInfo*           _pInfo ;
    NgapActsManagementDialog* _pListMgmtDlg ;
    bool                      _bIsNew ;


   	EditNgapDialog(TWindow* pere, NSContexte* pCtx, NSCodPrestInfo* pActInfo, NgapActsManagementDialog* pListMgmtDlg, bool bIsNew) ;
   	~EditNgapDialog() ;
   	void CmOk() ;   	void CmCancel() ;

  protected:

    // variables de saisie
    NSUtilEdit2*     _pCode ;
    NSUtilEdit2*     _pLabel ;
   	NSUtilEditSomme* _pMontantE ;
    NSUtilEditSomme* _pMontantF ;
    OWL::TComboBox*  _pCategory ;
    OWL::TStatic*		 _pSigle ;

    void SetupWindow() ;

    int    getIndexFromCategory(const string sCategory) const ;
    string getCategoryFromIndex(int iIndex) const ;

	DECLARE_RESPONSE_TABLE(EditNgapDialog) ;
};

//---------------------------------------------------------------------------#endif    // __NSFSE16_H

