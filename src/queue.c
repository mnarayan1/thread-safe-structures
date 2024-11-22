#include "queue.h"
#include <stdio.h>
#include <pthread.h>

Queue* queue_init() {
    Queue* q = malloc(sizeof(Queue));
    q->front = NULL;
    q->back = NULL;
}

void enqueue(Queue* q, void* item) {
    q_node* new_node = malloc(sizeof(q_node));
    new_node->data = item;
    new_node->next = NULL;

    if(!q->front) {
        q->front = malloc(sizeof(q_node));
        q->back = q->front;
    } else {
        q->back->next = new_node;
        q->back = new_node;
    }
}

void* dequeue(Queue* q) {
    if(!q->front) {
        return;
    }

    void* res = q->front->data;
    q->front = q->front->next;
    free(q->front);
    return res;
}