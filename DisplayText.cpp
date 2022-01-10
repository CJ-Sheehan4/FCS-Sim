#include "DisplayText.h"
DisplayText::DisplayText(std::string initStr, sf::Vector2f pos, sf::Color color) {
	str = initStr;
	font.loadFromFile("Azonix.otf");
	text.setString(str);
	text.setFont(font);
	text.setCharacterSize(15);
	text.setFillColor(color);
	// text.setFillColor(sf::Color(217, 17, 203));
	text.setPosition(pos);
}
void DisplayText::changeStr(std::string newStr) {
	str = newStr;
	text.setString(str);
}
void DisplayText::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(text);
}