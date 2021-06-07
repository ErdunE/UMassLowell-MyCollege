#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Body.h"
#include <iostream>
#include <memory>
#include <iomanip>

using namespace sf;
using namespace std;

int main(int argc, char** args)
{
    if (argc != 3)
    {
        cout << "usage: NBody T dt" << endl;
        exit(0);
    }
    double T = atof(args[1]);
    double dt = atof(args[2]);
    double t = 0.0;
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
        body->init();
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
        if (t < T)
        {
            vector<Body> backup;
            for(auto body : bodys)
                backup.push_back(Body(*body));
            for(uint j = 0; j < bodys.size();j++)
                bodys[j]->step(dt, backup);
            t += dt;

            cout << n << std::setprecision(2)<< endl << radius << endl;
            for(uint j = 0; j < bodys.size(); j++)
            {
                cout << *bodys[j] << endl;
            }

        }

    }
    cout << n << std::setprecision(2)<< endl << radius << endl;
    for(uint j = 0; j < bodys.size(); j++) {
        cout << *bodys[j] << endl;
    }
}
