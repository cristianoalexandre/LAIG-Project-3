#ifndef SOCKET_H
#define	SOCKET_H

#ifdef __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <sys/file.h>
#include <features.h>
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

#endif

#include <string>
#include <iostream>
#include <cstdlib>
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
	unsigned int socketDescriptor;

public:
	Socket();
	Socket(string address, unsigned int port);
	void open(string address, unsigned int port, bool nonblock = true);
	void sendMsg(string msg);
	string readMsg();
	void disconnect();
};

int setNonBlocking(unsigned int fd);

#endif	/* SOCKET_H */

