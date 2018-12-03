#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define SEND_USER_ACTION 'u'
#define SEND_PASSWORD_ACTION 'p'
#define LOGIN_RESPONSE_ACTION 'r'

#define SUCCESS "success"
#define FAILED "failed"
#define OK "OK"
#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 40000 /*port*/ 

char username[20];
char password[20];
char *sendUsername(){
  printf("%s\n","Nhap username" );
  scanf("%s",username);
  return username;
}

char *sendPassword(){
  printf("%s\n","Nhap password" );
  scanf("%s",password);
  return password;
}

void clear(char * s){
  memset(s, 0, strlen(s));
}
int
main(int argc, char **argv) 
{
 int sockfd, responseLength;
 struct sockaddr_in servaddr;
 char sendline[MAXLINE], recvline[MAXLINE];
	
 //basic check of the arguments
 //additional checks can be inserted
 if (argc !=2) {
  perror("Usage: TCPClient <IP address of the server"); 
  exit(1);
 }
	
 //Create a socket for the client
 //If sockfd<0 there was an error in the creation of the socket
 if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
  perror("Problem in creating the socket");
  exit(2);
 }
	
 //Creation of the socket
 memset(&servaddr, 0, sizeof(servaddr));
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr= inet_addr(argv[1]);
 servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order
	
 //Connection of the client to the socket 
 if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
  perror("Problem in connecting to the server");
  exit(3);
 }
	char * response;
 while (1) {
  clear(sendline);
	sendUsername();
  sprintf(sendline, "%c_%s", SEND_USER_ACTION, username);
  send(sockfd, sendline, strlen(sendline), 0); 
  clear(recvline);

  recv(sockfd, recvline, MAXLINE,0);
  response =  recvline + 2;


  if(strcmp("OK", response) == 0){
    sendPassword();
      clear(sendline);
        sprintf(sendline, "%c_%s", SEND_PASSWORD_ACTION, password);
    send(sockfd, sendline, strlen(sendline), 0);  
  }
  clear(recvline);
  recv(sockfd, recvline, MAXLINE,0);
  response =  recvline + 2;
  puts(response);
}
 exit(0);
}