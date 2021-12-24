#include "StateCircle.h"
StateCircle::StateCircle(std::string initState) {
	// setting the state number
	state = initState;
	// create circle state
	shape.setRadius(50.f);
	shape.setFillColor(sf::Color::Green);
	sf::FloatRect circRect = shape.getLocalBounds();
	shape.setOrigin(circRect.left + circRect.width / 2.0f,
		circRect.top + circRect.height / 2.0f);
	shape.setPosition(50.f, 50.f);
	// Create font
	font.loadFromFile("Azonix.otf");
	// Create text for state number
	// set it to the middle of circle state
	text.setString(state);
	text.setFont(font);
	text.setCharacterSize(25);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Red);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(shape.getOrigin());


}
void StateCircle::setPosition(sf::Vector2i pos) {
	shape.setPosition(pos.x, pos.y);
	text.setPosition(pos.x, pos.y);
}
sf::FloatRect StateCircle::getGlobalBounds() {
	return shape.getGlobalBounds();
}
sf::FloatRect StateCircle::getLocalBounds() {
	return shape.getLocalBounds();
}
void StateCircle::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(shape);
	target.draw(text);
}



