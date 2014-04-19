#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600), "Custom mouse cursor");
	window.setMouseCursorVisible(false);

	// Create a CircleShape with radius 10
	sf::CircleShape cursor(10);
	// Set the origin of the cursor at the center of it
	cursor.setOrigin(cursor.getGlobalBounds().width/2, cursor.getGlobalBounds().height/2);

	while (window.isOpen())
	{
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        cursor.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

        window.clear();
        window.draw(cursor);
        window.display();
	}
}