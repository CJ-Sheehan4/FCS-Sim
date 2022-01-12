#ifndef DISPLAYTEXT_H
#define DISPLAYTEXT_H
#include <SFML/Graphics.hpp>
#include "TransStr.h"
#include <string>

class DisplayText : public sf::Drawable {
public:
	DisplayText(std::string initStr, sf::Vector2f pos, sf::Color color);
	void changeColor(sf::Color color);
	void changeStr(std::string newStr);
private:
	std::string str;
	sf::Font font;
	sf::Text text;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
};

#endif 
