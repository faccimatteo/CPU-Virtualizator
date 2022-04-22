/*This file contains all the instructions that our virtual machine can execute*/
#include "../include/read.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int stack[16384]; /*stack array*/
int r[32]; /*registry array*/
unsigned int ip; /*instruction pointer*/
unsigned int sp; /*stack pointer*/

/*HALT: terminate program*/
int HALT(){
  return 0;
}

/*DISPLAY: print on stdout value of the registers (-1: all of them)*/
void DISPLAY(int pos){
  int i;
  /*print all possible registers*/
  if(pos==-1)
    for(i=0;i<32;i++)
      printf("R[%d] %d\n",i,r[i]);
  if(pos>=0 && pos<32){
    printf("R[%d] %d\n",pos,r[pos]);
  }else{
      printf("Value of register not correct. Possible register value 0-31.\n");
      exit(0);
    }
}

/*PRINT_STACK: print on stdout stack values*/
void PRINT_STACK(int valore){
  if(valore<0 && valore>16384){
    printf("PRINT_STACK: choose a value between 0 and 16384.\n");
    exit(0);
  }else
      while(valore){
        printf("Position %d : Value: %d\n",valore,stack[valore]);
        valore--;
      }
}

/*PUSH: insert on the stack the value of the registry defined by pos, and increment the stack pointer. Terminate if stack overflow*/
void PUSH(int pos){
  if(pos>=0 && pos<32){
    if(sp<16384){
      stack[sp]=r[pos];
      sp=sp+1;
    }else{
      printf("Stack is full. Cannot add other element. Stack Overflow\n");
      exit(0);
    }
  }else{
      printf("Position of the registry not correct. Possible registers 0-31\n");
      exit(0);
    }
}

/*POP: copy the value taken from the stack (after the decreasing) in the registry. Terminates if stack underflow*/
void POP(int pos){
  if(pos>=0 && pos<32){
    if(sp>0){
      sp=sp-1; /*when a pop will be executed, the value will override this current position on the stack*/
      r[pos]=stack[sp];
    }else{
      printf("Stack is empty. Cannot delete other elements. Stack Underflow\n");
      exit(0);
    }
  }else{
    printf("Position of the registry not correct. Possible registers 0-31\n");
    exit(0);
  }
}

/*MOV: copy the value in the registry*/
void MOV(int pos,int valore){
  if(pos>=0 && pos<32)
    r[pos]=valore;
    else{
      printf("Position of the registry not correct. Possible registers 0-31\n");
      exit(0);
    }
}

/*JMP: substitute instruction pointer with value in pos*/
void JMP(int pos){
  ip=pos;
}

/*CALL: execute a call to a subroutine. Terminate if stack overflow*/
void CALL(int pos){
  if(sp<16384){
    stack[sp]=(ip+2); /*ip+1 pos is dedicated to subroutine parameter*/
    sp=sp+1;
    JMP(pos);
  }else{
    printf("Stack is full. Cannot add other element. Stack Overflow\n");
    exit(0);
  }
}

/*RET: return from a subroutine. Terminate if stack underflow*/
void RET(){
  if(sp>0){
    sp=sp-1;
    ip=stack[sp]; /*restore the instruction pointer value with the one previously saved before function call */
  }else{
    printf("Stack is empty. Cannot delete other elements. Stack Underflow\n");
    exit(0);
  }
}

/*JZ(JUMP-ZERO): substitute the value of the instruction pointer with the value in pos1 if the value of the registry in pos2 is 0*/
void JZ(int P1,int P2){
  if(P2>=0 && P2<32){
    if(r[P2]==0)
      ip=P1;
      else
        ip=ip+3; /*if condition is not satisfied, passing to the next instruction*/
  }else{
    printf("Position of the registry not correct. Possible registers 0-31\n");
    exit(0);
  }
}

/*JPOS(JUMP-POS): substitute the value of the instruction pointer with the value in pos1 if the value of the registry in pos2 is positive*/
void JPOS(int P1,int P2){
  if(P2>=0 && P2<32){
    if(r[P2]>0)
      ip=P1;
      else
        ip=ip+3; /*if condition is not satisfied, passing to the next instruction*/
  }else{
    printf("Position of the registry not correct. Possible registers 0-31\n");
    exit(0);
  }
}

/*JNEG(JUMP-NEG): substitute the value of the instruction pointer with the value in pos1 if the value of the registry in pos2 is negative*/
void JNEG(int P1,int P2){
  if(P2>=0 && P2<32){
    if(r[P2]<0)
      /*assegno a ip il valore di P1*/
      ip=P1;
      else
        ip=ip+3;/*nel caso in cui la condizione non si sia verificata allora dovrò passare all'istruzione successiva*/
  }else{
    printf("Position of the registry not correct. Possible registers 0-31\n");
    exit(0);
  }
}

/*ADD: integer sum between registry value in pos1 and pos2. The result of the sum is copied in the registry identified by pos3. Terminate if aritmethic overflow or underflow*/
void ADD(int P1,int P2,int P3){
  if((P1>=0 && P1<32)&&(P2>=0 && P2<32)&&(P3>=0 && P3<32)){
    if(((pow(2,31)-1)-r[P2]<r[P1])){
      printf("Aritmethic sum overflow\n");
      exit(0);
    }
    else if((r[P1]<-pow(2,31)-r[P2])){
      printf("Aritmethic sum underflow\n");
      exit(0);
    }else
      r[P3]=r[P1]+r[P2];
  }else{
    printf("Position of the registry not correct. Possible registers 0-31\n");
    exit(0);
  }
}

/*SUB: integer subtraction between registry value in pos1 and pos2. The result of the subtraction is copied in the registry identified by pos3. Terminate if aritmethic overflow or underflow*/
void SUB(int P1,int P2,int P3){
  if((P1>=0 && P1<32)&&(P2>=0 && P2<32)&&(P3>=0 && P3<32)){
    if((r[P2]-pow(2,31)>r[P1])){
      printf("Aritmethic sub overflow\n");
      exit(0);
    }
    else if(r[P1]>(pow(2,31)-1)+r[P2]){
      printf("Aritmethic sub underflow\n");
      exit(0);
    }else
      r[P3]=r[P1]-r[P2];
  }else{
    printf("Position of the registry not correct. Possible registers 0-31\n");
    exit(0);
  }
}

/*MUL: integer multiplication between registry value in pos1 and pos2. The result of the multiplication is copied in the registry identified by pos3. Terminate if aritmethic overflow or underflow*/
void MUL(int P1,int P2,int P3){
  if((P1>=0 && P1<32)&&(P2>=0 && P2<32)&&(P3>=0 && P3<32)){
    if((r[P2]<0 && r[P1]<((pow(2,31)-1)/r[P2])) || (r[P2]>0 && r[P1]>((pow(2,31)-1)/r[P2]))){
      printf("Aritmethic mult overflow\n");
      exit(0);
    }
    else if((r[P2]>0 && r[P1]<-pow(2,31)/r[P2]) || (r[P2]<0 && (r[P1]>-pow(2,31)/-r[P2]))){
      printf("Aritmethic mult underflow\n");
      exit(0);
    }else
      r[P3]=r[P1]*r[P2];
  }else{
    printf("Position of the registry not correct. Possible registers 0-31\n");
    exit(0);
  }
}

/*DIV: integer division between registry value in pos1 and pos2. The result of the division is copied in the registry identified by pos3. Terminate if aritmethic overflow or underflow or registry in pos2 is equal to 0*/
void DIV(int P1,int P2,int P3){
  if((P1>=0 && P1<32)&&(P2>=0 && P2<32)&&(P3>=0 && P3<32)){
    if(r[P2]==0){
      printf("Cannot divide by 0\n");
      exit(0);
    }else if((r[P2]>0 && r[P1]>(pow(2,31)-1)*r[P2]) || (r[P2]<0 && r[P1]<(pow(2,31)-1)*r[P2])){
      printf("Aritmethic div overflow\n");
      exit(0);
    }else if((r[P2]>0 && r[P1]<-pow(2,31)*r[P2]) || (r[P2]<0 && r[P1]>-pow(2,31)*r[P2])){
      printf("Aritmethic div underflow\n");
      exit(0);
    }
      r[P3]=r[P1]/r[P2];
  }else{
    printf("Position of the registry not correct. Possible registers 0-31\n");
    exit(0);
  }
}

/*esegui:apre il file e lo esegue istruzione per istruzione*/
/*esegui: open the file and execute instructions line by line*/
void esegui(char *filename){
  int i=0,end=0,dim=0;
  int *program;

  /*read file so program and its dim are defined*/
  program=read(filename,&dim);
  
  /*initializing stack*/
  for(i=0;i<16384;i++){
    stack[i]=0;
  }
  
  /*initializing registers*/
  for(i=0;i<32;i++){
    r[i]=0;
  }

  /*stack pointer and instruction pointer are initialized to 0*/
  ip, sp, i=0;
  
  /*checking all possible instruction cases*/
  while(i<dim && end==0){
    switch(program[i])
      case 0:{
        HALT();
        end=1;
        break;
      case 1:
        DISPLAY(program[i+1]);
        i=i+2;
        ip=i;
        break;
      case 2:
        PRINT_STACK(program[i+1]);
        i=i+2;
        ip=i;
        break;
      case 10:
        PUSH(program[i+1]);
        i=i+2;
        ip=i;
        break;
      case 11:
        POP(program[i+1]);
        i=i+2;
        ip=i;
        break;
      case 12:
        MOV(program[i+1],program[i+2]);
        i=i+3;
        ip=i;
        break;
      case 20:
        CALL(program[i+1]);
        i=ip;
        break;
      case 21:
        RET();
        i=ip;
        break;
      case 22:
        JMP(program[i+1]);
        i=ip;
        break;
      case 73:
        JZ(program[i+1],program[i+2]);
        i=ip;
        break;
      case 74:
        JPOS(program[i+1],program[i+2]);
        i=ip;
        break;
      case 75:
        JNEG(program[i+1],program[i+2]);
        i=ip;
        break;
      case 80:
        ADD(program[i+1],program[i+2],program[i+3]);
        i=i+4;
        ip=i;
        break;
      case 81:
        SUB(program[i+1],program[i+2],program[i+3]);
        i=i+4;
        ip=i;
        break;
      case 82:
        MUL(program[i+1],program[i+2],program[i+3]);
        i=i+4;
        ip=i;
        break;
      case 83:
        DIV(program[i+1],program[i+2],program[i+3]);
        i=i+4;
        ip=i;
        break;

    }
  }

  free(program);
}
