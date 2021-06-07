#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
  sf::RenderWindow window(sf::VideoMode(600, 600), "Hello world!");
  sf::Texture texture;
    
  if (!texture.loadFromFile("sprite.png"))
  {
    std::cout << "Do not found the sprite.png" << std::endl;
  }
    
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setPosition(200,200);
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
        // move up
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      {
        sprite.move(0.f, -10.f);
      }
        //move down
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
        sprite.move(0.f, 10.f);
      }
        //move left
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      {
        sprite.move(-10.f, 0.f);
      }
        //move right
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      {
        sprite.move(10.f, 0.f);
      }
        // page move up
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
      {
        sprite.setScale(1.1f,1.1f);
      }
        // page move down
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
      {
        sprite.setScale(0.9f,0.9f);
      }

    }
    window.clear();
    window.draw(sprite);
    window.display();
  }
  return 0;
}
