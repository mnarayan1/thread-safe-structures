#include <stdio.h>
#include <pthread.h>

typedef struct _q_node_t {
    struct _q_node_t *next;
    void* data;
} q_node;


typedef struct {
    q_node* front;
    q_node* back;
} Queue;