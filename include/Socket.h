#ifndef SOCKET_H
#define	SOCKET_H

#ifdef __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdio>
#include <cstring>	
#include <cstdlib>
#include <unistd.h>
#include <cctype>
#include <strings.h>

#endif
#ifdef _WIN32
#include <WinSock2.h>
#include <windows.h>

#define perror(s) \
		fprintf(stderr,"\n%s %d\n", s, WSAGetLastError())

#pragma comment( lib, "wsock32.lib" )
#endif

#include <string>
#include <iostream>
#include <string.h>

using namespace std;


/** All of the #ifdef macros must be mantained, in order
to mantain portability of code between Windows and Linux. */

/** TODO: Add MacOS #defines */

#define MAX_MSG_LENGTH 255

class Socket
{
private:
	string address;
	unsigned int port;
#ifdef __linux__
	unsigned int socketDescriptor;
#elif defined _WIN32
	SOCKET socketDescriptor;
#endif
	struct sockaddr_in server;
	struct hostent *hp;

public:
	Socket();
	Socket(string address, unsigned int port);
	void open(string address, unsigned int port);
	void sendMsg(string msg);
	string readMsg(bool nonblock = true);
	void disconnect();
};

#endif	/* SOCKET_H */

