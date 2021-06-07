#include "Square.hpp"

void Square::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(polygon, states);
    }

Square::Square(const Vector2f& a, const Vector2f& b, const Vector2f& c, const Vector2f& d)
    {
        polygon.setPointCount(4);
        polygon.setPoint(0, a);
        polygon.setPoint(1, b);
        polygon.setPoint(2, c);
        polygon.setPoint(3, d);
        polygon.setFillColor(sf::Color::Green);
    }
