#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP
#include <stdint.h>

class RingBuffer
{
 private:
    int16_t *data;
    int count;
    int capacity;
    int front;
    int end;

 public:
    explicit RingBuffer(int capacity);
    ~RingBuffer();
    int size();
    bool isEmpty();
    bool isFull();
    void enqueue(int16_t x);
    int16_t dequeue();
    int16_t peek();
};

#endif
