#ifndef CHAT_SERVER_H_
#define CHAT_SERVER_H_

#include "chat.h"
#include "list.h"

struct client_data_th{
   char nickname[MAXNNSIZE];
};

struct share_data_th{
  int clsockfd;
  SockaddrIn client_addr;
  List* socket_list_pt;
};

typedef struct client_data_th ClientData;
typedef struct share_data_th ShareData;

void* handle_sharing(void* data);
void start_sharing_thread(pthread_t* thread_pt, int clsockfd, SockaddrIn client_addr, List* socket_list_pt);
void send_all(List* socket_list_pt, char* nickname, char* message, int says);
void handle_client(char* nickname, int* clsock_pt, List* socket_list_pt);
void running_message();
void binding(int* sock_pt, SockaddrIn* server_addr_pt);
void listening(int* sock_pt);
void accepting(int* new_pt, int* sock_pt, SockaddrIn* client_addr_pt);

#endif /* CHAT_SERVER_ */
