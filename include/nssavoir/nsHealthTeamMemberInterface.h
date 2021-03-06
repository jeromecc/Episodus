// -----------------------------------------------------------------------------
// nsHealthTeamMemberInterface.h
// -----------------------------------------------------------------------------
// Interface Visuelle de Gestion d'un Membre de l'Equipe de Sant�
// -----------------------------------------------------------------------------
// $Revision: 1.4 $
// $Author: pameline $
// $Date: 2013/12/15 15:48:39 $
// -----------------------------------------------------------------------------
// FLP - juin 2004
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

#ifndef __HEALTHTEAMMEMBERINTERACE_H__
# define __HEALTHTEAMMEMBERINTERACE_H__

# include <owl/dialog.h>
# include <owl/listbox.h>
# include <owl/listwind.h>
# include <owl/static.h>
# include <owl/edit.h>
# include <owl/checkbox.h>

# include "nsbb\nsednum.h"
# include "nsbb\nscomboutil.h"
# include "nsbb\nsedilex.h"

#ifdef _ENTERPRISE_DLL
  #include "enterpriseLus/nsglobalLus.h"
#else
  #include "partage/nsglobal.h"
#endif
# include "nautilus\nssuper.h"

# include "nssavoir\nsHealthTeam.h"

// -----------------------------------------------------------------------------
// class HTIMandate
// -----------------------------------------------------------------------------
// used in HealthTeamMemberInterfaceinterface
// -----------------------------------------------------------------------------
class HTIMandate : public NSRoot
{
  friend class HealthTeamMemberInterface ;

  public:

	  // constructors/destrucor
	  HTIMandate(NSContexte *pCtx, NSHealthTeamMandate *pMa)	: NSRoot(pCtx)					{ pMandate = pMa ; }
	  HTIMandate(HTIMandate& src)															: NSRoot(src.pContexte)	{ pMandate = src.pMandate ; }
	  ~HTIMandate()                                                                   {}

    HTIMandate&												operator=(const HTIMandate& src) { pMandate = src.pMandate ; return (*this) ; }

	  // functions
	  NSHealthTeamMandate::mandateType	getType()						 { return pMandate->getType() ; }
	  string														getProfession()			 { return pMandate->getProfession() ; }
    string														getProfessionLabel() ;
	  string														getSpeciality()			 { return pMandate->getSpeciality() ; }
    string														getSpecialityLabel() ;
	  DistanceType											getDistance()				 { return pMandate->getDistance() ; }
	  int																getAngle()					 { return pMandate->getAngle() ; }
    string                            getStringAngle()     { return pMandate->getStringAngle(pContexte) ; }
	  string														getBeginDate() 			 { return pMandate->getBeginDate() ; }
	  string														getEndDate() 				 { return pMandate->getEndDate() ; }
	  int																getStatus()					 { return pMandate->getStatus() ; }

//	string														getSDistance()																		{ return pMandate->getSDistance() ; }

//	bool												isValid() ;

  protected:

    NSHealthTeamMandate								*getMandate()	{ return pMandate ; }

  private:

    NSHealthTeamMandate         			*pMandate ;
} ;

typedef vector<HTIMandate *>								HTIMandateVector ;
typedef HTIMandateVector::iterator					HTIMandateIter ;
typedef HTIMandateVector::const_iterator		HTIMandateConstIter ;
typedef HTIMandateVector::reverse_iterator	HTIMandateRIter ;
//typedef NTArray<HTIMandate>          			HTIMandateArray ;

class HTIMandateArray : public HTIMandateVector
{
  public:

	  HTIMandateArray()	: HTIMandateVector() {}
    HTIMandateArray(const HTIMandateArray& src) ;
    HTIMandateArray(NSContexte *pCtx, NSHTMMandateArray *pMandates) ;
    ~HTIMandateArray() { vider() ; }

    HTIMandateArray& operator=(const HTIMandateArray& src) ;

    void reinit(NSContexte *pCtx, const NSHTMMandateArray *pMandates) ;

  private:

 	  void vider() ;
} ;

// additionnal RS du 30/08/04
class HTComboBox : public OWL::TComboBox, NSRoot
{
  public:

    enum HTCOMBOTYPE { distanceType = 0, angleType } ;

    // Constructeur par vecteur
    // TWindow *parent                : fenetre parent
    // NSContexte *pCtx               : contexte
    // VecteurString *pVecteurString  : vecteur contenant les codes lexiques
    HTComboBox(TWindow *parent, int resId, NSContexte *pCtx, HTCOMBOTYPE type, VecteurString *pVecteurString = NULL) ;
    ~HTComboBox() ;                                                                                       // Destructeur

    void                SetupWindow() ;
    string              getSelCode() ;
    int                 getIntSelCode() ;
    void                setCode(string sValue) ;
    void                EvKeyUp(uint key, uint repeatCount, uint flags) ;
    void                EvKeyDown(uint key, uint repeatCount, uint flags) ;
    uint                EvGetDlgCode(MSG far* msg);
    bool                isVisible();
    void                AddIntegerCode(int code);
    void                AddDistances();
    void                AddAngles();

  protected:

    VecteurString       _aIntegerCodes ;  // code contenant les distances ou angles
    string              _sCode ;         //
    bool                _bWinStd ;       //
    HTCOMBOTYPE         _HTType ;
    TWindow            *_pDlgParent ;   // Parent de la combo

  DECLARE_RESPONSE_TABLE(HTComboBox) ;
} ;

bool		mandateSortByTypeSup			(HTIMandate *pM1, HTIMandate *pM2) ;
bool		mandateSortByTypeInf			(HTIMandate *pM1, HTIMandate *pM2) ;
bool		mandateSortByProfessionSup(HTIMandate *pM1, HTIMandate *pM2) ;
bool		mandateSortByProfessionInf(HTIMandate *pM1, HTIMandate *pM2) ;
bool		mandateSortBySpecialitySup(HTIMandate *pM1, HTIMandate *pM2) ;
bool		mandateSortBySpecialityInf(HTIMandate *pM1, HTIMandate *pM2) ;
bool		mandateSortByDistanceSup	(HTIMandate *pM1, HTIMandate *pM2) ;
bool		mandateSortByDistanceInf	(HTIMandate *pM1, HTIMandate *pM2) ;
bool		mandateSortByAngleSup			(HTIMandate *pM1, HTIMandate *pM2) ;
bool		mandateSortByAngleInf			(HTIMandate *pM1, HTIMandate *pM2) ;
bool		mandateSortByBeginDateSup	(HTIMandate *pM1, HTIMandate *pM2) ;
bool		mandateSortByBeginDateInf	(HTIMandate *pM1, HTIMandate *pM2) ;
bool		mandateSortByEndDateSup		(HTIMandate *pM1, HTIMandate *pM2) ;
bool		mandateSortByEndDateInf		(HTIMandate *pM1, HTIMandate *pM2) ;

class NSListMandatesWindow ;

class _CLASSMODE HealthTeamMemberInterface : public NSUtilDialog
{
  friend class HealthTeamMandateInterface ;

  public:

	  // constructors/destructor
	  HealthTeamMemberInterface(HealthTeamInterface* parent, NSContexte *pCtx, NSHealthTeamMember *pM = NULL) ;
    HealthTeamMemberInterface(RosaceDrawer *parent, NSContexte *pCtx, NSHealthTeamMember *pM) ;
	  ~HealthTeamMemberInterface() ;

	  // display functions
	  void   SetupWindow() ;
	  void   SetupColumns() ;
	  // void                        SetStringName(std::string name);

	  void   DispInfoListe(TLwDispInfoNotify& dispInfo) ;
	  void   LVNColumnclick(TLwNotify& lwn) ;
	  void   sortByColumn(int iColumn) ;
	  void   displayList() ;

	  // functions
	  void   CmNewMandate() ;
	  void   CmDelMandate() ;
	  void   CmModMandate() ;
    void   CmCloseMandate() ;
    void   CmDismissMember() ;

	  void   CmOk() ;
    void   CmCancel() ;

	  string getName() { return sMemberName ; }
	  string getID()   { return "" ; }	// fabTODO

  private:

	  string getLabelFromLexiCode(string sLexiCode) ;

	  // variables
	  string               sMemberName ;
	  NSTeamManager        *pTManager ;
	  NSHealthTeamMember   *pMember ;

    TStatic              *pInformation ;

	  NSListMandatesWindow *pListMandates ;
	  HTIMandateArray			 *pMandates ;
    bool                 bNaturallySorted ;
    int                  iSortedColumn ;

  DECLARE_RESPONSE_TABLE(HealthTeamMemberInterface) ;
} ;


class _CLASSMODE HealthTeamMandateInterface : public NSUtilDialog
{
  public:
	  // constructors/destructor
	  HealthTeamMandateInterface(HealthTeamMemberInterface *pParentWindow, NSContexte *pCtx, NSHealthTeamMandate *pMandate) ;
    HealthTeamMandateInterface(TWindow* parent, NSContexte *pCtx, std::string name, NSHealthTeamMandate *pM = NULL, int angle = -1, std::string distance = "-1") ;
	  ~HealthTeamMandateInterface() ;

    void   initObjects() ;

	  // display functions
	  void   SetupWindow() ;
	  void   CmOk() ;
    void   CmCancel() ;

	  // functions
	  string getStringValue(OWL::TEdit *pEdit)          { char szBuffer[128] ; pEdit->GetText(szBuffer, 128) ; return string(szBuffer) ; }
	  int    getIntValue   (OWL::TEdit *pEdit)          { char szBuffer[128] ; pEdit->GetText(szBuffer, 128) ; return atoi(szBuffer) ; }
	  string getStringDate (NSUtilEditDateHeure *pEdit) { string sBuffer ;     pEdit->getDate(&sBuffer) ;      return sBuffer ; }
	  string getCBValue    (NSComboBox *pCombo) 				{ return (pCombo->getSelCode()) ; }

  protected:

 	  void ActualiseEnd();
    void GetProfession();

  private:

	  // variables
	  OWL::TStatic								*pName ;
	  NSUtilLexique								*pProfession ;
	  NSUtilLexique								*pSpeciality ;
	  NSComboBox									*pCBType ;
	  HTComboBox									*pDistance ;
	  HTComboBox									*pAngle ;
	  NSUtilEditDateHeure					*pBeginDate ;
	  NSUtilEditDateHeure					*pEndDate ;
	  NSEditNum										*pDuration ;
	  NSComboBox									*pCBDurationUnit ;

    std::string									 name ;
	  NSHealthTeamMandate					*pMandate ;
	  HealthTeamMemberInterface		*pHTMemberInterface ;

    bool 												_special_init ;
    int 												_change_angle ;
    int												  _change_distance ;

    void 												specialInit() ;

  DECLARE_RESPONSE_TABLE(HealthTeamMandateInterface) ;
} ;


class NSListMandatesWindow : public TListWindow, public NSRoot
{
  public:
	  // constructors/destructor
	  NSListMandatesWindow(HealthTeamMemberInterface *parent, NSContexte *pCtx, int ressourceId, TModule *module = 0) ;
	  ~NSListMandatesWindow() ;

	  // control functions
	  void                        SetupWindow() ;
    void        								EvLButtonDblClk(uint modKeys, NS_CLASSLIB::TPoint& point) ;
    void        								EvRButtonDown(uint modkeys, NS_CLASSLIB::TPoint& point) ;    void        								EvKeyDown(uint key, uint repeatCount, uint flags);    int         								IndexItemSelect() ;
    void        								EvSetFocus(HWND hWndLostFocus) ;

	  // functions	  void												CmNewMandate() 																		{ pHTMInterface->CmNewMandate() ; }
//	void												CmDelMandate() 																		{ pHTMInterface->CmDelMandate() ; }
	  void												CmModMandate() 																		{ pHTMInterface->CmModMandate() ; }
    void												CmCloseMandate()																	{ pHTMInterface->CmCloseMandate() ; }
  private:	  int													indexSel ;
	  HealthTeamMemberInterface		*pHTMInterface ;

  DECLARE_RESPONSE_TABLE(NSListMandatesWindow) ;
} ;


//
// Fen�tre de cr�ation d'un mandat
//
class _CLASSMODE CreateMandatInterface : public NSUtilDialog
{
  public:
    CreateMandatInterface(TWindow* parent, NSContexte *pCtx, std::string login ="", std::string pass = "") ;
    ~CreateMandatInterface();

    void											SetupWindow() ;
    void											CmOk() ;
    void											CmCancel() ;
    void											CmHelp() ;
    void											CmDefineMandat(); // Fonction qui ouvre la fenetre de d�finition du mandat

  protected:
	  //
    // Verifie si la fenetre a �t� correctement remplie
    // Remplie true si elle est correctement remplie  et faux sinon
	  bool 											CheckFull();

    //
    // Fonction qui recupere les informations remplie sur les fenetres
    //
    void											full_data();

    //
    // Recuperer les infos sur la personne a ajouter
    //
    void 											NewHealthMemberInformation();

  protected:

	  std::string	 				_acteur_login;     // Login de l'utilisateur
	  std::string  				_acteur_password; 		 // Password de l'utilisateur
    std::string	 			 	_member_adeli;  // identifiant professionnel
    std::string	 				_member_ldv;  // identifiant Ldv
    std::string					_acteur_liden;
    NSHealthTeamMember*         _member;
    bool         				_is_md5;
    bool								_admin; //indique si l'utilisateur est un administrateur qui a des droits sur le compte
    OWL::TEdit*			 		_acteur_edit_login;
    OWL::TEdit*			 		_acteur_edit_password;
    OWL::TEdit* 			 	_member_edit_ldv;
    OWL::TEdit*       	_member_edit_adeli;
    OWL::TEdit*					_acteur_edit_liden;
    OWL::TCheckBox*			_is_admin;

	  std::string _pass_to_add; 	// nom de la personne a rejouter dans l'equipe de sant�
    std::string _login_to_add;  // login crytp� de la personne a reajouter dans l'equipe de sant�

  DECLARE_RESPONSE_TABLE(CreateMandatInterface) ;
};

#endif // __HEALTHTEAMMEMBERINTERACE_H__

