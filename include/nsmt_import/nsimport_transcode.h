//---------------------------------------------------------------------------
#ifndef __NSIMPORT_TRANSCODE_H
#define __NSIMPORT_TRANSCODE_H

#include "nsmt_version\nsv_person.h"
#include "nsmt_version\nsv_docum.h"
#include "nssavoir\nspatbas.h"
#include "nssavoir\nstransa.h"
#include "nssavoir\nsgraphe.h"
#include "nsbb\nspatpat.h"
#include "ns_sgbd\nschemin.h"

//
// Taille des champs du fichier TRANSCODE
//
#define TRI_TYPE_LEN  		   3
#define TRI_OLDCODE_LEN    100#define TRI_NEWCODE_LEN	    13
#define TRI_FLAG_LEN		     1

//
// Ordre des champs du fichier TRANSCODE
//
#define TRI_TYPE_FIELD       1
#define TRI_OLDCODE_FIELD    2
#define TRI_NEWCODE_FIELD    3
#define TRI_FLAG_FIELD       4

//---------------------------------------------------------------------------
//  Classe NSVTranscode
//---------------------------------------------------------------------------

//
// Objet donn�es
//
class NSITranscodeData
{
	public :

		//
    // Variables de stockage des valeurs
    //
    char type[TRI_TYPE_LEN + 1] ;
    char old_code[TRI_OLDCODE_LEN + 1] ;
    char new_code[TRI_NEWCODE_LEN + 1] ;
    char flag[TRI_FLAG_LEN + 1] ;

		NSITranscodeData() { metAZero() ; }
		NSITranscodeData(const NSITranscodeData& rv) ;

		NSITranscodeData& operator=(const NSITranscodeData& src) ;
		int 		          operator==(const NSITranscodeData& o) ;

		void metAZero() ;
};

//
// Objet d�riv� de NSFiche utilis� pour les op�rations de base de donn�es
//
class NSITranscode : public NSFiche
{
	public :

		//
    // Variables de stockage des valeurs
    //
    NSITranscodeData* pDonnees ;

    NSITranscode(NSSuper* pSuper) ;
    NSITranscode(NSSuper* pSuper, hDBICur hCurSrc) ; // Constructeur curseur clon�
    ~NSITranscode() ;

    void  alimenteFiche() ;
    void  videFiche() ;
    DBIResult open() ;
} ;

#endif  // #ifndef __NSIMPORT_TRANSCODE_H

