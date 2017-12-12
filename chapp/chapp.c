#include "chat_client.h"

int main(int argc, char *argv[]){
  int sockfd;
  char nickname[MAXNNSIZE];
  char message[MAXMESSAGESIZE];
  char* hostname;
  SockaddrIn server_addr;
  if(argc != 2){
    exitbecause("chapp", "Host name is not given !");
  }
  /*Try to connect to the server*/
  hostname = argv[1];
  set_server_hostname(hostname, &server_addr);
  create_socket(&sockfd);  
  connecting(&sockfd, &server_addr);  
  /* Welcome the user (and retrieve the nickname) */
  welcome(nickname);
  /* Sending nickname to the server */
  sending(&sockfd, nickname, strlen(nickname));
  printf("Your are now in the %sRoom !\n", APPNAME);
  /* Start the thread who will receive all messages send by the server */
  pthread_t receiving_thread;
  start_receiving_thread(&receiving_thread, &sockfd);
  /*Start asking user messages to send to the server*/
  while(1){
    userinput(message, MAXMESSAGESIZE);
    sending(&sockfd, message, strlen(message));
  }
  pthread_cancel(receiving_thread);
  close(sockfd);
  return EXIT_SUCCESS;
}

