#include "chat_server.h"
/**
* Send the message <message> to all socket present in the list pointed by <socket_list_pt>.
* All messages are preceded by the <nickname> of the client who did something.
* If the message is something that the client with <nickname> says, the variable <says> must be 1, else <says> must be 0.
*/
void send_all(List* socket_list_pt, char* nickname, char* message, int says){
  
  char result[MAXBUFSIZE];
  strcpy(result, "");
  strcat(result, nickname);
  strcat(result, " ");
  strcat(result, !says ? "" : CHATSAYING);
  strcat(result, message);
  Item* i;
  for (i = *socket_list_pt; i != NULL; i = i->next) {
    sending(&i->data, result, strlen(result));
  }
}
/**
* @threadfunction
* Handle a client a share all his informations with others connected clients.
* First, the function ask the nickname of the client.
* Then call to function <handle_client>.
*/
void* handle_sharing(void* data){
  ShareData* share_data_pt = (ShareData*)data;
  int* clsock_pt = &share_data_pt->clsockfd;
  SockaddrIn* client_addr_pt = &share_data_pt->client_addr;
  List* socket_list_pt = share_data_pt->socket_list_pt;
  char nickname[MAXNNSIZE];
  int connected = 1;
  receiving(nickname, clsock_pt); // ask for client nickname
  connected = !(strlen(nickname)) ? 0 : 1;
  if(connected){
    append_list(socket_list_pt, *clsock_pt);
    handle_client(nickname, clsock_pt, socket_list_pt);
    delete_list(socket_list_pt, *clsock_pt);
    send_all(socket_list_pt, nickname, "disconnected", 0);
    printf("[%s][%s] %s disconnected\n", SERVERNAME, strtime(), nickname);
  }else{
    printf("[%s][%s] Client %s disconnected before giving nickname \n", SERVERNAME, strtime(), inet_ntoa(client_addr_pt->sin_addr));
  }
  /* the client is disconnected here */
  close(*clsock_pt);
  free(share_data_pt);
  pthread_exit(0);
}

void start_sharing_thread(pthread_t* thread_pt, int clsockfd, SockaddrIn client_addr,List* socket_list_pt){
  ShareData* share_data_pt = (ShareData*)malloc(sizeof(ShareData));
  share_data_pt->clsockfd = clsockfd;
  share_data_pt->client_addr = client_addr;
  share_data_pt->socket_list_pt = socket_list_pt;
	pthread_create(thread_pt, NULL, handle_sharing, (void*)share_data_pt);
}
/**
* Handle a client while he is connected to the server.
* The client nickname is <nickname> and the associate socket, his the socket pointed by <clsock_pt>.
* Handling means that the server will wait for the client to send message, and then send this message to all connected clients.
*/
void handle_client(char* nickname, int* clsock_pt, List* socket_list_pt){
  char message[MAXMESSAGESIZE];
  ClientData client_data;
	strcpy(client_data.nickname, nickname);
  send_all(socket_list_pt, client_data.nickname, "is connected", 0);
  printf("[%s][%s] %s is connected\n", SERVERNAME, strtime(), client_data.nickname);
  int connected = 1;
  receiving(message, clsock_pt);
  connected = !(strlen(message)) ? 0 : 1;
  while(connected){
    printf("[%s][%s] %s %s %s\n", SERVERNAME, strtime(), client_data.nickname, CHATSAYING, message);
    send_all(socket_list_pt, client_data.nickname, message, 1);
    receiving(message, clsock_pt);
    connected = !(strlen(message)) ? 0 : 1;
  }
}
void running_message(){
  printf("%s Server is running ..\n", APPNAME);
  fflush(stdout);
}

void binding(int* sock_pt, SockaddrIn* server_addr_pt){
  if(bind(*sock_pt, (Sockaddr*)server_addr_pt, sizeof(Sockaddr)) == -1){
    exitbecause("chat_server", "binding"); 
  }
}

void listening(int* sock_pt){
  if(listen(*sock_pt, BACKLOG) == -1){
    exitbecause("chat_server", "listening");
  }
}
void accepting(int* new_pt, int* sock_pt, SockaddrIn* client_addr_pt){
  unsigned int sin_size = sizeof(SockaddrIn);
  *new_pt = accept(*sock_pt, (Sockaddr*)client_addr_pt, &sin_size);
  if(*new_pt == -1){
    exitbecause("chat_server", "accepting");
  }
}

