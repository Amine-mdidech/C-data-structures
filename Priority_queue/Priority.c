#include<stdio.h>
#include<stdlib.h>

typedef struct prioQueue{
  int elements;
  int* array;
  unsigned capacity;
}prioqueue;

prioqueue* creatqueue(int item);
prioqueue* enqueue(prioqueue* queue, int item);
int isfull(prioqueue* queue);
int isempty(prioqueue* queue);
int dequeue(prioqueue* queue);

int main(void) {
  prioqueue* queue = creatqueue(4);
  enqueue(queue, 10);
  enqueue(queue, 20);
  enqueue(queue, 30);
  enqueue(queue, 40);
  
  printf("%d has been dequeud",dequeue(queue));
}

prioqueue* creatqueue(int capacity){
  prioqueue* queue = (prioqueue*)malloc(sizeof(prioqueue));
  queue->elements=0;
  queue->capacity=capacity;
  queue->array=(int*)malloc(queue->capacity* sizeof(prioqueue));
  return queue;
}

prioqueue* enqueue(prioqueue* queue, int item){
  int i,j;
  if(isfull(queue))
  return(0);
  if(isempty(queue)){
    queue->array[queue->elements++]=item;
    printf("%d\n",item);
    return(0);
  }
  for(i=queue->elements-1,j=0;j<=i;j++){
    if(item>queue->array[queue->elements])
    queue->array[queue->elements+1]=queue->array[queue->elements];
    else break;
  }
  queue->array[queue->elements+1]=item;
  queue->elements=queue->elements+1;
  printf("%d\n",item);
}

int isfull(prioqueue* queue){
  return(queue->elements==queue->capacity);
}

int isempty(prioqueue* queue){
  return(queue->elements==0);
}

int dequeue(prioqueue* queue){
  if(isempty(queue))
  return 999999;
  int item=queue->array[queue->elements];
}












