#ifndef __MIMEDICT
#define __MIMEDICT
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "debug.h"

class mimedict
{
	private:
		read();
		typedef struct
		{
			char *type;
			char *extension;
		} mimeStruct;
		mimestuct *mimeList;
		char *filePath;
		
	public:
		mimedict(char *path);
		char *getType(char *extension);
		virtual ~mimedict()
		{
			
		}
};
#endif
