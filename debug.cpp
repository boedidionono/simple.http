#include "debug.h"

void DBG(const char *txt, bool d)
{
	if (d)
		fprintf(stdout, "%s\n", txt);
}
