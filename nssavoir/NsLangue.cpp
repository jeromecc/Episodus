//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#ifdef _INCLUS
  #include "partage\Nsglobal.h"
  #include "nsbb\nsutidlg.h"
#endif

#include "nautilus\nssuper.h"
#include "nssavoir\nslangue.h"

//***************************************************************************
// Impl�mentation des m�thodes NSLanguesData
//***************************************************************************

//---------------------------------------------------------------------------
//  Constructeur.
//---------------------------------------------------------------------------
NSLanguesData::NSLanguesData()
{
  memset(code,    0, LANGUES_CODE_LEN + 1) ;
	memset(libelle, 0, LANGUES_LIBEL_LEN + 1) ;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
NSLanguesData::NSLanguesData(const NSLanguesData& rv)
{
	strcpy(code,    rv.code) ;
	strcpy(libelle, rv.libelle) ;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
NSLanguesData::~NSLanguesData()
{
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
NSLanguesData&
NSLanguesData::operator=(const NSLanguesData& src)
{
  if (this == &src)
    return *this ;

	strcpy(code,    src.code) ;
	strcpy(libelle, src.libelle) ;

	return *this ;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int
NSLanguesData::operator == ( const NSLanguesData& o )
{
  if ((strcmp(code,    o.code)    == 0) &&
      (strcmp(libelle, o.libelle) == 0))
		return 1 ;

  return 0 ;
}

//***************************************************************************
//***************************************************************************

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
NSLangues::NSLangues(NSSuper* pSuper) : NSFiche(pSuper)
{
  pDonnees = new NSLanguesData() ;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
NSLangues::NSLangues(const NSLangues& rv) : NSFiche(rv._pSuper)
{
	//
	// Cr�e l'objet de donn�es
	//
	pDonnees = new NSLanguesData();
	//
	// Copie les valeurs du NSEncycloInfo d'origine
	//
	*pDonnees = *(rv.pDonnees);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
NSLangues::~NSLangues()
{
  delete pDonnees ;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void
NSLangues::alimenteFiche()
{
  alimenteChamp(pDonnees->code,    LANGUES_CODE_FIELD,  LANGUES_CODE_LEN) ;
  alimenteChamp(pDonnees->libelle, LANGUES_LIBEL_FIELD, LANGUES_LIBEL_LEN) ;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void
NSLangues::videFiche()
{
    videChamp(pDonnees->code,    LANGUES_CODE_FIELD,  LANGUES_CODE_LEN);
    videChamp(pDonnees->libelle, LANGUES_LIBEL_FIELD, LANGUES_LIBEL_LEN);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
DBIResult
NSLangues::open()
{
	char tableName[] = "LANGUES.DB" ;
	//
	// Appelle la fonction open() de la classe de base pour ouvrir
	// l'index primaire
	//
	lastError = NSFiche::open(tableName, NSF_PARTAGE_GLOBAL) ;
	return(lastError) ;
}

//---------------------------------------------------------------------------
//  Op�rateur d'affectation
//---------------------------------------------------------------------------
NSLangues&
NSLangues::operator=(const NSLangues& src)
{
  if (this == &src)
    return *this ;

  *pDonnees = *(src.pDonnees) ;

	return *this ;
}

//---------------------------------------------------------------------------
//  Op�rateur de comparaison
//---------------------------------------------------------------------------
int
NSLangues::operator==(const NSLangues& o)
{
  return (*pDonnees == *(o.pDonnees)) ;

//***************************************************************************
//***************************************************************************

//---------------------------------------------------------------------------
//  Constructeur par d�faut
//---------------------------------------------------------------------------
NSLanguesInfo::NSLanguesInfo()
{
  pDonnees = new NSLanguesData() ;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
NSLanguesInfo::NSLanguesInfo(const NSLangues* pLangue)
{
	//
	// Cr�e l'objet de donn�es
	//
	pDonnees = new NSLanguesData() ;
	//
	// Copie les valeurs du NSLangues
	//
	*pDonnees = *(pLangue->pDonnees) ;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
NSLanguesInfo::NSLanguesInfo(const NSLanguesInfo& rv)
{
	//
	// Cr�e l'objet de donn�es
	//
	pDonnees = new NSLanguesData() ;
	//
	// Copie les valeurs du NSEncycloInfo d'origine
	//
	*pDonnees = *(rv.pDonnees) ;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
NSLanguesInfo::~NSLanguesInfo()
{
  delete pDonnees ;
}

//---------------------------------------------------------------------------
//  Op�rateur d'affectation
//---------------------------------------------------------------------------
NSLanguesInfo&
NSLanguesInfo::operator=(const NSLanguesInfo& src)
{
  if (this == &src)
    return *this ;

	*pDonnees = *(src.pDonnees) ;

	return *this ;
}

//---------------------------------------------------------------------------
//  Op�rateur de comparaison
//---------------------------------------------------------------------------
int
NSLanguesInfo::operator==(const NSLanguesInfo& o)
{
  return (*pDonnees == *(o.pDonnees)) ;
}
