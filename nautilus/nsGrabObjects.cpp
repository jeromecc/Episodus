// NSGRABOBJECTS.CPP : Dialogues de capture d'images
////////////////////////////////////////////////////////////
#include <cstring.h>
#include <owl\clipboar.h>

#include "Compos.h"
#include "nsbb\nsattvaltools.h"
#include "nssavoir\nsfilecaptur.h"
#include "partage\nsdivfile.h"

#include "nautilus\nsGrabObjects.h"

#include "nautilus\nsepicap.h"



	(FARPROC) pAdrConvert = pContexte->getSuperviseur()->getGrabModule()->GetProcAddress(MAKEINTRESOURCE(M_CONVERTBMP)) ;

	if (pAdrConvert == NULL)
	{
		erreur("Impossible de r�cup�rer la fonction ConvertBmpToJpg()", standardError, 0) ;
		return false ;
	}

	bool bOk = ((*pAdrConvert)((string far *) (&sFichier), (NSContexte far *) pContexte)) ;
	if (!bOk)
	{
		erreur("Erreur � la conversion d'une image bmp.", standardError, 0) ;
		return false ;
	}
	int i = 0;
	char szNum[8] ;
	bool exist ;

	// Recherche d'un nom de fichier valide
	do
	{
		i++ ;
    itoa(i, szNum, 10) ;
    sFichier = sNameSeed + string(szNum) + string(".bmp") ;
    exist = NsFileExists(sPath + sFichier) ;
    if (false == exist)
    {
    	sFichierDest = sNameSeed + string(szNum) + string(".jpg") ;
      exist = NsFileExists(sPath + sFichierDest) ;
    }
	}
	while (exist) ;


	if (pAdrInitCamera == NULL)
	// on initialise la camera 0
	bool bOk = ((*pAdrInitCamera)((NSMatrox far *) pContexte->getSuperviseur()->getMatrox(),
                                    (int far) 0, (HWND far) handleClient, (NSContexte far *) pContexte,
                                    (long far*) (&lSizeX), (long far *) (&lSizeY))) ;
	if (!bOk)
	{
		erreur("Erreur au lancement de la fonction InitCamera", standardError, 0) ;
		return false ;
	}

	if (pAdrFreeCamera != NULL)
	{
		if (!bOk)
		{
    	erreur("Erreur au lancement de la fonction FreeCamera", standardError, 0) ;
      return false ;
    }
	}
	else
	{
		erreur("Impossible de r�cup�rer la fonction FreeCamera()", standardError, 0) ;
		return false ;
	}

	if (pAdrStopCamera != NULL)
		// on stoppe la camera 0
	else
	{
		erreur("Impossible de r�cup�rer la fonction FreeCamera()", standardError, 0) ;
		return false ;
	}

	if (pAdrNbCamera != NULL)
	{
		return true ;
	}
	else
	{
		erreur("Impossible de r�cup�rer la fonction NbCamera()", standardError, 0) ;
    nbCam = -1 ;
    return false ;
  }

	if (pAdrGrabFree != NULL)
	{
		if (!bOk)
		{
			erreur("Erreur au lancement de la fonction GrabFree", standardError, 0) ;
			return false ;
		}

		pContexte->getSuperviseur()->initMatrox(*ppMatrox) ;
	}
	else
	{
		erreur("Impossible de r�cup�rer la fonction GrabFree()", standardError, 0) ;
		return false ;
	}

	if (pAdrPlayCamera == NULL)
	// on lance la camera 0 (grabbing)
	bool bOk = ((*pAdrPlayCamera)((NSMatrox far *) pContexte->getSuperviseur()->getMatrox(), (int far) 0)) ;
	if (!bOk)
	{
		erreur("Erreur au lancement de la fonction GrabFrame", standardError, 0) ;
    return false ;
	}

	if (pAdrPhotoCamera == NULL)
	// on lance la camera 0 (grabbing)
	bool bOk = ((*pAdrPhotoCamera)((NSMatrox far *) pContexte->getSuperviseur()->getMatrox(), (int far) 0)) ;
	if (!bOk)
	{
		erreur("Erreur au lancement de la fonction GrabOneBuffer", standardError, 0) ;
    return false ;
	}

	if (pAdrCaptureImage == NULL)
                                    (string far) sFichier, (NSContexte far *) pContexte)) ;
	if (!bOk)
	{
		erreur("Erreur au lancement de la fonction CaptureImage", standardError, 0) ;
    return false ;
	}

	if (pAdrPanImage == NULL)

	if (pAdrZoomImage == NULL)
DEFINE_RESPONSE_TABLE1(NSMilGrabWindow, TWindow)
NSMilGrabWindow::NSMilGrabWindow(TWindow* parent, NSContexte* pCtx, AssistCaptureDialog* pAssistDlg)
}
NSMilGrabWindow::~NSMilGrabWindow()
    DestroyAcceleratorTable(hAccelerator) ;
    hAccelerator = 0 ;
  }
bool
	// R�cup�ration du pointeur sur la fonction NbCamera
    pGrabber->GrabFree() ;

	sMsg = "Sortie de NSGrabWindow::CanClose()" ;
	int dX = rect.Width() - rectClient.Width() ;
int
NSMilGrabWindow::EvCreate(CREATESTRUCT far& createStruct)
{
	return TWindow::EvCreate(createStruct) ;

	// pGrabber->PlayCamera();
}

bool
NSMilGrabWindow::PreProcessMsg(MSG &msg)
{
  PRECONDITION(GetHandle()) ;
  return hAccelerator ? ::TranslateAccelerator(GetHandle(), hAccelerator, &msg) : false ;
}

void
NSMilGrabWindow::EvSize(uint sizeType, NS_CLASSLIB::TSize& size)
{
	// lSizeX = (long) size.X();
	// lSizeY = (long) size.Y();
}

void
NSMilGrabWindow::EvRButtonUp(uint a, NS_CLASSLIB::TPoint& p)
{
	NS_CLASSLIB::TPoint lp = p ;
	OWL::TPopupMenu *menu = new OWL::TPopupMenu() ;

	bOpenMenu = true ;

	menu->AppendMenu(MF_STRING, IDC_PLAY, "Jouer cam�ra") ;
	menu->AppendMenu(MF_SEPARATOR, 0, 0) ;
	menu->AppendMenu(MF_STRING, IDC_CAPTURE,  "Capturer") ;
	ClientToScreen(lp) ;
	menu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, lp, 0, Parent->HWindow) ;
	delete menu ;
}

void
NSMilGrabWindow::EvLButtonUp(uint a, NS_CLASSLIB::TPoint& p)
{
	if (!bOpenMenu)
		CaptureImage() ;
}

void
NSMilGrabWindow::PlayCamera()
{
	bOpenMenu       = false ;
	bGrabInProgress = true ;
	GrabContinuous() ;

	//pGrabber->PlayCamera();
	// string sMsg = "Sortie de PlayCamera";
	// pContexte->getSuperviseur()->trace(&sMsg, 1);
}

void
NSMilGrabWindow::GrabContinuous()
{
	if (bGrabInProgress)
	{
		pGrabber->GrabFrame() ;
		// pContexte->getSuperviseur()->pNSApplication->PumpWaitingMessages();
		// PostMessage(WM_COMMAND, IDC_GRAB);
	}
}

void
NSMilGrabWindow::StopCamera()
{
	bOpenMenu       = false ;
	bGrabInProgress = false ;
	pGrabber->StopCamera() ;

	// string sMsg = "Sortie de StopCamera";
	// pContexte->getSuperviseur()->trace(&sMsg, 1);
}

void
NSMilGrabWindow::CaptureImage()
{
	string sFichier, sFichierDest ;
	string sPath = pContexte->PathName("IHTM") ;

	bOpenMenu = false ;

	StopCamera() ;

  if (!(pGrabber->FindFileName(string("Image"), &sFichier, &sFichierDest)))
  {
  	erreur("Can't find temporary file name.", standardError, 0) ;
  	PlayCamera() ;
		return ;
	}

	if (pGrabber->CaptureImage(sFichier, GetHandle()))
	{
		if (pGrabber->ConvertImage(sFichier))
		{
			sFichier = sPath + sFichier ;
			if (!DeleteFile(sFichier.c_str()))
				erreur("Erreur � la destruction du fichier BMP temporaire.", standardError, 0) ;
		}
	}

	PlayCamera() ;
}

void
NSMilGrabWindow::PanImage()
{
	string sRes ;
	long X, Y ;

	sRes = pContexte->getSuperviseur()->getMatrox()->pParamArray->ValParam("Pan") ;
	X = atol(sRes.c_str()) ;
	sRes = pContexte->getSuperviseur()->getMatrox()->pParamArray->ValParam("Scroll") ;
	Y = atol(sRes.c_str()) ;

	if ((X == 0L) && (Y == 0L))
		return ;

	NS_CLASSLIB::TRect rect = Parent->GetWindowRect() ;
	NS_CLASSLIB::TPoint point(rect.X(), rect.Y()) ;
	Parent->Parent->ScreenToClient(point) ;

	pGrabber->PanImage(X,Y) ;

	::InvalidateRect(NULL, NULL, TRUE) ;
	Parent->UpdateWindow() ;

	// resize de la fenetre
	lSizeX = lSizeX - X ;
	lSizeY = lSizeY - Y ;
	Parent->MoveWindow(point.X(), point.Y(), (int) lSizeX, (int) lSizeY) ;
	::InvalidateRect(NULL, NULL, TRUE) ;
	pContexte->getSuperviseur()->donneMainWindow()->UpdateWindow() ;
}

void
NSMilGrabWindow::ZoomImage()
{
	NS_CLASSLIB::TRect rect = Parent->GetWindowRect() ;
	NS_CLASSLIB::TRect rectClient = Parent->GetClientRect() ;
	int dX = rect.Width() - rectClient.Width() ;

	string sRes = pContexte->getSuperviseur()->getMatrox()->pParamArray->ValParam("Zoom") ;
	long   X    = atol(sRes.c_str()) ;

	if (X <= 1L)
		return ;

	NS_CLASSLIB::TPoint point(rect.X(), rect.Y()) ;
	Parent->Parent->ScreenToClient(point) ;

	// StopCamera();

	pGrabber->ZoomImage(X, X) ;

	// resize de la fenetre
	lSizeX = ((lSizeX - dX) * X) + dX ;
	lSizeY = ((lSizeY - dY) * X) + dY ;
	Parent->MoveWindow(point.X(), point.Y(), (int) lSizeX, (int) lSizeY) ;
	::InvalidateRect(NULL,NULL,TRUE) ;
	pContexte->getSuperviseur()->donneMainWindow()->UpdateWindow() ;
}

void
NSMilGrabWindow::SetWindowPosit()
{
	int X, Y, W, H ;
	string sPosition = pContexte->getSuperviseur()->getMatrox()->pParamArray->ValParam("Position") ;

	if (sPosition != string(""))
	{
		getWindowPosit(sPosition, X, Y, W, H) ;
		Parent->MoveWindow(X, Y, W, H) ;
	}
}

/****************** classe NSGrabChild **************************/
////////////////////////////////////////////////////////////////////

NSMilGrabChild::NSMilGrabChild(NSContexte* pCtx, TMDIClient& parent, const char far* title, NSMilGrabWindow* clientWnd)
NSMilGrabChild::~NSMilGrabChild()
		// if (retVal == IDYES)
DEFINE_RESPONSE_TABLE1(AssistCaptureDialog, NSUtilDialog)
AssistCaptureDialog::AssistCaptureDialog(TWindow* pere, NSContexte* pCtx)
{
AssistCaptureDialog::~AssistCaptureDialog()
void
	sHcorps = "Importation_d_une_image.html" ;

}
{
void AssistCaptureDialog::CheckPhase()
{
	Show(SW_SHOW) ;
	SetFocus() ;

	switch(phase)
	{
    case 1 :
        pPhase1->Check();
        pPhase2->Uncheck();
        pPhase3->Uncheck();
        break;
    case 2 :
        pPhase1->Uncheck();
        pPhase2->Check();
        pPhase3->Uncheck();
        break;
    case 3 :
        pPhase1->Uncheck();
        pPhase2->Uncheck();
        pPhase3->Check();
        break;
    default :
        erreur("Pb de phase inconnue dans le dialogue assistant de la capture", standardError, 0, GetHandle()) ;
	}
}

void
void
}

	if (pTwainAcquire == NULL)
	// on initialise la camera 0
	bool bOk = ((*pTwainAcquire)((string far) sFileName, (HWND far) hwnd)) ;
	if (!bOk)
	{
		erreur("Erreur au lancement de la fonction CaptureImage", standardError, 0) ;
		return false ;
	}

	if (pTwainSelectSource == NULL)
	// on initialise la camera 0
	return ((*pTwainSelectSource)((HWND far) hwnd)) ;
}

void
	int dX = rect.Width() - rectClient.Width() ;
		inf.seekg(0L, ios::end ) ;
		if ((size = inf.tellg()) >= 0)
    {
  		pDib = new TDib(inf) ;

void