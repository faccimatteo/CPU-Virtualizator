/*This file let us read all instructions written inside a cvm file*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*turn n ascii character into an integer number*/
int getInt(char numero){
  return numero-'0';
}

int* read(char *filename,int *dim){
  char line[100];
  int value=0, dimension=0;
  int *program;
  int i=0,j=0,count=0;
  FILE* scanner=fopen(filename,"r");


  if(scanner==NULL){
    printf("Cannot open file, %s has not been found\n",filename);
    exit(0);
    }else{
      /*fgets to take the first line to get instruction line number. 
      If no number is specified, search is done until a number is not found*/
      do{
        fgets(line,100,scanner);
        sscanf(line,"%d",&dimension);
      /*loop until a valid dim has not been set (!= from 0)*/
      }while(dimension==0);

      *dim=dimension;

      i=0;
      /*dynamic allocated array of integer with dimension specified by the number of line in the file*/
      program=(int*)malloc(sizeof(int)*(dimension));

      if(program!=NULL){

        /*initialyzing program array*/
        for(i=0;i<dimension;i++)
          program[i]=0;

        /*assigning to program array all the instruction of the file*/
        while(fgets(line,100,scanner) != NULL){/*loop until end file detection*/
          i=0;
          /*checking correctness of file length*/
          if(j>(dimension-1)){
            printf("File contains more instructions than than actually specified in the file (%d).\n",dimension);
            exit(0);
          }
          /*if first character is not between 0 and 9 or if it's different from ; or ' ' then return an error*/
          if((getInt(line[0])<0 || getInt(line[0])>9) && line[0]!=';' && line[0]!='-' && line[0]!=' ' && line[0]!='\n' && line[0]!='\r'){
            printf("Error line number %d:\n",count);
            printf("File lines have to be formed just by instructions or from comments (line starting with ;)\n");
            exit(0);
          }
          i=0;
          /*checking if the character is between 0 e 9, space, '-', \n o \r*/
          while((getInt(line[i])>=0 && getInt(line[i])<=9) || line[i]=='-' || line[i]==' '){
            if(sscanf(line,"%d",&program[j]))
              value=1;
            sscanf(line,"%d",&program[j]);
            i++;/*ready to scan the new line*/
          }

          if(value)
            j++;
          count++;/*track error line*/
          value=0;
        }

        /*checking for all instructions*/
        /*if jump is detected, must not be bigger than array's size*/
        i=0;
        while(i<dimension){
          switch(program[i]){
            /*HALT*/
            case 0:
              i++;
              count=i;
              break;
            /*DISPLAY*/
            case 1:
              i=i+2;
              count=i;
              break;
            /*PRINT_STACK*/
            case 2:
              i=i+2;
              count=i;
              break;
            /*PUSH*/
            case 10:
              i=i+2;
              count=i;
              break;
            /*POP*/
            case 11:
              i=i+2;
              count=i;
              break;
            /*MOV*/
            case 12:
              i=i+3;
              count=i;
              break;
            /*CALL*/
            case 20:
              if((program[i+1]>i && program[i+1]>(dimension-1)) || ((program[i+1]<i) && program[i+1]<0)){
                printf("CALL: value for jump to subroutine not valid. %d is not an accepted call.\n",program[i+1]);
                exit(0);
              }
              i=i+2;
              count=i;
              break;
            /*RET*/
            case 21:
              i++;
              count=i;
              break;
            /*JMP*/
            case 22:
              if((program[i+1]>i && program[i+1]>(dimension-1)) || ((program[i+1]<i) && program[i+1]<0)){
                printf("JMP: value for jump instruction not valid. %d is not an accepted value.\n", program[i+1]);
                exit(0);
              }
              i=i+2;
              count=i;
              break;
            /*JZ*/
            case 73:
              if((program[i+1]>i && program[i+1]>(dimension-1)) || ((program[i+1]<i) && program[i+1]<0)){
                printf("JZ: value for jump instruction not valid. %d is not an accepted value.\n", program[i+1]);
                exit(0);
              }
              i=i+3;
              count=i;
              break;
            /*JPOS*/
            case 74:
              if((program[i+1]>i && program[i+1]>(dimension-1)) || ((program[i+1]<i) && program[i+1]<0)){
                printf("JPOS: value for jump instruction not valid. %d is not an accepted value.\n", program[i+1]);
                exit(0);
              }
              i=i+3;
              count=i;
              break;
            /*JNEG*/
            case 75:
              if((program[i+1]>i && program[i+1]>(dimension-1)) || ((program[i+1]<i) && program[i+1]<0)){
                printf("JNEG: value for jump instruction not valid. %d is not an accepted value.\n", program[i+1]);
                exit(0);
              }
              i=i+3;
              count=i;
              break;
            /*ADD*/
            case 80:
              i=i+4;
              count=i;
              break;
            /*SUB*/
            case 81:
              i=i+4;
              count=i;
              break;
            /*MUL*/
            case 82:
              i=i+4;
              count=i;
              break;
            /*DIV*/
            case 83:
              i=i+4;
              count=i;
              break;
            default:
              printf("File contains not valid instruction. Line: %d Instruction: %d\n",count,program[i]);
              exit(0);
            }
          }
    }else{
      printf("Malloc failed");
      exit(0);
    }

    return program;
    }

}
