#include <iostream>
#include "Body.h"

Body::Body(double x, double y, double xpos, double ypos, double xvel, double yvel, double mass, const std::string &imgFile, double radius, int size)
{
}

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

void Body::load()
{
    sf::Image image;
    if(!image.loadFromFile(imageFile))
    {
        std::cout << "not found " + imageFile << std::endl;
        exit(0);
    }
    
    uint size = windowSize.x > windowSize.y ? windowSize.y/2 : windowSize.x/2;
    
    int X = (int)(xpos / radius * size);
    int Y = (int)((ypos / radius * size));
    
    X += size;
    Y += size;
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setPosition(X,Y);
}


