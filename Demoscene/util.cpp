#include <iostream>
#include <fstream>
#ifdef WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif
#include "util.h"


void devError(const char* pFileName, unsigned int line, const char* pError)
{
#ifdef WIN32
	char msg[1000];
	_snprintf_s(msg, sizeof(msg), "%s:%d: %s", pFileName, line, pError);
	MessageBoxA(NULL, msg, NULL, 0);
#else
	fprintf(stderr, "%s:%d: %s\n", pFileName, line, pError);
#endif    
}