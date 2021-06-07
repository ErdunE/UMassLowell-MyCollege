#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Body.h"
#include <iostream>
#include <memory>

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(800, 600, 32), "The Solar System!");
    window.setFramerateLimit(60);
    int n = 0;
    double radius = 0;
    cin >> n >> radius;
    string imageFile;
    vector<shared_ptr<Body>> bodys;
    for(int i = 0; i < n ;i++)
    {
        shared_ptr<Body> body = make_shared<Body>(radius, window.getSize());
        cin >> *body;
        body->load();
        bodys.push_back(body);
    }


    Event event{};
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                window.close();
                break;
            }
        }
        window.clear(Color::Black);
        for(int i = 0; i < n;i ++)
        {
            window.draw(*bodys[i]);
        }
        window.display();
    }
}
