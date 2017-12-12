#ifndef CHAT_CLIENT_H_
#define CHAT_CLIENT_H_

#include "chat.h"

void* handle_receiving(void* data);
void start_receiving_thread(pthread_t* thread_pt, int* sock_pt);
void welcome(char* nickname);
void connecting(int*, SockaddrIn* server_addr_pt);

#endif /* CHAT_CLIENT_ */
