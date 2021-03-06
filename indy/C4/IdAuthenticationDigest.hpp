// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdAuthenticationDigest.pas' rev: 4.00

#ifndef IdAuthenticationDigestHPP
#define IdAuthenticationDigestHPP

#pragma delphiheader begin
#pragma option push -w-
#include <IdHeaderList.hpp>	// Pascal unit
#include <IdHashMessageDigest.hpp>	// Pascal unit
#include <IdAuthentication.hpp>	// Pascal unit
#include <IdGlobal.hpp>	// Pascal unit
#include <IdException.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Idauthenticationdigest
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EIdInvalidAlgorithm;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION EIdInvalidAlgorithm : public Idexception::EIdException 
{
	typedef Idexception::EIdException inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EIdInvalidAlgorithm(const AnsiString Msg) : Idexception::EIdException(
		Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EIdInvalidAlgorithm(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Idexception::EIdException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EIdInvalidAlgorithm(int Ident, Extended Dummy) : Idexception::EIdException(
		Ident, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EIdInvalidAlgorithm(int Ident, const System::TVarRec 
		* Args, const int Args_Size) : Idexception::EIdException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EIdInvalidAlgorithm(const AnsiString Msg, int AHelpContext
		) : Idexception::EIdException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EIdInvalidAlgorithm(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EIdInvalidAlgorithm(int Ident, int AHelpContext) : 
		Idexception::EIdException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdInvalidAlgorithm(int Ident, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Idexception::EIdException(Ident, Args, Args_Size, 
		AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EIdInvalidAlgorithm(void) { }
	#pragma option pop
	
};

#pragma pack(pop)

class DELPHICLASS TIdDigestAuthentication;
#pragma pack(push, 4)
class PASCALIMPLEMENTATION TIdDigestAuthentication : public Idauthentication::TIdAuthentication 
{
	typedef Idauthentication::TIdAuthentication inherited;
	
protected:
	AnsiString FRealm;
	bool FStale;
	AnsiString FOpaque;
	Classes::TStringList* FDomain;
	AnsiString Fnonce;
	AnsiString FAlgorithm;
	Classes::TStringList* FQopOptions;
	Classes::TStringList* FOther;
	virtual Idauthentication::TIdAuthWhatsNext __fastcall DoNext(void);
	
public:
	__fastcall virtual ~TIdDigestAuthentication(void);
	virtual AnsiString __fastcall Authentication();
public:
	#pragma option push -w-inl
	/* TIdAuthentication.Create */ inline __fastcall virtual TIdDigestAuthentication(void) : Idauthentication::TIdAuthentication(
		) { }
	#pragma option pop
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------

}	/* namespace Idauthenticationdigest */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Idauthenticationdigest;
#endif
#pragma option pop	// -w-

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdAuthenticationDigest
