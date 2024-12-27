#include "queue.h"
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cond = PTHREAD_COND_INITIALIZER;

Queue* queue_init() {
    Queue* q = malloc(sizeof(Queue));
    if(!q) {
        perror("Failed to allocate memory for Queue");
        exit(1);
    }
    q->front = NULL;
    q->back = NULL;
    return q;
}

void enqueue(Queue* q, void* item) {
    q_node* new_node = malloc(sizeof(q_node));
    new_node->data = item;
    new_node->next = NULL;

    pthread_mutex_lock(&mutex);
    if(!q->front) {
        q->front = new_node;
        q->back = q->front;
        pthread_cond_signal(&cond);
    } else {
        q->back->next = new_node;
        q->back = new_node;
    }
    pthread_mutex_unlock(&mutex);
}

void* dequeue(Queue* q) {
    pthread_mutex_lock(&mutex);
    while(!q->front) {
        pthread_cond_wait(&cond, &mutex);
    }

    void* res = q->front->data;
    q_node* tmp = q->front;
    q->front = q->front->next;
    free(tmp);

    pthread_mutex_unlock(&mutex);
    return res;
}

void destroy(Queue* q) {
    if (!q) return;

    q_node* curr = q->front;
    while(q->front) {
        q_node* tmp = curr->next;
        free(curr);
        curr = tmp;
    }
    free(q);
}