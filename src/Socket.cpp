#include "Socket.h"

Socket::Socket()
{
#ifdef _WIN32
    wVersionRequested = MAKEWORD(1, 1);
#endif
}

Socket::Socket(string address)
{
#ifdef _WIN32
    wVersionRequested = MAKEWORD(1, 1);
#endif
    open(address);
}

void Socket::open(string address)
{
#ifdef __linux__
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
#elif defined _WIN32
    WORD wVersionRequested = MAKEWORD(1, 1); // request Winsock 1.1
    WSADATA wsaData;

    // Initialize Winsockets
    if (WSAStartup(wVersionRequested, &wsaData) != 0) //always needed
    {
        cerr << "Wrong version" << endl;
        WSACleanup();
        exit(1);
    }
#endif

    server.sin_family = AF_INET;
    hp = gethostbyname(address.c_str());

    memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);

    server.sin_port = htons(60001);
    connect(socketDescriptor, (struct sockaddr *) &server, sizeof server);
}

void Socket::sendMsg(string msg)
{
    send(socketDescriptor, msg.c_str(), msg.length() + 1, 0);
}

string Socket::readMsg(bool nonblock)
{
    char msg[MAX_MSG_LENGTH];

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