/*
 * This program creates a stream socket and initiates a connection with the
 * server given in the command line.
 * Messages are read from stdin and sent over the connection
 * until "quit" is typed in.
 * Then the socket is closed, ending the connection, and the program terminates.
 * In order to also terminate the server, "quit!" should be typed.
 * Command line:
 *	simple_cl hostname portnumber
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>	// for memcpy()...
#include <stdlib.h>	// for atoi()...
#include <unistd.h>	// for gethostname()...
#include <ctype.h>	// for tolower()...
#include <strings.h>

#define BUFS	1024
#define NAMS	64

#define GAME_SERVER 127.0.0.1
#define INITIAL_PORT 6001

char nclient[NAMS];

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in server;
    struct hostent *hp;
    char buf[BUFS];

    if (argc != 3)
    {
        fprintf(stderr, "\nUsage:\t %s hostname portnumber\n\n", argv[0]);
        exit(1);
    }

    /* Create socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("Opening stream socket");
        exit(1);
    }

    /* Connect socket using server name indicated in the command line */
    server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);
    if (hp == NULL)
    {
        perror("Trying to get host by name");
        exit(2);
    }
    memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
    server.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *) &server, sizeof server) < 0)
    {
        perror("Connecting stream socket");
        exit(1);
    }

    /* Get data from stdio and send through socket */
    for (;;) /* Repeat until "quit" is received */
    {
        fgets(buf, sizeof (buf), stdin);
        if (write(sock, buf, strlen(buf) + 1) < 0)
            perror("Writing on stream socket");
        // Time to finish?
        if (!strcasecmp(buf, "quit\n") || !strcasecmp(buf, "quit!\n"))
            break; // let's!
    }
    close(sock);
    exit(0);
} /* main */
