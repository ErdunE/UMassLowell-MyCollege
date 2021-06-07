#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Square.hpp"
#include <cmath>
#include <iostream>

using namespace sf;
RenderWindow app(VideoMode(800, 600, 32), "PTree");
class PTree : public sf::Drawable
{
private:
    
    int base_size;
    int depth_limit;
    
    void draw(float x1, float y1, float x2, float y2, int depth) const
    {
        if(depth == depth_limit)return;

        float dx = x2-x1;
        float dy = y1-y2;
        float x3 = x2 - dy;
        float y3 = y2 - dx;
        float x4 = x1 - dy;
        float y4 = y1 - dx;
        float x5 = x4 + 0.5 * (dx - dy);
        float y5 = y4 - 0.5 * (dx + dy);

        Square square(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2),sf::Vector2f(x3, y3),sf::Vector2f(x4, y4));
        square.draw(app, RenderStates::Default);

        draw(x4, y4, x5, y5, depth + 1);
        draw(x5, y5, x3, y3, depth + 1);
    }

public:
    
    PTree(int L, int n)
    {
        base_size = L;
        depth_limit = n+1;
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        int x = 400-base_size/2;
        draw(x, 500, x+base_size, 500, 0);
    }
};


int main(int argc, char** args)

{
	app.setFramerateLimit(60);
    
    if (argc != 3)
    {
        std::cout << "usage: ./ptree L N \n";
        return 0;
    }
    
	int L = atoi(args[1]);
	int N = atoi(args[2]);

	PTree pTree(L,N);
	Event event;
	while(app.isOpen())
    {
		while(app.pollEvent(event))
        {
			if(event.type == Event::Closed)
            {
				app.close();
				break;
			}
		}
		app.clear(Color::Black);
        pTree.draw(app, RenderStates::Default);
		app.display();
	}
}
