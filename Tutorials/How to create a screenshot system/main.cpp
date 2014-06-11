#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600), "Screenshot System");

	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
            	if (event.key.code == 89)
                {
                    // Capturing the window to a sf::Image
                    sf::Image screenshot = window.capture();

                    // Getting the actual time
                    time_t epoch_time;
                    struct tm *tm_p;
                    epoch_time = time( NULL );
                    tm_p = localtime( &epoch_time );

                    // Creating the screenshot name
                    std::string screenshotName = std::to_string(tm_p->tm_mday) + "-" + std::to_string(tm_p->tm_mon) + "-" + std::to_string(tm_p->tm_year) + " " + std::to_string(tm_p->tm_hour) + std::to_string(tm_p->tm_min) + std::to_string(tm_p->tm_sec);
                 
                    // Saving to a file
                    screenshot.saveToFile("screenshots/"+screenshotName+".png");   
                }
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}