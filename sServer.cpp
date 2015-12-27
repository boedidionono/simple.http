#include "sServer.hpp"

server::server(int port, bool d)
{
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	debugMode = d;
	
	//1. create socket
	sock_fileDes = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fileDes < 0)
	{
		perror("ERROR opening socket");
		exit(1);
	}
	//AF_INET atau AF_UNIX ----- SOCK_STREAM ->untuk TCP) | SOCK_DGRAM ->untuk UDP
	
	bzero((char *) &serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	//2. bind socket
	if (bind(sock_fileDes, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
	{
		perror("ERROR on binding");
		exit(1);
	}
	
	//3. listen 
	listen(sock_fileDes, 10); //10=number connection that can be waiting while the process is handling a particular connection
	connected = false;
}

ssize_t server::accept_and_get()
{
	if(!connected)
	{
		//4. Accept
		clienLen = sizeof(clientAddress);
		newsock_fileDes = accept(sock_fileDes, (struct sockaddr *) &clientAddress, &clienLen);
		if (newsock_fileDes < 0){
			perror("ERROR on accept");
			return -1;
		}
		connected = true;
	}
	bzero(buffer, 256);
	//5. Read data non block
	stats = recv(newsock_fileDes, buffer, 255, MSG_DONTWAIT);
	return stats;
}

int server::return_file(char *path)
{
	char buf[128];
	char ppath[100];
	sprintf(ppath, "%s", path);
	FILE * fd;
	char * line = NULL;
	size_t lineLen = 0;
	ssize_t read;

	fd = fopen(ppath, "r");
	if (fd == NULL)
	{
		sprintf(buf,"HTTP/1.1 404 Not Found\r\nServer: boedh's webServer 0.1b\r\nConnection: close\r\nContent-Type: text/html\r\n\r\n");
		write(newsock_fileDes, buf, 102);
		sprintf(buf,"<html><title>Error 404 Not Found</title><center><h1>Error 404 Not Found</h1> <br/><hr>Boedh Web Server/%s</center></html>", VERSION);
		write(newsock_fileDes, buf, 128);
		return -1;
	}
	sprintf(buf,"HTTP/1.1 200 OK\r\nServer: boedh's webServer 0.1b\r\nConnection: close\r\nContent-Type: text/html\r\n\r\n");
	write(newsock_fileDes, buf, 95);
	
	while ((read = getline(&line, &lineLen, fd)) != -1) {
		write(newsock_fileDes, line, read);
	}

	fclose(fd);
	if (line)
	   free(line);
	return 0;
}

char *server::get_buffer()
{
	return buffer;
}

void server::dispose_connection()
{
	close(newsock_fileDes);
	connected = false;
}

uint32_t server::get_clientAddress()
{
	return clientAddress.sin_addr.s_addr;
}
