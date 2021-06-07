#ifndef PS2_BODY_H
#define PS2_BODY_H
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

class Body : public sf::Drawable{

private:
    double radius, xpos, ypos, xvel, yvel, mass;
    std::string imageFile;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2u windowSize;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update();

public:
    Body(double radius, sf::Vector2u size);
    friend std::istream &operator>>(std::istream &input, Body& body);
    void init();
    void step(double time,  std::vector<Body>& bodies);
    friend std::ostream &operator<<(std::ostream &output, const Body& body);
};

#endif
