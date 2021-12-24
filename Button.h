#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <string>
class Button : public sf::Drawable {
public:
	Button(std::string inittext, sf::Vector2f initpos, sf::Vector2f initsize);
	sf::FloatRect getGlobalBounds();
	sf::FloatRect getLocalBounds();
private:
	std::string buttonText;
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
};

#endif 
