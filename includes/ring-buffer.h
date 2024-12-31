#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

// holds <capacity> of custom objects

typedef struct {
    void **buffer;
    int capacity;
    int head;
    int tail;
} RingBuffer;

RingBuffer* ring_buffer_init(int capacity);

bool rb_enqueue(RingBuffer *rb, void *value);
bool rb_dequeue(RingBuffer *rb, void **value);