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

void Socket::open(string address, unsigned int port, bool nonblock)
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

string Socket::readMsg()
{
	char msg[MAX_MSG_LENGTH];
	memset(msg,0,MAX_MSG_LENGTH*sizeof(char));

	if (recv(socketDescriptor, msg, MAX_MSG_LENGTH, 0) < 0)
	{
		cout << "Answer not ready!" << endl;
		return "";
	}
	else
	{
		cout << msg << endl;
		if (msg == "\n")
			return "";
		else
			return string(msg);
	}
}

void Socket::disconnect()
{
#ifdef __linux__
	close(socketDescriptor);
#elif defined _WIN32
	closesocket(socketDescriptor);
#endif
}

int setNonBlocking(unsigned int fd)
{
#ifdef __linux__
	int flags;

	if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
		flags = 0;
	return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
	u_long iMode=1;
	return ioctlsocket(fd,FIONBIO,&iMode);
#endif
}