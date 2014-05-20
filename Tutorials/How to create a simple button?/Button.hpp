#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

typedef void (*function)(void);

class Button: public sf::Drawable, public sf::Transformable
{
public:
	Button() {};
	Button(sf::Font& font, const sf::Vector2f size = sf::Vector2f(0,0));

	void setSize(const sf::Vector2f size);
	void setFont(sf::Font &font);
	void setString(const std::string string);
	void setBackgroundColor(const sf::Color &color);
	void setTextColor(const sf::Color &color);
	void setOutlineThickness(float thickness);
	void setOutlineColor(const sf::Color &color);

	void setOverAction(bool active = true);
	void setOverBackgroundColor(const sf::Color &color);
	void setOverTextColor(const sf::Color &color);
	void setOverOutlineColor(const sf::Color &color);

	void handler(sf::RenderWindow &window);
	void events(sf::Event &event);

	void setTriggerFunction(function triggerFunction);
private:
	void update();
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Vector2f m_size;
	sf::RectangleShape m_body;

	sf::Font* m_font;
	sf::Text m_text;

	sf::Color m_backgroundColor;
	sf::Color m_textColor;
	sf::Color m_outlineColor;

	sf::Color m_overBackgroundColor;
	sf::Color m_overTextColor;
	sf::Color m_overOutlineColor;

	bool m_overActive;

	bool m_mouseCursorOver;
	bool m_buttonPressed;
	function m_triggerFunction;
};

#endif