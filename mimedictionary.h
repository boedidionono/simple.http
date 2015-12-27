#ifndef __MIMEDICT
#define __MIMEDICT
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "debug.h"

class mimedict
{
	private:
		int read();
		typedef struct
		{
			char *type;
			char *extension;
		} mimeStruct;
		mimeStruct *mimeList;
		char *filePath;
		bool debugMode;
		size_t extNumber;
		
	public:
		mimedict(const char *path);
		char *getType(const char *extension);
		virtual ~mimedict()
		{
			
		}
};
#endif
