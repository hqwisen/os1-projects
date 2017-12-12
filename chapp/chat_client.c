#include "chat_client.h"

/**
* @threadfunction
* Handle all messages that the server send to us.
* The messages are printed with the reception time.
* If a connection problem appears, the thread stops.
*/
void* handle_receiving(void* data){
  int* sock_pt = (int*)data;
  char message[MAXBUFSIZE];
  receiving(message, sock_pt);
  int crashed = !(strlen(message)) ? 1 : 0;
  while(!crashed){
    printf("[%s] %s\n", strtime(), message);
    strcpy(message, "");
    receiving(message, sock_pt);
    crashed = !(strlen(message)) ? 1 : 0;

  }
  printf("%s crashed\n", SERVERNAME);
  exit(EXIT_FAILURE);
}

void start_receiving_thread(pthread_t* thread_pt, int* sock_pt){
	pthread_create(thread_pt, NULL, handle_receiving, (void*)sock_pt);
}

/**
* Welcome the user.
* Ask to his nickname, and put it in the string <nickname>.
*/
void welcome(char* nickname){
  printf("Welcome to the %s application !\n", APPNAME);
  printf("To start chatting please enter your nickname");
  printf(" (%d character max):\n", MAXNNSIZE);
  userinput(nickname, MAXNNSIZE);
  while(!strlen(nickname)){
    printf("Enter a nickname please !\n");
    userinput(nickname, MAXNNSIZE);
  }
  fflush(stdout);
}

void connecting(int* sock_pt, SockaddrIn* server_addr_pt){
  if(connect(*sock_pt, (Sockaddr *)server_addr_pt, sizeof(Sockaddr)) == -1){
    printf("Connection to the %s is impossible\n", SERVERNAME);
    exitbecause("chat_client", "connecting");
  }
}

