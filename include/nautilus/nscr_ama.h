//----------------------------------------------------------------------------
// ObjectWindows - (C) Copyright 1991, 1993 by Borland International
//   Tutorial application -- step12dv.cpp
//----------------------------------------------------------------------------

#ifndef __NSCR_AMA_H
#define __NSCR_AMA_H

#include <vector>
#include "nautilus/nscr_amx.h"

//
// D�finition de NSCRPhraseArray (Array de NSCRPhrase(s))
//

typedef vector<NSCRPhrase*> NSCRPhrArray ;
typedef NSCRPhrArray::iterator       NSCRPhrArrayIter ;
typedef NSCRPhrArray::const_iterator NSCRPhrArrayConstIter ;

class  NSCRPhraseArray : public NSCRPhrArray
{
  public :

	  // Constructeurs
    NSCRPhraseArray() : NSCRPhrArray() {}
    NSCRPhraseArray(const NSCRPhraseArray& rv) ;

	  // Destructeur
    virtual ~NSCRPhraseArray() ;

    // Op�rateur =
    NSCRPhraseArray& operator=(const NSCRPhraseArray& src) ;

    void vider() ;
};

#endif // __NSCR_ANA_H

