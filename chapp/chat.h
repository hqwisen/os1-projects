#ifndef CHAT_H_
#define CHAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>

#define CHATPORT 5555
#define BACKLOG 20
#define MAXBUFSIZE 2000
#define MAXNNSIZE 20
#define APPNAME "Chapp"
#define SERVERNAME "ChappServer"
#define CHATPREFIX ""
#define CHATSAYING "says: "
#define MAXMESSAGESIZE 1000

typedef struct sockaddr_in SockaddrIn;
typedef struct sockaddr Sockaddr;
typedef struct hostent Hostent;
typedef struct in_addr InAddr;
typedef unsigned long ip_t;

char buffer[MAXBUFSIZE];

char* strtime();
void exitbecause(char* exitmessage, char* source);
void purgestdin();
void purgebuffer();
void userinput(char* input, int length);
void receiving(char* message, int* sock_pt);
void sending(int* sock_pt, char* message, int length);
void set_host(Hostent** he, char* hostname);
void set_server_default(SockaddrIn* server_addr_pt);
void set_server_hostent(SockaddrIn* server_addr_pt, Hostent* he);
void set_server_hostname(char* hostname, SockaddrIn* server_addr_pt);
void set_server(SockaddrIn* server_addr_pt);
void set_default_option(int* sock_pt);
void create_socket(int* sock_pt);

#endif /* CHAT_H_ */

