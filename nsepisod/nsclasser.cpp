// --------------------------------------------------------------------------
// NSCLASSER.CPP
// --------------------------------------------------------------------------
// Fabrice LE PERRU - Novembre/Decembre 2001
// source : Fabrice LE PERRU -- nsepisodview.cpp - Aout 2001
//          -- source : R�mi SPAAK - Mai 1997
// --------------------------------------------------------------------------
#include <fstream>
#include <string.h>

#ifdef _ENTERPRISE_DLL
  #include "enterpriseLus/superLus.h"
  #include "enterpriseLus/nsglobalLus.h"
#else
  #include "partage/nsglobal.h"
#endif

// #include "nsepisod/eptables.h"
#include "nsepisod/nsclasser.h"
#include "nsepisod/nssoapdiv.h"

#ifdef _ENTERPRISE_DLL
  #include "enterpriseLus/personLus.h"
  #include "nsdatabaseLus/nsSQL.h"
  #include "enterpriseLus/nsdivfctForCgi.h"
  #include "mysql/mysql.h"
#else
  #include "nautilus\nssuper.h"
  #include "partage\nsdivfct.h"

  #include "nautilus\nsepicap.h"
  #include "nsepisod\nsepidiv.h"
#endif

#include "nsepisod/nsldvuti.h"
#include "nssavoir/nsfilgd.h"

#ifndef __linux__
#include "nssavoir/nscaptur.h"
#endif

#include "dcodeur/nsphrase.h"
#include "dcodeur/nsgenlan.h"

#include "nssavoir/nspatho.h"
#include "nsepisod/flechiesDB.h"

long ElemSet::lObjectCount          = 0 ;
long ElemSetArray::lObjectCount     = 0 ;
long TermsParser::lObjectCount      = 0 ;
long ParseElem::lObjectCount        = 0 ;
long ParseElemArray::lObjectCount   = 0 ;
long ClassifElem::lObjectCount      = 0 ;
long ClassifElemArray::lObjectCount = 0 ;

// -----------------------------------------------------------------------------
//
//  Classe de supervision des classifications
//
// -----------------------------------------------------------------------------
classifExpert::classifExpert(NSContexte* pCtx)
#ifndef _ENTERPRISE_DLL
              :NSRoot(pCtx), _DBcurseur(pCtx->getSuperviseur())
#else
              :NSRoot(pCtx)
#endif
{
}

classifExpert::~classifExpert()
{
}

string
classifExpert::donnePattern(string sClassification)
{
  // CISP 2
  if (sClassification == "6CISP")
    return string("ABDFHKLNPRSTUWXYZ 0123456789 0123456789") ;

  // CIM 10
  if (sClassification == "6CIMA")
    return string("ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789 0123456789 . 0123456789 0123456789") ;

  return string("") ;
}

int
classifExpert::donneCodeSize(string sClassification)
{
  // CISP 2
  if (sClassification == "6CISP")
    return 3 ;

  // CIM 10
  if (sClassification == "6CIMA")
    return 6 ;

  return 0 ;
}

void
classifExpert::donneInterdits(string sClassification, string sCase,
                                            ElemSetArray* pForbidenDomain)
{
  if (NULL == pForbidenDomain)
    return ;

  string sCaseSens = string("") ;
  if (string("") != sCase)
    NSDico::donneCodeSens(&sCase, &sCaseSens) ;

  // CISP 2
  if (sClassification == "6CISP")
  {
    //
    // Interdits en fonction du sexe du patient
    // Forbiden codes due to patient's sex
    //
    if (pContexte->getPatient())
    {
#ifndef _ENTERPRISE_DLL
      if      (pContexte->getPatient()->estFeminin())
#else
      if      (pContexte->getPatient()->isFemale())
#endif
      {
        pForbidenDomain->push_back(new ElemSet("Y00", "Y99"));
      }
#ifndef _ENTERPRISE_DLL
      else if (pContexte->getPatient()->estMasculin())
#else
      else if (pContexte->getPatient()->isMale())
#endif
      {
        pForbidenDomain->push_back(new ElemSet("X00", "X99"));
        pForbidenDomain->push_back(new ElemSet("W00", "W99"));
      }
    }
    //
    // Interdits en fonction de la case
    // Forbiden codes due to coding location
    //
    if      (sCaseSens == "0MOTI") // Motif
    {
    }
    else if (sCaseSens == "0SOA0") // S du SOAP
    {
    }
    else if (sCaseSens == "0SOA5") // Proc�dure pr�-appr�ciation SOPAP
    {
      // Exclude symptoms and diagnosis
      pForbidenDomain->push_back(new ElemSet("?00", "?29")) ;
      pForbidenDomain->push_back(new ElemSet("?70", "?99")) ;
    }
    else if (sCaseSens == "0SOA4")  // diagnostic - diagnosis
    {
      // Exclude procedures
      pForbidenDomain->push_back(new ElemSet("?30", "?69")) ;
    }
    else if (sCaseSens == "0SOA3") // P du SOAP
    {
      // Exclude symptoms and diagnosis
      pForbidenDomain->push_back(new ElemSet("?00", "?29")) ;
      pForbidenDomain->push_back(new ElemSet("?70", "?99")) ;
    }
    else if (sCaseSens == "0SOPR") // Proc�dure r�alis�e du SOAP1P2
    {
      // Exclude symptoms and diagnosis
      pForbidenDomain->push_back(new ElemSet("?00", "?29")) ;
      pForbidenDomain->push_back(new ElemSet("?70", "?99")) ;
    }
    else if (sCaseSens == "0SOPP") // Proc�dure prescrite du SOAP1P2
    {
      // Exclude symptoms and diagnosis
      pForbidenDomain->push_back(new ElemSet("?00", "?29")) ;
      pForbidenDomain->push_back(new ElemSet("?70", "?99")) ;
    }
    return ;
  }

  // CIM 10
  if (sClassification == "6CIMA")
  {
    //
    // Interdits en fonction du sexe du patient
    // Forbiden codes due to patient's sex
    //
    if (pContexte->getPatient())
    {
#ifndef _ENTERPRISE_DLL
      if      (pContexte->getPatient()->estFeminin())
#else
      if      (pContexte->getPatient()->isFemale())
#endif
      {
        // pForbidenDomain->push_back(new ElemSet("Y00", "Y99"));
      }
#ifndef _ENTERPRISE_DLL
      else if (pContexte->getPatient()->estMasculin())
#else
      else if (pContexte->getPatient()->isMale())
#endif
      {
        pForbidenDomain->push_back(new ElemSet("O00", "O99.99")) ;
      }
    }
/*
        //
        // Interdits en fonction de la case
        // Forbiden codes due to coding location
				//
        if      (sCaseSens == "0MOTI") // Motif
        {
        }
        else if (sCaseSens == "0SOA0") // S du SOAP
        {
        }
        else if (sCaseSens == "0SOA5") // Proc�dure pr�-appr�ciation SOPAP
        {
            // Exclude symptoms and diagnosis
            pForbidenDomain->push_back(new ElemSet("?00", "?29"));
            pForbidenDomain->push_back(new ElemSet("?70", "?99"));
        }
        else if (sCaseSens == "0SOA4")  // diagnostic - diagnosis
        {
            // Exclude procedures
            pForbidenDomain->push_back(new ElemSet("?30", "?69"));
        }
        else if (sCaseSens == "0SOA3") // P du SOAP
        {
            // Exclude symptoms and diagnosis
            pForbidenDomain->push_back(new ElemSet("?00", "?29"));
            pForbidenDomain->push_back(new ElemSet("?70", "?99"));
        }
        else if (sCaseSens == "0SOPR") // Proc�dure r�alis�e du SOAP1P2
        {
            // Exclude symptoms and diagnosis
            pForbidenDomain->push_back(new ElemSet("?00", "?29"));
            pForbidenDomain->push_back(new ElemSet("?70", "?99"));
        }
        else if (sCaseSens == "0SOPP") // Proc�dure prescrite du SOAP1P2
        {
            // Exclude symptoms and diagnosis
            pForbidenDomain->push_back(new ElemSet("?00", "?29"));
            pForbidenDomain->push_back(new ElemSet("?70", "?99"));
        }
*/
  }
}

void
classifExpert::donneClassifArray(SOAPObject* pObjet,
                                 NSEpiClassifInfoArray *pArrayClassif,
                                 int iNiveau)
{
try
{
  if (NULL == pObjet)
    return ;

	string sClassif = pObjet->sClassification ;
	string sCase    = pObjet->sCase ;
	//
	// Si l'objet est issu d'une capture, on peut d�terminer son domaine
	// If the object comes from capture, we can define its domain
	//
#ifndef __linux__
	if ((iNiveau == niveauPreselection) && (pObjet->pCaptElemnt))
	{
		//
		// On instancie le domaine
    // Instanciating the domain
    //
    string sDomain = pObjet->pCaptElemnt->getClassifResultP() ;
  	ParseCategory Parser(donneCodeSize(sClassif), sClassif, donnePattern(sClassif));
		ElemSetArray* pElemDomain = Parser.DefDomain(sDomain) ;
    if (NULL == pElemDomain)
    	return ;
		//
		// On trouve les codes qui correspondent au domaine
		// Finding the codes that belong to the domain
		//
		fillList(sClassif, pElemDomain, pArrayClassif, pObjet->sCase) ;

    delete pElemDomain ;
		return ;
	}
#endif

#ifndef _ENTERPRISE_DLL

	// open table
	_DBcurseur.lastError = _DBcurseur.open() ;
	if (_DBcurseur.lastError != DBIERR_NONE)
	{
		erreur("classif.db -- Erreur � l'ouverture du fichier.", standardError, _DBcurseur.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		return ;
	}

	//
	// Loading forbiden domain
	//
	ElemSetArray ForbidenDomain ;
	if (iNiveau <= niveauAutorises)
		donneInterdits(sClassif, sCase, &ForbidenDomain) ;

	// d�finition de la cl� de recherche
	string cle = sClassif ;

	// recherche dans la base
	_DBcurseur.lastError = _DBcurseur.chercheClef(&cle,
                                                "",
                                                NODEFAULTINDEX,
                                                keySEARCHGEQ,
                                                dbiREADLOCK) ;
	if ((_DBcurseur.lastError != DBIERR_NONE) &&
        (_DBcurseur.lastError != DBIERR_RECNOTFOUND))
	{
		erreur("classif.db -- erreur � la recherche dans la base.", standardError, _DBcurseur.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		_DBcurseur.close() ;
		return ;
	}

	// r�cup�ration de l'enregistrement
	_DBcurseur.lastError = _DBcurseur.getRecord() ;
	if (_DBcurseur.lastError != DBIERR_NONE)
	{
		erreur("classif.db -- erreur de lecture dans la base.", standardError, _DBcurseur.lastError, pContexte->GetMainWindow()->GetHandle());
		_DBcurseur.close() ;
		return ;
	}

	// on continue tant qu'on reste dans la classification
	//
	while ((_DBcurseur.getClassification() == sClassif) &&
           (_DBcurseur.lastError == DBIERR_NONE))
	{
		NSEpiClassifInfo* pNewElem = new NSEpiClassifInfo(&_DBcurseur) ;

		//
		// si l'�l�ment n'est pas d�j� pr�sent dans l'array on le
		// rajoute (s'il n'est pas interdit)
		//
		if (false == ForbidenDomain.doesContain(pNewElem->getCode()))
			pArrayClassif->push_back(pNewElem) ;
		else
			delete pNewElem ;

		//
		// on passe � l'enregistrement suivant
		//
		_DBcurseur.lastError = _DBcurseur.suivant(dbiREADLOCK) ;
		if (_DBcurseur.lastError != DBIERR_NONE)
		{
			if (_DBcurseur.lastError != DBIERR_EOF)
			{
				erreur("classif.db -- erreur d'acc�s au message suivant.", standardError, _DBcurseur.lastError, pContexte->GetMainWindow()->GetHandle()) ;
				_DBcurseur.close() ;
				return ;
			}
		}
		else
		{
			// r�cup�ration de l'enregistrement suivant
			_DBcurseur.lastError = _DBcurseur.getRecord() ;
			if (_DBcurseur.lastError != DBIERR_NONE)
			{
				erreur("classif.db -- erreur de lecture dans la base.", standardError, _DBcurseur.lastError, pContexte->GetMainWindow()->GetHandle()) ;
				_DBcurseur.close() ;
				return ;
			}
		}
	}

	// on ferme la base
	_DBcurseur.lastError = _DBcurseur.close() ;
	if (_DBcurseur.lastError != DBIERR_NONE)
		erreur("classif.db -- erreur � la fermeture de la base.", standardError, _DBcurseur.lastError, pContexte->GetMainWindow()->GetHandle()) ;

#else

  //
	// Loading forbiden domain
	//
	ElemSetArray ForbidenDomain ;
	if (iNiveau <= niveauAutorises)
		donneInterdits(sClassif, sCase, &ForbidenDomain) ;

	// Looking for all codes that belong to given classification
  //
  string sQuery = string("SELECT * FROM classif WHERE CLASSIF = \"") + sClassif + string("\"") ;

  ontologyBaseManager* pOntologyManager = pContexte->getSuperviseur()->getDatabaseManager() ;
  if (NULL == pOntologyManager)
    return ;

  MYSQL_RES *pResult = pOntologyManager->executeQuery(sQuery, false) ;
  if ((MYSQL_RES *) NULL == pResult)
    return ;

  MYSQL_ROW Row = mysql_fetch_row(pResult) ;
  while (Row)
  {
    NSEpiClassifInfo* pNewElem = new NSEpiClassifInfo() ;
    pNewElem->alimenteFiche(&Row) ;

    Row = mysql_fetch_row(pResult) ;
  }

  mysql_free_result(pResult) ;

#endif // #ifndef _ENTERPRISE_DLL
}
catch (...)
{
	erreur("Exception classifExpert::donneClassifArray.", standardError) ;
}
}

//
// Pour une classification, ajoute � l'array de NSEpiClassifInfo les fiches
// des �l�ments de la classification contenus dans le domaine
//
void
classifExpert::fillList(string sClassification, ElemSetArray *pDomain,
                                    NSEpiClassifInfoArray *pArrayClassif,
                                    string sCase)
{
try
{
	if ((NULL == pArrayClassif) || (NULL == pDomain) || (pDomain->empty()))
		return ;

#ifndef _ENTERPRISE_DLL

	// open table
	_DBcurseur.lastError = _DBcurseur.open() ;
	if (_DBcurseur.lastError != DBIERR_NONE)
	{
		erreur("classif.db -- Erreur � l'ouverture du fichier.", standardError, _DBcurseur.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		return ;
	}

	//
	// Loading forbiden domain
	//
	ElemSetArray ForbidenDomain ;
	donneInterdits(sClassification, sCase, &ForbidenDomain) ;

	ElemSetIterator DomainIter = pDomain->begin();
	for (; pDomain->end() != DomainIter ; DomainIter++)
	{
		if (false == (*DomainIter)->isEmptySet())
		{
			string  sBornInf = (*DomainIter)->getBegin() ;
			string  sBornSup = (*DomainIter)->getEnd() ;

			// d�finition de la cl� de recherche
			string cle = sClassification + sBornInf ;

			// recherche dans la base
			_DBcurseur.lastError = _DBcurseur.chercheClef(&cle,
                                                    "",
                                                    NODEFAULTINDEX,
                                                    keySEARCHGEQ,
                                                    dbiREADLOCK) ;
			if ((_DBcurseur.lastError != DBIERR_NONE) &&
          (_DBcurseur.lastError != DBIERR_RECNOTFOUND))
			{
				erreur("classif.db -- erreur � la recherche dans la base.", standardError, _DBcurseur.lastError, pContexte->GetMainWindow()->GetHandle()) ;
        _DBcurseur.close() ;
        return ;
      }

			// r�cup�ration de l'enregistrement
			_DBcurseur.lastError = _DBcurseur.getRecord() ;
			if (_DBcurseur.lastError != DBIERR_NONE)
			{
      	erreur("classif.db -- erreur de lecture dans la base.", standardError, _DBcurseur.lastError, pContexte->GetMainWindow()->GetHandle());
        _DBcurseur.close() ;
        return ;
      }

			// on continue jusqu'� ce qu'on soit strictement sup�rieur �
			// la borne sup�rieure de l'�l�ment
			while ((sBornSup >= _DBcurseur.getCode()) &&
                    (_DBcurseur.lastError == DBIERR_NONE))
			{
				NSEpiClassifInfo* pNewElem = new NSEpiClassifInfo(&_DBcurseur) ;
        bool bElemAlreadyPresent = false ;

        // on v�rifie si l'�l�ment est pas d�j� pr�sent dans l'array que l'on renvoie
        if (false == pArrayClassif->empty())
        {
        	NSEpiClassifInfoIter ClassifInfoIter = pArrayClassif->begin() ;
          for ( ; (pArrayClassif->end() != ClassifInfoIter) &&
                                        (!(*pNewElem == *(*ClassifInfoIter))) ;
                                                        ClassifInfoIter++) ;
          if (pArrayClassif->end() != ClassifInfoIter)
          	bElemAlreadyPresent = true ;
        }

        //
        // si l'�l�ment n'est pas d�j� pr�sent dans l'array on le
        // rajoute (s'il n'est pas interdit)
        //
        if ((false == bElemAlreadyPresent) &&
                    (false == ForbidenDomain.doesContain(pNewElem->getCode())))
        	pArrayClassif->push_back(pNewElem) ;
        else
        	delete pNewElem ;

        //
        // on passe � l'enregistrement suivant
        //
        _DBcurseur.lastError = _DBcurseur.suivant(dbiREADLOCK) ;
        if (_DBcurseur.lastError != DBIERR_NONE)
        {
        	if (_DBcurseur.lastError != DBIERR_EOF)
          {
          	erreur("classif.db -- erreur d'acc�s au message suivant.", standardError, _DBcurseur.lastError, pContexte->GetMainWindow()->GetHandle());
            _DBcurseur.close() ;
            return ;
          }
        }
        else
        {
        	// r�cup�ration de l'enregistrement suivant
          _DBcurseur.lastError = _DBcurseur.getRecord() ;
          if (_DBcurseur.lastError != DBIERR_NONE)
          {
          	erreur("classif.db -- erreur de lecture dans la base.", standardError, _DBcurseur.lastError, pContexte->GetMainWindow()->GetHandle());
            _DBcurseur.close() ;
            return ;
          }
        }
      }
    }
  }

	// on ferme la base
	_DBcurseur.lastError = _DBcurseur.close() ;
	if (_DBcurseur.lastError != DBIERR_NONE)
		erreur("classif.db -- erreur � la fermeture de la base.", standardError, _DBcurseur.lastError, pContexte->GetMainWindow()->GetHandle()) ;

#else

  ontologyBaseManager* pOntologyManager = pContexte->getSuperviseur()->getDatabaseManager() ;
  if (NULL == pOntologyManager)
    return ;

  //
	// Loading forbiden domain
	//
	ElemSetArray ForbidenDomain ;
	donneInterdits(sClassification, sCase, &ForbidenDomain) ;

	ElemSetIterator DomainIter = pDomain->begin() ;
	for (; pDomain->end() != DomainIter ; DomainIter++)
	{
		if (false == (*DomainIter)->isEmptySet())
		{
			string  sBornInf = (*DomainIter)->getBegin() ;
			string  sBornSup = (*DomainIter)->getEnd() ;

      string sQuery = string("SELECT * FROM classif WHERE CLASSIF = \"") + sClassification + string("\"") ;

      if (sBornInf == sBornSup)
        sQuery += string(" AND CODE = \"") + sBornInf + string("\"") ;
      else
        sQuery += string(" AND CODE >= \"") + sBornInf + string("\" AND CODE <= \"") + sBornSup + string("\"") ;

      MYSQL_RES *pResult = pOntologyManager->executeQuery(sQuery, false) ;
      if (pResult)
      {
        MYSQL_ROW Row = mysql_fetch_row(pResult) ;
        while (Row)
        {
          NSEpiClassifInfo* pNewElem = new NSEpiClassifInfo() ;
          pNewElem->alimenteFiche(&Row) ;

          bool bElemAlreadyPresent = false ;

          // on v�rifie si l'�l�ment est pas d�j� pr�sent dans l'array que l'on renvoie
          if (false == pArrayClassif->empty())
          {
        	  NSEpiClassifInfoIter ClassifInfoIter = pArrayClassif->begin() ;
            for (; (pArrayClassif->end() != ClassifInfoIter) &&
                                        (!(*pNewElem == *(*ClassifInfoIter))) ;
                                                        ClassifInfoIter++) ;
            if (pArrayClassif->end() != ClassifInfoIter)
          	  bElemAlreadyPresent = true ;
          }

          //
          // si l'�l�ment n'est pas d�j� pr�sent dans l'array on le
          // rajoute (s'il n'est pas interdit)
          //
          if ((false == bElemAlreadyPresent) &&
                    (false == ForbidenDomain.doesContain(pNewElem->getCode())))
        	  pArrayClassif->push_back(pNewElem) ;
          else
        	  delete pNewElem ;

          Row = mysql_fetch_row(pResult) ;
        }

        mysql_free_result(pResult) ;
      }
    }
  }

#endif
}
catch (...)
{
	erreur("Exception classifExpert::fillList.", standardError) ;
}
}

string
classifExpert::chooseCode(SOAPObject* pObjet)
{
#ifndef _ENTERPRISE_DLL
try
{
	// Codes propos�s - candidate codes
	NSEpiClassifInfoArray aArrayClassif ;
	donneClassifArray(pObjet, &aArrayClassif, niveauPreselection) ;

	string sResult = "" ;

	if (pObjet->sClassification == "6CISP")
	{
		string sCtrlData = "" ;

		CISPFindCodeDlg* pFindCodeDlg
                            = new CISPFindCodeDlg(pContexte->GetMainWindow(),
                                                  pContexte,
                                                  pObjet,
                                                  niveauPreselection,
                                                  &aArrayClassif,
                                                  &sCtrlData) ;
		int iResult = pFindCodeDlg->Execute() ;

		if (iResult == IDOK)
		{
			sResult = pFindCodeDlg->getResult() ;
			storeControlData(sCtrlData) ;
		}

		delete pFindCodeDlg ;
	}
	else if (pObjet->sClassification == "6CIMA")
	{
		string sCtrlData = "" ;

		CIMFindCodeDlg* pFindCodeDlg
                            = new CIMFindCodeDlg(pContexte->GetMainWindow(),
                                                  pContexte,
                                                  pObjet,
                                                  niveauPreselection,
                                                  &aArrayClassif,
                                                  &sCtrlData) ;
		int iResult = pFindCodeDlg->Execute() ;

		if (iResult == IDOK)
		{
			sResult = pFindCodeDlg->getResult() ;
			storeControlData(sCtrlData) ;
		}

		delete pFindCodeDlg ;
	}

	return sResult ;
}
catch(TWindow::TXWindow& e)
{
  string sErr = string("Exception classifExpert::chooseCode : ") + e.why() ;
  erreur(sErr.c_str(), standardError, 0) ;
  return "" ;
}
catch (...)
{
	erreur("Exception classifExpert::chooseCode.", standardError, 0) ;
	return "";
}
#else
  return string("") ;
#endif
}

void
classifExpert::setControlString(string* pCtrlData, SOAPObject* pObjet,
                            int iInitialLevel, NSEpiClassifInfoArray* pArrayClassif,
                            NVLdVTemps* pTpsDebut, NVLdVTemps* pTpsFin,
                            string sResult, string sCodeSens)
{
    setControlString(pCtrlData, pObjet->sClassification, pObjet->sCase,
                        pObjet->sTexteInitial, iInitialLevel, pArrayClassif,
                        pTpsDebut, pTpsFin, sResult, sCodeSens) ;
}

void
classifExpert::setControlString(string* pCtrlData, string sClassification, string sCase,
                            string sTexteInitial, int iInitialLevel,
                            NSEpiClassifInfoArray* pArrayClassif,
                            NVLdVTemps* pTpsDebut, NVLdVTemps* pTpsFin,
                            string sResult, string sCodeSens)
{
  *pCtrlData = string("<classification_event") +
                    string(" classification=\"") + sClassification + string("\"") +
                    string(" case=\"")  + sCase                         + string("\"") +
                    string(" start=\"") + pTpsDebut->donneDateHeure()   + string("\"") +
                    string(" end=\"")   + pTpsFin->donneDateHeure()     + string("\"") +
                    string(">\n") ;
	*pCtrlData += string("  <patient") +
#ifndef _ENTERPRISE_DLL
                    string(" id=\"")    + pContexte->getPatient()->getNss() + string("\"") +
                    string(" sex=\"")   + pContexte->getPatient()->getSexe() + string("\"") +
                    string(" birthday=\"") + pContexte->getPatient()->getNaissance() + string("\"") +
#else
                    string(" id=\"")    + pContexte->getPatient()->getId() + string("\"") +
                    string(" sex=\"")   + pContexte->getPatient()->getGender() + string("\"") +
                    string(" birthday=\"") + pContexte->getPatient()->getBirthDate() + string("\"") +
#endif
                    string(">\n") ;
	*pCtrlData += string("  <text") ;
	if (sCodeSens != "")
		*pCtrlData += string(" semantic=\"") + sCodeSens + string("\"") ;
	*pCtrlData += string(">\n") ;
	*pCtrlData += sTexteInitial + string("\n") ;
	*pCtrlData += string("  </text>\n") ;
	*pCtrlData += string("  <proposals level=\"") ;
	if      (iInitialLevel == classifExpert::niveauPreselection)
	{
  	if (pArrayClassif)
    {
    	*pCtrlData += string("pre-selection\">\n") ;
      if (!(pArrayClassif->empty()))
      {
      	NSEpiClassifInfoIter i = pArrayClassif->begin() ;
        for ( ; i != pArrayClassif->end() ; i++)
        	*pCtrlData += string("    ") + (*i)->getCode() + string(" ") +
                                         (*i)->getLabel() + string("\n") ;
      }
      *pCtrlData += string("  </proposals>\n") ;
    }
    else
    	*pCtrlData += string("automatic\" />\n") ;
	}
	else if (iInitialLevel == classifExpert::niveauAutorises)
  	*pCtrlData += string("allowed\" />\n") ;
	else if (iInitialLevel == classifExpert::niveauTous)
  	*pCtrlData += string("any\" />\n") ;
	else
		*pCtrlData += string("unknown\" />\n") ;

	*pCtrlData += string("  <selected code=\"") + sResult + string("\" />\n") ;

	*pCtrlData += string("</classification_event>\n") ;
}

void
classifExpert::storeControlData(string sCtrlData)
{
    if (sCtrlData == "")
        return ;

    string sFichier = string("class") +
#ifndef _ENTERPRISE_DLL
                      pContexte->getUtilisateur()->getNss() +
                      string(".xml");
    sFichier = pContexte->PathName("BGLO") + sFichier ;
#else
                      pContexte->getUtilisateur()->getId() +
                      string(".xml");
#endif
    ofstream outFile ;
    outFile.open(sFichier.c_str(), ios::ate | ios::app) ;

    if (!outFile)
   	{
        string sErrMess = string("Erreur d'ouverture en �criture du fichier ")
                                                                    + sFichier ;
        erreur(sErrMess.c_str(), standardError) ;
   		return;
   	}
    //
    //
    outFile << sCtrlData ;
    outFile.close() ;
}

/*
//
// Ask the user to choose a code among a fixed domain
//
string
classifExpert::chooseCode(string sClassification, ElemSetArray* pDomain, string sCase)
{
		int     iResult;
		string  sResult = "";

		NSEpiClassifInfoArray* pArrayClassif = new NSEpiClassifInfoArray();
		fillList(sClassification, pDomain, pArrayClassif, sCase);

		if (sClassification == "6CISP")
		{
				CISPFindCodeDlg* pFindCodeDlg
														= new CISPFindCodeDlg(pContexte->GetMainWindow(),
																									pContexte,
																									sClassification,
																									pArrayClassif);
				iResult = pFindCodeDlg->Execute();

				if (iResult == IDOK)
						sResult = pFindCodeDlg->getResult();

				delete pFindCodeDlg;
		}

		delete pArrayClassif;

		return sResult;
}

//
// Ask the user to choose a code among a fixed domain
//
string
classifExpert::chooseCode(string sClassif, string sDomain, string sCase)
{
		ParseCategory* pParser = new ParseCategory(donneCodeSize(sClassif),
																							 sClassif,
																							 donnePattern(sClassif));
		ElemSetArray* pElemDomain = pParser->DefDomain(sDomain);

		string sResult = chooseCode(sClassif, pElemDomain, sCase);

		delete pElemDomain;
		delete pParser;

		return sResult;
}
*/

// ----------------------------------------------------------
// constructeur
// ----------------------------------------------------------
Classify::Classify(NSContexte* pCtx, string* psClassif, string* psConcept, string* psPath)
				 :NSRoot(pCtx)
{
  psClassification = psClassif ;

  pElement         = psConcept ;
  pChemin          = psPath ;
}

// ----------------------------------------------------------
// destructeur
// ----------------------------------------------------------
Classify::~Classify()
{
}

// cherche le code
// ----------------------------------------------------------
// renvoie le r�sultat par sClassifResult
// ----------------------------------------------------------
void
Classify::computeParsing(string  *psClassifResultO,
                         string  *psClassifResultP,
                         string  *psClassifResultI)
{
try
{
#ifndef _ENTERPRISE_DLL
	NSEpiClasser EpiClasser(pContexte->getSuperviseur()) ;
  EpiClasser.donneRelations(psClassifResultO, *pElement, *psClassification, "O") ;
  EpiClasser.donneRelations(psClassifResultP, *pElement, *psClassification, "P") ;
	EpiClasser.donneRelations(psClassifResultI, *pElement, *psClassification, "I") ;
#else
  NSEpiClasserInfo EpiClasser ;
  EpiClasser.donneRelations(psClassifResultO, *pElement, *psClassification, "O", pContexte->getSuperviseur()->getDatabaseManager()) ;
  EpiClasser.donneRelations(psClassifResultP, *pElement, *psClassification, "P", pContexte->getSuperviseur()->getDatabaseManager()) ;
	EpiClasser.donneRelations(psClassifResultI, *pElement, *psClassification, "I", pContexte->getSuperviseur()->getDatabaseManager()) ;
#endif
}
catch (...)
{
	erreur("Exception Classify::computeParsing.", standardError) ;
}
}

// ----------------------------------------------------------
// ParseSOAP::ParseSOAP(string *, NSContexte *)
// ----------------------------------------------------------
// constructeur
// ----------------------------------------------------------

ParseSOAP::ParseSOAP(NSContexte* pCtx, const string sClassifier, const string sChapter)
					:NSRoot(pCtx)
{
  _sClassifier = sClassifier ;
  _sChapter    = sChapter ;

  _pPatho = pContexte->getDico()->getPatholog() ;

  _psSOAPChemin    = (string*) 0 ;
  _psSOAP2Parse    = (string*) 0 ;
  _psResultParsing = (string*) 0 ;
}

// ----------------------------------------------------------
// ParseSOAP::~ParseSOAP(string *, NSContexte *)
// ----------------------------------------------------------
// destructeur
// ----------------------------------------------------------
ParseSOAP::~ParseSOAP()
{
  if (_psResultParsing)
    delete _psResultParsing ;
}

// ----------------------------------------------------------
// void ParseSOAP::ChangeSOAPEdit(string *)
// ----------------------------------------------------------
// permet de changer la string de recherche pour la requ�te
// dans le Lexique Nautilus
// ----------------------------------------------------------
// normalement cette fonction va devenir obsol�te puisqu'on
// ne passe plus la string de recherche dans le constructeur
// mais � la fonction de recherche directement
// ----------------------------------------------------------
void
ParseSOAP::ChangeSOAPEdit(string *psSOAPEdit)
{
  _psSOAP2Parse = psSOAPEdit ;
}


// ----------------------------------------------------------
// void ParseSOAP::computeParsing(string *, string *, string *)
// ----------------------------------------------------------
// fera le parsing de la chaine puis appelle la fonction de
// recherche dans le Lexique
// ----------------------------------------------------------
// renvoie le r�sultat par sClassifResult
// ----------------------------------------------------------
void    ParseSOAP::computeParsing(  string  *sLibelle,
                                    string  */*sChemin*/,
                                    string  *psClassifResultO,
                                    string  *psClassifResultP,
                                    string  *psClassifResultI,
                                    string  *psClassifResult3)
{
//    vector<string *> *psResult = new vector<string *> ;
//    string  sResult ;
//    sResult =
  searchTermsInLexique(sLibelle, psClassifResultO, psClassifResultP, psClassifResultI, psClassifResult3) ;
//    computeParsingElem(sLibelle, sChemin, psClassifResultO, psClassifResultP, psClassifResultI) ;
}


// ----------------------------------------------------------
// void ParseSOAP::searchTermsInLexique(string *, string *, string *, string *)
// ----------------------------------------------------------
// recherche dans le Lexique Nautilus des termes issues de la
// chaine ass� en param�tres
// Remarque :
// cette fonction sera tr�s probablement r�cursive
// ----------------------------------------------------------
// renvoie la liste des termes trouv�s
// ----------------------------------------------------------

void
ParseSOAP::searchTermsInLexique(string *psLibelle, string *psClassifResultO, string *psClassifResultP, string *psClassifResultI, string *psClassifResult3, bool bUse3BT)
{
try
{
	if (((string*) NULL == psLibelle) || (string("") == *psLibelle))
		return ;

  string sTrace = string("Processing text: ") + *psLibelle ;
  pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trSteps) ;

  TermsParser TheParser(pContexte, _sClassifier, _sChapter, bUse3BT) ;

  // First, check for the exact verbatim in "reference bases"
  //
  if (bUse3BT)
  {
#ifndef _ENTERPRISE_DLL
    NSThesaurus thesaurus(pContexte->getSuperviseur()) ;
#else
    NSThesaurusInfo thesaurus ;
#endif

    string sClinicalTerms = TheParser.FindAllClinicalTermsStartingWith(&thesaurus, psLibelle, _sClassifier) ;
    if (string("") != sClinicalTerms)
    {
      sTrace = string("Global text found as start in 3BT : ") + sClinicalTerms ;
      pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;
    }
    else
    {
      sTrace = string("Global text not found in 3BT.") ;
      pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;
    }

/*  Now all thesaurus are compiled into Clinical_Labels

    string sSentinelTerms = TheParser.FindAllSentinelTermsStartingWith(&thesaurus, psLibelle, *psClassifier) ;
    if (string("") != sSentinelTerms)
    {
      sTrace = string("Global text found as start in Sentinelles : ") + sSentinelTerms ;
      pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;
    }
    else
    {
      sTrace = string("Global text not found in Sentinelles.") ;
      pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;
    }
*/

    // if ((string("") != sClinicalTerms) || (string("") != sSentinelTerms))
    if (string("") != sClinicalTerms)
    {
      if (psClassifResultP)
        *psClassifResultP = sClinicalTerms ;

      // *psClassifResultP = TheParser.sBasicOnlyAddNewcodes(*psClassifResultP, sSentinelTerms) ;

      return ;
    }
  }

  // Taking an array of individual words after removing all punctuation characters
  //
	ParseElemArray aParseResult ;
	initParseElemArray(psLibelle, &aParseResult) ;

	if (aParseResult.empty())
		return ;

  // Getting the array of individual and compound words (like "corps �tranger")
  //
	ParseElemArray Temp ;
	initGroupElemArray(&aParseResult, &Temp) ;

  // Looking for classification codes
  //
	ElemSetArray *pResult = TheParser.Compute(&Temp) ;

	*psClassifResultO = string("") ;                  //pTheParser->getsObligatoire()) ;

	if (pResult)
  {
		*psClassifResultP = string(pResult->toString()) ; // pTheParser->getsPossible()) ;
    delete pResult ;
  }
	else
		*psClassifResultP = string("") ;

	*psClassifResultI = string("") ;                  //pTheParser->getsInterdit()) ;

/*
    // begin test fab
    NSEpiClassifInfoArray   *pTestArray = new NSEpiClassifInfoArray() ;
    NSEpiClassifDB          *pClassifDB = new NSEpiClassifDB(pContexte) ;
    pClassifDB->searchDomainInClassif(string("6CISP"), pResult, pTestArray) ;
    delete pClassifDB ;
    // end test fab
*/

    // maintenant il faut essayer de trouver les diff�rents termes dans le Lexique
    // en essayant toutes les combinaisons possibles
    // une solution faisable serait d'essayer de trouver des termes qui correspondent
    // au moins dans leur amorce � tous les mots donn�s par Purge, si un mot ne correspond
    // � aucun terme du Lexique (son amorce), c'est pas la peine de faire des recherches
    // avec ce terme en d�but

/*
    ofstream    outFile ;
    outFile.open("resultTestSOAP.log") ;
    if (outFile)
        for (pIter = pResult->begin() ; pIter != pResult->end() ; pIter++)
            outFile.write((*pIter)->c_str(), strlen((*pIter)->c_str())) ;
		outFile.close() ;
*/
}
catch (...)
{
	erreur("Exception ParseSOAP::searchTermsInLexique.", standardError) ;
}
}

void
ParseSOAP::initParseElemArray(string* psLibelle, ParseElemArray* pParseResult)
{
	if (((ParseElemArray*) NULL == pParseResult) ||
                 ((string*) NULL == psLibelle) || (*psLibelle == string("")))
		return ;

	string sLibelPurge = *psLibelle ;
  vector<string*>* pPurgeResult = Purge(&sLibelPurge) ;
  if ((vector<string*>*) NULL == pPurgeResult)
  	return ;

  if (pPurgeResult->empty())
	{
		delete pPurgeResult ;
  	return ;
	}

	ParseElemArray aParseResult(pPurgeResult) ;

  // Il faut supprimer pPurgeResult
  //
  for (vector<string *>::iterator pIter = pPurgeResult->begin() ; pPurgeResult->end() != pIter ; )
	{
		delete *pIter ;
		pPurgeResult->erase(pIter) ;
	}
  delete pPurgeResult ;

  *pParseResult = aParseResult ;
}

void
ParseSOAP::initGroupElemArray(ParseElemArray* pLoneWords, ParseElemArray* pGroups)
{
	if (((ParseElemArray*) NULL == pGroups) ||
              ((ParseElemArray*) NULL == pLoneWords) || (pLoneWords->empty()))
		return ;

	pGroups->vider() ;

  addAllGroups(pLoneWords, pGroups) ;

/*
	ParseElemIter   pIter ;

	// on essaye de voir si un groupe de mot peut commencer par un terme
	// si on ne trouve pas d'occurence dans le LexiqueFlechies, aucun groupe
	// de mots ne peut commencer par cette occurence

	for (pIter = pLoneWords->begin() ; pIter != pLoneWords->end() ; pIter++)
	{
  	INDBLEVEL iResultLevel ;
		bool bResult = findInLexiq((*pIter)->getContent(), 0, &iResultLevel) ;
		if (!bResult && (iResultLevel != INDBasABegining))
			(*pIter)->setNotInFirst(true) ;
	}

	// il faut maintenant cr�er des groupes de mots commencant par les termes
	// qui peuvent commencer un groupe de mots

  NSEpiFlechiesDB Flechies(pContexte) ;

	for (pIter = pLoneWords->begin() ; pIter != pLoneWords->end() ; pIter++)
		if ((*pIter)->getNotInFirst() == false)
		{
    	ParseElem* pGroupElem = findGroup(*pIter, pLoneWords, &Flechies) ;
      if (pGroupElem)
				pGroups->push_back(pGroupElem) ;
		}
*/
}

//
// The goal of this method is to kill small groups that are inside or cross
// a larger group
//
// for example :
// "diab�te" is inside "diab�te type 2"
// "angine" and "poitrine" are inside "angine de poitrine"
//
// So, in the sentence ABCDEFG if we have the groups A AB BCDE CD EFG G
// BCDE is the biggest, and kills AB, CD and EFG ; thus remains A BCDE and G
// WARNING: We must take care not to have AB kill A before AB is killed by BCDE
//
void
ParseSOAP::cleanGroupElemArray(ParseElemArray* pGroups)
{
	if (((ParseElemArray*) NULL == pGroups) || (pGroups->empty()))
		return ;

	int iCurrentSize = 0xFFFF ;

	bool bRunning = true ;

	while (bRunning)
	{
		// First step : find the new iCurrentSize as max of NbTerms < iCurrentSize
    //
    int iNewCurrentSize = 0 ;

    for (ParseElemIter pIter = pGroups->begin() ; pGroups->end() != pIter ; pIter++)
			if (((*pIter)->getNbOfTerms() < iCurrentSize) &&
                           ((*pIter)->getNbOfTerms() > iNewCurrentSize))
    		iNewCurrentSize = (*pIter)->getNbOfTerms() ;

    if (0 == iNewCurrentSize)
    	return ;

    iCurrentSize = iNewCurrentSize ;

    // Second step : groups with this NbOfTerms can kill smallest groups
    //
    for (ParseElemIter pRefIter = pGroups->begin() ; pGroups->end() != pRefIter ; pRefIter++)
    {
			if ((*pRefIter)->getNbOfTerms() == iCurrentSize)
      {
				int iRefLeftPos  = (*pRefIter)->getPos() ;
				int iRefRightPos = iRefLeftPos + (*pRefIter)->getNbOfTerms() - 1 ;

				bool bPosBeforeRef = true ;
        bool bKilledBeforeRef = false ;

        for (ParseElemIter pIter = pGroups->begin() ; pGroups->end() != pIter ; )
        {
        	if (pIter == pRefIter)
          	bPosBeforeRef = false ;

          if ((*pIter)->getNbOfTerms() < iCurrentSize)
          {
          	int iLeftPos = (*pIter)->getPos() ;
						int iRightPos = iLeftPos + (*pIter)->getNbOfTerms() - 1 ;

          	if ((iLeftPos <= iRefRightPos) && (iRightPos >= iRefLeftPos))
            {
            	// Killing objects before pRefIter is dangerous because
              // it changes pRefIter itself ; so we just mark it for deletion
              // by setting NbOfTerms to -1
							//
              if (bPosBeforeRef)
              {
              	bKilledBeforeRef = true ;
                (*pIter)->setNbOfTerms(-1) ;
                pIter++ ;
              }
              else
              {
              	delete *pIter ;
        				pGroups->erase(pIter) ;
              }
            }
            else
          		pIter++ ;
          }
          else
          	pIter++ ;
        }
        //
        // If we killed items before pRefIter, pRefIter is no longer valid
        //
        if (bKilledBeforeRef)
        {
        	// Kill terms marked for deletion
          //
        	for (ParseElemIter pIter = pGroups->begin() ; pIter != pGroups->end() ; )
          {
          	if ((*pIter)->getNbOfTerms() == -1)
            {
            	delete *pIter ;
            	pGroups->erase(pIter) ;
            }
            else
            	pIter++ ;
          }
          //
          // Reset pRefIter
          //
        	pRefIter = pGroups->begin() ;
        }
			}
		}
	}
}

// ----------------------------------------------------------
// ParseElem *ParseSOAP::findGroupMax(ParseElem *, ParseElemArray *)
// ----------------------------------------------------------
// � partir d'un �l�ment dans l'array des �l�ments trouv�s
// cette fonction cherche � trouver le plus grand groupe de mots commen�ant par
// les termes pouvant commencer un groupe de termes
// ----------------------------------------------------------
// renvoie le nouvel �l�ment trouv�
// ----------------------------------------------------------
ParseElem*
ParseSOAP::findLargerGroup(ParseElem *pElem, ParseElemArray *pArray, NSEpiFlechiesDB* pFlechies)
{
try
{
	if ((NULL == pElem) || (NULL == pArray) || (pArray->empty()))
		return NULL ;

	int           Pos   = 0 ;
  ParseElemIter pIter = pArray->begin() ;
  //
  // Placing the iterator on the good word
  //
	for ( ; (pIter != pArray->end()) && (*pIter != pElem) ; pIter++, Pos++) ;
  if (pIter == pArray->end())
		return NULL ;

	int    nbTermsTemp = 0 ;
  string sResultTemp = "" ;

	string sResult     = "" ;
	int    nbTerms     = 0 ;

  // Testing terms by adding one by one the following words
  //
	for ( ; (pIter != pArray->end()) ; pIter++)
	{
		if (sResultTemp != "")
		{
    	char cLastChar = sResultTemp[strlen(sResultTemp.c_str()) - 1] ;

			if (cLastChar != '\'')
    		sResultTemp += string(" ") ;
		}

    sResultTemp += (*pIter)->getContent() ;
    nbTermsTemp++ ;

		INDBLEVEL iResultLevel ;
		bool bResult = findInLexiq(sResultTemp, pFlechies, &iResultLevel) ;
    //
    // Good term : prepare the result
    //
    if (bResult)
		{
			sResult = sResultTemp ;
			nbTerms = nbTermsTemp ;
		}
    //
    // Term that even doesn't begin a lexique concept : we leave
    //
		else if (iResultLevel != INDBasABegining)
			break ;
	}

	if (sResult != "")
		return new ParseElem(sResult, nbTerms, Pos) ;
  else
  	return NULL ;
}
catch (...)
{
	erreur("Exception ParseSOAP::findLargerGroup.", standardError) ;
	return NULL ;
}
}

void
ParseSOAP::addAllGroups(ParseElemArray *pLoneArray, ParseElemArray *pGroupArray, NSEpiFlechiesDB* pFlechies)
{
try
{
	if ((NULL == pGroupArray) || (NULL == pLoneArray) || (pLoneArray->empty()))
		return ;

	// We need good pos for pLoneArray
  //
  pLoneArray->setAllPos() ;

  int _iPos = 0 ;

	for (ParseElemIter pRefIter = pLoneArray->begin() ; pLoneArray->end() != pRefIter ; pRefIter++)
	{
		int    nbTermsTemp = 0 ;
		string sResultTemp = string("") ;

    _iPos = (*pRefIter)->getPos() ;

    for (ParseElemIter pIter = pRefIter ; pLoneArray->end() != pIter ; pIter++)
    {
      if (string("") != sResultTemp)
      {
        char cLastChar = sResultTemp[strlen(sResultTemp.c_str()) - 1] ;

        if (cLastChar != '\'')
          sResultTemp += string(" ") ;
      }

      sResultTemp += (*pIter)->getContent() ;
      nbTermsTemp++ ;

      INDBLEVEL iResultLevel ;
      bool bResult = findInLexiq(sResultTemp, pFlechies, &iResultLevel) ;
      //
      // Good term : prepare the result
      //
      if (bResult)
      	pGroupArray->push_back(new ParseElem(sResultTemp, nbTermsTemp, _iPos)) ;
      //
      // Term that even doesn't begin a lexique concept : we leave
      //
      else if (iResultLevel != INDBasABegining)
        break ;
    }
	}
}
catch (...)
{
	erreur("Exception ParseSOAP::addAllGroups.", standardError) ;
	return ;
}
}

// ----------------------------------------------------------
// bool ParseSOAP::findInLexiq(string)
// ----------------------------------------------------------
// regarde si le terme repr�sent� par la string pass�e en
// param�tre est pr�sent ou pas dans le lexique
// ----------------------------------------------------------
// renvoie true si le terme est pr�sent, sinon false
// ----------------------------------------------------------
bool
ParseSOAP::findInLexiq(string ps2Find, NSEpiFlechiesDB* pFlechies, INDBLEVEL* pLevel)
{
try
{
  bool bTermFound = false ;

	if (pFlechies)
		bTermFound = pFlechies->isInDB(&ps2Find, pLevel) ;
  else
  {
	  NSEpiFlechiesDB Flechies(pContexte) ;
    bTermFound = Flechies.isInDB(&ps2Find, pLevel) ;
  }

  string sTrace = string("Term ") + ps2Find ;
  if (false == bTermFound)
    sTrace += string(" not") ;
  sTrace += string(" found in Flechies.") ;
  pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;

  return bTermFound ;
}
catch (...)
{
	erreur("Exception ParseSOAP::findInLexiq.", standardError) ;
	return false ;
}
}

// ----------------------------------------------------------
// vector<string *> *ParseSOAP::Purge(string *)
// ----------------------------------------------------------
// d�coupe la chaine de caract�re en petits morceaux qui
// repr�sente chacun un mot, on enl�ve en m�me temps tous les
// signes de ponctuations
// ----------------------------------------------------------
// renvoie la liste des �l�ments �l�mentaires (mots)
// ----------------------------------------------------------
vector<string *>*
ParseSOAP::Purge(string *sLibelle)
{
try
{
	vector<string *> *pResult = new vector<string *> ;

	if (*sLibelle == "")
		return (pResult) ;

	//
	// Etape 1 : on remplace les caract�res de ponctuation par des blancs
	//
	string sToRemove = string(";:?!") ;

  size_t iPos ;
  for (size_t i = 0 ; i < strlen(sToRemove.c_str()) ; i++)
	{
		iPos = sLibelle->find(sToRemove[i]) ;
    while (iPos != NPOS)
    {
			sLibelle->replace(iPos, 1, " ") ;
			iPos = sLibelle->find(sToRemove[i]) ;
    }
	}

	//
	// Etape 1 bis : on remplace les caract�res de ponctuation par des blancs
  //               si ce ne sont pas des s�parateurs num�riques
	//
	sToRemove = string(",.") ;

  for (size_t i = 0 ; i < strlen(sToRemove.c_str()) ; i++)
	{
		iPos = sLibelle->find(sToRemove[i]) ;
    while (iPos != NPOS)
    {
    	// We check if the char to remove is not between 2 numbers
      //
    	if ((iPos == 0) || (iPos == strlen(sLibelle->c_str())-1) ||
          ((iPos > 0) && (!isdigit((*sLibelle)[iPos-1]))) ||
          ((iPos < strlen(sLibelle->c_str())-1) && (!isdigit((*sLibelle)[iPos+1])))
         )
				sLibelle->replace(iPos, 1, " ") ;

			iPos = sLibelle->find(sToRemove[i], iPos + 1) ;
    }
	}

	// Etape 2 : on remplace les apostrophes par des blancs

	//  � r�fl�chir plus s�rieusement
	//  les termes du Lexique peuvent contenir des apostrophes
	// 	from nsparse (STEP project)
	iPos = 0 ;
	while (sLibelle->find("'", iPos + 1) != string::npos)
	{
		iPos = sLibelle->find("'", iPos + 1) ;
		sLibelle->insert(iPos + 1, " ") ;
	}

/*
		iPos = 0 ;
		while (sLibelle->find("'", iPos + 1) != NPOS)
		{
				iPos = sLibelle->find("'", iPos + 1) ;
				sLibelle->insert(iPos, " ") ;
				iPos = iPos + 2 ;
				sLibelle->insert(iPos, " ") ;
		}
*/

	// Etape 3 : on supprime les blancs en exc�s
	//
	strip(*sLibelle, stripBoth) ;

	iPos = 0;
	while (sLibelle->find(" ", iPos + 1) != NPOS)
	{
		iPos = sLibelle->find(" ", iPos + 1) ;
		while (sLibelle->find(" ", iPos + 1) == iPos + 1)
			sLibelle->erase(iPos, 1) ;
	}

	// Etape 4 : on met les mots dans l'array r�sultat
	//
	int iPosBegin = 0 ;
	do
	{
		if (sLibelle->find(" ", iPosBegin + 1) != NPOS)
			iPos = sLibelle->find(" ", iPosBegin + 1) ;
		else
			iPos = strlen(sLibelle->c_str()) ;

		pResult->push_back(new string(*sLibelle, iPosBegin, iPos - (iPosBegin)) ) ;

		iPosBegin = iPos + 1;
	}
	while (iPos < strlen(sLibelle->c_str()) ) ;

	return (pResult) ;
}
catch (...)
{
	erreur("Exception ParseSOAP::Purge.", standardError) ;
	return NULL ;
}
}

// ----------------------------------------------------------
// void ParseSOAP::computeParsingElem(string *, string *, string *)
// ----------------------------------------------------------
// fait la recherche d'un �l�ment dans le Lexique et renvoie
// le r�sultat par sClassifResult
// ----------------------------------------------------------
bool
ParseSOAP::computeParsingElem(  string  *sLibelle,
                                string  *sChemin,
                                string  *psClassifResultO,
                                string  *psClassifResultP,
                                string  *psClassifResultI,
                                string  *psClassifResult3)
{
try
{
	_psSOAP2Parse = sLibelle ;
	_psSOAPChemin = sChemin ;

	if (ParsingEq())
	{
    string sCodeSens ;
		pContexte->getDico()->donneCodeSens(getCodeParsing(), &sCodeSens) ;

#ifndef _ENTERPRISE_DLL
		NSEpiClasser EpiClasser(pContexte->getSuperviseur()) ;
		EpiClasser.donneRelations(psClassifResultO, sCodeSens, _sClassifier, "O") ;
		EpiClasser.donneRelations(psClassifResultP, sCodeSens, _sClassifier, "P") ;
		EpiClasser.donneRelations(psClassifResultI, sCodeSens, _sClassifier, "I") ;
#else
    NSEpiClasserInfo EpiClasser ;
    EpiClasser.donneRelations(psClassifResultO, sCodeSens, _sClassifier, "O", pContexte->getSuperviseur()->getDatabaseManager()) ;
    EpiClasser.donneRelations(psClassifResultP, sCodeSens, _sClassifier, "P", pContexte->getSuperviseur()->getDatabaseManager()) ;
	  EpiClasser.donneRelations(psClassifResultI, sCodeSens, _sClassifier, "I", pContexte->getSuperviseur()->getDatabaseManager()) ;
#endif
	}
	return true ;
}
catch (...)
{
	erreur("Exception ParseSOAP::computeParsingElem.", standardError) ;
	return false;
}
}

// ----------------------------------------------------------
// bool     ParseSOAP::ParsingEq()
// ----------------------------------------------------------
// Le but de cette m�thode est de trouver un terme dans le
// Lexique un terme qui matche "exactement" avec la requ�te
// ----------------------------------------------------------
// renvoie un bool�en -- si on a trouv� un terme qui matche
// ou pas
// ----------------------------------------------------------
bool
ParseSOAP::ParsingEq()                   // renvoie le nombre de termes trouv�s
{
try
{
  char* pcSOAPRadixReq = new char[strlen(_psSOAP2Parse->c_str()) + 1] ;
  char* pcSOAPRadix    = new char[strlen(_psSOAP2Parse->c_str()) + 1] ;

  // la requ�te se fait en majuscule � cause des probl�mes d'accentuations
  // on garde quand m�me une chaine pour la comparaison avec la requ�te
  strcpy(pcSOAPRadixReq, _psSOAP2Parse->c_str()) ;
  strcpy(pcSOAPRadix,    _psSOAP2Parse->c_str()) ;
  ConvertitMajuscule(pcSOAPRadixReq) ;

  // on s'arrete au premier mot pour la requ�te
  // on s'occupe plus tard de tester toutes les possibilit�s avec les mots suivants
  // (probl�mes au niveau des requ�tes avec plusieurs mots)
  // la m�thode GEQ cherche >= or les termes du Lexique peuvent avoir plusieurs espaces avant le deuxi�me mot
  int iPos = _psSOAP2Parse->find(" ") ;
  pcSOAPRadix[iPos]    = '\0' ;
  pcSOAPRadixReq[iPos] = '\0' ;

  // on recherche dans le Lexique keySEARCHEQ, keySEARCHGEQ, keySEARCHGT
  // cette requ�te cherche un terme du Lexique "proche" (dont le d�but est le plus proche)
  string sToFind = string(pcSOAPRadixReq) ;

#ifndef _ENTERPRISE_DLL
  _pPatho->trouveLibelle(&sToFind, keySEARCHGEQ, dbiWRITELOCK) ;
  // si on a rien trouv�, on arr�te
  if (_pPatho->lastError != DBIERR_NONE)
#else
  if (false == _pPatho->trouveLibelleApproche(pContexte->getUserLanguage(), &sToFind))
#endif
  {
    delete[] pcSOAPRadixReq ;
    delete[] pcSOAPRadix ;
    return (false) ;
  }

  // on trouve la racine commune
  size_t iCompare ;
  for (iCompare = 0 ; (iCompare <= strlen(pcSOAPRadix)) &&
                        (strncmp(_pPatho->_Donnees.getLabel().c_str(), pcSOAPRadix, iCompare) == 0) ;
                        iCompare++)
        ;
  pcSOAPRadix[--iCompare] = '\0' ;
  pcSOAPRadixReq[iCompare] = '\0' ;

#ifndef _ENTERPRISE_DLL

  int comp = 0 ;

  // on va essayer de trouver d'autres occurences
  while ((_pPatho->lastError == DBIERR_NONE) && (0 == comp))
  {
    // purification du r�sultat de la requ�te
    // (nettoyage des caract�res sp�ciaux utilis�s dans le Lexique)
    string  sLibelleAffiche ;
    _pPatho->_Donnees.donneLibelleAffiche(&sLibelleAffiche) ;

    // on v�rifie si le terme trouv� correspond � la requ�te
    if (sLibelleAffiche == *_psSOAP2Parse)
    {
      delete[] pcSOAPRadixReq ;
      delete[] pcSOAPRadix ;

      return (true) ;
    }
    _pPatho->lastError = _pPatho->suivant(dbiWRITELOCK) ;
    if (_pPatho->lastError == DBIERR_NONE)
    {
      _pPatho->lastError = _pPatho->getRecord() ;
			if (_pPatho->lastError == DBIERR_NONE)
      {
        char donneeFiche[255] ;
        strncpy(donneeFiche, _pPatho->_Donnees.libelle, strlen(_pPatho->_Donnees.libelle)) ;
        donneeFiche[strlen(_pPatho->_Donnees.libelle)] = '\0' ;
        ConvertitMajuscule(donneeFiche) ;

        // on fait une comparaison avec la racine (test de continuation)
        comp = strncmp(donneeFiche, pcSOAPRadixReq, strlen(pcSOAPRadix)) ;
      }
    }
  }
#endif

  delete[] pcSOAPRadixReq ;
  delete[] pcSOAPRadix ;

  // � ce stade on a test� tous les termes de la liste d'�l�ments probables (du moins "proche")
  // mais on a pas trouv� de terme qui matche assez
  return (false) ;
}
catch (...)
{
  erreur("Exception ParseSOAP::ParsingEq.", standardError) ;
  return false ;
}
}

// ----------------------------------------------------------
// string   *ParseSOAP::getLibelleParsing()
// ----------------------------------------------------------
// Cette m�thode renvoie le terme trouv�e dans le Lexique
// ----------------------------------------------------------
// renvoie un string *
// ----------------------------------------------------------
string*
ParseSOAP::getLibelleParsing()
{
try
{
  if (_psResultParsing)
    delete _psResultParsing ;

	_psResultParsing = new string(_pPatho->_Donnees.getLabel()) ;

	return (_psResultParsing) ;
}
catch (...)
{
	erreur("Exception ParseSOAP::getLibelleParsing.", standardError) ;
	return NULL ;
}
}

// ----------------------------------------------------------
// string   *ParseSOAP::getCodeParsing()
// ----------------------------------------------------------
// Cette m�thode renvoie le code correspondant au terme
// trouv�e dans le Lexique
// ----------------------------------------------------------
// renvoie un string *
// ----------------------------------------------------------
string*
ParseSOAP::getCodeParsing()
{
try
{
  if (_psResultParsing)
    delete _psResultParsing ;

	_psResultParsing = new string(_pPatho->_Donnees.getCode()) ;

	return (_psResultParsing) ;
}
catch (...)
{
	erreur("Exception ParseSOAP::getCodeParsing.", standardError) ;
	return NULL;
}
}

// ----------------------------------------------------------
// void ParseSOAP::ConvertitMajuscule(char *)
// ----------------------------------------------------------
// convertit une chaine en majuscule
// ----------------------------------------------------------

void
ParseSOAP::ConvertitMajuscule(char* chaine)
{
  for (size_t i = 0 ; i < strlen(chaine) ; i++)
  {
    switch (chaine[i])
    {
      case '�' ://200
      case '�' :
      case '�' :
      case '�' :
			case '�' :
      case '�' :
      case '�' :
      case '�' : chaine[i] =  'E' ;
        break;
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' : //197
      case '�' :
      case '�' : //226
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' : chaine[i] =  'A' ;
                 break;
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' : chaine[i] =  'I' ;
                 break;
      case '�' ://220
      case '�' :
      case '�' :
      case '�' : //216
      case '�' :
      case '�' :
      case '�' :
      case '�' : chaine[i] =  'U' ;
                 break;
      case '�' : //213
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' : //242
      case '�' :
      case '�' :
      case '�' :
      case '�' : chaine[i] = 'O' ;
                 break;
      case '�' :
      case '�' : chaine[i] = 'N' ; //209
                 break;
      case '�' :
      case '�' : chaine[i] = 'Y' ; //209
                 break;
      case '�' :
      case '�' : chaine[i] = 'C' ; //209
                 break;
      case '�' : chaine[i] = 'D' ; //209
                 break;
#ifdef __linux__
      default  : chaine[i] = toupper(chaine[i]) ;
#endif
    }
  }
#ifndef __linux__
  chaine = strupr(chaine) ;
#endif
}

string
ParseSOAP::ConvertitMajuscule(string sChaine)
{
	char* pcChaine = new char[strlen(sChaine.c_str()) + 1] ;
	strcpy(pcChaine, sChaine.c_str()) ;

  ConvertitMajuscule(pcChaine) ;

  string sMajChaine = string(pcChaine) ;
  delete[] pcChaine ;

  return sMajChaine ;
}

// ----------------------------------------------------------
// ParseCategory::ParseCategory(string, string, string)
// ----------------------------------------------------------
// initialise un objet ParseCategory avec les valeurs de
// chacun des Pattern pour les diff�rents domaines
// (un pattern pour tout les domaines serait peut-�tre suffisant)
// ----------------------------------------------------------
// constructeur
// ----------------------------------------------------------

/*
ParseCategory::ParseCategory(string sObligatoire, string sPossible, string sInterdit)
{
		sPatternObligatoire = string(sObligatoire);
		sPatternPossible    = string(sPossible);
		sPatternInterdit    = string(sInterdit);
}
*/

// ----------------------------------------------------------
// ParseCategory::ParseCategory(int, string, string)
// ----------------------------------------------------------
// construit un �l�ment ParseCategory � partir du nombre de
// Digit de la classification, le nom de cette classification
// (label) et son pattern
// ----------------------------------------------------------
// constructeur
// ----------------------------------------------------------
ParseCategory::ParseCategory(int nb, string label, string pattern)
{
try
{
  nbDigit   = nb ;
  sLabel    = label ;
  psPattern = new vector<string *> ;

  int iPosBeg = 0 ;
  int iPosEnd = pattern.find(" ") ;
  int iLength = iPosEnd - iPosBeg ;

  while (iLength > 0)
  {
    string *pNewString = new string(pattern, iPosBeg, iLength) ;
    psPattern->push_back(pNewString) ;

    iPosBeg = iPosEnd + 1 ;
    iPosEnd = pattern.find(" ", iPosBeg) ;
    if (iPosEnd < iPosBeg)
      iPosEnd = strlen(pattern.c_str()) ;
    iLength = iPosEnd - iPosBeg ;
  }

  pDomainObligatoire = new ElemSetArray() ;
  pDomainPossible    = new ElemSetArray() ;
  pDomainInterdit    = new ElemSetArray() ;
  pDomain3BT         = new ElemSetArray() ;

  sObligatoire = string("") ;
  sPossible    = string("") ;
  sInterdit    = string("") ;
  s3BT         = string("") ;
}
catch (...)
{
  erreur("Exception ParseCategory ctor.", standardError) ;
}
}

// ----------------------------------------------------------
// ParseCategory::~ParseCategory()
// ----------------------------------------------------------
// destructeur
// ----------------------------------------------------------
ParseCategory::~ParseCategory()
{
//    delete psPattern ;
  pDomainObligatoire->vider() ;
  delete pDomainObligatoire ;
  pDomainPossible->vider() ;
  delete pDomainPossible ;
  pDomainInterdit->vider() ;
  delete pDomainInterdit ;
  pDomain3BT->vider() ;
  delete pDomain3BT ;

  if (false == psPattern->empty())
  {
    pstringIterator i = psPattern->begin() ;
    for ( ; i != psPattern->end() ; )
    {
      delete *i ;
      psPattern->erase(i) ;
    }
  }
  delete psPattern ;
}

// ----------------------------------------------------------
// void ParseCategory::DefObligatoire(string)
// ----------------------------------------------------------
// d�finit le domaine obligatoire d'un objet ParseCategory
// � partir d'une string d�finissant ce domaine
// ----------------------------------------------------------
// ----------------------------------------------------------
void
ParseCategory::DefObligatoire(string sDefine)
{
  sObligatoire = sDefine ;

  if (NULL != pDomainObligatoire)
    delete pDomainObligatoire ;
    
  pDomainObligatoire = DefDomain(sDefine) ;
}

// ----------------------------------------------------------
// void ParseCategory::DefObligatoire(ElemSetArray *)
// ----------------------------------------------------------
// d�finit le domaine obligatoire d'un objet ParseCategory
// � partir d'un domaine, d�finit aussi la string qui correspond
// ----------------------------------------------------------
// ----------------------------------------------------------
void
ParseCategory::DefObligatoire(ElemSetArray *pElemSetArray)
{
  if (NULL != pDomainObligatoire)
    delete pDomainObligatoire ;

  pDomainObligatoire = pElemSetArray ;

  if (NULL != pElemSetArray)
    sObligatoire = pDomainObligatoire->toString() ;
}

// ----------------------------------------------------------
// void ParseCategory::DefPossible(string)
// ----------------------------------------------------------
// d�finit le domaine possible d'un objet ParseCategory
// � partir d'une string d�finissant ce domaine
// ----------------------------------------------------------
// ----------------------------------------------------------
void
ParseCategory::DefPossible(string sDefine)
{
  sPossible = sDefine ;

  if (NULL != pDomainPossible)
    delete pDomainPossible ;

  pDomainPossible = DefDomain(sDefine) ;
}

// ----------------------------------------------------------
// void ParseCategory::DefPossible(ElemSetArray *)
// ----------------------------------------------------------
// d�finit le domaine possible d'un objet ParseCategory �
// partir d'un domaine, d�finit aussi la string qui correspond
// ----------------------------------------------------------
// ----------------------------------------------------------
void
ParseCategory::DefPossible(ElemSetArray *pElemSetArray)
{
  if (NULL != pDomainPossible)
    delete pDomainPossible ;

  pDomainPossible = pElemSetArray ;

  if (NULL != pElemSetArray)
    sPossible = pDomainPossible->toString() ;
}

// ----------------------------------------------------------
// void ParseCategory::DefInterdit(string)
// ----------------------------------------------------------
// d�finit le domaine interdit d'un objet ParseCategory �
// partir de la string qui d�finit le domaine
// ----------------------------------------------------------
// ----------------------------------------------------------
void
ParseCategory::DefInterdit(string sDefine)
{
  sInterdit = sDefine ;

  if (NULL != pDomainInterdit)
    delete pDomainInterdit ;

  pDomainInterdit = DefDomain(sDefine) ;
}

// ----------------------------------------------------------
// void ParseCategory::DefInterdit(ElemSetArray *)
// ----------------------------------------------------------
// d�finit le domaine interdit d'un objet ParseCategory �
// partir d'un domaine, d�finit aussi la string qui correspond
// ----------------------------------------------------------
// ----------------------------------------------------------
void
ParseCategory::DefInterdit(ElemSetArray *pElemSetArray)
{
  if (NULL != pDomainInterdit)
    delete pDomainInterdit ;

  pDomainInterdit = pElemSetArray ;

  if (NULL != pElemSetArray)
    sInterdit = pDomainInterdit->toString() ;
}

void
ParseCategory::Def3BT(string sDefine)
{
  s3BT = sDefine ;

  if (NULL != pDomain3BT)
    delete pDomain3BT ;

  pDomain3BT = DefDomain(sDefine) ;
}

void
ParseCategory::Def3BT(ElemSetArray *pElemSetArray)
{
  if (NULL != pDomain3BT)
    delete pDomain3BT ;

  pDomain3BT = pElemSetArray ;

  if (NULL != pElemSetArray)
    s3BT = pDomain3BT->toString() ;
}

// ----------------------------------------------------------
// void ParseCategory::DefCritere(string, string, string)
// ----------------------------------------------------------
// d�finit les domaines Oblgatoire, Possible et Interdit d'un
// objet ParseCategory � partir des string qui correspondent
// ----------------------------------------------------------
// ----------------------------------------------------------
void
ParseCategory::DefCritere(string sDefO, string sDefP, string sDefI, string sDef3)
{
  DefObligatoire(sDefO) ;
  DefPossible(sDefP) ;
  DefInterdit(sDefI) ;
  Def3BT(sDef3) ;
}

// ----------------------------------------------------------
// ElemSetArray *ParseCategory::DefDomain(string)
// ----------------------------------------------------------
// d�finit un domaine � partir d'une string
// ----------------------------------------------------------
// renvoie le domaine (�ventuellement vide, mais != NULL)
// ----------------------------------------------------------
ElemSetArray*
ParseCategory::DefDomain(string sDomain)
{
try
{
	ElemSetArray* pESAResult = new ElemSetArray() ;

	if (string("") == sDomain)
		return pESAResult ;

	size_t iPosBeg = 0 ;
	size_t iPosEnd = sDomain.find(";") ;
	if (iPosEnd == NPOS)
		iPosEnd = strlen(sDomain.c_str()) ;
	int iLength = iPosEnd - iPosBeg ;

	while (iPosEnd < strlen(sDomain.c_str()) + 1)
	{
		ElemSet* pNewElem = new ElemSet(string(sDomain, iPosBeg, iLength)) ;

		ElemSetArray ElemSetArrayResult ;
		pNewElem->ComputeJoker(*psPattern, &ElemSetArrayResult) ;

		if (ElemSetArrayResult.empty())
			pESAResult->push_back(pNewElem) ;
		else
		{
			for (ElemSetIterator ElemSetIter = ElemSetArrayResult.begin() ; ElemSetIter != ElemSetArrayResult.end() ; ElemSetIter++)
				pESAResult->push_back(new ElemSet(*(*ElemSetIter))) ;
			delete pNewElem ;
		}

		iPosBeg = iPosEnd + 1 ;
		if (iPosBeg < strlen(sDomain.c_str()))
		{
			iPosEnd = sDomain.find(";", iPosBeg) ;
			if (iPosEnd == NPOS)
				iPosEnd = strlen(sDomain.c_str()) ;
			iLength = iPosEnd - iPosBeg ;
		}
		else
			iPosEnd = strlen(sDomain.c_str()) + 1 ;
	}
	return (pESAResult) ;      // pour l'instant, le r�sultat sera psResult
}
catch (...)
{
	erreur("Exception ParseCategory::DefDomain.", standardError) ;
	return NULL ;
}
}

// ----------------------------------------------------------
// ElemSet::ElemSet(string)
// ----------------------------------------------------------
// prend en param�tre la d�finition d'un �l�ment sous forme
// de string
// ----------------------------------------------------------
// constructeur
// ----------------------------------------------------------
ElemSet::ElemSet(string sElem)
{
  lObjectCount++ ;

  if (string("") == sElem)
  {
    sBegin    = string("") ;
    sEnd      = string("") ;
    bEmptySet = false ;
    return ;
  }

  size_t iPos = sElem.find("-") ;
  if (NPOS != iPos)
  {
    sBegin = string(sElem, 0, iPos) ;
    sEnd   = string(sElem, iPos + 1, strlen(sElem.c_str()) - iPos - 1) ;
  }
  else
  {
    sBegin = string(sElem) ;
    sEnd   = string(sElem) ;
  }
  reorder() ;
  bEmptySet = false ;
}

// ----------------------------------------------------------
// ElemSet::ElemSet(string, string)
// ----------------------------------------------------------
// prend en param�tres, la borneSup et la borneInf de
// l'�l�ment
// ----------------------------------------------------------
// constructeur
// ----------------------------------------------------------
ElemSet::ElemSet(string sElemBegin, string sElemEnd)
{
  lObjectCount++ ;

  if (string("") != sElemBegin)
    sBegin = sElemBegin ;
  else
    sBegin = string("") ;

  if (string("") != sElemEnd)
    sEnd   = sElemEnd ;
  else
    sEnd   = string("") ;

  reorder() ;

  if ((string("") == sBegin) && (string("") == sEnd))
    bEmptySet = true ;
  else
    bEmptySet = false ;
}

// ----------------------------------------------------------
// ElemSet::ElemSet(string, string, bool)
// ----------------------------------------------------------
// prend en param�tres, la borneSup et la borneInf de
// l'�l�ment ainsi qu'un bool qui d�finit si l'�l�ment est un
// �l�ment vide
// ----------------------------------------------------------
// constructeur
// ----------------------------------------------------------
ElemSet::ElemSet(string sElemBegin, string sElemEnd, bool bElemEmpty)
{
  lObjectCount++ ;

  if (string("") != sElemBegin)
    sBegin = sElemBegin ;
  else
    sBegin = string("") ;

  if (string("") != sElemEnd)
    sEnd   = sElemEnd ;
  else
    sEnd   = string("") ;

  reorder() ;
  bEmptySet = bElemEmpty ;
}

// ----------------------------------------------------------
// constructeur copie - copy ctor
// ----------------------------------------------------------
ElemSet::ElemSet(const ElemSet& rv)
{
  lObjectCount++ ;

  if (string("") != rv.sBegin)
    sBegin = rv.sBegin ;
  else
    sBegin = string("") ;

  if (string("") != rv.sEnd)
    sEnd   = rv.sEnd ;
  else
    sEnd   = string("") ;

  bEmptySet = rv.bEmptySet ;
}

// ----------------------------------------------------------
// op�rateur d'affectation
// ----------------------------------------------------------
ElemSet&
ElemSet::operator=(const ElemSet& src)
{
  if (&src == this)
    return *this ;

  if (string("") != src.sBegin)
    sBegin = src.sBegin ;
  else
    sBegin = string("") ;

  if (string("") != src.sEnd)
    sEnd   = src.sEnd ;
  else
    sEnd   = string("") ;

  bEmptySet = src.bEmptySet ;

  return *this ;
}

// ----------------------------------------------------------
// On classe de fa�on � ce que sBegin <= sEnd
// ----------------------------------------------------------
void
ElemSet::reorder()
{
  if (sBegin <= sEnd)
    return ;

  string sBuff = sBegin ;
  sBegin = sEnd ;
  sEnd   = sBuff ;
}

// ----------------------------------------------------------
// string ElemSet::toString()
// ----------------------------------------------------------
// permet l'affichage d'un ElemSet
// ----------------------------------------------------------
// renvoie la string qui correspond � la d�finition d'un �l�ment
// ----------------------------------------------------------
string
ElemSet::toString()
{
  string sResult = sBegin ;
  if (sBegin != sEnd)
  {
    if (sResult != "")
      sResult += string("-") ;
    sResult += sEnd ;
  }
  return (sResult) ;
}

/*
// ----------------------------------------------------------
// int ElemSet::CountJoker(string)
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
int     ElemSet::CountJoker(string sElem)
{
		int iPos = sElem.find("?", iPos);
		int iResult = 0;

		while (iPos != NPOS)
		{
				iPos = sElem.find("?", iPos);
				iResult++;
		}
		return iResult;
}
*/


// ----------------------------------------------------------
// bool ElemSet::HasJoker()
// ----------------------------------------------------------
// ----------------------------------------------------------
// cette fonction retourne si l'�l�ment comporte des
// caract�res Jokers ou pas
// ----------------------------------------------------------
bool
ElemSet::HasJoker()
{
  if ((sBegin.find("?") != NPOS) || (sEnd.find("?") != NPOS))
    return true ;
  else
    return false ;
}

// ----------------------------------------------------------
// void ElemSet::ComputeJoker(vector<string *>; ElemSetArray *)
// ----------------------------------------------------------
// cette fonction est "la" fonction qui fait le traitement des
// Joker.
// la liste de string (premier param�tre) est la liste des
// Pattern correspondant � chacun des Digits
// la liste d'�l�ments (deuxi�me param�tre) est la liste des
// �l�ments g�n�r�e par cette fonction
// cette fonction est r�cursive (pas dans le sens puriste du
// terme, mais elle s'appelle elle-m�me afin de traiter tous
// les caract�res Joker pr�sents dans un �l�ment)
// ----------------------------------------------------------
// cette fonction g�n�re la liste des �l�ments correspondant
// � une d�finition donn�e avec des caract�res Joker
// elle ne traite pas pour l'instant des simplifications de
// domaine d'�l�ments relatifs � des �l�ments cons�cutifs
// (exemple : plusieurs �l�ments cons�cutifs pourraient �tre
// remplac�s par un intervalle)
// cette fonctionnalit� devra certainement �tre faite par
// une autre fonction
// ----------------------------------------------------------
void
ElemSet::ComputeJoker(vector<string *> sPatterns, ElemSetArray *pElemSetResult)
{
try
{
  if ((NULL == pElemSetResult) || (true == sPatterns.empty()))
    return ;

	if (!(this->HasJoker()))
		return ;

	size_t iJokerPos = sBegin.find("?") ;

	// Il est impossible de traiter des jokers h�t�rog�nes, comme A?1-A2?
	// Heterogeneous jokers, like A?1-A2?, can't get solved
	if (iJokerPos != sEnd.find("?"))
	{
		// il faudrait retourner une erreur
		return ;
	}

	string sBornInf = sBegin ;
	string sBornSup = sEnd ;
	string sPattern = *(sPatterns[iJokerPos]);

	for (size_t i = 0 ; i < strlen(sPattern.c_str()) ; i++)
	{
		// Elaboration d'un intervalle possible
		// Building of a "less generic" interval
		sBornInf[iJokerPos] = sPattern[i] ;
		sBornSup[iJokerPos] = sPattern[i] ;

		ElemSet *pNewElemSet = new ElemSet(sBornInf, sBornSup) ;

		// Cet intervalle peut contenir des jokers, on it�re
		// This interval may still contain jokers, we iterate
		ElemSetArray NewElemSetResult ;
		pNewElemSet->ComputeJoker(sPatterns, &NewElemSetResult) ;

		if (NewElemSetResult.empty())
			pElemSetResult->push_back(pNewElemSet) ;
		else
		{
			for (ElemSetIterator ElemSetIter = NewElemSetResult.begin() ; ElemSetIter != NewElemSetResult.end() ; ElemSetIter++)
				pElemSetResult->push_back(new ElemSet(*(*ElemSetIter))) ;
			delete pNewElemSet ;
		}
	}
}
catch (...)
{
	erreur("Exception ElemSet::ComputeJoker.", standardError) ;
}
}

// ----------------------------------------------------------
//
// Does the code belong to that ElemSet ?
//
// ----------------------------------------------------------
bool
ElemSet::doesContain(const string sCode) const
{
  // Les chaines vides sont pi�geuses dans les comparaisons
  // Empty strings are tricky when compared

  if (string("") == sCode)
    return false ;
  if ((string("") == sBegin) && (string("") == sEnd))
    return false ;

  //  Cas trivial
  if ((sBegin == sCode) || (sEnd == sCode))
    return true ;

  string sBornInf ;
  string sBornSup ;
  string sCompare ;

  size_t iCodeSize = strlen(sCode.c_str()) ;
  size_t iElemSize = strlen(sBegin.c_str()) ;

  // Jokers ?
  size_t iJokerPos = sBegin.find("?") ;
  if (NPOS != iJokerPos)
  {
    // Heterogeneous jokers, like A?1-A2?, can't get solved
    if (iJokerPos != sEnd.find("?"))
      return false ;

    // Size matters : it is only possible to compare strings with same size

    // if sCode is shorter than sBegin, and trailing chars are not jokers
    // return false : ex A?3-A?5 compared with A4
    if (iCodeSize < iElemSize)
    {
      if ((string(sBegin, iCodeSize, iElemSize - iCodeSize) != string(iElemSize - iCodeSize, '?')) ||
          (string(sEnd, iCodeSize, iElemSize - iCodeSize) != string(iElemSize - iCodeSize, '?')))
        return false ;
      else
      {
        sBornInf = string(sBegin, 0, iCodeSize) ;
        sBornSup = string(sEnd, 0, iCodeSize) ;
        sCompare = sCode ;
      }
    }
    else
    {
      sBornInf = sBegin ;
      sBornSup = sEnd ;
      // if sCode is longer than sBegin, we truncate it
      if (iCodeSize > iElemSize)
        sCompare = string(sCode, 0, iElemSize) ;
      else
        sCompare = sCode ;
    }

    // On supprime les colonnes qui poss�dent des jokers
    // We delete columns with a joker
    iJokerPos = sBornInf.find("?") ;
    while (iJokerPos != NPOS)
    {
      // Heterogeneous jokers, like A?1-A2?, can't get solved
      if (iJokerPos != sBornSup.find("?"))
        return false ;

      size_t iSize = strlen(sBornInf.c_str()) ;
      if (iJokerPos < iSize - 1)
      {
        sBornInf = string(sBornInf, 0, iJokerPos) + string(sBornInf, iJokerPos+1, iSize-iJokerPos-1) ;
        sBornSup = string(sBornSup, 0, iJokerPos) + string(sBornSup, iJokerPos+1, iSize-iJokerPos-1) ;
        sCompare = string(sCompare, 0, iJokerPos) + string(sCompare, iJokerPos+1, iSize-iJokerPos-1) ;
      }
      else if (iJokerPos > 0)
      {
        sBornInf = string(sBornInf, 0, iJokerPos) ;
        sBornSup = string(sBornSup, 0, iJokerPos) ;
        sCompare = string(sCompare, 0, iJokerPos) ;
      }
      else
        return true ;  // only jokers

      iJokerPos = sBornInf.find("?") ;
    }
  }
  // No jokers
  else
  {
    // Size matters : it is only possible to compare strings with same size

    // if sCode is shorter than sBegin
    // ex A23-A25 compared with A2 = false
    // ex A13-A32 compared with A2 = true
    if (iCodeSize < iElemSize)
    {
      sBornInf = string(sBegin, 0, iCodeSize) ;
      sBornSup = string(sEnd, 0, iCodeSize) ;
      sCompare = sCode ;
      if ((sCode > sBornInf) && (sCode < sBornSup))
        return true ;
      else
        return false ;
    }
    else
    {
      sBornInf = sBegin ;
      sBornSup = sEnd ;
      // if sCode is longer than sBegin, we truncate it
      if (iCodeSize > iElemSize)
        sCompare = string(sCode, 0, iElemSize) ;
      else
        sCompare = sCode ;
    }
  }
  if ((sCompare >= sBornInf) && (sCompare <= sBornSup))
    return true ;
  else
    return false ;
}

/*
// ----------------------------------------------------------
// ElemSetArray *ElemSet::ComputeJoker(vector<string *> *)
// ----------------------------------------------------------
// ne fait pas grand chose
// ----------------------------------------------------------
// cette fonction est obsol�te (il faudrai juste v�rifier
// qu'elle n'est plus appeler nulle part avant de la virer
// ----------------------------------------------------------
// renvoie un ensemble qui n'est m�me pas remplie
// ----------------------------------------------------------
ElemSetArray    *ElemSet::ComputeJoker(vector<string *> *psPattern)
{
		ElemSetArray    *pElemSetArrayResult = new ElemSetArray();

		if (this->sBegin == this->sEnd) // cas d'un �l�ment simple
		{
				int         nbJoker = this->CountJoker(this->sBegin);
				int         iJokerPos = this->sBegin.find("?");

				for (int i = 0; (i < nbJoker) && (iJokerPos != NPOS); i++)
				{
						iJokerPos = this->sBegin.find("?", iJokerPos);
				}
/-
// !!! cas particulier '?' � la fin --> on cr�� un intervalle !!!
				if (iJokerPos + nbJoker == strlen(this->sBegin.c_str()))
				// si les '?' sont � la fin, on cr�� un intervalle
				{
						for ( ; iJokerPos <= strlen(this->sBegin.c_str()) ; iJokerPos++)
						{
								string  sPattern = *(*psPattern)[iJokerPos];         // on r�cup�re le pattern correspondant au Digit
								// remplacement du '?' de d�but d'intervalle par le minimum du Digit
								char    sPatternMin[2];
								sprintf(sPatternMin, "%c", sPattern.at(0));
								this->sBegin.replace(iJokerPos, 1, sPatternMin);
								// remplacement du '?' de fin d'intervalle par le maximum du Digit
								char    sPatternMax[2];
								sprintf(sPatternMax, "%c", sPattern.at(strlen(sPattern.c_str()) - 1));
								this->sEnd.replace(iJokerPos, 1, sPatternMax);
						}
				}
-/
		}
		return (pElemSetArrayResult);
}
*/


/*
// ----------------------------------------------------------
// void ElemSet::ComputeJokerInterval()
// ----------------------------------------------------------
// traite des Joker dans les intervalles
// les intervalles devront �tre trait�s autrement
// ----------------------------------------------------------
// cette fonction est obsol�te (il faudrai juste v�rifier
// qu'elle n'est plus appeler nulle part avant de la virer)
// ----------------------------------------------------------
// modifie les bornes de l'�l�ment courant (this)
// ----------------------------------------------------------
void    ElemSet::ComputeJokerInterval()
{
		if (this->sBegin < this->sEnd)
		{
				// devrait �tre le min et max correspondant au Pattern et pas "0" et "9"
				if (CountJoker(sBegin) > 0)
						ReplaceJoker(sBegin, "0");
				if (CountJoker(sEnd) > 0)
						ReplaceJoker(sEnd, "9");
		}
}
*/


/*
// ----------------------------------------------------------
// void ElemSet::ReplaceJoker(string, string)
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
void    ElemSet::ReplaceJoker(string sBorn, string s2Replace)
{
		int iPos = sBorn.find("?");
		while (iPos != NPOS)
		{
				sBorn.replace(iPos, 1, s2Replace);
				iPos = sBorn.find("?", iPos);
		}
}
*/


// ----------------------------------------------------------
// bool ElemSet::intersect(ElemSet *)
// ----------------------------------------------------------
// v�rifie qu'un �l�ment croise un autre �l�ment
// ----------------------------------------------------------
// renvoie un bool�en -- si les deux �l�ments (this et pElem)
// se croisent ou pas
// ----------------------------------------------------------
bool
ElemSet::intersect(ElemSet *pElem)
{
  if (NULL == pElem)
    return false ;

  // si pElem et this sont des ensembles vides
  if ((true == pElem->bEmptySet) && (true == this->bEmptySet))
    return true ;

  // si pElem ou this est l'ensemble vide
  if ((true == pElem->bEmptySet) || (true == this->bEmptySet))
    return false ;

  // si pElem->borneSup est dans this
  if ((pElem->sEnd >= sBegin) && (pElem->sEnd <= sEnd))
    return true ;

  // si pElem->borneInf est dans this
  if ((pElem->sBegin >= sBegin) && (pElem->sBegin <= sEnd))
    return true ;

  // si this->borneSup est dans pElem
  if ((sEnd >= pElem->sBegin) && (sEnd <= pElem->sEnd))
    return true ;

  // si this->borneInf est dans pElem
  if ((sBegin >= pElem->sBegin) && (sBegin <= pElem->sEnd))
    return true ;

  // sinon (on est dans un cas o� il n'y a pas d'intersection)
  return false ;
}

// ----------------------------------------------------------
// ElemSet *ElemSet::Smaller(ElemSet *)
// ----------------------------------------------------------
// donne le plus petit intervalle
// ----------------------------------------------------------
// renvoie un ElemSet *
// ----------------------------------------------------------
ElemSet*
ElemSet::Smaller(ElemSet* pElem)
{
try
{
  string sBorneInf = sBegin ;
  string sBorneSup = sEnd ;

  if ((NULL != pElem) && (sBegin <= pElem->sBegin))
    sBorneInf = string(pElem->sBegin) ;

  if ((NULL != pElem) && (sEnd >= pElem->sEnd))
    sBorneSup = string(pElem->sEnd) ;

  ElemSet *pResult = new ElemSet(sBorneInf, sBorneSup) ;
  return (pResult) ;
}
catch (...)
{
  erreur("Exception ElemSet::Smaller.", standardError) ;
  return NULL ;
}
}

// ----------------------------------------------------------
// vector<ElemSet *> *ElemSet::inter(vector<ElemSet *> *)
// ----------------------------------------------------------
// donne l'intersection entre un element et un domaine
// ----------------------------------------------------------
// renvoie le domaine (liste d'�l�ments)
// ----------------------------------------------------------
ElemSetArray*
ElemSet::inter(ElemSetArray *pElems)
{
try
{
	ElemSetArray* pResult = new ElemSetArray() ;
	if ((NULL == pElems) || (pElems->empty()))
		return (pResult) ;

	ElemSetArray::iterator pElemIter ;
	// calcul des intersections
	for (pElemIter = pElems->begin() ; pElems->end() != pElemIter ; pElemIter++)
	{
		if (intersect(*pElemIter))
			pResult->push_back(Smaller(*pElemIter)) ;
		else
			pResult->push_back(new ElemSet("", "", true)) ;
	}
	return (pResult) ;
}
catch (...)
{
	erreur("Exception ElemSet::inter.", standardError) ;
	return NULL;
}
}

// ----------------------------------------------------------
// void ElemSet::ComputeUnion(ElemSetArray *)
// ----------------------------------------------------------
// calcul l'union minimale entre plusieurs �l�ments
// calcul le domaine sans redondance
// ----------------------------------------------------------
// ----------------------------------------------------------
void
ElemSet::ComputeUnion(ElemSetArray *pElems)
{
try
{
	if ((NULL == pElems) || (pElems->empty()))
		return ;

  ElemSetIterator ElemIter ;
  bool            bOneEmptySet = false ;
  bool            bOneElem = false ;

  // calcul des unions entre les intersections se chevauchant
  for (ElemIter = pElems->begin() ; ElemIter != pElems->end() ; )
  {
    if (((*ElemIter) != this) && (intersect(*ElemIter)))
    {
      if ((false == (*ElemIter)->bEmptySet) && (false == this->bEmptySet))
      {
        bOneElem = true ;
        if (sBegin > (*ElemIter)->sBegin)
          sBegin = string((*ElemIter)->sBegin) ;
        if (sEnd < (*ElemIter)->sEnd)
          sEnd = string((*ElemIter)->sEnd) ;
      }
      delete *ElemIter ;
      pElems->erase(ElemIter) ;
    }
    else
    {
      if (((*ElemIter) != this) && (true == (*ElemIter)->bEmptySet))
      {
        bOneEmptySet = true ;
        delete *ElemIter ;
        pElems->erase(ElemIter) ;
      }
      else
        ElemIter++ ;
    }
  }

  if ((true == bOneEmptySet) && (false == bOneElem))
    pElems->push_back(new ElemSet("", "", true)) ;
}
catch (...)
{
  erreur("Exception ElemSet::ComputeUnion.", standardError) ;
}
}

// ----------------------------------------------------------
// constructeur
// ----------------------------------------------------------
ElemSetArray::ElemSetArray(string sDomaine)
						 :ElemSetVector()
{
  lObjectCount++ ;
}

// ----------------------------------------------------------
// ElemSetArray::~ElemSetArray()
// ----------------------------------------------------------
// ----------------------------------------------------------
// destructeur
// ----------------------------------------------------------
ElemSetArray::~ElemSetArray()
{
  lObjectCount-- ;

	vider() ;
}

ElemSetArray::ElemSetArray(const ElemSetArray& rv)
             :ElemSetVector()
{
  lObjectCount++ ;

  if (false == rv.empty())
    for (ElemSetConstIterator i = rv.begin() ; rv.end() != i ; i++)
      push_back(new ElemSet(**i)) ;
}

bool
ElemSetArray::doesContain(const string sCode) const
{
  if (empty())
    return false ;

  for (ElemSetConstIterator i = begin() ; end() != i ; i++)
    if ((*i)->doesContain(sCode))
      return true ;

  return false ;
}

// ----------------------------------------------------------
// bool ElemSetArray::isEmpty()
// ----------------------------------------------------------
// informe si l'array d'ElemSet est vide ou pas
// ----------------------------------------------------------
// renvoie un bool, si l'ensemble ne contient pas d'�l�ments
// ----------------------------------------------------------
bool
ElemSetArray::isEmpty()
{
  if (empty())
    return true ;

  for (ElemSetIterator i = begin() ; end() != i ; i++)
  {
    if (false == (*i)->isEmptySet())
      return false ;
    if (string("") != (*i)->getBegin())
      return false ;
  }
  return true ;
}

// ----------------------------------------------------------
// void ElemSetArray::vider()
// ----------------------------------------------------------
// vide l'array d'ElemSet
// ----------------------------------------------------------
// ----------------------------------------------------------
void
ElemSetArray::vider()
{
	if (empty())
		return ;

	for (ElemSetIterator i = begin() ; i != end() ; )
	{
		delete *i ;
		erase(i) ;
	}
}

// ----------------------------------------------------------
// ElemSetArray *ElemSet::minus(ElemSet *)
// ----------------------------------------------------------
// fait la soustraction de l'�l�ment pass� en parma�tre �
// l'�l�ment this
// ----------------------------------------------------------
// renvoie une liste d'�l�ments qui est le r�sultat
// ----------------------------------------------------------
ElemSetArray*
ElemSet::minus(ElemSet *pElem)
{
try
{
	ElemSetArray* pResult = new ElemSetArray() ;

	if (NULL == pElem)
		return pResult ;

	if (pElem->isEmptySet())
	{
		pResult->push_back(new ElemSet(sBegin, sEnd, bEmptySet)) ;
		return pResult ;
	}

	if (isEmptySet())
	{
		pResult->push_back(new ElemSet("", "", true)) ;
		return pResult ;
	}

	ElemSet* p2remove = Smaller(pElem) ;
	if (sBegin < p2remove->getBegin())
		pResult->push_back(new ElemSet(sBegin, p2remove->getBegin())) ;

	if (sEnd > p2remove->getEnd())
		pResult->push_back(new ElemSet(p2remove->getEnd(), sEnd)) ;

	return (pResult) ;
}
catch (...)
{
  erreur("Exception ElemSet::minus.", standardError) ;
  return NULL ;
}
}

// ----------------------------------------------------------
// ElemSetArray *ElemSetArray::ComputeIntersection(ElemSetArray *)
// ----------------------------------------------------------
// donne l'intersection entre deux domaines
// appelle ComputeUnion pour avoir un domaine sans redondance
// ----------------------------------------------------------
// renvoie le domaine (sans redondance), c'est � dire
// l'intersection entre les deux domaines
// ----------------------------------------------------------
ElemSetArray*
ElemSetArray::ComputeIntersection(ElemSetArray *pElems)
{
try
{
	ElemSetArray* pResult = new ElemSetArray() ;

	if (NULL == pElems)
		return (pResult) ;

	ElemSetArray::iterator  ElemIter ;

	if (empty() || isEmpty())
	{
		if (pElems->empty() || pElems->isEmpty())
			pResult->push_back(new ElemSet("", "", true)) ;
		else
      // pResult->insert(pResult->end(), pElems->begin(), pElems->end()) ;
      for (ElemSetIterator it = pElems->begin() ; pElems->end() != it ; it++)
        pResult->push_back(new ElemSet(**it)) ;
	}
	else
	{
		for (ElemIter = begin() ; end() != ElemIter ; ElemIter++)
		{
			ElemSetArray* pTemp = (*ElemIter)->inter(pElems) ;
      if (NULL != pTemp)
      {
        if (false == pTemp->empty())
				  // pResult->insert(pResult->end(), pTemp->begin(), pTemp->end()) ;
          for (ElemSetIterator it = pTemp->begin() ; pTemp->end() != it ; it++)
            pResult->push_back(new ElemSet(**it)) ;
            
        delete pTemp ;
      }
		}
	}
	pResult->ComputeUnion() ;
	return (pResult) ;
}
catch (...)
{
	erreur("Exception ElemSetArray::ComputeIntersection.", standardError) ;
	return NULL ;
}
}

// ----------------------------------------------------------
// void ElemSetArray::ComputeUnion()
// ----------------------------------------------------------
// calcul l'union des intersection en passant par la m�thode
// de ElemSet
// ----------------------------------------------------------
// ----------------------------------------------------------
void
ElemSetArray::ComputeUnion()
{
  if (empty())
    return ;

  ElemSetArray::iterator ElemIter ;
  for (ElemIter = begin() ; ElemIter != end() ; )
  {
    (*ElemIter)->ComputeUnion(this) ;
    if (ElemIter != end())
      ElemIter++ ;
  }
}

// ----------------------------------------------------------
// void ElemSetArray::minus(ElemSet *)
// ----------------------------------------------------------
// fait la soustraction d'un �l�ment � un ensemble d'�l�ments
// ----------------------------------------------------------
// le r�sultat est le contenu de this
// ----------------------------------------------------------
void
ElemSetArray::minus(ElemSet *pTerm)
{
try
{
	if ((NULL == pTerm) || (empty()))
		return ;

	for (ElemSetIterator ElemIter = begin() ; end() != ElemIter ; )
	{
		if (pTerm->intersect(*ElemIter))
		{
			ElemSetArray* p2add = (*ElemIter)->minus(pTerm) ;
      if (NULL != p2add)
      {
        if (false == p2add->empty())
			    // insert(end(), p2add->begin(), p2add->end()) ;
          for (ElemSetIterator it = p2add->begin() ; p2add->end() != it ; it++)
            push_back(new ElemSet(**it)) ;
        delete p2add ;
      }

			delete *ElemIter ;
			erase(ElemIter) ;
		}
		else
			ElemIter++ ;
	}
	ComputeUnion() ;
}
catch (...)
{
	erreur("Exception ElemSetArray::minus.", standardError) ;
}
}

// ----------------------------------------------------------
// void ElemSetArray::minus(ElemSetArray *)
// ----------------------------------------------------------
// fait la soustraction d'un domaine au domaine this
// ----------------------------------------------------------
// le r�sultat est contenu dans this
// ----------------------------------------------------------
void
ElemSetArray::minus(ElemSetArray *pTerms)
{
  if (empty())
    return ;

  for (ElemSetIterator ElemIter = pTerms->begin() ; ElemIter != pTerms->end() ; )
    this->minus(*ElemIter) ;

  this->ComputeUnion() ;
}

// ----------------------------------------------------------
// void ElemSetArray::print()
// ----------------------------------------------------------
// �crit un domaine dans le fichier SOAPelem.log � la racine
// de Nautilus
// ----------------------------------------------------------
// ----------------------------------------------------------
void
ElemSetArray::print(char *Message)
{
		ifstream    inFile;
		ofstream    outFile;
		string      line;
		string      sLastMessage ;

    inFile.open("SOAPelem.log");
		if (inFile)
		{
				while (!inFile.eof())
				{
						getline(inFile,line);
						if (line != "")
								sLastMessage += line + "\n";
				}
				inFile.close();
		}
		else // cas fichier vide
				sLastMessage = "";

		// On �crit le nouveau fichier reqerror.log
		outFile.open("SOAPelem.log");
	if (!outFile)
			return;

		outFile.write(sLastMessage.c_str(), strlen(sLastMessage.c_str()));
		sLastMessage = Message;
		sLastMessage += "\n";
		outFile.write(sLastMessage.c_str(), strlen(sLastMessage.c_str()));

		char    sMessage[256];
		for (ElemSetIterator ElemIter = this->begin() ; ElemIter != this->end() ; ElemIter++)
		{
				sprintf(sMessage, "sBegin : <%s> -- sEnd : <%s>\n", (*ElemIter)->getBegin().c_str(), (*ElemIter)->getEnd().c_str());
				outFile.write(sMessage, strlen(sMessage));
		}
		outFile.close();
}


// ----------------------------------------------------------
// string ElemSetArray::toString()
// ----------------------------------------------------------
// donne une string qui correspond � l'array d'ElemSet
// ----------------------------------------------------------
// renvoie la string correspondante
// ----------------------------------------------------------
string
ElemSetArray::toString()
{
  string sResult = "" ;
  if (empty())
    return sResult ;

  for (ElemSetIterator ElemIter = begin() ; end() != ElemIter ; ElemIter++)
  {
    string  sTemp = (*ElemIter)->toString() ;
    if (sTemp != "")
    {
      if (string("") != sResult)
        sResult += ";" ;
      sResult += sTemp ;
    }
  }
  return sResult ;
}

ElemSetArray&
ElemSetArray::operator=(const ElemSetArray& src)
{
  if (&src == this)
    return *this ;

  vider() ;

  if (false == src.empty())
    for (ElemSetConstIterator i = src.begin() ; src.end() != i ; i++)
      push_back(new ElemSet(**i)) ;

  return *this ;
}

// ----------------------------------------------------------
// TemsParser::TermsParser()
// ----------------------------------------------------------
// alloue les domaines Obligatoire, Possible, et Interdit
// ----------------------------------------------------------
// constructeur
// ----------------------------------------------------------
TermsParser::TermsParser(NSContexte* pCtx, string sClassif, string sChapter, bool bUse3bt)
						:NSRoot(pCtx)
{
try
{
  lObjectCount++ ;

  _sClassification = sClassif ;
  _sChapter        = sChapter ;
  _pObligatoire    = new ElemSetArray() ;
  _pPossible       = new ElemSetArray() ;
  _pInterdit       = new ElemSetArray() ;

  _bUse3bt = bUse3bt ;
}
catch (...)
{
  erreur("Exception TermsParser ctor.", standardError) ;
}
}

// ----------------------------------------------------------
// TemsParser::~TermsParser()
// ----------------------------------------------------------
// vide les domaines Obligatoire, Possible, et Interdit
// ----------------------------------------------------------
// destructeur
// ----------------------------------------------------------
TermsParser::~TermsParser()
{
  vider() ;

  _pObligatoire->vider() ;
  delete _pObligatoire ;
  _pPossible->vider() ;
  delete _pPossible ;
  _pInterdit->vider() ;
  delete _pInterdit ;

  lObjectCount-- ;
}

// ----------------------------------------------------------
// ElemSetArray *TermsParser::Compute()
// ----------------------------------------------------------
// fait les diverses op�rations pour obtenir le r�sultat de
// l'intersection de plusieurs domaines, � savoir
// 1    Union des domaines Possible
// 2    Union des domaines Interdit
// 3    Intersection des domaines Obligatoires
// 4    Intersection du r�sultat de 3 et de 1
// 5    retrait du r�sultat de 2 au r�sultat de 4
// ----------------------------------------------------------
// retourne le r�sultat de 5
// ----------------------------------------------------------
ElemSetArray*
TermsParser::Compute()
{
	ElemSetArray* pResult = ComputeWithPIntersection() ;
	if (pResult)
  {
    if (false == pResult->empty())
		  return (pResult) ;
    else
      delete pResult ;
  }
  return (ComputeWithPUnion()) ;
}

// ----------------------------------------------------------
// ElemSetArray *TermsParser::ComputeWithPUnion()
// ----------------------------------------------------------
// fait les diverses op�rations pour obtenir le r�sultat de
// l'intersection de plusieurs domaines, � savoir
// 1    Union des domaines Possible
// 2    Union des domaines Interdit
// 3    Intersection des domaines Obligatoires
// 4    Intersection du r�sultat de 3 et de 1
// 5    retrait du r�sultat de 2 au r�sultat de 4
// ----------------------------------------------------------
// retourne le r�sultat de 5
// ----------------------------------------------------------
ElemSetArray*
TermsParser::ComputeWithPUnion()
{
try
{
  ComputePUnion() ;
  ComputeIUnion() ;
  ComputeOIntersection() ;

  ElemSetArray *pResultDomain = _pObligatoire->ComputeIntersection(_pPossible) ;
  CheckI(pResultDomain) ;
  return (pResultDomain) ;
}
catch (...)
{
  erreur("Exception TermsParser::Compute 1.", standardError) ;
  return NULL ;
}
}

// ----------------------------------------------------------
// ElemSetArray *TermsParser::ComputeWithPIntersection()
// ----------------------------------------------------------
// fait les diverses op�rations pour obtenir le r�sultat de
// l'intersection de plusieurs domaines, � savoir
// 1    Intersection des domaines Obligatoires
// 2    Union des domaines Interdit
// 3    Intersection des domaines Possible
// 4    retrait du r�sultat 2 au r�sultat 3
// 5    Intersection du r�sultat de 1 et de 4
// ----------------------------------------------------------
// retourne le r�sultat de 5
// ----------------------------------------------------------
ElemSetArray*
TermsParser::ComputeWithPIntersection()
{
try
{
  ComputeOIntersection() ;
  ComputePIntersection() ;
  ComputeIUnion() ;
  CheckI(_pPossible) ;

  ElemSetArray *pResultDomain = _pObligatoire->ComputeIntersection(_pPossible) ;

  return (pResultDomain) ;
}
catch (...)
{
  erreur("Exception TermsParser::Compute 1.", standardError) ;
  return NULL ;
}
}

ElemSetArray*
TermsParser::Compute(ParseElemArray *pParseArray)
{
	ElemSetArray* pResult = ComputeWithPIntersection(pParseArray) ;
	if (pResult)
  {
    if ((false == pResult->empty()) && (false == pResult->isEmpty()))
		  return pResult ;
    delete pResult ;
  }
  return (ComputeWithPUnion()) ;
}

// ----------------------------------------------------------
// ElemSetArray *TermsParser::ComputeWithPUnion(ParseElemArray *)
// ----------------------------------------------------------
// fait les diverses op�rations pour obtenir le r�sultat de
// l'intersection de plusieurs domaines, � savoir
// 1    Union des domaines Possible
// 2    Union des domaines Interdit
// 3    Intersection des domaines Obligatoires
// 4    Intersection du r�sultat de 3 et de 1
// 5    retrait du r�sultat de 2 au r�sultat de 4
// ----------------------------------------------------------
// retourne le r�sultat de 5
// ----------------------------------------------------------
ElemSetArray*
TermsParser::ComputeWithPUnion(ParseElemArray *pParseArray)
{
try
{
  string sTrace = string("Entering ComputeWithPUnion") ;
  pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trSubSteps) ;

	if (!pParseArray || (pParseArray->empty()))
  {
    sTrace = string("Quitting ComputeWithPUnion due to empty set.") ;
    pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trSubSteps) ;
		return NULL ;
  }

  if (false == ComputeElements(pParseArray))
    return NULL ;

	ComputePUnion() ;
	ComputeIUnion() ;
	ComputeOIntersection() ;

	ElemSetArray* pResultDomain = _pObligatoire->ComputeIntersection(_pPossible) ;
	CheckI(pResultDomain) ;

  sTrace = string("Quitting ComputeWithPUnion.") ;
  pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trSubSteps) ;

	return (pResultDomain) ;
}
catch (...)
{
	erreur("Exception TermsParser::ComputeWithPUnion.", standardError) ;
	return NULL ;
}
}

// ----------------------------------------------------------
// ElemSetArray *TermsParser::ComputeWithPIntersection(ParseElemArray *)
// ----------------------------------------------------------
// fait les diverses op�rations pour obtenir le r�sultat de
// l'intersection de plusieurs domaines, � savoir
// 1    Union des domaines Possible
// 2    Union des domaines Interdit
// 3    Intersection des domaines Obligatoires
// 4    Intersection du r�sultat de 3 et de 1
// 5    retrait du r�sultat de 2 au r�sultat de 4
// ----------------------------------------------------------
// retourne le r�sultat de 5
// ----------------------------------------------------------
ElemSetArray*
TermsParser::ComputeWithPIntersection(ParseElemArray *pParseArray)
{
try
{
  string sTrace = string("Entering ComputeWithPIntersection") ;
  pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trSubSteps) ;

	if (((ParseElemArray*) NULL == pParseArray) || (pParseArray->empty()))
  {
    sTrace = string("Quitting ComputeWithPIntersection due to empty set.") ;
    pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trSubSteps) ;
		return (ElemSetArray*) 0 ;
  }

  if (false == ComputeElements(pParseArray))
    return (ElemSetArray*) 0 ;

	ElemSetArray* pResultDomain = new ElemSetArray() ;
  Compute3btIntersection() ;
	ComputeOIntersection() ;
	ComputePIntersection() ;
	ComputeIUnion() ;
	CheckI(_pPossible) ;

  //
  // If there are O and P, then don't take P into account
  //
	// Old code : if just O, they didn't appear ! : pResultDomain = pObligatoire->ComputeIntersection(pPossible) ;
  //
  if (false == _pObligatoire->empty())
    *pResultDomain = *_pObligatoire ;
  else
    *pResultDomain = *_pPossible ;

  sTrace = string("Quitting ComputeWithPIntersection.") ;
  pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trSubSteps) ;

	return (pResultDomain) ;
}
catch (...)
{
	erreur("Exception TermsParser::ComputeWithPIntersection.", standardError) ;
	return NULL ;
}
}

// ----------------------------------------------------------
// Get codes map for each sentence element
// ----------------------------------------------------------
bool
TermsParser::ComputeElements(ParseElemArray *pParseArray)
{
try
{
  if (((ParseElemArray*) NULL == pParseArray) || (pParseArray->empty()))
		return false ;

#ifndef _ENTERPRISE_DLL
  if (NULL == pContexte->getEpisodus())
    return false ;

  classifExpert* pExpert = pContexte->getEpisodus()->pClassifExpert ;
#else
  classifExpert* pExpert = pContexte->getSuperviseur()->getClassifExpert() ;
#endif
  if ((classifExpert*) NULL == pExpert)
    return false ;

  int     iSize    = pExpert->donneCodeSize(_sClassification) ;
  string  sPattern = pExpert->donnePattern(_sClassification) ;

#ifndef _ENTERPRISE_DLL
  NSThesaurus *pThesaurus = 0 ;
  //
  // If we have to use 3BT, open the table
  //
  if (_bUse3bt)
  {
    pThesaurus = new NSThesaurus(pContexte->getSuperviseur()) ;

    pThesaurus->lastError = pThesaurus->open() ;
    if (DBIERR_NONE != pThesaurus->lastError)
	  {
		  erreur("Clinical_Labels.db -- Erreur � l'ouverture du fichier Clinical_Labels.db", standardError, pThesaurus->lastError, pContexte->GetMainWindow()->GetHandle());
		  delete pThesaurus ;
      pThesaurus = 0 ;
	  }
  }
#else
  NSThesaurusInfo *pThesaurus = (NSThesaurusInfo*) 0 ;
  //
  // If we have to use 3BT, open the table
  //
  if (_bUse3bt)
    pThesaurus = new NSThesaurusInfo() ;
#endif

	for (ParseElemIter theParseSetIter = pParseArray->begin() ;
                     pParseArray->end() != theParseSetIter ; theParseSetIter++)
	{
    string sElement = (*theParseSetIter)->getContent() ;

		ParseSOAP SOAPParser(pContexte, _sClassification, _sChapter) ;
		SOAPParser.ChangeSOAPEdit(&sElement) ;

    string sTrace = string("Element: ") + sElement ;
    pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;

    // Have a look in 3BT for the element as a string
    //
    string s2Def3BT = string("") ;
    if (pThesaurus)
    {
      bool bResult = FindClinicalTerm(pThesaurus, &sElement) ;
      if (true == bResult)
      {
        s2Def3BT = pThesaurus->getClasserString(_sClassification) ;
        sTrace = string("- 3 : ") + s2Def3BT ;
        pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;
      }
    }

		if (SOAPParser.findInLexiq(sElement))
		{
			string s2DefO = string("") ;
      string s2DefP = string("") ;
      string s2DefI = string("") ;

#ifndef _ENTERPRISE_DLL
			NSEpiClasser EpiClasser(pContexte->getSuperviseur()) ;
#else
      NSEpiClasserInfo EpiClasser ;
#endif

			// � revoir
			string sCodeLexiq = SOAPParser.getCodeLexiq(sElement) ;
      string sCodeSens  = string("") ;
			pContexte->getDico()->donneCodeSens(&sCodeLexiq, &sCodeSens) ;

      sTrace = string("- Lexique code: ") + sCodeLexiq ;
      pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;

#ifndef _ENTERPRISE_DLL
			EpiClasser.donneRelations(&s2DefO, sCodeSens, _sClassification, "O") ;
      sTrace = string("- O : ") + s2DefO ;
      pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;

			EpiClasser.donneRelations(&s2DefP, sCodeSens, _sClassification, "P") ;
      sTrace = string("- P : ") + s2DefP ;
      pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;

			EpiClasser.donneRelations(&s2DefI, sCodeSens, _sClassification, "I") ;
      sTrace = string("- I : ") + s2DefI ;
      pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;
#else
			EpiClasser.donneRelations(&s2DefO, sCodeSens, _sClassification, "O", pContexte->getSuperviseur()->getDatabaseManager()) ;
      sTrace = string("- O : ") + s2DefO ;
      pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;

			EpiClasser.donneRelations(&s2DefP, sCodeSens, _sClassification, "P", pContexte->getSuperviseur()->getDatabaseManager()) ;
      sTrace = string("- P : ") + s2DefP ;
      pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;

			EpiClasser.donneRelations(&s2DefI, sCodeSens, _sClassification, "I", pContexte->getSuperviseur()->getDatabaseManager()) ;
      sTrace = string("- I : ") + s2DefI ;
      pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;
#endif

      // If this sentence element has not been found in 3BT, check if one of
      // the flechies labels for this lexique code can fit
      //
      if ((string("") == s2Def3BT) && (pThesaurus))
      {
        bool bResult = FindFlexClinicalTerm(pThesaurus, &sCodeSens) ;
        if (true == bResult)
        {
          s2Def3BT = pThesaurus->getClasserString(_sClassification) ;
          sTrace = string("- 3 for \"") + pThesaurus->getLabelFr() + string("\": ") + s2Def3BT ;
          pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;
        }
      }

			if ((string("") != s2DefO) || (string("") != s2DefP) || (string("") != s2DefI) || (string("") != s2Def3BT))
			{
				ParseCategory* pElemParser = new ParseCategory(iSize, _sClassification, sPattern);
				pElemParser->DefCritere(s2DefO, s2DefP, s2DefI, s2Def3BT) ;
				push_back(pElemParser) ;
			}
		}
    else
    {
      sTrace = string("- Not in Lexique.") ;
      pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trDetails) ;

      if (string("") != s2Def3BT)
			{
				ParseCategory* pElemParser = new ParseCategory(iSize, _sClassification, sPattern) ;
				pElemParser->DefCritere(string(""), string(""), string(""), s2Def3BT) ;
				push_back(pElemParser) ;
			}
    }
	}

  if (pThesaurus)
  {
#ifndef _ENTERPRISE_DLL
    pThesaurus->lastError = pThesaurus->close() ;
    if (DBIERR_NONE != pThesaurus->lastError)
		  erreur("Clinical_Labels.db -- erreur � la fermeture de la base.", standardError, pThesaurus->lastError, pContexte->GetMainWindow()->GetHandle()) ;
#endif
    delete pThesaurus ;
  }

  return true ;
}
catch (...)
{
	erreur("Exception TermsParser::ComputeElements.", standardError) ;
	return NULL ;
}
}

// ----------------------------------------------------------
// Finds a sentence element in 3BT
// ----------------------------------------------------------
#ifndef _ENTERPRISE_DLL

bool
TermsParser::FindClinicalTerm(NSThesaurus *pClinicalBase, string* pElement)
{
  if ((NULL == pClinicalBase) || (NULL == pElement) || (string("") == *pElement))
    return false ;

  string sLibelleReq = pseumaj(*pElement) ;
  // size_t iLibelleLen = strlen(sLibelleReq.c_str()) ;

  pClinicalBase->lastError = pClinicalBase->chercheClef(&sLibelleReq, "FrClinicalLabels", NODEFAULTINDEX, keySEARCHGEQ, dbiREADLOCK) ;

  HWND hParentForMessages = 0 ;
  if (NULL != pContexte->GetMainWindow())
    hParentForMessages = pContexte->GetMainWindow()->GetHandle() ;

  //
  // Testing DBIERR_EOF because it is what happens when searching for a "strange char" such as '�'
  //
  if ((DBIERR_NONE != pClinicalBase->lastError) && (DBIERR_RECNOTFOUND != pClinicalBase->lastError) && (DBIERR_EOF != pClinicalBase->lastError))
	{
    string sErrorTxt = string("Clinical_Labels.DB -- erreur � la recherche dans la base Clinical_Labels.DB.") ;
		erreur(sErrorTxt.c_str(), standardError, pClinicalBase->lastError, hParentForMessages) ;
		return false ;
	}

	if ((DBIERR_RECNOTFOUND == pClinicalBase->lastError) || (DBIERR_EOF == pClinicalBase->lastError))
		return false ;

	pClinicalBase->lastError = pClinicalBase->getRecord() ;
	if (DBIERR_NONE != pClinicalBase->lastError)
	{
		erreur("Clinical_Labels.DB -- erreur � la r�cup�ration del'enregistrement", standardError, pClinicalBase->lastError, hParentForMessages) ;
		return false ;
	}

  string sLabel      = pClinicalBase->getLabelFr() ;
  string sUpperLabel = pseumaj(sLabel) ;

  return (sUpperLabel == sLibelleReq) ;
}

string
TermsParser::FindAllClinicalTermsStartingWith(NSThesaurus *pClinicalBase, string* pElement, string sClassif)
{
  return string("") ;
}

string
TermsParser::FindAllSentinelTermsStartingWith(NSThesaurus *pClinicalBase, string* pElement, string sClassif)
{
  return string("") ;
}

// ----------------------------------------------------------
// Check if a flex label for this lexique code exists in 3BT
// ----------------------------------------------------------
bool
TermsParser::FindFlexClinicalTerm(NSThesaurus *pClinicalBase, string* pLexiqueCode)
{
  if ((NULL == pClinicalBase) || (NULL == pLexiqueCode) || (string("") == *pLexiqueCode))
    return false ;

  VectString aFlexLabels ;

  // First step: get all flex labels for a given lexique code
  //
  NSEpiFlechiesDB Flechies(pContexte) ;
  bool bSuccess = Flechies.getAllLabelsForCode(*pLexiqueCode, &aFlexLabels) ;

  if ((false == bSuccess) && (true == aFlexLabels.empty()))
    return false ;

  if (true == aFlexLabels.empty())
    return false ;

  // Second step: check if one of these labels exists in 3BT
  //
  for (IterString it = aFlexLabels.begin() ; aFlexLabels.end() != it; it++)
    if (true == FindClinicalTerm(pClinicalBase, *it))
      return true ;

  return false ;
}

#else

bool
TermsParser::FindClinicalTerm(NSThesaurusInfo *pClinicalBase, string* pElement)
{
  if ((NULL == pClinicalBase) || (NULL == pElement) || (string("") == *pElement))
  {
    string sTrace = string("TermsParser::FindClinicalTerm -> empty parameters.") ;
    pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trError) ;
    return false ;
  }

  string sLibelleReq = pseumaj(*pElement) ;

  // Looking for all codes that belong to given classification
  //
  string sQuery = string("SELECT * FROM clinical_labels WHERE FR_Clinical_Label = \"") + sLibelleReq + string("\"") ;

  ontologyBaseManager* pOntologyManager = pContexte->getSuperviseur()->getDatabaseManager() ;
  if (NULL == pOntologyManager)
  {
    string sTrace = string("TermsParser::FindClinicalTerm -> null ontology manager.") ;
    pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trError) ;
    return false ;
  }

  MYSQL_RES *pResult = pOntologyManager->executeQuery(sQuery, false) ;
  if ((MYSQL_RES *) NULL == pResult)
  {
    string sTrace = string("TermsParser::FindClinicalTerm -> incorrect query ") + sQuery ;
    pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trError) ;
    return false ;
  }

  MYSQL_ROW Row = mysql_fetch_row(pResult) ;
  if (Row)
    pClinicalBase->alimenteFiche(&Row) ;

  mysql_free_result(pResult) ;

  string sLabel      = pClinicalBase->getLabelFr() ;
  string sUpperLabel = pseumaj(sLabel) ;

  return (sUpperLabel == sLibelleReq) ;
}

string
TermsParser::FindAllClinicalTermsStartingWith(NSThesaurusInfo *pClinicalBase, string* pElement, string sClassif)
{
  if ((NULL == pClinicalBase) || (NULL == pElement) || (string("") == *pElement))
  {
    string sTrace = string("TermsParser::FindClinicalTerm -> empty parameters.") ;
    pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trError) ;
    return string("") ;
  }

  string sLibelleReq = pseumaj(*pElement) ;

  // Looking for all codes that belong to given classification
  //
  string sQuery = string("SELECT * FROM clinical_labels WHERE FR_Clinical_Label LIKE \"") + sLibelleReq + string("%\"") ;

  ontologyBaseManager* pOntologyManager = pContexte->getSuperviseur()->getDatabaseManager() ;
  if (NULL == pOntologyManager)
  {
    string sTrace = string("TermsParser::FindClinicalTerm -> null ontology manager.") ;
    pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trError) ;
    return string("") ;
  }

  MYSQL_RES *pResult = pOntologyManager->executeQuery(sQuery, false) ;
  if ((MYSQL_RES *) NULL == pResult)
  {
    string sTrace = string("TermsParser::FindClinicalTerm -> incorrect query ") + sQuery ;
    pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trError) ;
    return string("") ;
  }

  size_t iStartLength = strlen(sLibelleReq.c_str()) ;

  string sResult = string("") ;

  MYSQL_ROW Row = mysql_fetch_row(pResult) ;
  while (Row)
  {
    pClinicalBase->alimenteFiche(&Row) ;

    string sMajLabel = pseumaj(pClinicalBase->_Donnees._labelFr) ;

    bool bIsOk = false ;

    // Perfect fit
    //
    if (sMajLabel == sLibelleReq)
      bIsOk = true ;
    //
    // Check that we don't include 'hemoculture' when "h�mocult" is asked
    // char following start must not be a letter or a number
    //
    else
    {
      size_t iLabelLength = strlen(sMajLabel.c_str()) ;
      if (iLabelLength > iStartLength)
      {
        char nextChar = sMajLabel[iStartLength] ;

        bool bIsChar = false ;
        if ((nextChar >= 'A') && (nextChar <= 'Z'))
          bIsChar = true ;

        bool bIsNum = false ;
        if ((nextChar >= '0') && (nextChar <= '9'))
          bIsNum = true ;

        bIsOk = !bIsChar && !bIsNum ;
      }
    }

    if (bIsOk)
    {
      string s2Def3BT = pClinicalBase->getClasserString(sClassif) ;

      if (string("") != s2Def3BT)
        sResult = sBasicOnlyAddNewcodes(sResult, s2Def3BT) ;
    }

    Row = mysql_fetch_row(pResult) ;
  }

  mysql_free_result(pResult) ;

  return sResult ;
}

string
TermsParser::FindAllSentinelTermsStartingWith(NSThesaurusInfo *pClinicalBase, string* pElement, string sClassif)
{
  if ((NULL == pClinicalBase) || (NULL == pElement) || (string("") == *pElement))
  {
    string sTrace = string("TermsParser::FindAllSentinelTermsStartingWith -> empty parameters.") ;
    pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trError) ;
    return string("") ;
  }

  string sLibelleReq = pseumaj(*pElement) ;

  // Looking for all codes that belong to given classification
  //
  string sQuery = string("SELECT * FROM sentinelles WHERE FR_Clinical_Label LIKE \"") + sLibelleReq + string("%\"") ;

  ontologyBaseManager* pOntologyManager = pContexte->getSuperviseur()->getDatabaseManager() ;
  if (NULL == pOntologyManager)
  {
    string sTrace = string("TermsParser::FindAllSentinelTermsStartingWith -> null ontology manager.") ;
    pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trError) ;
    return string("") ;
  }

  MYSQL_RES *pResult = pOntologyManager->executeQuery(sQuery, false) ;
  if ((MYSQL_RES *) NULL == pResult)
  {
    string sTrace = string("TermsParser::FindAllSentinelTermsStartingWith -> incorrect query ") + sQuery ;
    pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trError) ;
    return string("") ;
  }

  string sResult = string("") ;

  MYSQL_ROW Row = mysql_fetch_row(pResult) ;
  while (Row)
  {
    pClinicalBase->alimenteFicheSentinelle(&Row) ;

    // string sTrace = string("TermsParser::FindAllSentinelTermsStartingWith, label = \"") + pClinicalBase->getLabelFr() + string("\", code = \"") + pClinicalBase->pDonnees->icpc2 + string("\"") ;
    // pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trSubDetails) ;

    string s2Def3BT = pClinicalBase->getClasserString(sClassif) ;

    if (string("") != s2Def3BT)
      sResult = sBasicOnlyAddNewcodes(sResult, s2Def3BT) ;

    Row = mysql_fetch_row(pResult) ;
  }

  mysql_free_result(pResult) ;

  return sResult ;
}

// ----------------------------------------------------------
// Check if a flex label for this lexique code exists in 3BT
// ----------------------------------------------------------
bool
TermsParser::FindFlexClinicalTerm(NSThesaurusInfo *pClinicalBase, string* pLexiqueCode)
{
  if ((NULL == pClinicalBase) || (NULL == pLexiqueCode) || (string("") == *pLexiqueCode))
    return false ;

  VectString aFlexLabels ;

  // First step: get all flex labels for a given lexique code
  //
  NSEpiFlechiesDB Flechies(pContexte) ;
  bool bSuccess = Flechies.getAllLabelsForCode(*pLexiqueCode, &aFlexLabels) ;

  if ((false == bSuccess) && (true == aFlexLabels.empty()))
    return false ;

  if (true == aFlexLabels.empty())
    return false ;

  // Second step: check if one of these labels exists in 3BT
  //
  for (IterString it = aFlexLabels.begin() ; aFlexLabels.end() != it; it++)
    if (true == FindClinicalTerm(pClinicalBase, *it))
      return true ;

  return false ;
}

#endif

string
TermsParser::sBasicOnlyAddNewcodes(string sExistingSet, string sIncomingSet)
{
  if (string("") == sExistingSet)
    return sIncomingSet ;

  if (string("") == sIncomingSet)
    return sExistingSet ;

  ClasseStringVector StringVect ;
  DecomposeChaine(&sIncomingSet, &StringVect, ";") ;
  if (StringVect.empty())
    return sExistingSet ;

  for (iterClassString it = StringVect.begin() ; it != StringVect.end() ; it++)
  {
    string sCode = (*it)->getItem() ;
    if (string::npos == sExistingSet.find(sCode))
      sExistingSet += string(";") + sCode ;
  }

  return sExistingSet ;
}

// ----------------------------------------------------------
// void TermsParser::ComputePUnion()
// ----------------------------------------------------------
// fait l'union des Possible
// ----------------------------------------------------------
// le r�sultat est stock� au niveau du pointeur pPossible de
// TermsParser
// ----------------------------------------------------------
void
TermsParser::ComputePUnion()
{
  if (false == empty())
    for (ParseCategoryIterator TermIter = begin() ; end() != TermIter ; TermIter++)
    {
      ElemSetArray* pPossibleDomain = (*TermIter)->getPossibleDomain() ;
      if (pPossibleDomain)
      {
        if (false == pPossibleDomain->isEmpty())
          // pPossible->insert( pPossible->end(),
          //                   (*TermIter)->getPossibleDomain()->begin(),
          //                   (*TermIter)->getPossibleDomain()->end()) ;
          for (ElemSetIterator it = pPossibleDomain->begin() ; pPossibleDomain->end() != it ; it++)
            _pPossible->push_back(new ElemSet(**it)) ;
      }
    }

  _pPossible->ComputeUnion() ;
}

// ----------------------------------------------------------
// void TermsParser::ComputeIUnion()
// ----------------------------------------------------------
// fait l'union des interdit
// ----------------------------------------------------------
// le r�sultat est stock� au niveau du pointeur pInterdit de
// TermsParser
// ----------------------------------------------------------
void
TermsParser::ComputeIUnion()
{
  if (false == empty())
    for (ParseCategoryIterator TermIter = begin() ; end() != TermIter ; TermIter++)
    {
      ElemSetArray* pInterditDomain = (*TermIter)->getInterditDomain() ;
      if (pInterditDomain)
      {
        if (false == pInterditDomain->isEmpty())
          // pInterdit->insert(pInterdit->end(), (*TermIter)->getInterditDomain()->begin(), (*TermIter)->getInterditDomain()->end()) ;
          for (ElemSetIterator it = pInterditDomain->begin() ; pInterditDomain->end() != it ; it++)
            _pInterdit->push_back(new ElemSet(**it)) ;
      }
    }

  _pInterdit->ComputeUnion() ;
}

// ----------------------------------------------------------
// void TermsParser::ComputeOIntersection()
// ----------------------------------------------------------
// fait l'intersection des Obligatoire
// ----------------------------------------------------------
// stocke le r�sultat au niveau du pointeur pObligatoire de
// TermsParser
// ----------------------------------------------------------
void
TermsParser::ComputeOIntersection()
{
  if (empty())
    return ;

  for (ParseCategoryIterator TermIter = begin() ; end() != TermIter ; TermIter++)
  {
    if (_pObligatoire->empty())
    {
      ElemSetArray *pElemSetArray = (*TermIter)->getObligatoireDomain() ;
      if ((false == pElemSetArray->empty()) && (false == pElemSetArray->isEmpty()))
        // pObligatoire->insert(pObligatoire->end(), pElemSetArray->begin(), pElemSetArray->end()) ;
        for (ElemSetIterator it = pElemSetArray->begin() ; pElemSetArray->end() != it ; it++)
          _pObligatoire->push_back(new ElemSet(**it)) ;
    }
    else
    {
      ElemSetArray* pResult = (*TermIter)->getObligatoireDomain()->ComputeIntersection(_pObligatoire) ;
      if (pResult)
      {
        *_pObligatoire = *pResult ;
        delete pResult ;
      }
    }
  }

  _pObligatoire->ComputeUnion() ;
}

void
TermsParser::Compute3btIntersection()
{
  if (empty())
    return ;

  for (ParseCategoryIterator TermIter = begin() ; end() != TermIter ; TermIter++)
  {
    if (_pObligatoire->empty())
    {
      ElemSetArray *pElemSetArray = (*TermIter)->get3btDomain() ;
      if ((false == pElemSetArray->empty()) && (false == pElemSetArray->isEmpty()))
        for (ElemSetIterator it = pElemSetArray->begin() ; pElemSetArray->end() != it ; it++)
          _pObligatoire->push_back(new ElemSet(**it)) ;
    }
    else
    {
      ElemSetArray* pResult = (*TermIter)->get3btDomain()->ComputeIntersection(_pObligatoire) ;
      if (NULL != pResult)
      {
        *_pObligatoire = *pResult ;
        delete pResult ;
      }
    }
  }

  _pObligatoire->ComputeUnion() ;
}

// ----------------------------------------------------------
// void TermsParser::ComputePIntersection()
// ----------------------------------------------------------
// fait l'intersection des Possible
// ----------------------------------------------------------
// stocke le r�sultat au niveau du pointeur pPossible de
// TermsParser
// ----------------------------------------------------------
void
TermsParser::ComputePIntersection()
{
  if (empty())
    return ;

  for (ParseCategoryIterator TermIter = begin() ; end() != TermIter ; TermIter++)
  {
    if (_pPossible->empty())
    {
      ElemSetArray *pElemSetArray = (*TermIter)->getPossibleDomain() ;
      if ((false == pElemSetArray->empty()) && (false == pElemSetArray->isEmpty()))
        // pPossible->insert(pPossible->end(), pElemSetArray->begin(), pElemSetArray->end()) ;
        for (ElemSetIterator it = pElemSetArray->begin() ; pElemSetArray->end() != it ; it++)
          _pPossible->push_back(new ElemSet(**it)) ;
    }
    else
      // pPossible = (*TermIter)->getPossibleDomain()->ComputeIntersection(pPossible) ;
    {
      ElemSetArray* pResult = (*TermIter)->getPossibleDomain()->ComputeIntersection(_pPossible) ;
      if (pResult)
      {
        *_pPossible = *pResult ;
        delete pResult ;
      }
    }
  }

  _pPossible->ComputeUnion() ;
}

// ----------------------------------------------------------
// void TermsParser::CheckI
// ----------------------------------------------------------
// retire du domaine pass� en param�tre le domaine des Interdit
// ----------------------------------------------------------
// modifie le domaine pass� en param�tre
// ----------------------------------------------------------
void
TermsParser::CheckI(ElemSetArray *pResult)
{
	if (empty())
		return ;

	for (ParseCategoryIterator TermIter = begin() ; end() != TermIter ; )
	{
		ElemSetArray* pIDomain = (*TermIter)->getInterditDomain() ;

		if (pIDomain->empty())
			TermIter++ ;
		else
		{
			if (pIDomain->isEmpty())
				TermIter++ ;
			else
			{
				ElemSetArray *pTemp = pIDomain->ComputeIntersection(pResult) ;

				if (pTemp->empty() || pTemp->isEmpty())
					TermIter++ ;
				else
					pResult->minus(pTemp) ;

        delete pTemp ;
			}
		}
	}
}

void
TermsParser::vider()
{
  if (empty())
    return ;

  for (ParseCategoryIterator i = begin() ; end() != i ; )
	{
		delete *i ;
		erase(i) ;
	}
}

// ----------------------------------------------------------
// NSEpiFlechiesDB::NSEpiFlechiesDB(NSContexte*)
// ----------------------------------------------------------
// constructeur
// ----------------------------------------------------------
NSEpiFlechiesDB::NSEpiFlechiesDB(NSContexte* pCtx)
								:NSRoot(pCtx)
{
try
{
#ifndef _ENTERPRISE_DLL
	_pPatho = pContexte->getDico()->donnePatholog("fr", &string("PTOTO")) ;
#else
  _pPatho = (NSPatholog*) 0 ;
#endif
	_pPhraseur = new NSPhraseur(pContexte) ;
	_pPropos   = new NsProposition(pContexte, &_pPhraseur, NsProposition::notSetType, NsProposition::notSetConjonct, false) ;
	_pGenFR    = new NSGenerateurFr(pContexte, _pPropos, "fr") ;
}
catch (...)
{
	erreur("Exception NSEpiFlechiesDB ctor.", standardError) ;
}
}

// ----------------------------------------------------------
// NSEpiFlechiesDB::~NSEpiFlechiesDB()
// ----------------------------------------------------------
// retire du domaine pass� en param�tre le domaine des Interdit
// ----------------------------------------------------------
// modifie le domaine pass� en param�tre
// ----------------------------------------------------------
NSEpiFlechiesDB::~NSEpiFlechiesDB()
{
	delete _pGenFR ;
	delete _pPropos ;
	if (_pPhraseur)
		delete _pPhraseur ;
}

#ifndef _ENTERPRISE_DLL
// ----------------------------------------------------------
// NSEpiFlechiesDB::CreateDatabaseFlechies()
// ----------------------------------------------------------
// m�thode remplissant la base flechies.db
// la m�thode utilis� est on parcourt le Lexique, et pour
// chaque terme on rajoute les champs dans la base flechies
// ----------------------------------------------------------
// remplit la base flechies.db
// ----------------------------------------------------------
void
NSEpiFlechiesDB::CreateDatabaseFlechies(bool* pbContinuer, OWL::TEdit* pAffichage)
{
try
{
	_sIdCpt = string("0000") ;
	_pPatho->lastError = _pPatho->debut(dbiREADLOCK);
	if ((_pPatho->lastError != DBIERR_NONE) && (_pPatho->lastError != DBIERR_EOF))
	{
		erreur("Erreur de positionnement.", standardError, _pPatho->lastError, pContexte->GetMainWindow()->GetHandle());
		return ;
	}

	bool bTourner = true;
	while ((DBIERR_EOF != _pPatho->lastError) && bTourner)
	{
		_pPatho->lastError = _pPatho->getRecord();
		if (DBIERR_NONE != _pPatho->lastError)
		{
			erreur("Erreur de lecture dans la base.", standardError, _pPatho->lastError, pContexte->GetMainWindow()->GetHandle());
			return ;
		}

		if (pAffichage)
			pAffichage->SetText(_pPatho->_Donnees.libelle) ;
		pContexte->getSuperviseur()->getApplication()->PumpWaitingMessages() ;

		// remplissage de la base flechies.db
		rempliDatabase(&(_pPatho->_Donnees)) ;

		// on se positionne sur le message suivant
		_pPatho->lastError = _pPatho->suivant(dbiREADLOCK);
		if ((_pPatho->lastError != DBIERR_NONE) && (_pPatho->lastError != DBIERR_EOF))
		{
			erreur("Erreur d'acc�s au message suivant.", standardError, _pPatho->lastError, pContexte->GetMainWindow()->GetHandle());
			return ;
		}
		if (pbContinuer)
			bTourner = *pbContinuer;
	}
}
catch (...)
{
	erreur("Exception NSEpiFlechiesDB::CreateDatabaseFlechies.", standardError, 0) ;
}
}

// ----------------------------------------------------------
// NSEpiFlechiesDB::rempliDatabase(NSPatholog *)
// ----------------------------------------------------------
// gr�ce au g�n�rateur FR on cr�� un libell� pour chaque flexion
// le code Lexique reste alors le m�me
// ----------------------------------------------------------
// remplit la base flechies.db terme � terme
// ----------------------------------------------------------
void
NSEpiFlechiesDB::rempliDatabase(NSPathologData *pDonnees)
{
  // on a le code (dans pDonnees), maintenant on va appeler chacun des genres pour voir si il y a
  // une flexion qui existe pour ce genre l�, si il y en a une, on la met dans la base flechies.db
  for (int genre = 0 ; genre <= 7 ; genre++)
  {
    string  sLibelle ;
    _pGenFR->donneLibelleAffiche(&sLibelle, pDonnees, genre) ;
    if (sLibelle != "")
      traiteFormeFlechie("", sLibelle, pDonnees->code) ;
  }
}
#endif  // _ENTERPRISE_DLL

bool
NSEpiFlechiesDB::traiteFormeFlechie(string sAvant, string sLibelle, string sCode, int iDep)
{
	if (sLibelle == "")
	{
		rempliDatabaseFlechies(sAvant, sCode) ;
		return true ;
	}

	size_t	iPos	= sLibelle.find('-', iDep) ;

	size_t	iTempPos = iPos ;
	int			cpt = 1 ;
	while (iTempPos != string::npos)
	{
		iTempPos = sLibelle.find('-', iTempPos + 1) ;
		cpt++ ;
	}

	if (cpt > 4)
	{
		rempliDatabaseFlechies(sLibelle, sCode) ;
		return true ;
	}

	string	sTempLibelle ;
	string	sAvantLibelle	;

	if (iPos != string::npos)
	{
		sTempLibelle	= string(sLibelle, iPos + 1, strlen(sLibelle.c_str()) - (iPos + 1)) ;
		sAvantLibelle	= string(sLibelle, 0, iPos) ;
	}
	else
	{
		sTempLibelle	= "" ;
		sAvantLibelle	= sLibelle ;
		iPos = strlen(sLibelle.c_str()) ;
	}

	if (sAvant != "")
	{
		int	iAvantLen = strlen(sAvant.c_str()) ;

		if ((sAvant[iAvantLen - 1] == ' ') && (sAvantLibelle != "") && (sAvantLibelle[0] == ' '))
		{
			traiteFormeFlechie(sAvant + '-' + sAvantLibelle, sTempLibelle, sCode) ;

			strip(sAvant, stripRight) ;
			strip(sAvantLibelle, stripLeft) ;
			traiteFormeFlechie(sAvant + ' ' + sAvantLibelle, sTempLibelle, sCode) ;
			return true ;
		}

		if ((sAvant[iAvantLen - 1] >= '0') && (sAvant[iAvantLen - 1] <= '9') &&
				(sAvantLibelle != "") && (sAvantLibelle[0] >= '0') && (sAvantLibelle[0] <= '9'))
		{
			traiteFormeFlechie(sAvant + ' ' + sAvantLibelle, sTempLibelle, sCode) ;
			traiteFormeFlechie(sAvant + '-' + sAvantLibelle, sTempLibelle, sCode) ;
			return true ;
		}

		traiteFormeFlechie(sAvant + ' ' + sAvantLibelle, sTempLibelle, sCode) ;
		traiteFormeFlechie(sAvant + '-' + sAvantLibelle, sTempLibelle, sCode) ;
		traiteFormeFlechie(sAvant + sAvantLibelle, sTempLibelle, sCode) ;
	}
	else
		traiteFormeFlechie(string(sLibelle, 0, iPos), sTempLibelle, sCode) ;

	return true ;
/*
	rempliDatabaseFlechies(sLibelle, sCode) ;

	// Traitement des '-' : on ajoute �galement une forme sans le '-' et
	// une forme o� le '-' est remplac� par un ' '
	size_t iPos = sLibelle.find('-', iDep);
	if (iPos != NPOS)
	{
		// Pour �viter l'explosion combinatoire, on ne traite pas les
		// �l�ments qui ont plus de 4 '-'
		int i       = 0;
		int thePos  = iPos;
		while (thePos != NPOS)
		{
			i++;
			thePos = sLibelle.find('-', thePos + 1);
		}
		if (i > 4)
			return true;

		string sAvant = "";
		string sApres = "";

		if (iPos > 0)
			sAvant = string(sLibelle, 0, iPos);
		if (strlen(sLibelle.c_str()) > iPos + 1)
			sApres = string(sLibelle, iPos + 1, strlen(sLibelle.c_str()) - iPos - 1);

		string sNoSpace     = sAvant + sApres;
		string sBlanckSpace = sAvant + string(1, ' ') + sApres;

		if ((sAvant != "") && (sApres != ""))
		{
			// Si le '-' s�pare deux chiffres, il ne faut pas les coller
			if ((sAvant[strlen(sAvant.c_str())-1] >= '0') &&
					(sAvant[strlen(sAvant.c_str())-1] <= '9') &&
					(sApres[0] >= '0') && (sApres[0] <= '9'))
				traiteFormeFlechie(sBlanckSpace, sCode);
			// Si le '-' s�pare deux ' ', il faut remplacer par un ' '
			else if ((sAvant[strlen(sAvant.c_str())-1] == ' ') && (sApres[0] == ' '))
			{
				strip(sAvant, stripRight);
				strip(sApres, stripLeft);
				sBlanckSpace = sAvant + string(1, ' ') + sApres;
				traiteFormeFlechie(sBlanckSpace, sCode);
			}
			else
			{
				traiteFormeFlechie(sNoSpace, sCode);
				traiteFormeFlechie(sBlanckSpace, sCode);
			}
		}
		else
		{
			traiteFormeFlechie(sLibelle, sCode, iPos+1);
			traiteFormeFlechie(sNoSpace, sCode);
		}
		traiteFormeFlechie(sBlanckSpace, sCode);
	}
*/
}

void
NSEpiFlechiesDB::incrementeIdCpt()
{
	int		iDigit	= 3 ;
	bool	tourner	= true ;

	while (tourner)
	{
		(_sIdCpt[iDigit])++ ;
		if ((_sIdCpt[iDigit] > '9') && (_sIdCpt[iDigit] < 'A'))
		{
			_sIdCpt[iDigit] = 'A' ;
			tourner = false ;
		}
		else
		{
			if (_sIdCpt[iDigit] > 'Z')
			{
				_sIdCpt[iDigit] = '0' ;
				iDigit-- ;
			}
			else
				tourner = false ;
		}
	}
}

// ----------------------------------------------------------
// string ParseSOAP::getCodeLexiq(string)
// ----------------------------------------------------------
// prend en param�tre le Libelle et informe sur le code
// Lexique correspondant au libelle
// ----------------------------------------------------------
// renvoie une string contenant le code Lexique
// ----------------------------------------------------------
string
ParseSOAP::getCodeLexiq(string sLibelle)
{
try
{
  if (string("") == sLibelle)
    return string("") ;

  string sLibelleReq = ConvertitMajuscule(sLibelle) ;

#ifndef _ENTERPRISE_DLL

  size_t iLibelleLen = strlen(sLibelleReq.c_str()) ;

  NSFlechies baseFlechies(pContexte->getSuperviseur()) ;

	baseFlechies.lastError = baseFlechies.open() ;
	if (baseFlechies.lastError != DBIERR_NONE)
	{
		erreur("flechies.db -- Erreur � l'ouverture du fichier flechies.db", standardError, baseFlechies.lastError, pContexte->GetMainWindow()->GetHandle());
		return string("") ;
	}

	baseFlechies.lastError = baseFlechies.chercheClef(&sLibelleReq, "LIBELLES", NODEFAULTINDEX, keySEARCHGEQ, dbiREADLOCK) ;

	if ((baseFlechies.lastError != DBIERR_NONE) && (baseFlechies.lastError != DBIERR_RECNOTFOUND))
	{
		erreur("flechies.db -- erreur � la recherche dans la base flechies.db.", standardError, baseFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		baseFlechies.close() ;
		return string("") ;
	}

	if (baseFlechies.lastError == DBIERR_RECNOTFOUND)
	{
		baseFlechies.lastError = baseFlechies.close() ;
		if (baseFlechies.lastError != DBIERR_NONE)
			erreur("flechies.db -- Erreur de fermeture de la base flechies.db.", standardError, baseFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		return string("") ;
	}

	baseFlechies.lastError = baseFlechies.getRecord() ;
	if (baseFlechies.lastError != DBIERR_NONE)
	{
		erreur("flechies.db -- erreur � la r�cup�ration del'enregistrement", standardError, baseFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		if (baseFlechies.lastError != DBIERR_NONE)
			erreur("flechies.db -- Erreur de fermeture de la base flechies.db.", standardError, baseFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		return string("") ;
	}

	string sLibelleTemp = ConvertitMajuscule(baseFlechies.getLabel()) ;

	baseFlechies.lastError = baseFlechies.close() ;
	if (baseFlechies.lastError != DBIERR_NONE)
		erreur("flechies.db -- Erreur de fermeture de la base flechies.db.", standardError, baseFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;

	if ((strlen(sLibelleTemp.c_str()) >= iLibelleLen) &&
      (string(sLibelleReq, 0, iLibelleLen) == sLibelleTemp))
		return baseFlechies.getCode() ;

#else

  // Looking for this label in Flechies
  //
  // Looking for all codes that belong to given classification
  //
  string sQuery = string("SELECT * FROM flechies WHERE LIBELLE = \"") + sLibelleReq + string("\"") ;

  ontologyBaseManager* pOntologyManager = pContexte->getSuperviseur()->getDatabaseManager() ;
  if (NULL == pOntologyManager)
    return string("") ;

  MYSQL_RES *pResult = pOntologyManager->executeQuery(sQuery, false) ;
  if ((MYSQL_RES *) NULL == pResult)
    return string("") ;

  MYSQL_ROW Row = mysql_fetch_row(pResult) ;
  if (Row)
  {
    NSFlechiesInfo flechiInfo ;
    flechiInfo.alimenteFiche(&Row) ;

    mysql_free_result(pResult) ;

    return flechiInfo.getCode() ;
  }

  mysql_free_result(pResult) ;

#endif

	return string("") ;
}
catch (...)
{
	erreur("Exception ParseSOAP::getCodeLexiq.", standardError) ;
	return string("") ;
}
}

// ----------------------------------------------------------
// bool NSEpiFlechiesDB::isInDB(string *)
// ----------------------------------------------------------
// informe si le terme correspondant au libelle pass� en
// param�tre est pr�sent ou pas dans le lexique
// ----------------------------------------------------------
// renvoie true si le terme est pr�sent, sinon false
// ----------------------------------------------------------
bool
NSEpiFlechiesDB::isInDB(string *sLibelle, INDBLEVEL* pLevel)
{
try
{
  if (NULL == sLibelle)
    return false ;

#ifndef _ENTERPRISE_DLL

  NSFlechies  baseFlechies(pContexte->getSuperviseur()) ;
	baseFlechies.lastError = baseFlechies.open() ;

	if (baseFlechies.lastError != DBIERR_NONE)
	{
		erreur("flechies.db -- Erreur � l'ouverture du fichier flechies.db", standardError, baseFlechies.lastError, pContexte->GetMainWindow()->GetHandle());
    if (pLevel)
    	*pLevel = INDBdatabaseError ;
		return false;
	}

  string sLibelleReq = ConvertitMajuscule(*sLibelle) ;
  size_t iLibelleLen = strlen(sLibelleReq.c_str()) ;

	baseFlechies.lastError = baseFlechies.chercheClef(&sLibelleReq, "LIBELLES", NODEFAULTINDEX, keySEARCHGEQ, dbiREADLOCK) ;
  //
  // Testing DBIERR_EOF because it is what happens when searching for a "strange char" such as '�'
  //
	if ((baseFlechies.lastError != DBIERR_NONE) && (baseFlechies.lastError != DBIERR_RECNOTFOUND) && (baseFlechies.lastError != DBIERR_EOF))
	{
		erreur("flechies.db -- erreur � la recherche dans la base flechies.db.", standardError, baseFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		baseFlechies.close() ;
		if (pLevel)
    	*pLevel = INDBdatabaseError ;
		return false ;
	}

	if ((baseFlechies.lastError == DBIERR_RECNOTFOUND) || (baseFlechies.lastError == DBIERR_EOF))
	{
		baseFlechies.lastError = baseFlechies.close() ;
		if (baseFlechies.lastError != DBIERR_NONE)
			erreur("flechies.db -- Erreur de fermeture de la base flechies.db.", standardError, baseFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
    if (pLevel)
    	*pLevel = INDBnotAtAll ;
		return false ;
	}

	baseFlechies.lastError = baseFlechies.getRecord() ;
	if (baseFlechies.lastError != DBIERR_NONE)
	{
		erreur("flechies.db -- erreur � la r�cup�ration del'enregistrement", standardError, baseFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
    if (pLevel)
    	*pLevel = INDBdatabaseError ;
		return false ;
	}

	string sLibelleTemp = ConvertitMajuscule(baseFlechies.getLabel()) ;

	baseFlechies.lastError = baseFlechies.close() ;
	if (baseFlechies.lastError != DBIERR_NONE)
		erreur("flechies.db -- Erreur de fermeture de la base flechies.db.", standardError, baseFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;

	if (sLibelleTemp == sLibelleReq)
	{
		if (pLevel)
    	*pLevel = INDBcompleteTerm ;
		return true ;
	}

	if (pLevel)
	{
  	// if sLibelleReq is the word or group of words that begins sLibelleTemp
		if ((strlen(sLibelleTemp.c_str()) > iLibelleLen) &&
        (string(sLibelleTemp, 0, iLibelleLen) == sLibelleReq) &&
        (sLibelleTemp[iLibelleLen] == ' '))
    	*pLevel = INDBasABegining ;
		else
			*pLevel = INDBnotAtAll ;
	}

#else

  // Looking for all codes that belong to given classification
  //
  string sQuery = string("SELECT * FROM flechies WHERE LIBELLE LIKE \"") + *sLibelle + string("%\"") ;

  ontologyBaseManager* pOntologyManager = pContexte->getSuperviseur()->getDatabaseManager() ;
  if (NULL == pOntologyManager)
  {
    if (pLevel)
    	*pLevel = INDBdatabaseError ;

    string sTrace = string("NSEpiFlechiesDB::isInDB -> null ontology manager.") ;
    pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trError) ;

    return false ;
  }

  string sErrorMessage = string("") ;
  MYSQL_RES *pResult = pOntologyManager->executeQuery(sQuery, false, &sErrorMessage) ;
  if ((MYSQL_RES *) NULL == pResult)
  {
    string sTrace = string("NSEpiFlechiesDB::isInDB \"") + *sLibelle + string("\" not found") ;

    if (string("") == sErrorMessage)
      pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trSubDetails) ;
    else
    {
      sTrace += string(" -> ") + sErrorMessage ;
      pContexte->getSuperviseur()->trace(&sTrace, 1, NSSuper::trError) ;
    }

    if (pLevel)
    	*pLevel = INDBdatabaseError ;
    return false ;
  }

  // Don't do that, because mysql_num_rows cannot be called after mysql_use_result()
/*

  int totalrows = mysql_num_rows(pResult) ;
  if (0 == totalrows)
  {
    if (pLevel)
    	*pLevel = INDBnotAtAll ;
    return false ;
  }
*/

  MYSQL_ROW Row = mysql_fetch_row(pResult) ;

  if (NULL == Row)
  {
    if (pLevel)
    	*pLevel = INDBnotAtAll ;
    return false ;
  }

  string sLibelleReq = ConvertitMajuscule(*sLibelle) ;

  while (Row)
  {
    NSFlechiesInfo flechiInfo ;
    flechiInfo.alimenteFiche(&Row) ;

    string sLibelleTemp = ConvertitMajuscule(flechiInfo.getLabel()) ;

    if (sLibelleReq == sLibelleTemp)
    {
      if (pLevel)
    	  *pLevel = INDBcompleteTerm ;

      mysql_free_result(pResult) ;
      return true ;
    }

    Row = mysql_fetch_row(pResult) ;
  }

  if (pLevel)
    *pLevel = INDBasABegining ;

  mysql_free_result(pResult) ;

#endif

	return false ;
}
catch (...)
{
	erreur("Exception NSEpiFlechiesDB::isInDB.", standardError) ;
	return false ;
}
}

// -----------------------------------------------------------------------------
// bool NSEpiFlechiesDB::isInDB(string *, char)
// -----------------------------------------------------------------------------
// informe si le terme correspondant au libelle pass� en param�tre est pr�sent
// ou pas dans le lexique avec un code LExique commencant par le caract�re
// fourni en deuxi�me param�tre
// -----------------------------------------------------------------------------
// renvoie true si le terme est pr�sent, sinon false
// -----------------------------------------------------------------------------
bool
NSEpiFlechiesDB::isInDB(string *sLibelle, char cTypeCode)
{
try
{
  // -------------------------------------------------------------------------
  // on ouvre la table
  // -------------------------------------------------------------------------

  NSFlechies Flechies(pContexte->getSuperviseur()) ;

#ifndef _ENTERPRISE_DLL
  Flechies.lastError = Flechies.open() ;

  if (Flechies.lastError != DBIERR_NONE)
  {
    erreur("flechies.db -- Erreur � l'ouverture du fichier flechies.db", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle());
    return false ;
  }

  // -------------------------------------------------------------------------
  // on met le libell� � rechercher en majuscule pour �vincer le probl�me des
  // lettres accentu�es
  // -------------------------------------------------------------------------

  char *pcLibelleReq = new char[strlen(sLibelle->c_str()) + 1] ;
  strcpy(pcLibelleReq, sLibelle->c_str()) ;
  ConvertitMajuscule(pcLibelleReq) ;
  string *sLibelleReq = new string(pcLibelleReq) ;
  // int					iLibelleLen			= strlen(pcLibelleReq) ;
  delete pcLibelleReq ;

  char  *pcLibelleTemp = 0 ;
  string sLibelleTemp  = "" ;

  // -------------------------------------------------------------------------
  // on ex�cute la recherche
  // -------------------------------------------------------------------------

  Flechies.lastError = Flechies.chercheClef(sLibelleReq, "LIBELLES", NODEFAULTINDEX, keySEARCHGEQ, dbiREADLOCK) ;
  if ((Flechies.lastError != DBIERR_NONE) && (Flechies.lastError != DBIERR_RECNOTFOUND))
  {
    erreur("flechies.db -- erreur � la recherche dans la base flechies.db.", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
    delete sLibelleReq ;
    Flechies.close() ;
    return false ;
  }

  if (Flechies.lastError == DBIERR_RECNOTFOUND)
  {
    Flechies.lastError = Flechies.close() ;
    if (Flechies.lastError != DBIERR_NONE)
      erreur("flechies.db -- Erreur de fermeture de la base flechies.db.", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
    delete sLibelleReq ;
    Flechies.close() ;
    return false ;
  }
  else
  {
    // -----------------------------------------------------------------------
    // si on est ici, c'est que la requ�te a trouv� au moins une occurence
    // --> on r�cup�re l'enregistrement
    // -----------------------------------------------------------------------

    Flechies.lastError = Flechies.getRecord() ;
    if (Flechies.lastError != DBIERR_NONE)
    {
      erreur("flechies.db -- erreur � la r�cup�ration del'enregistrement", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
      delete sLibelleReq ;
      Flechies.close() ;
      return false ;
    }

    pcLibelleTemp = new char[strlen(Flechies.getLabel().c_str()) + 1] ;
    strcpy(pcLibelleTemp, Flechies.getLabel().c_str()) ;
    ConvertitMajuscule(pcLibelleTemp) ;
    sLibelleTemp = string(pcLibelleTemp) ;
    delete[] pcLibelleTemp ;

    // -----------------------------------------------------------------------
    // on v�rifie que le code correspondant au chapitre de code lexique
    // recherch� (premi�re lettre du code Lexique)
    // sinon on regarde si le terme pr�c�dent correspond au libell� recherch�
    // (?? bug de la recherche dans Paradox ??)
    // -----------------------------------------------------------------------

    if ((Flechies.getCode())[0] != cTypeCode)
    {
      Flechies.lastError = Flechies.precedent(dbiREADLOCK) ;
      if (Flechies.lastError != DBIERR_NONE)
      {
        erreur("flechies.db -- erreur � la r�cup�ration del'enregistrement", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
        delete sLibelleReq ;
        Flechies.close() ;
        return false ;
      }

      Flechies.lastError = Flechies.getRecord() ;
      if (Flechies.lastError != DBIERR_NONE)
      {
        erreur("flechies.db -- erreur � la r�cup�ration del'enregistrement", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
        delete sLibelleReq ;
        Flechies.close() ;
        return false ;
      }

      pcLibelleTemp = new char[strlen(Flechies.getLabel().c_str()) + 1] ;
      strcpy(pcLibelleTemp, Flechies.getLabel().c_str()) ;
      ConvertitMajuscule(pcLibelleTemp) ;
      sLibelleTemp = string(pcLibelleTemp) ;
      delete[] pcLibelleTemp ;

      // ---------------------------------------------------------------------
      // si le libell� ne correspond pas � la requ�te on revient sur le terme
      // sur lequel on pointait lors de l'ex�cution de la recherche
      // ---------------------------------------------------------------------

      if (strcmp(sLibelleTemp.c_str(), sLibelleReq->c_str()) != 0)
      {
        Flechies.lastError = Flechies.suivant(dbiREADLOCK) ;
        if (Flechies.lastError != DBIERR_NONE)
        {
          erreur("flechies.db -- erreur � la r�cup�ration del'enregistrement", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
          delete sLibelleReq ;
          Flechies.close() ;
          return false ;
        }

        Flechies.lastError = Flechies.getRecord() ;
        if (Flechies.lastError != DBIERR_NONE)
        {
          erreur("flechies.db -- erreur � la r�cup�ration del'enregistrement", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
          delete sLibelleReq ;
          Flechies.close() ;
          return false ;
        }

        pcLibelleTemp = new char[strlen(Flechies.getLabel().c_str()) + 1] ;
        strcpy(pcLibelleTemp, Flechies.getLabel().c_str()) ;
        ConvertitMajuscule(pcLibelleTemp) ;
        sLibelleTemp = string(pcLibelleTemp) ;
        delete[] pcLibelleTemp ;
      }
    }

    // -----------------------------------------------------------------------
    // si on est pas sur un enregistrement correspondant au chapitre de code
    // lexique recherch�e on passe � l'enregistrement suivant tant que le
    // libell� correspond � la requ�te effectu�e
    // -----------------------------------------------------------------------

    while (((Flechies.getCode())[0] != cTypeCode) && (strcmp(sLibelleTemp.c_str(), sLibelleReq->c_str()) == 0))
    {
      Flechies.lastError = Flechies.suivant(dbiREADLOCK) ;
      if (Flechies.lastError != DBIERR_NONE)
      {
        erreur("flechies.db -- erreur � la r�cup�ration del'enregistrement", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
        delete sLibelleReq ;
        Flechies.close() ;
        return false ;
      }

      Flechies.lastError = Flechies.getRecord() ;
      if (Flechies.lastError != DBIERR_NONE)
      {
        erreur("flechies.db -- erreur � la r�cup�ration del'enregistrement", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
        delete sLibelleReq ;
        Flechies.close() ;
        return false ;
      }

      pcLibelleTemp = new char[strlen(Flechies.getLabel().c_str()) + 1] ;
      strcpy(pcLibelleTemp, Flechies.getLabel().c_str()) ;
      ConvertitMajuscule(pcLibelleTemp) ;
      sLibelleTemp = string(pcLibelleTemp) ;
      delete[] pcLibelleTemp ;
    }

    pcLibelleTemp	= new char[strlen(Flechies.getLabel().c_str()) + 1] ;
    string sCode = Flechies.getCode() ;
    strcpy(pcLibelleTemp, Flechies.getLabel().c_str()) ;
    ConvertitMajuscule(pcLibelleTemp) ;
    sLibelleTemp = string(pcLibelleTemp) ;
    delete[] pcLibelleTemp ;

    Flechies.lastError = Flechies.close() ;
    if (Flechies.lastError != DBIERR_NONE)
      erreur("flechies.db -- Erreur de fermeture de la base flechies.db.", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
    Flechies.close() ;

    // -----------------------------------------------------------------------
    // on v�rifie que le libell� correspond bien au libell� recherch� et si le
    // code lexique correpond bien au chapitre recherch�
    // -----------------------------------------------------------------------
    if ((strcmp(sLibelleReq->c_str(), sLibelleTemp.c_str()) == 0) && (sCode[0] == cTypeCode))
    {
      delete sLibelleReq ;
      return true ;
    }
    else
    {
      delete sLibelleReq ;
      return false ;
    }
  }
#else
  return false ;
#endif
}
catch (...)
{
  erreur("Exception NSEpiFlechiesDB::isInDB.", standardError) ;
  return false ;
}
}

string
NSEpiFlechiesDB::getCodeLexiq(string sLibelle)
{
try
{
  size_t iLibSize = strlen(sLibelle.c_str()) ;
  if ((0 == iLibSize) || (iLibSize > FLECHIES_LIBELLE_LEN))
    return string("") ;

	string		 sResult = string("") ;
	NSFlechies Flechies(pContexte->getSuperviseur()) ;

#ifndef _ENTERPRISE_DLL

  Flechies.lastError = Flechies.open() ;
	if (DBIERR_NONE != Flechies.lastError)
	{
		erreur("flechies.db -- Erreur � l'ouverture du fichier flechies.db", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		return sResult ;
	}

	string sLibelleReq = ConvertitMajuscule(sLibelle) ;

	Flechies.lastError = Flechies.chercheClef(&sLibelleReq,
                                            "LIBELLES",
                                            NODEFAULTINDEX,
                                            keySEARCHGEQ,
                                            dbiREADLOCK) ;
	if ((DBIERR_NONE != Flechies.lastError) && (DBIERR_RECNOTFOUND != Flechies.lastError))
	{
		erreur("flechies.db -- erreur � la recherche dans la base flechies.db.", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		Flechies.close() ;
		return sResult ;
	}

	if (DBIERR_RECNOTFOUND == Flechies.lastError)
	{
		Flechies.lastError = Flechies.close() ;
		if (DBIERR_NONE != Flechies.lastError)
			erreur("flechies.db -- Erreur de fermeture de la base flechies.db.", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		return sResult ;
	}
	else
	{
		Flechies.lastError = Flechies.getRecord() ;
		if (DBIERR_NONE != Flechies.lastError)
		{
			erreur("flechies.db -- erreur � la r�cup�ration de l'enregistrement", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
			Flechies.close() ;
			return sResult ;
		}

		string sLibelleTemp = Flechies.getLabel() ;
    sLibelleTemp = ConvertitMajuscule(sLibelleTemp) ;

    if (sLibelleTemp == sLibelleReq)
      sResult	= Flechies.getCode() ;

		Flechies.lastError = Flechies.close() ;
		if (DBIERR_NONE != Flechies.lastError)
			erreur("flechies.db -- Erreur de fermeture de la base flechies.db.", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;

    return sResult ;
	}

#else
  return string("") ;
#endif
}
catch (...)
{
	erreur("Exception NSEpiFlechiesDB::isInDB.", standardError) ;
	return string("") ;
}
}

/**
 *  Returns the code corresponding to label and which 1st char is specified.
 *
 * @param sLibelle label to look for in Flechies
 * @param cTypeCode code root
 *
 * @return The code if found, or ""
 *
 */
string
NSEpiFlechiesDB::getCodeLexiq(string sLibelle, char cTypeCode)
{
try
{
  size_t iLibSize = strlen(sLibelle.c_str()) ;
  if ((0 == iLibSize) || (iLibSize > FLECHIES_LIBELLE_LEN))
    return string("") ;

  string sResult = "" ;

	if ((sLibelle == string("")) || (strlen(sLibelle.c_str()) > PATHO_LIBELLE_LEN))
		return sResult ;

#ifndef _ENTERPRISE_DLL

  NSFlechies dbFlechies(pContexte->getSuperviseur()) ;

	dbFlechies.lastError = dbFlechies.open() ;
	if (dbFlechies.lastError != DBIERR_NONE)
	{
		erreur("flechies.db -- Erreur � l'ouverture du fichier flechies.db", standardError, dbFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		return sResult ;
	}

	size_t _iLibSize = strlen(sLibelle.c_str()) ;
  string sLibelleReq = "" ;

  if (_iLibSize > 1)
		sLibelleReq = ConvertitMajuscule(sLibelle) ;
	else
    sLibelleReq = sLibelle ;

	string sLibelleTemp = "" ;

	dbFlechies.lastError = dbFlechies.chercheClef(&sLibelleReq, "LIBELLES", NODEFAULTINDEX, keySEARCHGEQ, dbiREADLOCK) ;
	if ((dbFlechies.lastError != DBIERR_NONE) && (dbFlechies.lastError != DBIERR_RECNOTFOUND))
	{
		erreur("flechies.db -- erreur � la recherche dans la base flechies.db.", standardError, dbFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		dbFlechies.close() ;
		return sResult ;
	}

	if (dbFlechies.lastError == DBIERR_RECNOTFOUND)
	{
		dbFlechies.lastError = dbFlechies.close() ;
		if (dbFlechies.lastError != DBIERR_NONE)
			erreur("flechies.db -- Erreur de fermeture de la base flechies.db.", standardError, dbFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		return string("") ;
	}

	dbFlechies.lastError = dbFlechies.getRecord() ;
  if (dbFlechies.lastError != DBIERR_NONE)
	{
		erreur("flechies.db -- erreur � la r�cup�ration de l'enregistrement", standardError, dbFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		dbFlechies.close() ;
		return string("") ;
	}

	if (_iLibSize > 1)
		sLibelleTemp = ConvertitMajuscule(dbFlechies.getLabel()) ;
	else
		sLibelleTemp = dbFlechies.getLabel() ;

	if ((dbFlechies.getCode())[0] != cTypeCode)
	{
		dbFlechies.lastError = dbFlechies.precedent(dbiREADLOCK) ;
		if (dbFlechies.lastError != DBIERR_NONE)
		{
    	if (dbFlechies.lastError != DBIERR_BOF)
				erreur("flechies.db -- NSEpiFlechiesDB::getCodeLexiq(string *, char) -- erreur � la r�cup�ration de l'enregistrement", standardError, dbFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
			dbFlechies.close() ;
			return string("") ;
		}

		dbFlechies.lastError = dbFlechies.getRecord() ;
		if (dbFlechies.lastError != DBIERR_NONE)
		{
			erreur("flechies.db -- NSEpiFlechiesDB::getCodeLexiq(string *, char) -- erreur � la r�cup�ration de l'enregistrement", standardError, dbFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ; ;
			dbFlechies.close() ;
			return string("") ;
		}

		if (_iLibSize > 1)
			sLibelleTemp = ConvertitMajuscule(dbFlechies.pDonnees->getLabel()) ;
		else
			sLibelleTemp = dbFlechies.pDonnees->getLabel() ;

		if (sLibelleTemp != sLibelleReq)
		{
			dbFlechies.lastError = dbFlechies.suivant(dbiREADLOCK) ;
			if (dbFlechies.lastError != DBIERR_NONE)
			{
      	if (dbFlechies.lastError != DBIERR_EOF)
					erreur("flechies.db -- NSEpiFlechiesDB::getCodeLexiq(string *, char) -- erreur � la r�cup�ration de l'enregistrement", standardError, dbFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
				dbFlechies.close() ;
        return string("") ;
      }

      dbFlechies.lastError = dbFlechies.getRecord() ;
			if (dbFlechies.lastError != DBIERR_NONE)
			{
				erreur("flechies.db -- NSEpiFlechiesDB::getCodeLexiq(string *, char) -- erreur � la r�cup�ration de l'enregistrement", standardError, dbFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
				dbFlechies.close() ;
				return string("") ;
			}

			if (_iLibSize > 1)
				sLibelleTemp = ConvertitMajuscule(dbFlechies.pDonnees->getLabel()) ;
			else
				sLibelleTemp = dbFlechies.pDonnees->getLabel() ;
    }
  }

	while (((dbFlechies.getCode())[0] != cTypeCode) && (sLibelleTemp == sLibelleReq))
  {
		dbFlechies.lastError = dbFlechies.suivant(dbiREADLOCK) ;
		if (dbFlechies.lastError != DBIERR_NONE)
		{
			erreur("flechies.db -- NSEpiFlechiesDB::getCodeLexiq(string *, char) -- erreur � la r�cup�ration de l'enregistrement", standardError, dbFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
      dbFlechies.close() ;
      return string("") ;
    }

		dbFlechies.lastError = dbFlechies.getRecord() ;
		if (dbFlechies.lastError != DBIERR_NONE)
		{
			erreur("flechies.db -- NSEpiFlechiesDB::getCodeLexiq(string *, char) -- erreur � la r�cup�ration de l'enregistrement", standardError, dbFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
			dbFlechies.close() ;
      return string("") ;
    }

		if (_iLibSize > 1)
			sLibelleTemp = ConvertitMajuscule(dbFlechies.pDonnees->getLabel()) ;
		else
			sLibelleTemp = dbFlechies.pDonnees->getLabel() ;
	}

	if (_iLibSize > 1)
		sLibelleTemp = ConvertitMajuscule(dbFlechies.pDonnees->getLabel()) ;
	else
		sLibelleTemp = dbFlechies.pDonnees->getLabel() ;

	sResult = dbFlechies.getCode() ;

	dbFlechies.lastError = dbFlechies.close() ;
	if (dbFlechies.lastError != DBIERR_NONE)
		erreur("flechies.db -- Erreur de fermeture de la base flechies.db.", standardError, dbFlechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;

	if ((sLibelleReq == sLibelleTemp) && (sResult[0] == cTypeCode))
		return sResult ;
  else
    return string("") ;

#else

  // Looking for all codes that belong to given classification
  //
  string sQuery = string("SELECT * FROM flechies WHERE LIBELLE = \"") + sLibelle + string("\" AND LEFT(CODE, 1) = \"") + string(1, cTypeCode) + string("\"") ;

  ontologyBaseManager* pOntologyManager = pContexte->getSuperviseur()->getDatabaseManager() ;
  if (NULL == pOntologyManager)
    return string("") ;

  MYSQL_RES *pResult = pOntologyManager->executeQuery(sQuery, false) ;
  if ((MYSQL_RES *) NULL == pResult)
    return string("") ;

  MYSQL_ROW Row = mysql_fetch_row(pResult) ;
  if (Row)
  {
    NSFlechiesInfo flechiesInfo ;
    flechiesInfo.alimenteFiche(&Row) ;

    sResult = flechiesInfo.getCode() ;
  }

  mysql_free_result(pResult) ;

  return sResult ;

#endif
}
catch (...)
{
	erreur("Exception NSEpiFlechiesDB::getCodeLexiq.", standardError) ;
	return string("") ;
}
}

/**
 *  Get all labels for a given code
 *
 * @param sCode code to look labels for
 * @param pLabels pointer to a label tank
 *
 * @return true if successful
 *
 */
bool
NSEpiFlechiesDB::getAllLabelsForCode(string sCode, VectString *pLabels)
{
  if ((string("") == sCode) || (NULL == pLabels))
    return false ;

  size_t iCodeSize = strlen(sCode.c_str()) ;
  if (iCodeSize > FLECHIES_CODE_LEN)
    return false ;

  bool bExplore = true ;

#ifndef _ENTERPRISE_DLL

  NSFlechies dbFlechies(pContexte->getSuperviseur()) ;

  HWND hParentForMessages = 0 ;
  if (NULL != pContexte->GetMainWindow())
    hParentForMessages = pContexte->GetMainWindow()->GetHandle() ;

	dbFlechies.lastError = dbFlechies.open() ;
	if (DBIERR_NONE != dbFlechies.lastError)
	{
		erreur("flechies.db -- Erreur � l'ouverture du fichier flechies.db", standardError, dbFlechies.lastError, hParentForMessages) ;
		return false ;
	}

  dbFlechies.lastError = dbFlechies.chercheClef(&sCode, "CODES", NODEFAULTINDEX, keySEARCHGEQ, dbiREADLOCK) ;
	if ((DBIERR_NONE != dbFlechies.lastError) && (DBIERR_RECNOTFOUND != dbFlechies.lastError))
	{
		erreur("flechies.db -- erreur � la recherche dans la base flechies.db.", standardError, dbFlechies.lastError, hParentForMessages) ;
		dbFlechies.close() ;
		return false ;
	}

	if (DBIERR_RECNOTFOUND == dbFlechies.lastError)
	{
		dbFlechies.lastError = dbFlechies.close() ;
		if (DBIERR_NONE != dbFlechies.lastError)
			erreur("flechies.db -- Erreur de fermeture de la base flechies.db.", standardError, dbFlechies.lastError, hParentForMessages) ;
		return true ;
	}

  // Go from record to record while the code is good
  //
  while ((DBIERR_NONE == dbFlechies.lastError) && (true == bExplore))
  {
	  dbFlechies.lastError = dbFlechies.getRecord() ;
    if (dbFlechies.lastError != DBIERR_NONE)
	  {
		  erreur("flechies.db -- erreur � la r�cup�ration de l'enregistrement", standardError, dbFlechies.lastError, hParentForMessages) ;
      bExplore = false ;
		  break ;
	  }

    // Check that sRecordCode includes sCode as a begining
    //
    string sRecordCode = dbFlechies.getCode() ;
    if (strlen(sRecordCode.c_str()) < iCodeSize)
      break ;
    if (string(sRecordCode, 0, iCodeSize) != sCode)
      break ;

    pLabels->push_back(new string(dbFlechies.getLabel())) ;

    dbFlechies.lastError = dbFlechies.suivant(dbiREADLOCK) ;
    if (dbFlechies.lastError != DBIERR_NONE)
    {
      if (dbFlechies.lastError != DBIERR_EOF)
      {
        erreur("flechies.db -- erreur au passage � l'enregistrement suivant", standardError, dbFlechies.lastError, hParentForMessages) ;
        bExplore = false ;
      }
    }
  }

  dbFlechies.lastError = dbFlechies.close() ;
	if (dbFlechies.lastError != DBIERR_NONE)
		erreur("flechies.db -- Erreur de fermeture de la base flechies.db.", standardError, dbFlechies.lastError, hParentForMessages) ;

#else

  // Looking for all codes that belong to given classification
  //
  string sQuery = string("SELECT * FROM flechies WHERE CODE = \"") + sCode + string("\"") ;

  ontologyBaseManager* pOntologyManager = pContexte->getSuperviseur()->getDatabaseManager() ;
  if (NULL == pOntologyManager)
    return false ;

  MYSQL_RES *pResult = pOntologyManager->executeQuery(sQuery, false) ;
  if ((MYSQL_RES *) NULL == pResult)
    return false ;

  MYSQL_ROW Row = mysql_fetch_row(pResult) ;
  while (Row)
  {
    NSFlechiesInfo flechiesInfo ;
    flechiesInfo.alimenteFiche(&Row) ;

    pLabels->push_back(new string(flechiesInfo.getLabel())) ;

    Row = mysql_fetch_row(pResult) ;
  }

  mysql_free_result(pResult) ;

#endif

  return bExplore ;
}

// ----------------------------------------------------------
// void NSEpiFlechiesDB::ConvertitMajuscule(char *)
// ----------------------------------------------------------
// convertit une chaine en majuscule
// ----------------------------------------------------------
// ----------------------------------------------------------
void
NSEpiFlechiesDB::ConvertitMajuscule(char* chaine)
{
  for (size_t i = 0 ; i < strlen(chaine); i++)
  {
    switch (chaine[i])
    {
      case '�' ://200
      case '�' :
      case '�' :
      case '�' :
			case '�' :
      case '�' :
      case '�' :
      case '�' : chaine[i] =  'E' ;
                 break;
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' : //197
      case '�' :
      case '�' : //226
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' : chaine[i] =  'A' ;
                 break;
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' : chaine[i] =  'I' ;
                 break;
      case '�' ://220
      case '�' :
      case '�' :
      case '�' : //216
      case '�' :
      case '�' :
      case '�' :
      case '�' : chaine[i] =  'U' ;
                 break;
      case '�' : //213
      case '�' :
      case '�' :
      case '�' :
      case '�' :
      case '�' : //242
      case '�' :
      case '�' :
      case '�' :
      case '�' : chaine[i] = 'O' ;
                 break;
      case '�' :
      case '�' : chaine[i] = 'N' ; //209
                 break;
      case '�' :
      case '�' : chaine[i] = 'Y' ; //209
                 break;
      case '�' :
      case '�' : chaine[i] = 'C' ; //209
                 break;
      case '�' : chaine[i] = 'D' ; //209
                 break;
#ifdef __linux__
      default  : chaine[i] = toupper(chaine[i]) ;
#endif
    }
  }
#ifndef __linux__
  chaine = strupr(chaine) ;
#endif
}

string
NSEpiFlechiesDB::ConvertitMajuscule(string sChaine)
{
	char* pcChaine = new char[strlen(sChaine.c_str()) + 1] ;
	strcpy(pcChaine, sChaine.c_str()) ;

  ConvertitMajuscule(pcChaine) ;

  string sMajChaine = string(pcChaine) ;
  delete[] pcChaine ;

  return sMajChaine ;
}

// ----------------------------------------------------------
// NSEpiFlechiesDB::findElem(string, string)
// ----------------------------------------------------------
// recherche un �l�ment dans la base "flechies.db"
// attention !!! on utilise une grosse bidouille, comme on
// remplit la base petit � petit code par code, c'est � dire
// qu'on remplit la base � partir des codes Lexique pris dans
// l'ordre, on ne retombe pas sur un autre code Lexique
// identique ce qu'on fait pour eviter les doublons c'est de
// regarder les derniers �l�ments (� partir de la fin de la
// base), jusqu'� ce que le code ne soit plus le m�me, si un
// terme a le m�me code et le m�me libell� on l'aura trouv�
// attention !!! ne marche que si la base est vide et qu'on
// rajoute les champs dans l'ordre des codes du Lexique
// Nautilus
// ----------------------------------------------------------
// remplit la base flechies.db
// ----------------------------------------------------------
bool
NSEpiFlechiesDB::findElem(string sLibelle, string sCode)
{
try
{
  // apr�s maintes tentatives, je rempli la base sans faire de chercheClef ou chercheCLefComposite
  // le probl�me �tant en utilisant chercheClefComposite, impossibilit� de rajouter un enregistrement
  // dans la base --> erreur Index is read only
  // le probl�me �tant en utilisant chercheClef, qu'il fallait reconstruire l'index � chaque fois qu'on
  // rajoutait un enregistrement
  // la solution qui a �t� adopt�e (m�me si elle propre � ce cas pr�cis), c'est de rajouter les enregistrements
  // les uns apr�s les autres en regardant dans les derniers enregistrements qui ont le m�me code lexique
  // s'ils n'ont pas de libelle identiques -- cette technique marche parce qu'on ajoute les enregistrements
  // code lexique par code lexique

  NSFlechies Flechies(pContexte->getSuperviseur()) ;

#ifndef _ENTERPRISE_DLL
  Flechies.lastError = Flechies.open() ;
  if (Flechies.lastError != DBIERR_NONE)
  {
    erreur("flechies.db -- Erreur � l'ouverture du fichier flechies.db", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
		return false ;
  }
  Flechies.lastError = Flechies.fin(dbiREADLOCK) ;

  // Fichier vide
  if (Flechies.lastError == DBIERR_BOF)
  {
    Flechies.close() ;
		return false ;
  }

  // Erreur anormale
  if (Flechies.lastError != DBIERR_NONE)
	{
		erreur("flechies.db -- Erreur de positionnement dans la base flechies.db.", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle());
		Flechies.close() ;
		return false ;
	}

  Flechies.getRecord() ;
  while (Flechies.getCode() == sCode)
  {
    if (Flechies.pDonnees->getLabel() == sLibelle)
    {
      Flechies.close() ;
      return true ;
    }
    Flechies.precedent(dbiREADLOCK) ;
    Flechies.getRecord() ;

    if (Flechies.lastError != DBIERR_NONE)
    {
      erreur("flechies.db -- Erreur de positionnement dans la base flechies.db.", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
      Flechies.close() ;
      return false ;
    }
  }

  Flechies.close() ;
#endif
  return false ;
}
catch (...)
{
	erreur("Exception NSEpiFlechiesDB::findElem.", standardError) ;
	return false ;
}
}

// ----------------------------------------------------------
// bool NSEpiFlechiesDB::rempliDatabseFlechies(string, string)
// ----------------------------------------------------------
// � partir du libelle et du code Lexique ins�re un �l�ment
// dans la base Flechies
// ----------------------------------------------------------
// renvoie si le terme a �t� ins�r� ou pas dans la base
// ----------------------------------------------------------
bool
NSEpiFlechiesDB::rempliDatabaseFlechies(string sLibelle, string sCode)
{
try
{
#ifndef _ENTERPRISE_DLL
  if (!findElem(sLibelle, sCode))
  {
    incrementeIdCpt() ;
    NSFlechies Flechies(pContexte->getSuperviseur()) ;
    Flechies.lastError = Flechies.open() ;
    if (Flechies.lastError != DBIERR_NONE)
    {
      erreur("flechies.db -- Erreur � l'ouverture du fichier flechies.db", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;
      return false ;
    }

    Flechies.pDonnees->setId(_sIdCpt) ;
    Flechies.pDonnees->setLabel(sLibelle) ;
    Flechies.pDonnees->setCode(sCode) ;

    // on l'ins�re dans la base Messages
    Flechies.lastError = Flechies.appendRecord() ;
    if (Flechies.lastError != DBIERR_NONE)
    {
      erreur("flechies.db -- Erreur � l'insertion du message dans la base flechies.db.", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle());
      Flechies.close() ;
      return false ;
    }

    Flechies.lastError = Flechies.close() ;
    if (Flechies.lastError != DBIERR_NONE)
      erreur("flechies.db -- Erreur de fermeture de la base flechies.db.", standardError, Flechies.lastError, pContexte->GetMainWindow()->GetHandle()) ;

    return true ;
  }
#endif
  return false ;
}
catch (...)
{
		erreur("Exception NSEpiFlechiesDB::rempliDatabaseFlechies.", standardError) ;
		return false;
}
}

// ----------------------------------------------------------
//                     ParseElem
// ----------------------------------------------------------

ParseElem::ParseElem(string sElem)
{
  lObjectCount++ ;

  _sContent    = sElem ;
  _bNotInFirst = false ;
  _nbOfTerms   = 1 ;
  _iPos        = 0 ;
}

ParseElem::ParseElem(string sElem, int nbTerms, int Pos)
{
  lObjectCount++ ;

  _sContent    = sElem ;
  _bNotInFirst = false ;
  _nbOfTerms   = nbTerms ;
  _iPos        = Pos ;
}

ParseElem::ParseElem(const ParseElem& rv)
{
  lObjectCount++ ;

	_bNotInFirst = rv._bNotInFirst ;
	_sContent    = rv._sContent ;
	_nbOfTerms   = rv._nbOfTerms ;
	_iPos        = rv._iPos ;
}

ParseElem&
ParseElem::operator=(const ParseElem& src)
{
  if (&src == this)
    return *this ;

	_bNotInFirst = src._bNotInFirst ;
	_sContent    = src._sContent ;
	_nbOfTerms   = src._nbOfTerms ;
	_iPos        = src._iPos ;

	return *this ;
}

// ----------------------------------------------------------
// ParseElemArray::ParseElemArray(vector<string *> *)
// ----------------------------------------------------------
// � partir d'une liste de string, ins�re les �l�ments qui
// correspondent dans le ParseElemArray
// ----------------------------------------------------------
// constructeur
// ----------------------------------------------------------
ParseElemArray::ParseElemArray(vector<string*> *pList)
{
  lObjectCount++ ;

try
{
	if (((vector<string*>*) NULL == pList) || (pList->empty()))
		return ;

	for (vector<string*>::iterator pIter = pList->begin() ;
                                  pList->end() != pIter ; pIter++)
		push_back(new ParseElem(**pIter)) ;

	setAllPos() ;
}
catch (...)
{
	erreur("Exception ParseElemArray ctor.", standardError) ;
}
}

ParseElemArray::ParseElemArray(const ParseElemArray& rv)
{
  lObjectCount++ ;

	if (false == rv.empty())
		for (ParseElemConstIter pIter = rv.begin() ; rv.end() != pIter ; pIter++)
			push_back(new ParseElem(**pIter)) ;
}

void
ParseElemArray::setAllPos()
{
	if (empty())
		return ;

	int iPos = 1 ;
	for (ParseElemIter pIter = begin() ; end() != pIter ; pIter++, iPos++)
		(*pIter)->setPos(iPos) ;
}

// ----------------------------------------------------------
// ParseElemArray::~ParseElemArray()
// ----------------------------------------------------------
// vide la liste
// ----------------------------------------------------------
// destructeur
// ----------------------------------------------------------
ParseElemArray::~ParseElemArray()
{
	vider() ;

  lObjectCount-- ;
}

// ----------------------------------------------------------
// void ParseElemArray::vider()
// ----------------------------------------------------------
// vide la liste
// ----------------------------------------------------------
// ----------------------------------------------------------
void    ParseElemArray::vider()
{
	if (empty())
		return ;

	for (ParseElemIter i = begin() ; end() != i ; )
	{
		delete *i ;
		erase(i) ;
	}
}

ParseElemArray&
ParseElemArray::operator=(const ParseElemArray &src)
{
  if (&src == this)
    return *this ;

	vider() ;

	if (false == src.empty())
		for (ParseElemConstIter pIter = src.begin() ; src.end() != pIter ; pIter++)
			push_back(new ParseElem(**pIter)) ;

	return *this ;
}

// ----------------------------------------------------------
// NSEpiClassifDB::NSEpiClassifDB(NSContexte *)
// ----------------------------------------------------------
// alloue les ensembles correspondant au diff�rents chapitres
// et au diff�rents termes g�n�riques
// ----------------------------------------------------------
// constructeur
// ----------------------------------------------------------
NSEpiClassifDB::NSEpiClassifDB(NSContexte *pCtx)
							 :NSRoot(pCtx)
{
try
{
  _pChap    = new ClassifElemArray ;
  _pLibelle = new ClassifElemArray ;
}
catch (...)
{
  erreur("Exception NSEpiClassifDB ctor.", standardError) ;
}
}

// ----------------------------------------------------------
// NSEpiFlechiesDB::~NSEpiFlechiesDB()
// ----------------------------------------------------------
// vide les ensembles
// ----------------------------------------------------------
// destructeur
// ----------------------------------------------------------
NSEpiClassifDB::~NSEpiClassifDB()
{
  // il faudrait aussi les vider
  _pChap->vider() ;
  delete _pChap ;
  _pLibelle->vider() ;
  delete _pLibelle ;
}

// ----------------------------------------------------------
// void NSEpiClassifDB::rempliClassifCISP(string)
// ----------------------------------------------------------
// rempli les �l�ments CISP de la base Classif � partir du nom
// de fichier o� sont stock�es les donn�es
// ----------------------------------------------------------
// ----------------------------------------------------------
void
NSEpiClassifDB::rempliClassifCISP(string sFileCISP)
{
try
{
  ifstream    inFile ;
  string      sSepar = string("\t") ;
  string      sCode ;
  string      sLibelle ;
  string      line_string ;

#ifndef _ENTERPRISE_DLL
  NSEpiClassif Classif(pContexte->getSuperviseur()) ;

  // ouverture de la base
  Classif.lastError = Classif.open() ;
  if (Classif.lastError != DBIERR_NONE)
  {
    erreur("classif.db -- Erreur � l'ouverture du fichier.", standardError, Classif.lastError, pContexte->GetMainWindow()->GetHandle()) ;
    return ;
  }

  // ouverture du fichier
  inFile.open(sFileCISP.c_str()) ;
  if (!inFile.is_open())
  {
//        erreur("erreur � l'ouverture du fichier") ;
    return ;
  }

  // parcours du fichier
  while (getline(inFile, line_string))
  {
    if (string("") != line_string)
    {
      // recherche du s�parateur
      size_t separPos = line_string.find(sSepar);
      if ((separPos != NPOS) && (separPos != 0) && (separPos != strlen(line_string.c_str())))
      {
        // d�finition du code et du libell�
        sCode    = string(line_string, 0, separPos) ;
        sLibelle = string(line_string, separPos + 1, (strlen(line_string.c_str()) - (separPos + 1))) ;

        // si c'est un titre de chapitre on le rajoute dans l'array des chapitres
        if (strlen(sCode.c_str()) == 1)
          _pChap->push_back(new ClassifElem(sCode, sLibelle)) ;

        if (strlen(sCode.c_str()) == 3)
        {
          // si c'est un code g�n�rique, on le rajoute dans l'array des codes g�n�riques
          if (sCode.find("-") == 0)
            _pLibelle->push_back(new ClassifElem(sCode, sLibelle)) ;
          else
          {
            // on remplit l'enregistrement
            Classif.setClassification("6CISP") ;
            Classif.setCode(sCode) ;
            Classif.setLabel(sLibelle) ;

            // r�cup�ration du chapitre correspondant � partir du code
            char sChap[5] ;
            sprintf(sChap, "%c", (Classif.getCode())[0]) ;
            Classif.setChapter(sChap) ;

            // on ins�re l'enregistrement
            Classif.lastError = Classif.appendRecord() ;
            if (Classif.lastError != DBIERR_NONE)
            {
              erreur("classif.db -- Erreur � l'insertion de l'enregistrement dans la base.", standardError, Classif.lastError, pContexte->GetMainWindow()->GetHandle()) ;
              Classif.close() ;
              return ;
            }
          }
        }
      }
    }
  }

  // parcours de l'array des chapitres et des codes g�n�riques pour cr�er les codes propres � chaque chapitre
  for (ClassifElemIter ChapIter = _pChap->begin() ; _pChap->end() != ChapIter ; ChapIter++)
  {
    for (ClassifElemIter ProcIter = _pLibelle->begin() ; _pLibelle->end() != ProcIter ; ProcIter++)
    {
      Classif.setClassification("6CISP") ;

      sCode = (*ChapIter)->getCode() + (*ProcIter)->getCode() ;
      Classif.setCode(sCode) ;

      sLibelle = (*ProcIter)->getLibelle() + " (" + (*ChapIter)->getLibelle() + ")" ;
      Classif.setLabel(sLibelle) ;

      Classif.setChapter((*ChapIter)->getCode()) ;

      Classif.lastError = Classif.appendRecord() ;
      if (Classif.lastError != DBIERR_NONE)
      {
        erreur("classif.db -- Erreur � l'insertion de l'enregistrement dans la base.", standardError, Classif.lastError, pContexte->GetMainWindow()->GetHandle()) ;
        Classif.close() ;
        return ;
      }
    }
  }

  Classif.lastError = Classif.close() ;
  if (Classif.lastError != DBIERR_NONE)
    erreur("classif.db -- erreur de fermeture de la base", standardError, Classif.lastError, pContexte->GetMainWindow()->GetHandle()) ;

  inFile.close() ;
#endif
}
catch (...)
{
	erreur("Exception NSEpiClassifDB::rempliClassifCISP.", standardError) ;
}
}

void
NSEpiClassifDB::rempliClassifCIM(string sFileCIM)
{
try
{
  ifstream inFile ;
  string   sSepar = string("\t") ;
  string   sCode ;
  string   sLibelle ;
  string   line_string ;

#ifndef _ENTERPRISE_DLL
  NSEpiClassif Classif(pContexte->getSuperviseur()) ;

  // ouverture de la base
  Classif.lastError = Classif.open() ;
  if (Classif.lastError != DBIERR_NONE)
  {
    erreur("classif.db -- Erreur � l'ouverture du fichier.", standardError, Classif.lastError, pContexte->GetMainWindow()->GetHandle()) ;
    return ;
  }

  // ouverture du fichier
  inFile.open(sFileCIM.c_str()) ;
  if (!inFile.is_open())
  {
    erreur("erreur � l'ouverture du fichier", standardError, 0) ;
    return ;
  }

  // parcours du fichier
  while (getline(inFile, line_string))
  {
    if (line_string != "")
    {
      // recherche du s�parateur
      size_t separPos = line_string.find(sSepar) ;
      if ((separPos != NPOS) && (separPos != 0) && (separPos != strlen(line_string.c_str())))
      {
        // d�finition du code et du libell�
        sCode    = string(line_string, 0, separPos) ;
        sLibelle = string(line_string, separPos + 1, (strlen(line_string.c_str()) - (separPos + 1))) ;

        // validation/modification du code

        // Le code doit avoir au moins 3 digits A-Z 0-9 0-9
        if (strlen(sCode.c_str()) > 2)
        {
          if (((sCode[0] >= 'A') && (sCode[0] <= 'Z')) &&
              ((sCode[1] >= '0') && (sCode[1] <= '9')) &&
              ((sCode[2] >= '0') && (sCode[2] <= '9')))
          {
            // Si le code a plus de 3 char, le quatri�me doit �tre
            // un point (suivi d'un 0-9) ou un 0-9 qu'on d�cale
            if (strlen(sCode.c_str()) > 3)
            {
              if (sCode[3] != '.')
                sCode = string(sCode, 0, 3) + string(".")
                               + string(sCode, 3, strlen(sCode.c_str())-3) ;

              if (sCode[3] == '.')
              {
                if (strlen(sCode.c_str()) == 4)
                  sCode = "" ;
                else if ((sCode[4] < '0') || (sCode[4] > '9'))
                  sCode = "" ;
              }
            }
          }
          else
            sCode = "" ;
        }
        else
          sCode = "" ;

        if ((sCode != "") && (sLibelle != ""))
        {
          // on remplit l'enregistrement
          Classif.setClassification("6CIMA") ;
          Classif.setCode(sCode) ;
          Classif.setLabel(sLibelle) ;

          // r�cup�ration du chapitre correspondant � partir du code
          string sChap = "";
          char cCode = sCode[0];
          switch (cCode)
          {
            case 'A' : sChap = "1"; break;
            case 'B' : sChap = "1"; break;
            case 'C' : sChap = "2"; break;
            case 'D' :
              if (strlen(sCode.c_str()) > 1)
              {
                if (sCode[1] < '5')
                  sChap = "2" ;
                else
                  sChap = "3" ;
              }
              break ;
            case 'E' : sChap = "4"; break;
            case 'F' : sChap = "5"; break;
            case 'G' : sChap = "6"; break;
            case 'H' :
              if (strlen(sCode.c_str()) > 1)
              {
                if (sCode[1] < '6')
                  sChap = "7" ;
                else
                  sChap = "8" ;
              }
              break ;
            case 'I' : sChap = "9"; break;
            case 'J' : sChap = "A"; break;
            case 'K' : sChap = "B"; break;
            case 'L' : sChap = "C"; break;
            case 'M' : sChap = "D"; break;
            case 'N' : sChap = "E"; break;
            case 'O' : sChap = "F"; break;
            case 'P' : sChap = "G"; break;
            case 'Q' : sChap = "H"; break;
            case 'R' : sChap = "I1"; break;
            case 'S' :
            case 'T' :
            case 'U' : sChap = "I2"; break;
            case 'V' :
            case 'W' :
            case 'X' :
            case 'Y' : sChap = "I3"; break;
            case 'Z' : sChap = "J"; break;
          }
          Classif.setChapter(sChap) ;

          // on ins�re l'enregistrement
          Classif.lastError = Classif.appendRecord() ;
          if (Classif.lastError != DBIERR_NONE)
          {
            erreur("classif.db -- Erreur � l'insertion de l'enregistrement dans la base.", standardError, Classif.lastError, pContexte->GetMainWindow()->GetHandle()) ;
            Classif.close() ;
            return ;
          }
        }
      }
    }
  }

  Classif.lastError = Classif.close() ;
  if (Classif.lastError != DBIERR_NONE)
    erreur("classif.db -- erreur de fermeture de la base", standardError, Classif.lastError, pContexte->GetMainWindow()->GetHandle()) ;

  inFile.close() ;
#endif
}
catch (...)
{
	erreur("Exception NSEpiClassifDB::rempliClassifCIM.", standardError) ;
}
}

// ----------------------------------------------------------------------------
//                                ClassifElem
// ----------------------------------------------------------------------------

ClassifElem::ClassifElem(string s2Code, string s2Libelle)
{
  lObjectCount++ ;

  _sCode    = s2Code ;
  _sLibelle = s2Libelle ;
}

ClassifElem::ClassifElem(const ClassifElem& rv)
{
  lObjectCount++ ;

  _sCode    = rv._sCode ;
  _sLibelle = rv._sLibelle ;
}

ClassifElem&
ClassifElem::operator=(const ClassifElem& src)
{
  if (&src == this)
    return *this ;

  _sCode    = src._sCode ;
  _sLibelle = src._sLibelle ;

  return *this ;
}

// ----------------------------------------------------------
// string ClassifElem::getCode()
// ----------------------------------------------------------
// renvoie le code correspondant � un ClassifElem
// ----------------------------------------------------------
// renvoie une string
// ----------------------------------------------------------
string
ClassifElem::getCode()
{
  if (_sCode.find("-") != NPOS)
  {
    string sResult = _sCode.substr(1, 2) ;
    return sResult ;
  }

  return _sCode ;
}


// ----------------------------------------------------------
// void ClassifElemArray::vider()
// ----------------------------------------------------------
// vide l'array
// ----------------------------------------------------------
// ----------------------------------------------------------
void
ClassifElemArray::vider()
{
  if (empty())
    return ;

  for (ClassifElemIter i = begin() ; end() != i ; )
  {
    delete *i ;
    erase(i) ;
  }
}


// ----------------------------------------------------------
// ClassifElemAray::~ClassifElemArray()
// ----------------------------------------------------------
// ----------------------------------------------------------
// destructeur
// ----------------------------------------------------------
ClassifElemArray::~ClassifElemArray()
{
  vider() ;

  lObjectCount-- ;
}

// ----------------------------------------------------------
// void NSEpiClassifDB::searchDomainInClassif(string, ElemSetArray *, NSEpiClassifInfoArray *)
// ----------------------------------------------------------
// � partir de la classification, d'un domaine, renvoie l'array
// des NSEpiClassifInfo correspondante par le troisi�me param�tre
// ----------------------------------------------------------
// ----------------------------------------------------------
void
NSEpiClassifDB::searchDomainInClassif(string sClassification, ElemSetArray *pDomain, NSEpiClassifInfoArray *pArrayClassif)
{
try
{
  if ((NULL == pDomain) || pDomain->empty())
    return ;

//      cette m�thode doit, � partir d'un domaine, ajouter � l'array pArrayClassif (s'ils n'y sont pas d�j�)
//      les NSEpiClassifInfo des codes contenus dans le pDomain, en v�rifiant qu'ils existent dans classif.db
//      d'o� array de NSepiClassifInfo
#ifndef _ENTERPRISE_DLL
  NSEpiClassif Classif(pContexte->getSuperviseur()) ;
  Classif.lastError = Classif.open() ;
  if (Classif.lastError != DBIERR_NONE)
  {
    erreur("classif.db -- Erreur � l'ouverture du fichier.", standardError, Classif.lastError, pContexte->GetMainWindow()->GetHandle()) ;
    return ;
  }

  for (ElemSetIterator DomainIter = pDomain->begin() ; DomainIter != pDomain->end() ; DomainIter++)
  {
    if (false == (*DomainIter)->isEmptySet())
    {
      string sBornInf = (*DomainIter)->getBegin() ;
      string sBornSup = (*DomainIter)->getEnd() ;

      // d�finition de la cl� de recherche
      string cle = sClassification + sBornInf ;

      // recherche dans la base
      Classif.lastError = Classif.chercheClef(&cle, "", NODEFAULTINDEX, keySEARCHGEQ, dbiREADLOCK) ;
      if ((Classif.lastError != DBIERR_NONE) && (Classif.lastError != DBIERR_RECNOTFOUND))
      {
        erreur("classif.db -- erreur � la recherche dans la base.", standardError, Classif.lastError, pContexte->GetMainWindow()->GetHandle()) ;
        Classif.close() ;
        return ;
      }

      // r�cup�ration de l'enregistrement
      Classif.lastError = Classif.getRecord() ;
      if (Classif.lastError != DBIERR_NONE)
      {
        erreur("classif.db -- erreur de lecture dans la base.", standardError, Classif.lastError, pContexte->GetMainWindow()->GetHandle()) ;
        Classif.close() ;
        return ;
      }

      // on continue jusqu'� ce qu'on soit strictement sup�rieur � la borne sup�rieure de l'�l�ment
      while (sBornSup >= Classif.getCode())
      {
        NSEpiClassifInfo *pNewElem = new NSEpiClassifInfo(&Classif) ;
        bool bElemAlreadyPresent = false ;

        // on v�rifie si l'�l�ment est pas d�j� pr�sent dans l'array que l'on renvoie
        for (NSEpiClassifInfoIter ClassifInfoIter = pArrayClassif->begin() ; ClassifInfoIter != pArrayClassif->end() ; ClassifInfoIter++)
        {
          if (pNewElem == (*ClassifInfoIter))
            bElemAlreadyPresent = true ;
        }

        // si l'�l�ment n'est pas d�j� pr�sent dans l'array on le rajoute
        if (bElemAlreadyPresent == false)
          pArrayClassif->push_back(pNewElem) ;
        else
          delete pNewElem ;

        // on passe � l'enregistrement suivant
        Classif.lastError = Classif.suivant(dbiREADLOCK) ;
        if (Classif.lastError != DBIERR_NONE)
        {
          erreur("classif.db -- erreur d'acc�s au message suivant.", standardError, Classif.lastError, pContexte->GetMainWindow()->GetHandle()) ;
          Classif.close() ;
          return ;
        }

        // r�cup�ration de l'enregistrement suivant
        Classif.lastError = Classif.getRecord() ;
        if (Classif.lastError != DBIERR_NONE)
        {
          erreur("classif.db -- erreur de lecture dans la base.", standardError, Classif.lastError, pContexte->GetMainWindow()->GetHandle()) ;
          Classif.close() ;
          return ;
        }
      }
    }
  }

  // on ferme la base
  Classif.lastError = Classif.close() ;
  if (Classif.lastError != DBIERR_NONE)
    erreur("classif.db -- erreur � la fermeture de la base.", standardError, Classif.lastError, pContexte->GetMainWindow()->GetHandle()) ;
#endif
}
catch (...)
{
	erreur("Exception NSEpiClassifDB::searchDomainInClassif.", standardError) ;
}
}

bool
NSEpiClassifDB::searchCode(string sClassification, string sCode, NSEpiClassifInfo *pClassifInfo)
{
try
{
  if ((NULL == pClassifInfo) || (string("") == sClassification) || (string("") == sCode))
    return false ;
#ifndef _ENTERPRISE_DLL
  NSEpiClassif Classif(pContexte->getSuperviseur()) ;
  Classif.lastError = Classif.open() ;
  if (Classif.lastError != DBIERR_NONE)
  {
    erreur("classif.db -- Erreur � l'ouverture du fichier.", standardError, Classif.lastError, pContexte->GetMainWindow()->GetHandle()) ;
    return false ;
  }

  CURProps curProps ;
  /* DBIResult lastError = */ DbiGetCursorProps(Classif.PrendCurseur(), curProps) ;
  Byte* pIndexRec = new Byte[curProps.iRecBufSize] ;
  memset(pIndexRec, 0, curProps.iRecBufSize) ;
  DbiPutField(Classif.PrendCurseur(), CLASSIF_CLASSIF_FIELD, pIndexRec, (Byte*) sClassification.c_str()) ;
  DbiPutField(Classif.PrendCurseur(), CLASSIF_CODE_FIELD,    pIndexRec, (Byte*) sCode.c_str()) ;

  Classif.lastError = Classif.chercheClefComposite("",
                                                   0,
                                                   keySEARCHEQ,
                                                   dbiWRITELOCK,
                                                   pIndexRec) ;
  delete[] pIndexRec ;

  if (DBIERR_NONE != Classif.lastError)
  {
    Classif.close() ;
    return false ;
  }

  Classif.lastError = Classif.getRecord() ;
  if (DBIERR_NONE != Classif.lastError)
  {
  	erreur("Erreur � la lecture d'une fiche Classif.", standardError, Classif.lastError) ;
    Classif.close() ;
    return false ;
  }

  *pClassifInfo = Classif ;

  // on ferme la base
  Classif.lastError = Classif.close() ;
  if (Classif.lastError != DBIERR_NONE)
    erreur("classif.db -- erreur � la fermeture de la base.", standardError, Classif.lastError, pContexte->GetMainWindow()->GetHandle()) ;
#endif
  return true ;
}
catch (...)
{
	erreur("Exception NSEpiClassifDB::searchDomainInClassif.", standardError) ;
  return false ;
}
}

