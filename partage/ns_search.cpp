// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Research methods
// -----------------------------------------------------------------------------
// $Revision: 1.6 $
// $Author: pameline $
// $Date: 2014/01/29 20:44:39 $
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Copyright Nautilus, 2004
// http://www.nautilus-info.com
// -----------------------------------------------------------------------------
// Ce logiciel est un programme informatique servant � g�rer et traiter les
// informations de sant� d'une personne.
//
// Ce logiciel est r�gi par la licence CeCILL soumise au droit fran�ais et
// respectant les principes de diffusion des logiciels libres. Vous pouvez
// utiliser, modifier et/ou redistribuer ce programme sous les conditions de la
// licence CeCILL telle que diffus�e par le CEA, le CNRS et l'INRIA sur le site
// "http://www.cecill.info".
//
// En contrepartie de l'accessibilit� au code source et des droits de copie, de
// modification et de redistribution accord�s par cette licence, il n'est offert
// aux utilisateurs qu'une garantie limit�e. Pour les m�mes raisons, seule une
// responsabilit� restreinte p�se sur l'auteur du programme, le titulaire des
// droits patrimoniaux et les conc�dants successifs.
//
// A cet �gard  l'attention de l'utilisateur est attir�e sur les risques
// associ�s au chargement, � l'utilisation, � la modification et/ou au
// d�veloppement et � la reproduction du logiciel par l'utilisateur �tant donn�
// sa sp�cificit� de logiciel libre, qui peut le rendre complexe � manipuler et
// qui le r�serve donc � des d�veloppeurs et des professionnels avertis
// poss�dant des connaissances informatiques approfondies. Les utilisateurs sont
// donc invit�s � charger et tester l'ad�quation du logiciel � leurs besoins
// dans des conditions permettant d'assurer la s�curit� de leurs syst�mes et ou
// de leurs donn�es et, plus g�n�ralement, � l'utiliser et l'exploiter dans les
// m�mes conditions de s�curit�.
//
// Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez pris
// connaissance de la licence CeCILL, et que vous en avez accept� les termes.
// -----------------------------------------------------------------------------
// This software is a computer program whose purpose is to manage and process
// a person's health data.
//
// This software is governed by the CeCILL  license under French law and abiding
// by the rules of distribution of free software. You can use, modify and/ or
// redistribute the software under the terms of the CeCILL license as circulated
// by CEA, CNRS and INRIA at the following URL "http://www.cecill.info".
//
// As a counterpart to the access to the source code and  rights to copy, modify
// and redistribute granted by the license, users are provided only with a
// limited warranty and the software's author, the holder of the economic
// rights, and the successive licensors have only limited liability.
//
// In this respect, the user's attention is drawn to the risks associated with
// loading, using, modifying and/or developing or reproducing the software by
// the user in light of its specific status of free software, that may mean that
// it is complicated to manipulate, and that also therefore means that it is
// reserved for developers and experienced professionals having in-depth
// computer knowledge. Users are therefore encouraged to load and test the
// software's suitability as regards their requirements in conditions enabling
// the security of their systems and/or data to be ensured and, more generally,
// to use and operate it in the same conditions as regards security.
//
// The fact that you are presently reading this means that you have had
// knowledge of the CeCILL license and that you accept its terms.
// -----------------------------------------------------------------------------

  #include "enterpriseLus/nsdivfctForCgi.h"
#else
  #include "nautilus\nssuper.h"
  #include "partage\nsdivfct.h"
#endif
//***************************************************************************
MappingNSSearchResult::end()
{
  return (_data.end()) ;
}

//***************************************************************************
  tpsNow.takeTime() ;

  string sFil = sParams ;

  bool bProgress = true ;
  do
  {
    string sField ;
    splitString(sFil, &sField, &sFil, '|') ;

  	if (sField == sFil)
      bProgress = false ;

    strip(sField, stripBoth) ;

    string sValue = string("") ;
    splitString(sField, &sField, &sValue, '=') ;
    strip(sValue, stripBoth) ;

    if (string("") != sValue)
    {
      // F R and C are used for controls automatic filling
      //
      if      ('D' == sField[0])
      {
      	_sStartingDatePattern = sValue ;

        NVLdVTemps tpsObj ;
        tpsObj.takeTime() ;

        string sAjoutAns  = string(_sStartingDatePattern, 0, 2) ;
        string sAjoutMois = string(_sStartingDatePattern, 2, 2) ;
        string sAjoutJour = string(_sStartingDatePattern, 4, 2) ;

        if (sAjoutAns != "00")
  	      tpsObj.ajouteAns((-1) * atoi(sAjoutAns.c_str()), false /* don't normalize */) ;
        if (sAjoutMois != "00")
  	      tpsObj.ajouteMois((-1) * atoi(sAjoutMois.c_str()), false /* don't normalize */) ;
        if (sAjoutJour != "00")
  	      tpsObj.ajouteJours((-1) * atoi(sAjoutJour.c_str())) ;

        _sStartingDate = tpsObj.donneDateHeure() ;
      }
      else if ('M' == sField[0])
      {
      	_sMandatoryPath = sValue ;
        _bMandatoryForYesOrNo = false ;
      }
      else if ('N' == sField[0])
      {
      	_sMandatoryPath = sValue ;
        _bMandatoryForYesOrNo = true ;
      }
      else if ('E' == sField[0])
      {
        if      ('C' == sValue[0])
          _iEpisodeStatus = episodeClosed ;
        else if ('O' == sValue[0])
          _iEpisodeStatus = episodeOpened ;
        else if ('F' == sValue[0])
          _iEpisodeStatus = episodeFuture ;
      }
      else if ('A' == sField[0])
      {
      	_sMandatoryArchetype = sValue ;
      }
    }
  }
  while(bProgress) ;