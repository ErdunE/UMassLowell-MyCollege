/*
  Copyright 2015 Fred Martin, fredm@cs.uml.edu
  Mon Mar 30 08:58:49 2015

  based on Princeton's GuitarHeroLite.java
  www.cs.princeton.edu/courses/archive/fall13/cos126/assignments/guitar.html

  build with
  g++ -Wall -c GuitarHeroLite.cpp -lsfml-system \
     -lsfml-audio -lsfml-graphics -lsfml-window
  g++ -Wall GuitarHeroLite.o RingBuffer.o GuitarString.o \
   -o GuitarHeroLite -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window
*/

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <math.h>
#include <limits.h>

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>

#include "GuitarString.hpp"

#define CONCERT_A 220.0
#define SAMPLES_PER_SEC 44100

using namespace std;

vector<sf::Int16> makeSamplesFromString(GuitarString gs) {
    std::vector<sf::Int16> samples;

    gs.pluck();
    int duration = 8;  // seconds
    int i;
    for (i = 0; i < SAMPLES_PER_SEC * duration; i++) {
        gs.tic();
        samples.push_back(gs.sample());
    }

    return samples;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(300, 200), "SFML Guitar Hero Lite");
    sf::Event event;
    double freq;
    vector<GuitarString*> gs_list;
    vector<sf::SoundBuffer*> buffers;
    vector<sf::Sound*> sounds;


    // we're reusing the freq and samples vars, but
    // there are separate copies of GuitarString, SoundBuffer, and Sound
    //   for each note
    //
    // GuitarString is based on freq
    // samples are generated from GuitarString
    // SoundBuffer is loaded from samples
    // Sound is set to SoundBuffer

    vector<sf::Int16> samples;
    for (int i = 0; i < 37; i++) {
        freq = 440 * pow(2, (i - 24.0) / 12.0);

        gs_list.push_back(new GuitarString(freq));
        sounds.push_back(new sf::Sound());
        buffers.push_back(new sf::SoundBuffer());
        auto *sound = sounds[i];
        auto *buf = buffers[i];
        auto& gs = *gs_list[i];
        samples = makeSamplesFromString(gs);
        if (!buf->loadFromSamples(&samples[0], samples.size(), 2, SAMPLES_PER_SEC))
            throw std::runtime_error("sf::SoundBuffer: failed to load from samples.");
        sound->setBuffer(*buf);
    }


    vector<int> keyboard = {sf::Keyboard::Q, sf::Keyboard::Num2, sf::Keyboard::W, sf::Keyboard::E, sf::Keyboard::Num4,
                            sf::Keyboard::R, sf::Keyboard::Num5, sf::Keyboard::T, sf::Keyboard::Y, sf::Keyboard::Num7,
                            sf::Keyboard::U, sf::Keyboard::Num8, sf::Keyboard::I, sf::Keyboard::Num9, sf::Keyboard::O,
                            sf::Keyboard::P, sf::Keyboard::Dash, sf::Keyboard::LBracket, sf::Keyboard::Equal,
                            sf::Keyboard::Z, sf::Keyboard::X, sf::Keyboard::D, sf::Keyboard::C, sf::Keyboard::F,
                            sf::Keyboard::V, sf::Keyboard::G, sf::Keyboard::B, sf::Keyboard::N, sf::Keyboard::J,
                            sf::Keyboard::M, sf::Keyboard::K, sf::Keyboard::Comma, sf::Keyboard::Period,
                            sf::Keyboard::SemiColon,
                            sf::Keyboard::Slash, sf::Keyboard::Quote, sf::Keyboard::Space};
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    for (unsigned long i = 0; i < keyboard.size(); i++) {
                        if (event.key.code == keyboard[i]) {
                            sounds[i]->play();
                            break;
                        }
                    }
                    break;

                default:
                    break;
            }

            window.clear();
            window.display();
        }
    }
    for(ulong i = 0; i < gs_list.size(); i++) {
        delete gs_list[i];
        delete sounds[i];
    }
    return 0;
}

