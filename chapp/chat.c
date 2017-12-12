#include "chat.h"
/**
* @return the time as a HH:MM:SS string
*/
char* strtime(){
  static char str[10];
  char tmp[2];
  time_t rawtime;
  time(&rawtime);
  struct tm* timeinfo =  localtime(&rawtime);
  sprintf(tmp, "%d", timeinfo->tm_hour);
  strcpy(str, tmp);
  strcat(str, ":");
  sprintf(tmp, "%d", timeinfo->tm_min);
  strcat(str, tmp);
  strcat(str, ":");
  sprintf(tmp, "%d", timeinfo->tm_sec);
  strcat(str, tmp);
  return str;
}

/**
* exit the program and show the source exit, a given exit message, and the perror
*/
void exitbecause(char* source, char* exitmessage){
  char message[100] = "";
  strcat(message, source);
  strcat(message, "  →  ");
  strcat(message, exitmessage);
  strcat(message, "\nperror");
  perror(message);
  exit(EXIT_FAILURE);
}

void purgestdin(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

void purgebuffer(){
  strcpy(buffer, "");
}

/**
* scan the characters entered by the user, and put it in <input>.
* the max length of input is <length>.
*/
void userinput(char* input, int length){
  printf("%s", CHATPREFIX);
  fflush(stdout);
  if(fgets(input, length+1, stdin)){
    // removing the \n
    char *p = strchr(input, '\n');
    if (p){
      *p = '\0';
    }else{
      purgestdin(); // purge if to much characters it the buffer
    }
  }else{
    purgestdin();
    exitbecause("chat","userinput");
  }
}

/**
* Wait to receive a message from the socket pointed by <sock_pt>.
* If there is a connection problem with the socket, the length of <message> will be 0.
*/
void receiving(char* message, int* sock_pt){
  int numbytes;
  numbytes = recv(*sock_pt, buffer, MAXBUFSIZE, 0);
  if(numbytes == -1){
    numbytes = 0;
  }else{
    strncpy(message, buffer, numbytes);
  }
  message[numbytes] = '\0';
}

/**
* Send the message <message> with length <length>.
*/
void sending(int* sock_pt, char* message, int length){
  if(send(*sock_pt, message, length, 0) == -1){
    exitbecause("chat", "sending");
  }
}

void set_host(Hostent** he, char* hostname){
  *he = gethostbyname(hostname);
  if(*he == NULL){
    exitbecause("chat", "set_host");
  }
}

void set_server_default(SockaddrIn* server_addr_pt){
  server_addr_pt->sin_family = AF_INET;         // host byte order
  server_addr_pt->sin_port = htons(CHATPORT);     // short, network byte order
  memset(&(server_addr_pt->sin_zero), '\0', 8); // zero the rest of the struct
}

void set_server_hostent(SockaddrIn* server_addr_pt, Hostent* he){
  set_server_default(server_addr_pt);
  server_addr_pt->sin_addr = *((InAddr*)he->h_addr);
}

void set_server_hostname(char* hostname, SockaddrIn* server_addr_pt){
    Hostent *he;
    set_host(&he, hostname);
    set_server_hostent(server_addr_pt, he);    
}

void set_server(SockaddrIn* server_addr_pt){
  ip_t sockip = INADDR_ANY;
  set_server_default(server_addr_pt);
  server_addr_pt->sin_addr.s_addr = sockip;
}

void set_default_option(int* sock_pt){
  int yes = 1;
  if(setsockopt(*sock_pt, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
    exitbecause("chat", "set_default_option");
  }
}

void create_socket(int* sock_pt){
  if((*sock_pt = socket(PF_INET, SOCK_STREAM, 0)) == -1){
    exitbecause("chat", "create_socket");
  }
  set_default_option(sock_pt);
}

