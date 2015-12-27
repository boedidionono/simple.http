#ifndef M_SERVER
#define M_SERVER

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "version.h"
#include "mimedictionary.h"

class server
{
	public :
	server(int port, bool d);
	ssize_t accept_and_get();
	char *get_buffer();
	void dispose_connection();
	int return_file(char *path);
	uint32_t get_clientAddress();
	virtual ~server()
	{
		printf("freeing socket\n");
		close(newsock_fileDes);
		close(sock_fileDes);
	}
	
	private:
	char *getExtension(char *file);
	bool debugMode;
	struct timeval tv;
	int retval;
	int sock_fileDes, newsock_fileDes, stats;
	unsigned int clienLen;
	char buffer[256];
	struct sockaddr_in serverAddress, clientAddress;
	bool connected;
	mimedict *myMime;
};
#endif
