#include "chat_server.h"
#include "list.h"

int main(){
  int sockfd, new_fd;   // listen on sockfd, new connection on new_fd
  SockaddrIn server_addr;
  SockaddrIn client_addr;
  List socket_list; // List containing clients socket descriptor
  init_list(&socket_list);
  /* Set server informations */
  create_socket(&sockfd);   
  set_server(&server_addr);
  binding(&sockfd, &server_addr);
  /* Show the running message */
  running_message();
  /* Listenning connection */
  listening(&sockfd);
  pthread_t* sharing_thread;
  /* Accepting clients connections and start a thread who will handle him */
  while(1){
    accepting(&new_fd, &sockfd, &client_addr);
    printf("[%s][%s] connection received from client %s\n", SERVERNAME, strtime(), inet_ntoa(client_addr.sin_addr));
    sharing_thread = (pthread_t*)malloc(sizeof(pthread_t));
    start_sharing_thread(sharing_thread, new_fd, client_addr, &socket_list);
  }
  close(sockfd);
  return EXIT_SUCCESS;
}
