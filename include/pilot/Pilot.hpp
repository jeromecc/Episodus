#ifndef PILOT_H
#define PILOT_H

/*//////////////////////////////////////////////////////*/
/*														*/
/*	Created by:	Dominique Sauquet   					*/
/*  Created on:	May 2003   								*/
/*														*/
/*//////////////////////////////////////////////////////*/

#include <pilot/JavaSystem.hpp>

class _CLASSESGBD Pilot
/*********************/
{
  protected:

	  static jclass classPilot ;
    jobject newPilot ;

  public:

	  static int Init(const char* config) ;
    //return the number of services
	  static int AddServices(const char* serviceFile) ;
    //return the number of services
	  static int AddServicesFromDirectory(const char* serviceDir) ;
    //return the number of services
    static int InitFromResource(const char* resourceName) ;

    static void Trace(const string &sMsg) ;

	  Pilot() ;
	  ~Pilot() ;
	  char* Execute(char* inputData, bool ifDOMElement) ;
};

#endif // PILOT_H

