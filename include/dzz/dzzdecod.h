#ifndef __DZZDECOD_H

class NSDocumentData ;
#include "dcodeur\nsdkd.h"
//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
class decodage : public decodageBase
{
  public:
    // Donn�es statiques
    static string _sExamen ;   // Type d'examen
    static int    _iCompteur ; // Compteur (ex : pour num�roter les precriptions)

    static int             _iNiveau ;
    static NSDocumentData* _pDocument ;

    enum DECODENIVEAU { iTitre = 0, iChapitre, iSsChapitre, iTexte, iConclusion } ;

    // M�thodes
    //
    decodage(NSContexte* pCtx)    : decodageBase(pCtx) {}
    decodage(decodageBase* pBase) : decodageBase(pBase) {}
    decodage(const decodage& rv)  : decodageBase(rv.pContexte) {} ;
    virtual ~decodage() {}

    void BioLibre(int colonne, string decDeb = string(""), string decFin = string(""), int sautLigne = 0) ;
    void lesionVide(string phrase, int colonne)  ;
    void debutPhrase() { setDcodeur(string("")) ; }
    void finPhrase()   { setDcodeur(string("")) ; }
    // Debrou

    void entete(gereDate* pDateExam);

//-----------------------------------------------------------------
//
// Assure le d�codage du ventricule gauche
//-----------------------------------------------------------------
class decGeneral : public decodage
{
  public:

    // Constructeur
    ~decGeneral() {}

    // Lancement du d�codage

    void versi(int colonne) ;

#endif  // __DZZDECOD_H