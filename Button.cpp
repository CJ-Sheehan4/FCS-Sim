#include "Button.h"
Button::Button(std::string inittext, sf::Vector2f initpos, sf::Vector2f initsize) {
	buttonText = inittext;
	shape.setSize(initsize);
	shape.setPosition(initpos);
	shape.setFillColor(sf::Color::Green);
	sf::FloatRect RectRect = shape.getLocalBounds();
	shape.setOrigin(RectRect.left + RectRect.width / 2.0f,
		RectRect.top + RectRect.height / 2.0f);

	// Create font
	font.loadFromFile("Azonix.otf");
	// Create text for state number
	// set it to the middle of circle state
	text.setString(buttonText);
	text.setFont(font);
	text.setCharacterSize(15);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Red);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(shape.getPosition());


}
sf::FloatRect Button::getGlobalBounds() {
	return shape.getGlobalBounds();
}
sf::FloatRect Button::getLocalBounds() {
	return shape.getLocalBounds();
}
void Button::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(shape);
	target.draw(text);
}