#ifndef __NSDOCHIS_H

#include "partage\ns_vector.h"
#include "nsdn\nsdocum.h"

// #include "nsdn\nsdocnoy.h"
// #include "nsbb\nspatpat.h"

//document + sa patpatho

class NSDocumentHisto : public NSDocumentInfo
	public:

		// pointeur pDocNoy de stockage des documents (ne pas faire de new)
		NSPatPathoArray* pPatPathoArray ;
		char             dateDoc[DOC_CREATION_LEN + 1] ;

		//constructeurs  Destructeur
		NSDocumentHisto(NSDocumentInfo* pNSDocument, bool bNoDocnoy /* fictif : pour distinguer les ctors */) ;
		NSDocumentHisto(NSDocumentInfo* pNSDocumentInfo, NSNoyauDocument* pDoc = 0) ;
		~NSDocumentHisto() ;

		//copie
    NSDocumentHisto& operator=(NSDocumentHisto src) ;

		// Surcharges des op�rateurs

		char* GetDateDoc() ;
    void 	ResetDateDoc() ;

    bool  checkPptConsistency() ;
};

//
//

typedef vector<NSDocumentHisto*> NSDocumentHistoArray ;
//Reverse_iter on  NSDocumentHistoArray
class NSDocHistoArray : public NSDocumentHistoArray
public :

	// Constructeurs
	NSDocHistoArray(NSDocHistoArray& rv) ;

	// Destructeur
  void vider() ;

	DocumentIter TrouveDocHisto(const string codeDocBrut) ;

DocumentIter
NSDocHistoArray::TrouveDocHisto(const string codeDocBrut)
{
	if (true == empty())
		return NULL ;

	DocumentIter iterNode = begin() ;
	for (; iterNode != end(); iterNode++)
	{
		string codeDoc = (*iterNode)->getID() ;
		string codeDocMeta = (*iterNode)->sCodeDocMeta ;
		if ((codeDocBrut == codeDoc) || (codeDocBrut == codeDocMeta))
			return iterNode ;
	}
	return end() ;
}

#endif