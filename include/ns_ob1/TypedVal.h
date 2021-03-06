/*
** Copyright Nautilus, (10/9/2004)
** fabrice.le_perru@nautilus-info.com
** david.giocanti@nautilus-info.com

** Ce logiciel est un programme informatique servant � [rappeler les
** caract�ristiques techniques de votre logiciel].

** Ce logiciel est r�gi par la licence CeCILL soumise au droit fran�ais et
** respectant les principes de diffusion des logiciels libres. Vous pouvez
** utiliser, modifier et/ou redistribuer ce programme sous les conditions
** de la licence CeCILL telle que diffus�e par le CEA, le CNRS et l'INRIA
** sur le site "http://www.cecill.info".

** En contrepartie de l'accessibilit� au code source et des droits de copie,
** de modification et de redistribution accord�s par cette licence, il n'est
** offert aux utilisateurs qu'une garantie limit�e.  Pour les m�mes raisons,
** seule une responsabilit� restreinte p�se sur l'auteur du programme,  le
** titulaire des droits patrimoniaux et les conc�dants successifs.

** A cet �gard  l'attention de l'utilisateur est attir�e sur les risques
** associ�s au chargement,  � l'utilisation,  � la modification et/ou au
** d�veloppement et � la reproduction du logiciel par l'utilisateur �tant
** donn� sa sp�cificit� de logiciel libre, qui peut le rendre complexe �
** manipuler et qui le r�serve donc � des d�veloppeurs et des professionnels
** avertis poss�dant  des  connaissances  informatiques approfondies.  Les
** utilisateurs sont donc invit�s � charger  et  tester  l'ad�quation  du
** logiciel � leurs besoins dans des conditions permettant d'assurer la
** s�curit� de leurs syst�mes et ou de leurs donn�es et, plus g�n�ralement,
** � l'utiliser et l'exploiter dans les m�mes conditions de s�curit�.

** Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez
** pris connaissance de la licence CeCILL, et que vous en avez accept� les
** termes.
*/
// -----------------------------------------------------------------------------
// A TypedVal is a manifest type: a combination of a discriminant, identifying
// the type, and a union, carrying the value. Their purpose is to represent the
// values of BB1 object attributes. Values of user-defined types must
// necessarily be carried as void pointers.
// There are no assignment operators.
// -----------------------------------------------------------------------------

#ifndef __TYPEDVAL_H__
#define __TYPEDVAL_H__ 1

/**
*  for friend declaration
*/
class BB1Object ;
class NautilusEvent ;

#ifdef __GNUC__
#pragma interface
#endif // __GNUC__

#include "ns_ob1\OB1Export.h"
#include "ns_ob1\BB1types.h"
#include "nsbb\nspatpat.h"
#include "partage\ns_search.h"
#include "ns_ob1\NautilusType.h"
#include "ns_ob1\BB1UserEvent.h"

// -----------------------------------------------------------------------------
// These are the types that an attribute can take. This enumeration type is used
// as a discriminant for the union, and as a property of the attribute.
// -----------------------------------------------------------------------------

/**
* \brief Type-Value pair
*/
/**
* Representation of a variable  and it's value  <BR>
* Repr�senation d'une variable (Paire Type-Valeur)
*/
class _BBKEXPORT TypedVal
{
  // Allowed to call Discriminant(void)
  friend class BB1Object ;
  friend std::string ComputeSortingId(TypedVal& temp) ;
  friend std::string GetStringFromSortingId(std::string sortingID) ;

 public:

	void InitWithZeros()
	{
		// assign the default value
    //
		boolVal			   = false ;
		intVal         = 0 ;
		doubleVal		   = 0 ;
		longVal			   = 0 ;
		_StringVal		 = NULLSTRING ;
		ptrVal			   = NULLPTR ;
		_patpathoVal	 = NULLPATHO ;
    _papeCathoIter = NULLPATPATHOITER ;
		_objectVal		 = NULLOBJECT ;
    _squest        = NULLLNAUTQUEST ;
    _pAnswerStatus = NULLLANSWERSTATUS ;
    _nautEvent     = NULLNAUTILUSEVENT ;
    _pSearchStruct = NULLSEARCHSTRUCT ;

#ifdef __OB1__UNOPTIM__
    floatVal		= 0 ;
    charVal			= 0 ;
    shortVal		= 0 ;
    uCharVal		= 0 ;
		uIntVal			= 0 ;
		uLongVal		= 0 ;
		uShortVal		= 0 ;
    pathsVal		= NULLPATHS ;
#endif
	} ;


  // ---------------------------------------------------------------------------
  // These are the constructors. There is one for each built-in data type and
  // for a few others. As an escape mechanism, a (void *) can be passed.
  // ---------------------------------------------------------------------------

	/**
  * default constructor
  */
	TypedVal() : _discr(UNBOUND)
	{
    _lTVCount++ ;
  	InitWithZeros() ;
	} ;

	/**
  * copy constructor
  * @param v typedVal to clone
  */
	TypedVal(const TypedVal& v)
	{
    _lTVCount++ ;

		// assign the discriminant
		_discr = v._discr ;

    // assign the default value
    InitWithZeros() ;

		// assign the real value
		switch (_discr)
		{
			case BB1BOOL			: boolVal    = v.boolVal ;    break ;
      case BB1INT				:	intVal     = v.intVal ;     break ;
			case BB1DOUBLE		:	doubleVal  = v.doubleVal ;  break ;
			case BB1LONG			:	longVal    = v.longVal ;    break ;
			case BB1STRING		:	_StringVal = v._StringVal ;	break ;
			case BB1POINTER		:	ptrVal     = v.ptrVal ;     break ;
      case BB1PATPATHOITER :
      	_papeCathoIter = new PatPathoIter(*(v._papeCathoIter)) ;
        break ;
			case BB1PATPATHO	:
      	if (true == v._extPtr)
        {
        	_extPtr = true ;
        	_patpathoVal = v._patpathoVal ;
        }
        else
        {
          _extPtr = false ;
      		_patpathoVal = new NSPatPathoArray(*(v._patpathoVal)) ;
      	}
      	break ;
			//case BB1OBJ				: *objectVal	= *(v.objectVal) ; break ;
      case OB1QEST      :
      	_squest = new NautilusQuestion(v._squest) ;
        break ;
      case OB1ANSWERSTATUS :
      	_pAnswerStatus = new AnswerStatus(*(v._pAnswerStatus)) ;
        break ;
      case BB1SEARCHSTRUCT :
        _pSearchStruct = new NSSearchStruct(*(v._pSearchStruct)) ;
        break ;
      case BB1NAUTEVENT :
      	if (v._extPtr == true)
        {
        	_extPtr = true;
        	_nautEvent = v._nautEvent ;
        }
        else
        {
          _extPtr = false ;
      		_nautEvent	= new NautilusEvent(*(v._nautEvent)) ;
      	}
        break ;
      case BB1HANDLES :
        {
          if (false == v._aHandles.empty())
            for (vector<HANDLE>::iterator it = (HANDLE*)v._aHandles.begin() ; v._aHandles.end() != it ; it++)
              _aHandles.push_back(*it) ;
        }
        break ;

#ifdef __OB1__UNOPTIM__
      case BB1FLOAT			:	floatVal  	= v.floatVal ;									 break ;
      case BB1PATHS			:	pathsVal		= new PathsList(*(v.pathsVal)) ; break ;
      case BB1CHAR			:	charVal   	= v.charVal ;                    break ;
      case BB1SHORT			:	shortVal  	= v.shortVal ;                   break ;
      case BB1ULONG			:	uLongVal  	= v.uLongVal ;	                 break ;
      case BB1USHORT		:	uShortVal 	= v.uShortVal ; 	               break ;
      case BB1UCHAR			:	uCharVal  	= v.uCharVal ;                   break ;
      case BB1UINT			:	uIntVal   	= v.uIntVal ;	                   break ;
#endif
		}
	} ;


	/**
  * Boolean Constructeur
  */
	TypedVal(const bool boolArg) : _discr(BB1BOOL)
	{
    _lTVCount++ ;

    InitWithZeros() ;

    boolVal = boolArg ;
	} ;

#ifdef __OB1__UNOPTIM__
	TypedVal(const char charArg) : _discr(BB1CHAR)
	{
    _lTVCount++ ;

    InitWithZeros() ;

    charVal = charArg ;
	} ;
#endif

	TypedVal(const double doubleArg) : _discr(BB1DOUBLE)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

    doubleVal = doubleArg ;
	} ;

#ifdef __OB1__UNOPTIM__
	TypedVal(const float floatArg) : _discr(BB1FLOAT)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

    floatVal = floatArg ;
	} ;
#endif

	TypedVal(const int intArg) : _discr(BB1INT)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

    intVal = intArg ;
	} ;

  /**
  * Long constructror
  * @param  longArg for initialisation
  */
	TypedVal(const long longArg) : _discr(BB1LONG)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

    longVal = longArg ;
	} ;

#ifdef __OB1__UNOPTIM__
	TypedVal(const short shortArg) : _discr(BB1SHORT)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

    shortVal = shortArg ;
	} ;
#endif

	TypedVal(const string& StringArg) : _discr(BB1STRING)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

    _StringVal = StringArg ;
	} ;

#ifdef __OB1__UNOPTIM__
	TypedVal(const unsigned char uCharArg) : _discr(BB1UCHAR)
	{
    _lTVCount++ ;

		InitWithZeros() ;

    uCharVal = uCharArg ;
	} ;
#endif

#ifdef __OB1__UNOPTIM__
	TypedVal(const unsigned int uIntArg) : _discr(BB1UINT)
	{
    _lTVCount++ ;

		InitWithZeros() ;

    uIntVal = uIntArg ;
	} ;
#endif

#ifdef __OB1__UNOPTIM__
	TypedVal(const unsigned long uLongArg) : _discr(BB1ULONG)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

		uLongVal = uLongArg ;
	} ;
#endif

#ifdef __OB1__UNOPTIM__
	TypedVal(const unsigned short uShortArg) : _discr(BB1USHORT)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

    uShortVal = uShortArg ;
	} ;
#endif

 	TypedVal(const Voidptr ptrArg) :	_discr(BB1POINTER)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

    ptrVal = ptrArg ;
	} ;

  TypedVal(const NautilusQuestion* arg) : _discr(OB1QEST)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

    if ((NULL == arg) || (NULLLNAUTQUEST == arg))
      _squest = NULLLNAUTQUEST ;
    else
    	_squest = new NautilusQuestion(arg) ;
	} ;

	TypedVal(AnswerStatus* arg) :_discr(OB1ANSWERSTATUS)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

    if ((NULL == arg) || (NULLLANSWERSTATUS == arg))
      _pAnswerStatus = NULLLANSWERSTATUS ;
    else
    	_pAnswerStatus = new AnswerStatus(arg) ;
	} ;

  TypedVal(NautilusEvent* pEvent, bool bExt = false) :_discr(BB1NAUTEVENT)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

    if (bExt)
    {
      _extPtr = true;
		  if (NULLNAUTILUSEVENT != pEvent)
			  _nautEvent	= pEvent ;
		  else
			  // patpathoVal	= new NSPatPathoArray(NULL) ;
        _nautEvent	= NULL ;
    }
    else
    {
      _extPtr = false;
	  	if (NULLNAUTILUSEVENT != pEvent)
		  	_nautEvent	= new NautilusEvent(*pEvent) ;
  		else
	  		_nautEvent	= new NautilusEvent() ;
    }
	} ;

  TypedVal(NSSearchStruct* arg) :_discr(BB1SEARCHSTRUCT)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

    if ((NULL == arg) || (NULLSEARCHSTRUCT == arg))
      _pSearchStruct = NULLSEARCHSTRUCT ;
    else
    	_pSearchStruct = new NSSearchStruct(*arg) ;
	} ;

#ifdef __OB1__UNOPTIM__
	TypedVal(PathsList *paths) : _discr(BB1PATHS)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

		if (paths)
			pathsVal = new PathsList(*paths) ;
		else
			pathsVal = new PathsList() ;
	} ;
#endif

	TypedVal(NSPatPathoArray *patPatho, bool bExt = false) : _discr(BB1PATPATHO)
	{
    _lTVCount++ ;

    InitWithZeros() ;

    if (bExt)
    {
      _extPtr = true;
		  if (NULLPATHO != patPatho)
			  _patpathoVal	= patPatho ;
		  else
			  // patpathoVal	= new NSPatPathoArray(NULL) ;
        _patpathoVal	= NULL ;
    }
    else
    {
      _extPtr = false;
	  	if (NULLPATHO != patPatho)
		  	_patpathoVal	= new NSPatPathoArray(*patPatho) ;
  		else
	  		_patpathoVal	= new NSPatPathoArray(NULL) ;
    }
	} ;

  TypedVal(PatPathoIter *jeanPaul) : _discr(BB1PATPATHOITER)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

    _papeCathoIter = jeanPaul ;
	} ;

	TypedVal(BB1Object *obj) : _discr(BB1OBJ)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

    _objectVal = obj ;
	} ;

	TypedVal(vector<HANDLE> *pHandles) : _discr(BB1HANDLES)
	{
    _lTVCount++ ;

  	InitWithZeros() ;

    if ((NULL == pHandles) || (pHandles->empty()))
      return ;

    vector<HANDLE>::iterator it = pHandles->begin() ;
    for ( ; pHandles->end() != it ; it++)
      _aHandles.push_back(*it) ;
	} ;

	~TypedVal()
	{
#ifdef __OB1__UNOPTIM__
		if ((BB1PATHS == _discr) && pathsVal)
    {
			delete pathsVal ;
      pathsVal = NULL ;
    }
#endif

    if ((OB1QEST == _discr)  && (NULLLNAUTQUEST != _squest))
    {
      delete (_squest) ;
      _squest = NULLLNAUTQUEST ;
    }

    if ((OB1ANSWERSTATUS == _discr) && (NULL != _pAnswerStatus))
    {
      delete (_pAnswerStatus) ;
      _pAnswerStatus = NULLLANSWERSTATUS ;
    }

		if ((BB1PATPATHO == _discr) && (NULLPATHO != _patpathoVal) && (false == _extPtr))
			delete _patpathoVal ;
    _patpathoVal = NULLPATHO ;

    if ((BB1NAUTEVENT == _discr) && (NULLNAUTILUSEVENT != _nautEvent) && (false == _extPtr))
			delete _nautEvent ;
    _nautEvent = NULLNAUTILUSEVENT ;

    if ((BB1SEARCHSTRUCT == _discr) && (NULLSEARCHSTRUCT != _pSearchStruct))
			delete _pSearchStruct ;
    _pSearchStruct = NULLSEARCHSTRUCT ;

    _lTVCount-- ;
	} ;

	TypedVal&					operator=(const TypedVal& v) ;

  inline
	bool							operator==(const TypedVal& v) const ;

	// ---------------------------------------------------------------------------
	// These are the read accessors: they extract the primitive value from the
	// instance. There is one for each built-in data type and for a few others. As
	// an escape mechanism, a void * can be returned. If there is a type mismatch,
	// a null value is returned.
	// ---------------------------------------------------------------------------

  /**
  * Return the bool value is the variable is bolean <BR>
  * Renvoie la valeur bool de la classe si cette variable est de type booleen
  * @return
  * <ul>
  *     <li> the boolean value if the variable is boolean </li>
  *     <li> false if the vairable is not bool's type</li>
  *</ul>
  */
	bool							getBool()      const { return (_discr == BB1BOOL)      ? boolVal 		: bool(false) ;				}
  int								getInt()       const { return (_discr == BB1INT)       ? intVal 			: int(0) ;						}
  NautilusQuestion* getNautQuest() const { return (_discr == OB1QEST)      ? _squest      : NULL ; 							}
  AnswerStatus*     getAnsStatus() const { return (_discr == OB1ANSWERSTATUS) ? _pAnswerStatus : NULL ; 		}
  NautilusEvent*    getNautEvent() const { return (_discr == BB1NAUTEVENT) ? _nautEvent : NULL ; 		        }
  NSSearchStruct*   getSearchPrm() const { return (_discr == BB1SEARCHSTRUCT) ? _pSearchStruct : NULL ; 		        }
	double						getDouble()    const { return (_discr == BB1DOUBLE)		? doubleVal 	: double(0) ;					}
	long							getLong()      const { return (_discr == BB1LONG)			? longVal   	: long(0) ;						}
  inline
	const string			getString()    const { return (_discr == BB1STRING)		? _StringVal		: NULLSTRING ;				}
	const Voidptr			getPtr()       const { return (_discr == BB1POINTER)   ? ptrVal			: 0 ;									}

  #ifdef __OB1__UNOPTIM__
  float							getFloat()  const { return (_discr == BB1FLOAT)		? floatVal  	: float(0) ;					}
	char							getChar()   const { return (_discr == BB1CHAR)			? charVal 		: char(0) ;						}
  short							getShort()  const { return (_discr == BB1SHORT)		? shortVal  	: short(0) ;					}
  unsigned char			getUChar()  const { return (_discr == BB1UCHAR)		? uCharVal 		: (unsigned char)0 ;	}
	unsigned int			getUInt()   const { return (_discr == BB1UINT)			? uIntVal 		: (unsigned int)0 ;		}
	unsigned long			getULong()  const { return (_discr == BB1ULONG)		? uLongVal 		: (unsigned long)0 ; 	}
	unsigned short		getUShort() const { return (_discr == BB1USHORT)		? uShortVal		: (unsigned short)0 ;	}
  PathsList					*getPaths()				{ return (_discr == BB1PATHS)		? pathsVal		:	0	;									}
  #endif

	NSPatPathoArray		*getPatPatho()         { return (BB1PATPATHO == _discr)     ? _patpathoVal   : NULL ; }
  bool 							IsExtPtr() const       { return  _extPtr ; }
  PatPathoIter      *getPatPathoIter()     { return (BB1PATPATHOITER == _discr) ? _papeCathoIter : NULL ; }
	BB1Object					*getObj()              { return (BB1OBJ == _discr)          ? _objectVal     : NULLOBJECT	;	 }
  vector<HANDLE>    *getHandles()          { return (BB1HANDLES == _discr)      ? &_aHandles     : NULLHANDLES	;	 }
  std::string       TypedVal::toString() const;

  void              swapPatho(NSPatPathoArray *patho, bool bExt = false) ;

  void              addHandle(HANDLE hHandle) ;
  void              addHandleWithCounter(HANDLE hHandle) ;
  void              removeHandle(HANDLE hHandle) ;
  void              removeHandleWithCounter(HANDLE hHandle) ;
  int               getHandlesCount() { return (BB1HANDLES == _discr) ? _aHandles.size() : -1	;	 }
  bool              isThisHandleHere(HANDLE hHandle) ;

	char							*typeName() const ;
	void							putTypedVal(std::ostream& os) const ;

 // private:
  inline AttType		Discriminant() const { return _discr ; }

  static long       getNbInstance()  { return _lTVCount ; }
  static void       initNbInstance() { _lTVCount = 0 ; }

 private:

	AttType						_discr ;			// The type of the value

  /**
  * Different primitive type that the variable can be
  */
  union						// The primitive value itself
	{
		bool						boolVal ;       /**< boolean value */
    int							intVal ;
		double					doubleVal ;     /**< double value */
		long						longVal ;       /**< long value */
		Voidptr					ptrVal ;        /**< pointer value */
    #ifdef __OB1__UNOPTIM__
    char						charVal ;
    unsigned char		uCharVal ;
		unsigned int		uIntVal ;
		unsigned long		uLongVal ;
		unsigned short	uShortVal ;
    short						shortVal ;
    float						floatVal ;
    #endif
  } ;

  // types with constructors can't appear in unions.

	string						_StringVal ;
	NSPatPathoArray*  _patpathoVal ;
  bool 							_extPtr ;  // Vraie si la patho est exterieur au blackboard
  PatPathoIter*     _papeCathoIter ;
  NautilusQuestion* _squest ;
  AnswerStatus*     _pAnswerStatus ;
  BB1Object*        _objectVal ;
  NautilusEvent*    _nautEvent ;
  vector<HANDLE>    _aHandles ;
  NSSearchStruct*   _pSearchStruct ;

  static long       _lTVCount ;

#ifdef __OB1__UNOPTIM__
  PathsList					*pathsVal ;
#endif
} ;

inline
bool TypedVal::operator==(const TypedVal& v) const
{
  if (this == &v)
		return (true) ;

	if (_discr != v._discr)
		return (false) ;
	else
  {
    switch (_discr)
    {
			case BB1INT				   : return (intVal    	    == v.intVal) ;
			case BB1DOUBLE		   : return (doubleVal 	    == v.doubleVal) ;
			case BB1LONG			   : return (longVal   	    == v.longVal) ;
			case BB1STRING		   : return (_StringVal     == v._StringVal) ;
			case BB1POINTER		   : return (ptrVal    	    == v.ptrVal) ;
			case BB1PATPATHO	   : return (_patpathoVal   == v._patpathoVal) ;
      case BB1PATPATHOITER : return (_papeCathoIter == v._papeCathoIter) ;
			case BB1OBJ				   : return (_objectVal     == v._objectVal) ;
      case OB1QEST         : return (*_squest       == *(v._squest)) ;
      case BB1NAUTEVENT    : return (_nautEvent     == v._nautEvent) ;
      case BB1SEARCHSTRUCT : return (*_pSearchStruct == *(v._pSearchStruct)) ;
      #ifdef __OB1__UNOPTIM__
      case BB1SHORT			   : return (shortVal  	    == v.shortVal) ;
      case BB1FLOAT			   : return (floatVal  	    == v.floatVal) ;
      case BB1CHAR			   : return (charVal   	    == v.charVal) ;
      case BB1PATHS			   : return (pathsVal 		  == v.pathsVal) ;
      case BB1UCHAR			   : return (uCharVal  	    == v.uCharVal) ;
			case BB1UINT			   : return (uIntVal   	    == v.uIntVal) ;
			case BB1ULONG			   : return (uLongVal  	    == v.uLongVal) ;
			case BB1USHORT		   : return (uShortVal 	    == v.uShortVal) ;
      case BB1HANDLES      :
      {
        if (_aHandles.empty() && v._aHandles.empty())
          return true ;
        if (_aHandles.empty() || v._aHandles.empty())
          return false ;

        vector<HANDLE>::iterator it1 = _aHandles.begin() ;
        vector<HANDLE>::iterator it2 = v._aHandles.begin() ;

        for ( ; (_aHandles.end() != it1) && (v._aHandles.end() != it2) ; it1++, it2++)
          if (*it1 != *it2)
            return false ;

        if ((_aHandles.end() != it1) || (v._aHandles.end() != it2))
          return false ;

        return true ;
      }
      #endif
			default              : return (false) ;
    }
  }
}

std::string _BBKEXPORT ComputeSortingId(TypedVal& temp) ;
std::string _BBKEXPORT GetStringFromSortingId(std::string sortingID) ;

std::ostream&		operator<<(std::ostream& os, const TypedVal& tv) ;

#endif // __TYPEDVAL_H__

