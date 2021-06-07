#include "GuitarString.hpp"
#include <chrono>

GuitarString::GuitarString(double frequency)
    {
        length = (int) (44100 / frequency);
        rb = new RingBuffer(length);
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        rd = new std::mt19937(seed);
    }

void GuitarString::pluck()
    {
        rb->empty();
        for (int i = 0; i < length; i++)
            rb->enqueue((*rd)());
    }

GuitarString::GuitarString(vector<sf::Int16> init)
    {
        rb = new RingBuffer(init.size());
        for (int n : init)
        {
            rb->enqueue(n);
        }
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        rd = new std::mt19937(seed);
    }

void GuitarString::tic()
    {
        tick++;
        int16_t t = rb->dequeue();
        rb->enqueue((int16_t) ((t + rb->peek()) / 2.0 * 0.996));
    }

sf::Int16 GuitarString::sample()
    {
        return rb->peek();
    }

int GuitarString::time()
    {
        return tick;
    }

GuitarString::~GuitarString()
    {
        delete rb;
    }


