#include <stdio.h>

#define MAX 10

typedef int element;

element stack[MAX];
int top;

void initialize(){top = -1;}

int empty(){return(top==-1);}

int full(){return(top==MAX-1);}

int push(element elt){
  if(!full()){stack[++top]=elt;return(1);}
  else{
    return(0);
  }
}

int pop(element * elt){
  if(!empty()){*elt=stack[top--];return(1);}
  else{
    return(0);
  }
}

int peek(element * elt){
  if(!empty()){*elt=stack[top];return(1);}
  else{
    return(0);
  }
}

int main(void){
  int i;
  initialize();
  for(i=1;i<MAX+1;i++){
    if(push(i))
    printf(" %d has been pushed\n",i);
    else{
      printf(" %d could not be pushed",i);
    }
  }
  if(peek(&i))printf("%d has peeked\n",i);
  else{
    printf("%d could not be peeked\n",i);
  }
  while(pop(&i))printf(" popped %d\n",i);
  if(peek(&i))printf("%d has peeked\n",i);
  else{
    printf("stack is empty");
  }
}




