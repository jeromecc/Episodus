//----------------------------------------------------------------------------//----------------------------------------------------------------------------

#ifndef __NS_SHADOK_H
#define __NS_SHADOK_H

#define PSTRG const char *

typedef struct CPS_StatusService {
  UINT16 NumVersionAPIs;      /* numero de version des APIs */
  UINT16 NumVersionAPI;       /* numero de version du service */
  UINT16 NumAPI;              /* numero du service API */
  UINT16 StatusAPI;           /* code retour de l'API */
  UINT16 StatusGestionnaire;  /* resultat d�execution des fonctions du Gestionnaire. */
  UINT16 StatusInterne;       /* etape interne du service */
  UINT16 StatusLecteur;       /* Code retour lecteur */
  UINT16 StatusCarte;         /* Status Carte ME1-ME2 */
} CPS_StatusService;

typedef struct CPS_InfosCarte {
  UINT8 IdEmetteur      [11];
  UINT8 IdCarteLog      [10];
  UINT8 CategorieCarte  [2];
  UINT8 DateEmis        [8];
  UINT8 DateFinVal      [8];
  } CPS_InfosCarte ;

// idEmetteur = "80250000017"

typedef struct CPS_InfosPorteur {
  UINT8 CodeCivilite    [2];
  UINT8 NomPatronym    [27];
  UINT8 NomMarital     [27];
  UINT8 Prenoms     [3][27];
  UINT8 PrenomUsuel    [27];
  UINT8 CodeLangues  [4][2];
  } CPS_InfosPorteur ;

UINT16 API_ENTRY CPS_OuvertureSession( PSTRG pNomRessource,
                                    PSTRG pNomAppli,
                                    struct CPS_StatusService PTR pStatusService,
                                    PUINT16 pNumSession,
                                    PUINT8 pFU);

UINT16 API_ENTRY CPS_InformationsCarte( UINT16  NumSession,
                                    struct  CPS_InfosCarte PTR pIC,
                                    struct  CPS_StatusService PTR pStatusService,
                                    PUINT16 pEtatCarte);

UINT16 API_ENTRY CPS_InformationsPorteur(UInt16 NumSession,
                                    struct CPS_InfosPorteur InfosPorteur PTR pIP,
                                    struct CPS_StatusService StatusService PTR pStatusService,
                                    PUINT16 pEtatCarte);

UINT16 API_ENTRY CPS_FermetureSession(PUINT16 pNumSession,
                                    struct CPS_StatusService PTR pStatusService);

#endif
