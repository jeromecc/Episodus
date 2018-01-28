#ifndef __IMP_GE_H
#define __IMP_GE_H

bool _export importer(NSContexte* pCtx);

static  TModule *pResMod;
        TModule *pNSResModule;

int     donneInt(FILE* inFile);
bool    erreur(FILE* inFile);

class NSXLLabel
{
    public:

        string sBalise;
        string sLabel;

        NSXLLabel(string sAttr, string sText);
        NSXLLabel(const NSXLLabel& rv);
        ~NSXLLabel();

        NSXLLabel& operator=(const NSXLLabel& src);
};

// d�finition d'un array de mod�les
typedef vector<NSXLLabel*> XLLabArray;
typedef XLLabArray::iterator XLLabelIter;

class XLLabelsArray : public XLLabArray
{
    public:

        // Constructeurs - Destructeur
        XLLabelsArray() : XLLabArray() {}
        XLLabelsArray(XLLabelsArray& rv);
        ~XLLabelsArray();

        bool trouveValeur(string* sVal, string* sUnit, string sCherche, string sDate = "");

        void    vider();
	    XLLabelsArray& operator=(XLLabelsArray src);
};
 /******************************************************************************************************/

class  NSFichier_Xls_DLG : public TDialog
{
    public:

        OWL::TListBox*  pFichierXls;
        string*         psFichier;

        NSFichier_Xls_DLG(TWindow* pere, NSContexte* pCtx, string* psFile, TModule* module = 0);
   	    ~NSFichier_Xls_DLG();

        void CmOk();
        void CmCancel();
        void SetupWindow();

    DECLARE_RESPONSE_TABLE(NSFichier_Xls_DLG);
};

#endif
/**************************************************************/
bool verifBalise(FILE* inFile, int car);
string donneChamp(FILE* inFile, int n);
int donneTaille(string taille, int type);
