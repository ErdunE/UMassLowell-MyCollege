#ifndef PS2_BODY_H
#define PS2_BODY_H

#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>

class Body : public sf::Drawable{

private:
    double radius, xpos, ypos, xvel, yvel, mass;
    std::string imageFile;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2u windowSize;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Body(double radius, sf::Vector2u size);
    Body(double x, double y, double xpos, double ypos, double xvel, double yvel, double mass, const std::string &imgFile, double radius, int size);
    friend std::istream &operator>>(std::istream &input, Body& body);
    void load();
};

#endif
