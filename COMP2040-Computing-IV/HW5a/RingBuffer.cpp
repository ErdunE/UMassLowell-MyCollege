#include <stdexcept>
#include "RingBuffer.hpp"

RingBuffer::RingBuffer(int capacity) : capacity(capacity)
{
    if (capacity < 1)
    {
        throw std::invalid_argument
        ("RB constructor: capacity must be greater than zero");
    }
    data = new int16_t[capacity];
    front = 0;
    end = -1;
    count = 0;
}

int RingBuffer::size()
{
    return count;
}

bool RingBuffer::isEmpty()
{
    return count == 0;
}

bool RingBuffer::isFull()
{
    return count == capacity;
}

void RingBuffer::enqueue(int16_t x)
{
    if (isFull())
    {
        throw std::runtime_error
        ("enqueue: can't enqueue to a full ring");
    }
    end = (end+1) % capacity;
    count++;
    data[end] = x;
}

int16_t RingBuffer::dequeue()
{
    int16_t v = peek();
    front = (front+1) % capacity;
    count--;
    return v;
}

int16_t RingBuffer::peek()
{
    if (isEmpty())
    {
        throw std::runtime_error
        ("enqueue: can't peek or dequeue from a empty ring");
    }
    return data[front];
}

RingBuffer::~RingBuffer()
{
    delete[] data;
}
