#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const unsigned int whiteKeys = 7;
const unsigned int blackKeys = 5;
const unsigned int keys = 12;

std::array<sf::SoundBuffer, keys> soundBuffers;
std::array<sf::Sound, keys> keySounds;

std::array<sf::RectangleShape, keys> keyRects;
const sf::Vector2f whiteKeySize(80, 230);
const sf::Vector2f blackKeySize(40, 120);

void loadBuffers()
{
    std::string filesName[keys] = {"sounds/C.wav", "sounds/D.wav", "sounds/E.wav", "sounds/F.wav", "sounds/G.wav", "sounds/A.wav", "sounds/B.wav", "sounds/C#.wav", "sounds/D#.wav", "sounds/F#.wav", "sounds/G#.wav", "sounds/A#.wav"};

    for (unsigned int i=0; i<soundBuffers.size(); ++i)
    {
        soundBuffers[i].loadFromFile(filesName[i]);
    }
}

void setBuffers()
{
    for (unsigned int i=0; i<keySounds.size(); ++i)
    {
        keySounds[i] = sf::Sound(soundBuffers[i]);
        keySounds[i].setPlayingOffset(sf::milliseconds(700));
    }
}

void setupPiano()
{
    // Creating the white keys
    for (unsigned int i=0; i<whiteKeys; ++i)
    {
        keyRects[i].setSize(whiteKeySize);
        keyRects[i].setFillColor(sf::Color::White);
        keyRects[i].setOutlineThickness(1);
        keyRects[i].setOutlineColor(sf::Color::Black);
        keyRects[i].setPosition(whiteKeySize.x*i,0);
    }

    // Creating the black keys
    // The i still goes until 7( whiteKeys) even if we only have 5 black keys to easily set their position
    // We use a j variable to know the position of rects in the array
    for (unsigned int i=0, j=whiteKeys; i<whiteKeys; ++i)
    {
        // Because in the position 2(E) and 6(B) we don't have black keys, we need to skip them
        if (i!=2 && i!=6)
        {
            keyRects[j].setSize(blackKeySize);
            keyRects[j].setFillColor(sf::Color::Black);
            keyRects[j].setOutlineThickness(1);
            keyRects[j].setOutlineColor(sf::Color::Black);

            // Setting the position of the black keys exactly between white ones
            keyRects[j].setPosition(i*whiteKeySize.x+blackKeySize.x/2+blackKeySize.x, 0);
            ++j;
        }
    }
}

int main()
{
    loadBuffers();
    setBuffers();
    setupPiano();

    //                       A,  S, D, F, G, H, J,  W, E,  R,  T,  Y
	int keyboardKey[keys] = {0, 18, 3, 5, 6, 7 ,9, 22, 4, 17, 19, 24};

	bool keyReady[keys] = {true, true, true, true, true, true, true, true, true, true, true, true};

	sf::RenderWindow window(sf::VideoMode(whiteKeySize.x*whiteKeys, whiteKeySize.y), "Piano");

	while (window.isOpen())
	{
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
            	for (unsigned int i=0; i<keys; ++i)
            	{
                    // Verifying if the key is pressed and ready
            		if (event.key.code == sf::Keyboard::Key(keyboardKey[i]) && keyReady[i])
            		{
            			keySounds[i].play();

                        // Setting the key state to false to know it was pressed
            			keyReady[i] = false;

                        // Coloring the white keys( the first 7) in red and the black keys(the rest) in dark red
            			if (i<7) keyRects[i].setFillColor(sf::Color::Red);
                        else keyRects[i].setFillColor(sf::Color(164,3,3));
            		}
            	}
            }

            if (event.type == sf::Event::KeyReleased)
            {
            	for (unsigned int i=0; i<keys; ++i)
            	{
                    // Verifying if the key is released and if it has been pressed
            		if (event.key.code == sf::Keyboard::Key(keyboardKey[i]) && !keyReady[i])
            		{
                        keySounds[i].stop();

                        // Resetting the playing offset
                        keySounds[i].setPlayingOffset(sf::milliseconds(700));

                        // Set the key state to true to make it playable
            			keyReady[i] = true;

                        // Coloring back the piano keys
            			if (i<whiteKeys) keyRects[i].setFillColor(sf::Color::White);
                        else keyRects[i].setFillColor(sf::Color::Black);
            		}
            	}
            }
        }

        window.clear();

        for (unsigned int i=0; i<keyRects.size(); ++i)
        {
        	window.draw(keyRects[i]);
        }

        window.display();
	}
}
