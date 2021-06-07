#ifndef PS2_SQUARE_HPP
#define PS2_SQUARE_HPP
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>

using sf::Vector2f;

class Square : public sf::Drawable
    {
    private:
        sf::ConvexShape polygon;
    public:
        Square(const Vector2f& a, const Vector2f& b, const Vector2f& c, const Vector2f& d);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    };

#endif
