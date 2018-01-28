#if !defined(__HTML2WORD_H)

#include <owl\docmanag.h>
#include <owl\docview.h>
#include <owl\mdichild.h>
#include <owl\decframe.h>
#include <owl\statusba.h>
#include <owl\controlb.h>
#include <owl\buttonga.h>
#include <owl\applicat.h>
#include <owl\richedit.h>
#include <owl\richedpr.h>
#include <owl\choosefo.h>
#include <richedit.h>

#include "nautilus\nsdocref.h"
#include "nautilus\richedap.h"
#include "nsbb\nsednum.h"

//#define MAXCARS 100000      // Limite du texte pour RichEdit
// #if defined(_DANSTXTDLL)
// #else
// #define _NSTTXCLASS __import
// #endif

// Constantes
//const int UnChk    = TCommandEnabler::Unchecked;
//const int Chk	   = TCommandEnabler::Checked;

#define _NSTTXCLASS _USERCLASS
class NSTtxDocumentExp;        // classe g�n�rique de documents texte nautilus
class TAutoWordFormEx;        // classe "Form" permettant de faire une vue - dialogue

// Vue pour les documents Word : windowview - dialogue d'automation
{
	public :

		NSUtilDialog*       pDialog;        // on garde un dialogue comme toolbox
		TWordBasicProxy*    pControl;
		wchar_t             wcWindowName[255];
		NSTtxDocumentExp*   pDocTtx;

		NSAutoWordViewExp(NSTtxDocumentExp& doc, TWindow *parent = 0);

		// fonction virtuelles de TView
		const char*   GetViewName() { return StaticName(); }
		TWindow*      GetWindow()   { return (TWindow*) this; }

		void PerformCreate(int menuOrId) ;
		void SetupWindow() ;
		void EvClose() ;
		bool CanClose() ;
		void FillStartupInfo(LPSTARTUPINFO psi) ;

		void CmLancer() ;

	protected:
		bool IsTabKeyMessage(MSG &msg);
		bool PreProcessMsg(MSG &msg);

	private:
		TAutoWordFormEx* Form;
	DECLARE_RESPONSE_TABLE(NSAutoWordViewExp);

class NSTtxDocumentExp : public TDocument, public NSRoot
{
	public:

		NSTtxDocumentExp(TDocument *parent = 0, NSContexte *pCtx = 0) ;

		void   SetNomFichier(string sFich)     { _sNomFichier     = sFich ; }

		// M�thodes virtuelles de TDocument
		bool Close() ;

		bool IsOpen() ;

#endif		// __HTML2WORD_H