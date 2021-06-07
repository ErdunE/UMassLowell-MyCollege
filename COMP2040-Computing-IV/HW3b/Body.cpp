#include <iostream>
#include "Body.h"
#include <vector>
#include <cmath>
#include <iomanip>

using std::vector;


void Body::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, sf::RenderStates::Default);
}

std::istream &operator>>(std::istream &input, Body &body)
{
    input >> body.xpos >> body.ypos >> body.xvel >> body.yvel >> body.mass >> body.imageFile;
    return input;
}

Body::Body(double radius, sf::Vector2u size)
{
    this->radius = radius;
    windowSize = size;
}

void Body::init()
{
    sf::Image image;
    if(!image.loadFromFile(imageFile))
    {
        std::cout << "not found the " + imageFile << std::endl;
        exit(0);
    }
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    update();
}

void Body::update()
{
    uint size = windowSize.x > windowSize.y ? windowSize.y/2 : windowSize.x /2;
    int X = (int)(xpos / radius * size);
    int Y = (int)((ypos / radius * size));
    X += size;
    Y += size;
    sprite.setPosition(X,Y);
}

void Body::step(double time, vector<Body>& bodies)
{
    double dxvel, dyvel;
    dxvel = dyvel = 0;
    for(auto& other : bodies)
    {
        if(other.imageFile == imageFile) continue;
        double G = 6.67e-11;
        double dx = other.xpos - xpos;
        double dy = other.ypos - ypos;
        double r2 = dx * dx + dy * dy;
        double F = G * other.mass * mass / r2;
        double Fx = F / sqrt(r2) * dx, Fy = F / sqrt(r2) * dy;
        double ax = Fx / mass, ay = Fy / mass;
        dxvel += ax * time;
        dyvel += ay * time;
    }
    xvel += dxvel;
    yvel += dyvel;
    xpos += xvel * time;
    ypos += yvel * time;
    update();
}

std::ostream &operator<<(std::ostream &output, const Body &body)
{
    output <<std::scientific << std::setprecision(4) << body.xpos << " " << body.ypos << " " << body.xvel << " " << body.yvel << " " << body.mass << " " << body.imageFile;
    return output;
}


