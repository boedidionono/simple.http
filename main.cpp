#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "sServer.hpp"
#include "confreader.h"
#include "version.h"
#include "mimedictionary.h"



#define DEFAULT_LISTEN_PORT 46969
int LISTEN_PORT;
char *DOC_ROOT;
bool debugMode=false;
server *m_server;

void exitHandler(int sigNum)
{
	delete m_server;
	exit(0);
}

int main(int argc, char **argv)
{
	signal(SIGINT, &exitHandler);
	signal(SIGKILL, &exitHandler);
	if(argc > 1)
	{
		if(strcmp(argv[1], "-?") == 0)
		{
			printf("Boedh Web Server help\n \t-?\tShow this help text\n\t-d\tEnable Debug mode\n\t-v\tShow this server program version\n");
			exit(0);
		}
		else if(strcmp(argv[1], "-d") == 0)
		{
			debugMode=true;
		}
		else if(strcmp(argv[1], "-v") == 0)
		{
			printf("%s\n", VERSION);
			exit(0);
		}
	}
	
	confreader myConf("server.conf", debugMode);
	myConf.read();
	LISTEN_PORT = atoi(myConf.getParameter("port"));
	DOC_ROOT = myConf.getParameter("root directory");
	bool todoRequest = false;
	m_server = new server(LISTEN_PORT, debugMode);
	char buffer[1024];
	memset(buffer, '\0',sizeof(char)*(1024));
	//sprintf(buffer, "-");
	while(1)
	{
		int length = m_server->accept_and_get();
		if(length > 0)
		{
			todoRequest = true;
			char *buf = m_server->get_buffer();
			for(int i = 0; i < length; i++)
			{
				if(buf[i] == '\r')
					//printf("\\r");
					sprintf(buffer, "%s\\r", buffer);
				else if(buf[i] == '\n')
					//printf("\\n\n");
					sprintf(buffer, "%s\\n", buffer);
				else
					//printf("%c", buf[i]);
					sprintf(buffer, "%s%c", buffer, buf[i]);
			}
		}
		else
		{
			if(todoRequest)
			{
				char fileName[100], *stopptr, *startptr, *tmp;
				DBG(buffer, debugMode);
				startptr = strstr(buffer, "GET");
				if(startptr == NULL)
				{
					todoRequest = false;
					memset(buffer, '\0',sizeof(char)*(1024));
					continue;
				}
				stopptr = strstr(buffer, "HTTP");
				int start = startptr - buffer + 4;
				int stop = stopptr - buffer - 1;
				//fileName = (char*)malloc(sizeof(char)*(stop-start)+1+strlen(DOC_ROOT));
				tmp = (char*)malloc(sizeof(char)*(stop-start)+1);
				memset(tmp, '\0', sizeof(char)*(stop-start)+1);
				memcpy(tmp, &buffer[start], stop-start);
				sprintf(fileName,"%s%s",DOC_ROOT,tmp);
				DBG(fileName, debugMode);
				m_server->return_file(fileName);
				todoRequest = false;
				//free(fileName);
				free(tmp);
				memset(buffer, '\0',sizeof(char)*(1024));
			}
			else
				m_server->dispose_connection();
		}
	}
	return 0;
}
