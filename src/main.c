#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/network.h"
#include "../include/server.h"

// set up signal handler
void INThandler(int);

int stop = 0;

int main(int argc, char *argv[]) {

  unsigned short port;

  // check for command line args
  if (argc == 2) {
    sscanf(argv[1], "%hu", &port);

    if (port < 1024) {
      fprintf(stderr, "\033[1;31mError\033[0;37m: Invalid port number "
                      ">:(\n\033[0;90mPlease specify a "
                      "port number greater than 1024.\033[0;37m\n");
      exit(1);
    }

  } else {
    printf("\033[1;33mWarning\033[0;37m: No port specified, using a random "
           "avalible port.\n");
    port = 0;
  }

  // set up signal handler
  signal(SIGINT, INThandler);

  // run the server!
  int status = server(port, (int *)&stop);

  printf("\nFSServer has quit. %s\033[0;37m\n",
         status == 1 ? "\033[1;31m[EXIT_ERROR]" : "\033[1;32m[EXIT_SUCCESS]");

  exit(status == 1 ? 1 : 0);
}

void INThandler(int sig) {
  signal(sig, SIG_IGN); // not sure what this does
  printf("\n\033[0;90mQuitting...\033[0;37m\n");
  // tell the other function to clean up memory and stuff
  stop = 1;
}
