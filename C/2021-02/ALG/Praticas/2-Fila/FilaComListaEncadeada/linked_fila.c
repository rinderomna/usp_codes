#include <stdio.h>
#include <stdlib.h>

#define FINISH -1

typedef struct node node_t;

struct node {
  int data;
  node_t *next;
};

typedef struct queue {
  node_t *start;
  node_t *end;
  int size;
} queue_t;

int main() {
  int number;
  queue_t int_queue;
  int_queue.start = NULL;
  int_queue.end = NULL;
  int_queue.size = 0;

  do {
    scanf("%d", &number);
    if (number != FINISH) {
      node_t *p = (node_t *)malloc(sizeof(node_t));
      p->data = number;
      p->next = NULL;
      if (int_queue.size == 0) {
        int_queue.start = p;
      } else {
        int_queue.end->next = p;
      }
      int_queue.end = p;
      int_queue.size++;
    }
  } while (number != FINISH);

  node_t *p = int_queue.start;
  while (p) {
    printf("%d ", p->data);
    int_queue.start = int_queue.start->next;
    free(p);
    p = int_queue.start;
    int_queue.size--;
  }

  printf("\n");

  return EXIT_SUCCESS;
}
