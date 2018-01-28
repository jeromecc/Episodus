// NSTTX.CPP		Document/Vues Traitement de texte
// R�mi SPAAK - Mai 1997

#define __NS_TTX_CPP
#include "AutoWordExp.h"

#include <owl\owlpch.h>
#include <owl\validate.h>
#include <owl\inputdia.h>
#include <fstream.h>

#include "nautilus\nssuper.h"
#include "export\html2word.h"


//
//					METHODES DE NSAutoWordViewExp
//
/******************************************************************************/

DEFINE_RESPONSE_TABLE1(NSAutoWordViewExp, TWindowView)
    EV_COMMAND(CM_FILECLOSE, EvClose),

    // Evenements g�r�s par la classe VCL AutoWord
    // EV_COMMAND(IDC_AW_ARCHIVER, CmArchiver),
    // EV_COMMAND(IDC_AW_VISUALISER, CmVisualiser),
    // EV_COMMAND(IDC_AW_EDITER, CmEditer),
    // EV_COMMAND(IDC_AW_COMPOSER, CmComposer),
    // EV_COMMAND(IDC_AW_FORMULES, CmFormules),
    // EV_COMMAND(IDC_AW_QUITTER, CmQuitter),

END_RESPONSE_TABLE;
// Attention il faut passer doc comme NSTtxDocument avec un contexte valide
				   :TWindowView(doc, parent), pDocTtx(&doc)
{
	Form     = 0 ;
	pControl = 0 ;
	pDialog  = 0 ;
}

NSAutoWordViewExp::~NSAutoWordViewExp()
	delete Form ;

	if (pDialog)
}

void
{
	// on cr�e la Form pour servir de zone client (on lui passe le handle parent)
	Form = new TAutoWordFormEx(Parent->GetHandle(), this) ;
	Form->Visible = false ;
	Form->ParentWindow = Parent->HWindow ;
	SetHandle(Form->Handle) ;

	::SetParent(Forms::Application->Handle, pDocTtx->pContexte->GetMainWindow()->HWindow) ;
	SetDocTitle(pDocTtx->GetTitle(),0) ;
}

// Fonction MakeVisible
NSAutoWordViewExp::MakeVisible()
{
	Form->Show() ;
	Form->Visible = true ;
}

void
{
	int X = 0, Y = 0;
	int W = Form->Width, H = Form->Height;

	TWindowView::SetupWindow();
	// La vue sera la fenetre client de la TMDIChild cr��e dans TMyApp::EvNewView

	Parent->SetWindowPos(0, X, Y, W, H, SWP_NOZORDER);

	bSessionEnCours = false;
	CmLancer();

void
{
	// fonction appel�e sur Fichier->Fermer
	CloseWindow() ;
}

bool
{
try
{
	// on place ici le code qui v�rifie si le document est bien sauvegard�
	// et la vue est ferm�e sans autre forme de proc�s...

	if ((pControl) && (pControl->IsBound()))
		pControl->Unbind() ;
		// CoUninitialize() ;
		delete pControl ;
		pControl = 0 ;
	}

	bool bOk = TWindowView::CanClose() ;
	// ici, bizarrement, apr�s un FileSaveAs, TWindowView::CanClose renvoie false
	return true ;
}
  string sExept = string("Nautilus a perdu le contr�le de Word dans la fonction de fermeture. ") +
                  string("Pour fermer Word, vous devez utiliser <Quitter> dans la fenetre <Document Word> de Nautilus.");
  erreur(sExept.c_str(), standardError, 0) ;
  return true ;
}
{
  erreur("Exception NSAutoWordViewExp::CanClose.", standardError, 0) ;
  return true ;
}
}
bool
{
	if (GetCapture() == NULL)
	{
		if (msg.message == WM_KEYDOWN || msg.message == WM_KEYUP)
		{
			if (msg.wParam == VK_TAB)
			{
				SendMessage(CN_BASE + msg.message, msg.wParam, msg.lParam);
				return true;
			}
		}
	}

	return false;

//
// this method, you can't tab between control on the form.
//
bool
NSAutoWordViewExp::PreProcessMsg(MSG &msg)
{
	bool result = IsTabKeyMessage(msg) ;

	if (!result)

	return result ;

void
{
    psi->cb = sizeof (*psi);
    psi->lpReserved = NULL;
    psi->lpDesktop = NULL;
    psi->lpTitle = NULL;
    psi->dwX = 0;
    psi->dwY = 0;
    psi->dwXSize = 0;
    psi->dwYSize = 0;
    psi->dwXCountChars = 0;
    psi->dwYCountChars = 0;
    psi->dwFillAttribute = 0;
    psi->dwFlags = STARTF_USESHOWWINDOW;
    psi->wShowWindow = SW_SHOWNORMAL;
    psi->cbReserved2 = 0;
    psi->lpReserved2 = NULL;
    psi->hStdInput = NULL;
    psi->hStdOutput = NULL;
    psi->hStdError = NULL;
}

void
{
    /************************** pour le hook ***************************
    // pour rendre le process fils et son primary thread h�ritables

    STARTUPINFO startupInfo;
    PROCESS_INFORMATION procInfo;
    DWORD lRet;
    char cmdline[255], pathname[255], command[255];
    SECURITY_ATTRIBUTES saProc, saThread;

    saProc.nLength = sizeof(saProc);
    saProc.bInheritHandle = true;

    saThread.nLength = sizeof(saThread);
    saThread.lpSecurityDescriptor = NULL;
    saThread.bInheritHandle = true;

    //////////////////////////////////////////////////////////////////////////////
    // Lancement de Word.Basic
    //////////////////////////////////////////////////////////////////////////////
    strcpy(pathname, "C:\\program files\\microsoft office\\office\\");
    strcpy(command, "winword.exe");

    // lRet = ExecuteCommand(pathname, command);
    sprintf(cmdline, "%s%s", pathname, command);
    FillStartupInfo(&startupInfo);

    if (!CreateProcess(NULL, cmdline, &saProc, &saThread, true, NORMAL_PRIORITY_CLASS,
                        NULL, pathname, &startupInfo, &procInfo))
    {
        MessageBox("Erreur sur CreateProcess");
        return;
    }

    // Attente de la fin de l'initialisation du process
    lRet = WaitForInputIdle(procInfo.hProcess, INFINITE);
    if (lRet != 0)
    {
        MessageBox("Erreur sur WaitForInputIdle");
        return;
    }
    *******************************************************************************/

	//CoInitialize(NULL);
	pControl = new TWordBasicProxy();

	try
	{
		pControl->Bind("Word.Basic");
	}
	catch (...)
	{
		MessageBox("Erreur Bind Word.Basic");
		//CoUninitialize();
		return;
	}

    CmEditer();
}

void
NSAutoWordViewExp::CmEditer()
{
try
{
	wchar_t wcFileName[255];
	if ((!pControl) || (!(pControl->IsBound())))
	// car il faudrait rajouter un hook pour d�tecter la fermeture
	// on se contente d'intercepter les exceptions XOLE
	if (bSessionEnCours)

	swprintf(wcFileName, L"%S", pDocTtx->GetNomFichier().c_str()) ;
	TAutoString asFileName(wcFileName) ;
	pControl->FileOpen(asFileName) ;
	// on affiche le titre du document
	SetDocTitle(pDocTtx->GetTitle(), 0) ;
}
catch (const TXOle& e)
{
  string sExept = string("Nautilus a perdu le contr�le de Word dans la fonction d'�dition. ") +
                  string("Pour fermer Word, vous devez utiliser <Quitter> dans la fenetre <Document Word> de Nautilus.");
  erreur(sExept.c_str(), standardError, 0) ;
}
catch (...)
{
  erreur("Exception NSAutoWordViewExp::CmEditer.", standardError, 0) ;
}
}
bool
{
try
{
	if (strlen(sWordName.c_str()) > 254)
	{
		string sMessage = string("HTMLtoWORD, nom de fichier trop long : ") + sWordName ;
		MessageBox(sMessage.c_str()) ;
		return false ;
	}

	short format ;
	wchar_t wcFormatName[255] ;
	wchar_t wcFileName[255] ;

	if (!bSessionEnCours)
		string sMessage = string("Vous devez avoir un fichier ouvert dans Word avant de pouvoir l'archiver dans ") + pDocTtx->pContexte->getSuperviseur()->getAppName() ;
		MessageBox(sMessage.c_str()) ;
		return false ;
	}

	// on sauvegarde en html sous la bonne localisation

	TAutoString asFormatName(wcFormatName) ;
	format = pControl->ConverterLookup(asFormatName) ;

	// sprintf(msg, "Format HTML = <%hd>", format);

    string sFileName = pDocTtx->pContexte->PathName("EHTM") + sWordName;
	swprintf(wcFileName, L"%S", sFileName.c_str()) ;
	TAutoString asFileName(wcFileName) ;

    pControl->FileClose(1);
    pControl->AppClose();
    CloseWindow() ;

    bSessionEnCours = false ;
  return true ;
}
catch (const TXOle& e)
{
  string sExept = string("Nautilus a perdu le contr�le de Word dans la fonction d'archivage. ") +
                  string("Pour fermer Word, vous devez utiliser <Quitter> dans la fenetre <Document Word> de Nautilus.") ;
  erreur(sExept.c_str(), standardError, 0) ;
  return false ;
}
catch (...)
{
  erreur("Exception NSAutoWordViewExp::saveHTMLtoWORD", standardError, 0) ;
  return false ;
}
}
/******************************************************************************/
/******************************************************************************/

// Constructeur NSTtxDocument

NSTtxDocumentExp::NSTtxDocumentExp(TDocument *parent, NSContexte *pCtx)
{
	// Mise � vide du nom de fichier
	SetNomFichier("") ;
	SetFichierExterne("") ;
	Open(0, "") ;
}

string NSTtxDocumentExp::GetDocExt()
	size_t i ;
	string sExt = string("") ;

  size_t iFileNameLen = strlen(_sNomFichier.c_str()) ;

	for (i = 0 ; (i < iFileNameLen) && ('.' != _sNomFichier[i]) ; i++) ;

	if (i < iFileNameLen)
	{
		// nomDoc[i] == '.'
		i++ ;
		while (i < iFileNameLen)
			sExt += _sNomFichier[i++] ;
	}

	return sExt ;
}

// Ouverture du document

bool NSTtxDocumentExp::Open(int /*mode*/, LPCSTR path)
	string sNomFichier = string("") ;

	// Si il existe, prise du nom de fichier de la fiche document

	// Sinon, on sort
	//	return false;

	//
	//
	SetNomFichier(sNomFichier) ;
	SetDirty(false) ;
	return true ;
}

// Fermeture du document
bool NSTtxDocumentExp::Close()
{
  // if (TDocument::Close())
  // 	 return false;

  SetNomFichier(string("")) ;
  return true ;
}

// Indique si document ouvert (il existe un fichier associ�)
bool NSTtxDocumentExp::IsOpen()
{
  return (string("") != _sNomFichier) ;
}

// Trouve un nom de fichier nautilus au document
////////////////////////////////////////////////////////////////
/*
bool NSTtxDocumentExp::Renommer(string& sNomFichier, string& sLocalis, string sType, string* psNomBrut)
{
    string sPath = "";
    string sExt = GetDocExt();

    if (!TrouveNomFichier(sType,sExt,sNomFichier,sLocalis))
    {
    	erreur("Pb � l'attribution d'un nouveau nom pour ce fichier",standardError,0,pContexte->GetMainWindow()->GetHandle());
   	    return false;
    }

    if (psNomBrut)
    {
        // Dans ce cas on renvoie aussi le nom brut (sans extension)
        size_t pos = sNomFichier.find('.');
        if (pos != NPOS)
            *psNomBrut = string(sNomFichier, 0, pos);
        else
            *psNomBrut = sNomFichier;
    }

    sPath = pContexte->PathName(sLocalis);

    // on construit le nom complet pour la sauvegarde
    SetNomFichier(sPath + sNomFichier);

    SetDirty(true);

    return true;
}
*/

// fin de html2word.cpp
//////////////////////////////////////////////////

