#include "../include/execute.h"
#include "../include/read.h"
#include "../include/print.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
  if(argc!=3)
    printf("Non conventional parameters number. Parameters must be 2. First: execute or print. Second: filename.cvm.\n");
  else if(!strncmp(&(*argv[argc-2]),"execute", 6)){
    esegui(&(*argv[argc-1]));
  }else if(!strncmp(&(*argv[argc-2]),"print", 6))
      stampa(&(*argv[argc-1]));
      else{
        printf("Unknown command\n");
      }

  return 0;
}
