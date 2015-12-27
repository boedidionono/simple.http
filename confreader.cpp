#include "confreader.h"


confreader::confreader(const char *filePath, bool debug)
{
	debugMode = debug;
	actual_confNumber = 0;
	configPath = (char*)malloc(sizeof(filePath));
	memcpy(configPath, filePath, strlen(filePath));
}

int confreader::read()
{
	FILE *fileDes;
	char * line = NULL;
	size_t lineLen = 0;
	ssize_t read;
	fileDes = fopen(configPath, "r");
	int paramPtr = 0;
	if (fileDes == NULL)
	{
		DBG("no configuration file found, using default setting", debugMode);
		return 1;
	}
	while ((read = getline(&line, &lineLen, fileDes)) != -1)
	{
		if(line[0] != ';' && line[0] != '#' && read > 1)
		{
			bufferparameter[paramPtr] = (char*)malloc(read-1);
			memcpy (bufferparameter[paramPtr], line, read-1);
			paramPtr++;
		}
	}
	actual_confNumber = paramPtr;

	fclose(fileDes);
	if (line)
	   free(line);
	return 0;
}

char *confreader::getParameter(const char *parameter)
{
	char *value = NULL;
	for(int i = 0; i < PARAMETER_NUMBER; i++)
	{
		if(strstr(bufferparameter[i], parameter) != NULL)
		{
			size_t offset = strlen(bufferparameter[i]) - strlen(parameter) - 1;
			value = (char*) calloc(offset, sizeof(char));
			memcpy(value, bufferparameter[i]+strlen(parameter)+1, offset);
			DBG(value, debugMode);
			break;
		}
	}
	return value;
}
