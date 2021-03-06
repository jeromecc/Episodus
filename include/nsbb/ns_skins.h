#ifndef NS_SKINS_H#define NS_SKINS_H

#include <owl\color.h>
#include <owl\gdiobjec.h>

#include "partage\ns_vector.h"
#include "nsbb\nsExport.h"

//
// class nsBoxPosition
// ~~~~~ ~~~~~~~~~~~~~~
class _NSBBCLASSE nsBoxPosition
{
  public:

    nsBoxPosition() ;
    nsBoxPosition(const nsBoxPosition& rv) ;
    ~nsBoxPosition() ;

    nsBoxPosition& operator=(const nsBoxPosition& src) ;

    void   initDefault() ;
    void   initFromBP(const nsBoxPosition* pBP) ;
    string initValue(string sAttribute, string sValue) ;

    //
    // GETs
    //

    string            getGlobalVPos()     { return sGlobalVPos ;      }
    string            getGlobalVPosRef()  { return sGlobalVPosRef ;   }

    string            getGlobalHPos()     { return sGlobalHPos ;      }
    string            getGlobalHPosRef()  { return sGlobalHPosRef ;   }

    string            getTopPosRef()      { return sTopPosRef ;       }
    string            getTopUnit()        { return sTopUnit ;         }
    int               getTopValue()       { return iTopValue ;        }

    string            getRightPosRef()    { return sRightPosRef ;     }
    string            getRightUnit()      { return sRightUnit ;       }
    int               getRightValue()     { return iRightValue ;      }

    string            getBottomPosRef()   { return sBottomPosRef ;    }
    string            getBottomUnit()     { return sBottomUnit ;      }
    int               getBottomValue()    { return iBottomValue ;     }

    string            getLeftPosRef()     { return sLeftPosRef ;      }
    string            getLeftUnit()       { return sLeftUnit ;        }
    int               getLeftValue()      { return iLeftValue ;       }

    string            getHeightUnit()     { return sHeightUnit ;      }
    int               getHeightValue()    { return iHeightValue ;     }
    string            getMinHeightUnit()  { return sMinHeightUnit ;   }
    int               getMinHeightValue() { return iMinHeightValue ;  }

    string            getWidthUnit()      { return sWidthUnit ;       }
    int               getWidthValue()     { return iWidthValue ;      }
    string            getMinWidthUnit()   { return sMinWidthUnit ;    }
    int               getMinWidthValue()  { return iMinWidthValue ;   }

    //
    // SETs
    //

    string setVPos(string sV) ;
    void   setGlobalVPos(string sV)     { sGlobalVPos = sV ;      }
    void   setGlobalVPosRef(string sV)  { sGlobalVPosRef = sV ;   }

    string setHPos(string sV) ;
    void   setGlobalHPos(string sV)     { sGlobalHPos = sV ;      }
    void   setGlobalHPosRef(string sV)  { sGlobalHPosRef = sV ;   }

    string setTop(string sV) ;
    void   setTopPosRef(string sV)      { sTopPosRef = sV ;       }
    void   setTopUnit(string sV)        { sTopUnit = sV ;         }
    void   setTopValue(int iV)          { iTopValue = iV ;        }

    string setRight(string sV) ;
    void   setRightPosRef(string sV)    { sRightPosRef = sV ;     }
    void   setRightUnit(string sV)      { sRightUnit = sV ;       }
    void   setRightValue(int iV)        { iRightValue = iV ;      }

    string setBottom(string sV) ;
    void   setBottomPosRef(string sV)   { sBottomPosRef = sV ;    }
    void   setBottomUnit(string sV)     { sBottomUnit = sV ;      }
    void   setBottomValue(int iV)       { iBottomValue = iV ;     }

    string setLeft(string sV) ;
    void   setLeftPosRef(string sV)     { sLeftPosRef = sV ;      }
    void   setLeftUnit(string sV)       { sLeftUnit = sV ;        }
    void   setLeftValue(int iV)         { iLeftValue = iV ;       }

    string setHeight(string sV) ;
    void   setHeightUnit(string sV)     { sHeightUnit = sV ;      }
    void   setHeightValue(int iV)       { iHeightValue = iV ;     }
    void   setMinHeightUnit(string sV)  { sMinHeightUnit = sV ;   }
    void   setMinHeightValue(int iV)    { iMinHeightValue = iV ;  }

    string setWidth(string sV) ;
    void   setWidthUnit(string sV)      { sWidthUnit = sV ;       }
    void   setWidthValue(int iV)        { iWidthValue = iV ;      }
    void   setMinWidthUnit(string sV)   { sMinWidthUnit = sV ;    }
    void   setMinWidthValue(int iV)     { iMinWidthValue = iV ;   }

	protected:

    string sGlobalVPos ;
    string sGlobalVPosRef ;

    string sGlobalHPos ;
    string sGlobalHPosRef ;

    string sTopPosRef ;
    string sTopUnit ;
    int    iTopValue ;

    string sRightPosRef ;
    string sRightUnit ;
    int    iRightValue ;

    string sBottomPosRef ;
    string sBottomUnit ;
    int    iBottomValue ;

    string sLeftPosRef ;
    string sLeftUnit ;
    int    iLeftValue ;

    string sHeightUnit ;
    int    iHeightValue ;
    string sMinHeightUnit ;
    int    iMinHeightValue ;

    string sWidthUnit ;
    int    iWidthValue ;
    string sMinWidthUnit ;
    int    iMinWidthValue ;

    string setPosAndRef(string sValue, string sPosLegalValues, string* psPos, string* psRef) ;
    string setNumericPosAndRef(string sValue, string* psRef, int* pNum, string* psUnit) ;
    string setNumericPos(string sValue, int* pNum, string* psUnit) ;

    bool   isNumAndUnit(string sValue) ;
} ;

//
// class nsSkin
// ~~~~~ ~~~~~~~~~~~~~~
class _NSBBCLASSE nsSkin
{
	public:

		// Style d'affichage d'un bmp de fond, compatible avec WPSTYLE
    enum TYPEBMPDRAW { DrawUndefined = 0, DrawCenter, DrawTile, DrawStretch, DrawMax, DrawAsForm } ;

    nsSkin(string sPath) ;
    nsSkin(const nsSkin& rv) ;
    ~nsSkin() ;

    void initToNull() ;

    //
    // GETs
    //
    string            getName()           { return _sName ;            }

    ClassLib::TColor* getBackColor()      { return _pBackColor ;       }
    string*           getBmp()            { return &_sBmp ;            }
    TDib*             getBackBmp()        { return _pBackBmp ;         }
    TYPEBMPDRAW       getBackDraw()       { return _iBmpDraw ;         }

    LOGFONT*          getLogFont()        { return _pFontDesc ;        }
    ClassLib::TColor* getFontColor()      { return _pFontColor ;       }
    ClassLib::TColor* getFontBackColor()  { return _pFontBackColor ;   }
    OWL::TIcon*   		getIcon()           { return _iCon;              }

    nsBoxPosition*    getBoxPosition()    { return &_boxPos ;          }

    //
    // SETs
    //
    void    setName(string sNM)     { _sName     = sNM;    }

    void setBackColor(ClassLib::TColor* color) ;
    void setBackBmp(string sB) ;
    void setBackBmp(OWL::TDib* pBackBmp) ;
    void setBackIco(string sB) ;
    void setBackDraw(TYPEBMPDRAW iBD) { _iBmpDraw  = iBD;    }
    void setIco(OWL::TIcon* sB)       { _iCon = sB;          }

    void setLogFont(LOGFONT* lFT) ;
    void setFontColor(ClassLib::TColor* FtCol) ;
    void setFontBackColor(ClassLib::TColor* FtCol) ;

    nsSkin& operator=(const nsSkin& src) ;

	protected:

  	string  _sName ;
    string  _sSkinPath ;

    //
    // Fond         : Couleur ou Bitmap
    // Background   : Color or Bitmap
    //
    ClassLib::TColor* _pBackColor ;
    OWL::TDib*        _pBackBmp ;
    string            _sBmp ;
    TYPEBMPDRAW       _iBmpDraw ;
    OWL::TIcon*				_iCon ;     // Icon

    //
    // Police de caractères : Description et Couleur
    // Font : description and color
    //
    LOGFONT*          _pFontDesc ;
    ClassLib::TColor* _pFontColor ;
    ClassLib::TColor* _pFontBackColor ;

    //
    // Position
    //
    nsBoxPosition     _boxPos ;
};

typedef vector<nsSkin*> skinsArray ;typedef skinsArray::iterator       skin_iter ;
typedef skinsArray::const_iterator skin_constIter ;

class _NSBBCLASSE skinArray : public skinsArray, public NSSuperRoot
{
	public :

		string _sTitle ;
    string _sAuthor ;
    string _sComment ;

    string _sAppName ;

		//
    // Constructeurs
		skinArray(NSSuper* pSuper) ;
		skinArray(const skinArray& rv) ;
		//
		// Destructeur
		//
		~skinArray() ;
		void vider() ;

		void    init(string sPath) ;
		nsSkin* donneSkin(string sName) ;
    nsSkin* donneSkinForLexique(string sCode) ;

		skinArray& operator=(const skinArray& src) ;
};
#endif  // NS_SKINS_H

