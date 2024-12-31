#include "ring-buffer.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t empty;
sem_t full;

RingBuffer* rb_init(int capacity) {
    RingBuffer* rb = malloc(sizeof(RingBuffer));

    if(!rb) {
        perror("Failed to allocate ring buffer");
        exit(1);
    }

    rb->capacity = capacity;
    rb->buffer = (void*)malloc(capacity * sizeof(int*));
    if(!rb->buffer) {
        perror("Failed to allocate ring buffer");
        free(rb);
        exit(1);
    }

    rb->head = 0;
    rb->tail = 0;

    sem_init(&empty, 0, capacity);
    sem_init(&full, 0, 0);

    return rb;
}

void rb_enqueue(RingBuffer *rb, void *value) {
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    rb->buffer[rb->tail] = value;
    rb->tail = (rb->tail + 1) % rb->capacity;

    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

void* rb_dequeue(RingBuffer *rb) {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    void* val = rb->buffer[rb->head];
    rb->head = (rb->head + 1) & rb->capacity;

    pthread_mutex_unlock(&mutex);
    sem_post(&empty); 

    return val;
}

void rb_destroy(RingBuffer *rb) {
    if(!rb) {
        return;
    }

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    pthread_mutex_destroy(&mutex);

    free(rb->buffer);
    free(rb);
}