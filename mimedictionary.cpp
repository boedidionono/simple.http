#include "mimedictionary.h"

mimedict::mimedict(const char *path)
{
	filePath = (char*) calloc(strlen(path), sizeof(char));
	memcpy(filePath, path, strlen(path));
	mimeList = (mimeStruct*)malloc(sizeof(mimeStruct)*1);
	read();
}

int mimedict::read()
{
	FILE *fileDes;
	char * line = NULL;
	size_t lineLen = 0;
	ssize_t read;
	fileDes = fopen(filePath, "r");
	size_t count = 0;
	if (fileDes == NULL)
	{
		DBG("no configuration file found, using default setting", debugMode);
		return 1;
	}
	while ((read = getline(&line, &lineLen, fileDes)) != -1)
	{
		if(line[0] != ';' && line[0] != '#' && read > 1)
		{
			mimeStruct ms;
			char *splitted = strtok(line, "\t");
			int ptr = 0;
			while (splitted != NULL)
			{
				switch(ptr)
				{
					case 0:
						ms.type = (char*)calloc(strlen(splitted), sizeof(char));
						memcpy(ms.type, splitted, strlen(splitted));
					break;
					
					case 1:
						ms.extension = (char*)calloc(strlen(splitted), sizeof(char));
						memcpy(ms.extension, splitted, strlen(splitted)-1);
					break;
				}
				splitted = strtok (NULL, "\t");
				ptr++;
			}
			mimeList[count] = ms;
			count++;
			mimeStruct *mimeList_tmp = (mimeStruct*)malloc(sizeof(mimeStruct)*(count));
			memcpy(mimeList_tmp, mimeList, sizeof(mimeStruct)*count);
			mimeList = (mimeStruct*)realloc(mimeList_tmp, sizeof(mimeStruct)*(count+1));
			memcpy(mimeList, mimeList_tmp, sizeof(mimeStruct)*count+1);
		}
	}
	extNumber = count;
	fclose(fileDes);
	if (line)
	   free(line);
	return 0;
}

char *mimedict::getType(const char *extension)
{
	char *tmp = NULL;
	for(size_t i = 0; i < extNumber; i++)
	{
		if(strstr(mimeList[i].extension, extension) != NULL)
		{
			tmp = mimeList[i].type;
			break;
		}
	}
	return tmp;
}
