#ifndef CONFREADER
#define CONFREADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "debug.h"

#define PARAMETER_NUMBER 5

class confreader
{
	private:
	char *bufferparameter[PARAMETER_NUMBER];
	char *configPath;
	bool debugMode;
	int actual_confNumber;
	
	public:
	confreader(const char *filePath, bool debug);
	int read();
	char *getParameter(const char *parameter);
	
};

#endif
