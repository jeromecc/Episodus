#include "nsbb\nsutidlg.h"

//
// Objet "Boite de dialogue" utilis� pour choisir la table � importer
//
class _NSOUTILCLASSE NsCocciDialog : public NSUtilDialog
{
    public:

        TCheckBox*	pChkPat;
        TCheckBox*	pChkCor;

		NsCocciDialog(TWindow* pere, NSContexte* pCtx);

		void SetupWindow();

        void lanceCvtPat();
        void lanceCvtCor();

    DECLARE_RESPONSE_TABLE(NsCocciDialog);
