#ifndef _GuitarString_H_
#define _GuitarString_H_

#include <vector>
#include <string>
#include <random>
#include <SFML/System.hpp>
#include <time.h>
#include "RingBuffer.hpp"

using std::vector;

class GuitarString
    {
    private:
        RingBuffer *rb{};
        int length;
        int tick{};
        std::mt19937 *rd;

    public:
        GuitarString(double frequency);
        GuitarString(vector<sf::Int16> init);
        void pluck();
        void tic();
        sf::Int16 sample();
        int time();
        ~GuitarString();
    };

#endif
