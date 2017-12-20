#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);


static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("WKP");
    exit(0);
  }
}

int main() {
 
  int from_client;
  int fnum;

  signal(SIGINT, sighandler);
  
  while(1){
    fnum = fork();
    printf("Subserver Process\n");
    from_client = server_setup();
    if(fnum == 0){
      subserver(from_client);
    }
  }

  return 0;
}

void subserver(int from_client) {
  int to_client = server_connect(from_client);
  char input[BUFFER_SIZE];
  
  while(read(from_client, input, sizeof(input))){
    printf("[%d] Text Received: %s\n", getpid(),input);
    process(input);
    write(to_client, input, sizeof(input));
  }

  exit(0);
}

void process(char * s) {
  while((*s = toupper(*s))){
    s++;
  }
}
