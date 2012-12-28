#include "Socket.h"
#ifdef _WIN32

#define _WINSOCKAPI_    // stops windows.h including winsock.h
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>

#define perror(s) \
		fprintf(stderr,"\n%s %d\n", s, WSAGetLastError())

#pragma comment( lib, "wsock32.lib" )

#endif

Socket::Socket()
{
}

Socket::Socket(string address, unsigned int port)
{
	open(address, port);
}

void Socket::open(string address, unsigned int port)
{
	struct sockaddr_in server;
	struct hostent *hp;

#ifdef __linux__
	socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
#elif defined _WIN32
	WORD wVersionRequested = MAKEWORD(1, 1); // request Winsock 1.1
	WSADATA wsaData;

	if (WSAStartup(wVersionRequested, &wsaData) != 0) //always needed
	{
		cerr << "Wrong version" << endl;
		WSACleanup();
		exit(1);
	}

	socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
#endif

	server.sin_family = AF_INET;
	hp = gethostbyname(address.c_str());

	memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
	server.sin_port = htons(port);
#ifdef __linux__
	connect(socketDescriptor, (struct sockaddr *) &server, sizeof server);
#elif defined _WIN32
	if (connect(socketDescriptor, (struct sockaddr *)&server, sizeof server) == SOCKET_ERROR)
	{
		//perror("");
		cerr << "Problem while connecting to the socket. Please make sure the Prolog game server is running.";
		cin.get();
		exit(-1);
	}
#endif
}

void Socket::sendMsg(string msg)
{
	send(socketDescriptor, msg.c_str(), msg.length() + 1, 0);
}

string Socket::readMsg(bool nonblock)
{
	char msg[MAX_MSG_LENGTH];
	memset(msg,0,MAX_MSG_LENGTH*sizeof(char));

	recv(socketDescriptor, msg, MAX_MSG_LENGTH, 0);

	return string(msg);
}

void Socket::disconnect()
{
#ifdef __linux__
	close(socketDescriptor);
#elif defined _WIN32
	closesocket(socketDescriptor);
#endif
}