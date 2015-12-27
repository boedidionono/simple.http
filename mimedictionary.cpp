#include "mimedictionary.h"

mimedict::mimedict(char *path)
{
	filePath = (char*) calloc(strlen(path), sizeof(char));
	memcpy(filePath, path, strlen(path));
}

void mimedict::read()
{
	FILE 
}
