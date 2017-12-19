#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);


static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("luigi");
    exit(0);
  }
}

int main() {
  int to_client;
  int from_client;
  char input[BUFFER_SIZE];
  int fo;
  
  while(1){
    fo = fork();
    if(fo == 0){
      printf("In child");
      subserver(server_connect(&to_client));
    }
    else{
      printf("In parent");
      wait(0);
      printf("Waiting for server");
    }
    }

  return 0;
}

void subserver(int from_client) {
  while(read(from_client, input, sizeof(input))){
    printf("Text Received: %s\n", input);
    process(input)
  }
  write(to_client, input, sizeof(input));
}

void process(char * s) {
  while((*s = toupper(*s))){
    s++;
  }
}
