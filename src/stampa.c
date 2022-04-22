/*this file prints all instructions written in a .cvm file, followinf the format INSTRUCTION PARAMETER1 PARAMETER2*/
#include "../include/read.h"
#include <stdlib.h>
#include <stdio.h>

void print(char *filename){

  int *programma;
  int i=0;
  int dim=0;

  programma=read(filename,&dim);

  while(i<dim){
    printf("[ %d] ",i);
    switch(programma[i]){
      /*HALT*/
      case 0:
        printf("HALT\n");
        i++;
        break;
      /*DISPLAY*/
      case 1:
        printf("DISPLAY R%d\n",programma[i+1]);
        i=i+2;
        break;
      /*PRINT_STACK*/
      case 2:
        printf("PRINT_STACK %d\n",programma[i+1]);
        i=i+2;
        break;
      /*PUSH*/
      case 10:
        printf("PUSH R%d\n",programma[i+1]);
        i=i+2;
        break;
      /*POP*/
      case 11:
        printf("POP R%d\n",programma[i+1]);
        i=i+2;
        break;
      /*MOV*/
      case 12:
        printf("MOV R%d %d\n",programma[i+1],programma[i+2]);
        i=i+3;
        break;
      /*CALL*/
      case 20:
        printf("CALL %d\n",programma[i+1]);
        i=i+2;
        break;
      /*RET*/
      case 21:
        printf("RET\n");
        i++;
        break;
      /*JMP*/
      case 22:
        printf("JMP %d\n",programma[i+1]);
        i=i+2;
        break;
      /*JZ*/
      case 73:
        printf("JZ %d R%d\n",programma[i+1],programma[i+2]);
        i=i+3;
        break;
      /*JPOSß*/
      case 74:
        printf("JPOS %d R%d\n",programma[i+1],programma[i+2]);
        i=i+3;
        break;
      /*JNEG*/
      case 75:
        printf("JNEG %d R%d\n",programma[i+1],programma[i+2]);
        i=i+3;
        break;
      /*ADD*/
      case 80:
        printf("ADD R%d R%d R%d\n",programma[i+1],programma[i+2],programma[i+3]);
        i=i+4;
        break;
      /*SUB*/
      case 81:
        printf("SUB R%d R%d R%d\n",programma[i+1],programma[i+2],programma[i+3]);
        i=i+4;
        break;
      /*MUL*/
      case 82:
        printf("MUL R%d R%d R%d\n",programma[i+1],programma[i+2],programma[i+3]);
        i=i+4;
        break;
      /*DIV*/
      case 83:
        printf("DIV R%d R%d R%d\n",programma[i+1],programma[i+2],programma[i+3]);
        i=i+4;
        break;
      }
    }
  free(programma);
}
