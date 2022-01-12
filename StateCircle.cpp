#include "StateCircle.h"
StateCircle::StateCircle(std::string initState) {
	// setting the state number
	state = initState;
	// create circle state
	shape.setRadius(50.f);
	shape.setFillColor(sf::Color::White);
	sf::FloatRect circRect = shape.getLocalBounds();
	shape.setOrigin(circRect.left + circRect.width / 2.0f,
		circRect.top + circRect.height / 2.0f);
	shape.setPosition(50.f, 50.f);
	// Create font
	font.loadFromFile("Pulang.otf");
	// Create text for state number
	// set it to the middle of circle state
	text.setString(state);
	text.setFont(font);
	text.setCharacterSize(25);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Blue);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(shape.getOrigin());
}
void StateCircle::setPosition(sf::Vector2i pos) {
	shape.setPosition(pos.x, pos.y);
	text.setPosition(pos.x, pos.y);
}
sf::Vector2f StateCircle::getPosition() {
	return shape.getPosition();
}
sf::FloatRect StateCircle::getGlobalBounds() {
	return shape.getGlobalBounds();
}
void StateCircle::setGlobalFR(sf::FloatRect initFr) {
	global_fr = initFr;
}
sf::FloatRect StateCircle::getGlobalFR() {
	return global_fr;
}
sf::FloatRect StateCircle::getLocalBounds() {
	return shape.getLocalBounds();
}
void StateCircle::setTextColor(sf::Color color) {
	text.setFillColor(color);
}
sf::Color StateCircle::getTextColor() {
	return text.getFillColor();
}
std::string StateCircle::getState() {
	return state;
}
char StateCircle::getStateChar() {
	return state[0];
}
void StateCircle::stateSelected(std::vector<std::shared_ptr<StateCircle>> states) {
	text.setFillColor(sf::Color(217, 17, 203));
}
void StateCircle::makeAcceptState(void) {
	shape.setOutlineColor(sf::Color(217, 17, 203));
	shape.setOutlineThickness(5);
}
void resetTextColor(std::vector<std::shared_ptr<StateCircle>> states) {
	for (int i = 0; i < states.size(); i++) {
		states[i]->setTextColor(sf::Color::Blue);
	}
}
bool twoStatesSelected(std::vector<std::shared_ptr<StateCircle>> states) {
	int num = 0;
	for (int i = 0; i < states.size(); i++) {
		if (states[i]->getTextColor() == sf::Color(217, 17, 203)) {
			num++;
		}
	}
	if (num > 1) {
		return true;
	}
	else {
		return false;
	}
}
void StateCircle::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(shape);
	target.draw(text);
}



