#include <SFML/Graphics.hpp>

#include <vector>

const int gravity = 500;

void move(sf::Vector2f &playerVelocity)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerVelocity.x = -gravity;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerVelocity.x = gravity;
	}
	else if (playerVelocity.x != 0)
	{
		playerVelocity.x = 0;
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600), "How to apply collision?");

	// Loading player texture
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("player.png")) return 0;

	// Creating player sprite
	sf::Sprite player;
	player.setTexture(playerTexture);

	// Loading grass texture
	sf::Texture grassTexture;
	if (!grassTexture.loadFromFile("grass.png")) return 0;

	// Creating a vector because we have more blocks and we will need them into a container
	std::vector<sf::Sprite> grass;

	// Add 4 grass blocks to the container
	grass.resize(4);
	for (std::size_t i=0; i<3; ++i)
	{
		grass[i].setTexture(grassTexture);
		grass[i].setPosition(128 * i, 384);
	}

	// Last grass block will bo above the first one
	grass[3].setTexture(grassTexture);
	grass[3].setPosition(0,256);

	// Create a sf::Vector2f for player velocity and add to the y variable value gravity
	sf::Vector2f playerVelocity(0, gravity);

	sf::Clock clock;
	while (window.isOpen())
	{
		// Get the frame elapsed time and restart the clock
		float dt = clock.restart().asSeconds();

		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Apply physics to player
        player.setPosition(player.getPosition().x + playerVelocity.x * dt, player.getPosition().y + playerVelocity.y * dt);

        for (std::size_t i=0; i<grass.size(); ++i)
        {
        	// Affected area
        	sf::FloatRect area;
        	if (player.getGlobalBounds().intersects(grass[i].getGlobalBounds(), area))
        	{
        		// Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
        		if (area.width > area.height)
				{
					if (area.contains({ area.left, player.getPosition().y }))
					{
						// Up side crash
						player.setPosition({ player.getPosition().x, player.getPosition().y + area.height });
					}
					else
					{
						// Down side crash
						player.setPosition({ player.getPosition().x, player.getPosition().y - area.height });
					}
				}
				else if (area.width < area.height)
				{
					if (area.contains({ player.getPosition().x + player.getGlobalBounds().width - 1.f, area.top + 1.f }))
					{
						//Right side crash
						player.setPosition({ player.getPosition().x - area.width, player.getPosition().y });
					}
					else
					{
						//Left side crash
						player.setPosition({ player.getPosition().x + area.width, player.getPosition().y });
					}
				}
        	}
        }

        move(playerVelocity);

        window.clear();
        
        // Draw the grass
        for (std::size_t i=0; i<grass.size(); ++i)
        {
        	window.draw(grass[i]);
        }

        // Draw the player
        window.draw(player);

        window.display();
	}	

	return 0;
}