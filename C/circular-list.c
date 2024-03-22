#include<stdio.h>
#include<stdlib.h>
// #include<stdbool.h>

typedef struct node {
  int data;
  struct node * next;
} Node;

typedef struct {
  Node *start;
  Node *end;
  int count;
  const int maxCount;
} CircularList;

void enqueue(CircularList *cList, int data)
{
  Node* newNode = malloc(sizeof(Node));
  
  newNode->data = data;

  if (cList->count == 0) {
    cList->start = newNode;
    cList->end = newNode;
    newNode->next = newNode;
    cList->count++;
  } else if (cList->count == cList->maxCount) {
    // We have reached max capacity.
    // Override data at start, and update the start pointer and end pointer.
    cList->start->data = data;
    free(newNode);

    cList->end = cList->start;
    cList->start = cList->start->next;
  } else {
    // Add it at the end.
    Node *endNode = cList->end;
    endNode->next = newNode;
    newNode->next = cList->start;
    cList->end = newNode;
    cList->count++;
  }
}

Node * dequeue(CircularList *cList) {
  if (cList->count == 0)
  return NULL;

  Node *retNode = cList->start;
  
  // Update Start
  cList->start = retNode->next;

  // Decrement count
  cList->count--;

  // Update the last node to point to start
  cList->end->next = cList->start;

  if (cList->count == 0) {
    // Update start and end
    cList->start = NULL;
    cList->end = NULL;
  }

  // De-link the Node from the list before returning
  retNode->next = NULL;

  return retNode;
}

void dumpList(CircularList *cList) {
  for(Node *tmp = cList->start; 1 ; tmp = tmp->next) {
    if (tmp) {
      printf("%d->", tmp->data);
    }

    if (tmp == cList->end) {
      break;
    }
  }
  printf("\nNodes count: %d maxCount: %d\n", cList->count, cList->maxCount);
}

int main(int argc, char *argv[])
{
  CircularList cList = { .start = NULL, .end = NULL, .count = 0, .maxCount = 5};

  dumpList(&cList);
  enqueue(&cList, 1);
  dumpList(&cList);
  enqueue(&cList, 2);
  dumpList(&cList);
  enqueue(&cList, 3);
  dumpList(&cList);
  enqueue(&cList, 4);
  dumpList(&cList);
  enqueue(&cList, 5);
  dumpList(&cList);
  enqueue(&cList, 6);
  dumpList(&cList);
  enqueue(&cList, 7);
  dumpList(&cList);
  enqueue(&cList, 8);
  dumpList(&cList);

  Node *node = dequeue(&cList);

  if (node) {
    printf("Dequeue data %d\n", node->data);
    free(node);
  }
  dumpList(&cList);

  node = dequeue(&cList);
  if (node) {
    printf("Dequeue data %d\n", node->data);
    free(node);
  }
  dumpList(&cList);

  node = dequeue(&cList);
  if (node) {
    printf("Dequeue data %d\n", node->data);
    free(node);
  }
  dumpList(&cList);

  node = dequeue(&cList);
  if (node) {
    printf("Dequeue data %d\n", node->data);
    free(node);
  }
  dumpList(&cList);

  node = dequeue(&cList);
  if (node) {
    printf("Dequeue data %d\n", node->data);
    free(node);
  }
  dumpList(&cList);

  node = dequeue(&cList);
  if (node) {
    printf("Dequeue data %d\n", node->data);
    free(node);
  }
  dumpList(&cList);

  enqueue(&cList, 1);
  dumpList(&cList);
  enqueue(&cList, 2);
  dumpList(&cList);

  node = dequeue(&cList);
  if (node) {
    printf("Dequeue data %d\n", node->data);
    free(node);
  }
  dumpList(&cList);

  node = dequeue(&cList);
  if (node) {
    printf("Dequeue data %d\n", node->data);
    free(node);
  }
  dumpList(&cList);

  return 0;
}