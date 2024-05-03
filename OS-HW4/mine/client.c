#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> /* close */

#define STUDENT_ID_LAST_4_DIGITS 2197
#define PORT1 10000 + STUDENT_ID_LAST_4_DIGITS
#define PORT2 20000 + STUDENT_ID_LAST_4_DIGITS

#define MAX_MSG 100

int main (int argc, char *argv[]) {

  int sd, rc, i, n = 0;
  struct sockaddr_in localAddr, servAddr;
  struct hostent *h;
  char* ip_addr = "127.0.0.1";
  char recvBuff[1024];
  
  if(argc < 4) {
    printf("usage: %s <server> <data1> <data2> ... <dataN>\n",argv[0]);
    exit(1);
  }

  h = gethostbyname("127.0.0.1");
//   if(h==NULL) {
//     printf("%s: unknown host '%s'\n",argv[0],ip_addr);
//     exit(1);
//   }

  servAddr.sin_family = h->h_addrtype;
  memcpy((char *) &servAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
  servAddr.sin_port = htons(PORT1);

  /* create socket */
  sd = socket(AF_INET, SOCK_STREAM, 0);
  if(sd<0) {
    perror("cannot open socket ");
    exit(1);
  }

  /* bind any port number */
  localAddr.sin_family = AF_INET;
  localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  localAddr.sin_port = htons(0);
  
  rc = bind(sd, (struct sockaddr *) &localAddr, sizeof(localAddr));
  if(rc<0) {
    printf("%s: cannot bind port TCP %u\n",argv[0],PORT1);
    perror("error ");
    exit(1);
  }
				
  /* connect to server */
  rc = connect(sd, (struct sockaddr *) &servAddr, sizeof(servAddr));
  if(rc<0) {
    perror("cannot connect ");
    exit(1);
  }


  //send data by client to server

  rc = send(sd,argv[1], strlen(argv[1]) + 1, 0);
  rc = send(sd,argv[2], strlen(argv[2]) + 1, 0);
  rc = send(sd,argv[3], strlen(argv[3]) + 1, 0);
  printf("%s: data%u sent first name: (%s)\n",argv[0],0,argv[1]);
  printf("%s: data%u sent last name: (%s)\n",argv[0],1,argv[2]);
  printf("%s: data%u sent birthday: (%s)\n",argv[0],2,argv[3]);


  //read data from server
  while( (n = read(sd, recvBuff, sizeof(recvBuff) - 1)) > 0){
    recvBuff[n] = 0;
    if(fputs(recvBuff, stdout) == EOF){
        printf("\n Error: Fputs error\n");
    }
  }

  return 0;
  
}

