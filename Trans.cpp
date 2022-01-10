#include "Trans.h"
#include <SFML/Graphics.hpp>
Trans::Trans() {

	line[0].color = sf::Color::Black;
	line[1].color = sf::Color(1, 235, 224);
}
Trans::Trans(std::shared_ptr<StateCircle> initS1, std::shared_ptr<StateCircle> initS2) {
	p1 = initS1->getPosition();
	p2 = initS2->getPosition();
	
	line[0] = p1;
	line[1] = p2;
	line[0].color = sf::Color::Black;
	line[1].color = sf::Color(1, 235, 224);
}
Trans::Trans(std::shared_ptr<StateCircle> initS1, std::shared_ptr<StateCircle> initS2, char initC) {
	p1 = initS1->getPosition();
	p2 = initS2->getPosition();

	line[0] = p1;
	line[1] = p2;
	line[0].color = sf::Color::Black;
	line[1].color = sf::Color(1, 235, 224);
	c = initC;
}
void Trans::setPoints(std::shared_ptr<StateCircle> initS1, std::shared_ptr<StateCircle> initS2) {
	s1 = initS1;
	s2 = initS2;
	p1 = s1->getPosition();
	p2 = s2->getPosition();

	line[0] = p1;
	line[1] = p2;
	line[0].color = sf::Color::Black;
	line[1].color = sf::Color(1, 235, 224);
}
char Trans::getC() {
	return c;
}
void Trans::setC(char newC) {
	c = newC;
	font.loadFromFile("Azonix.otf");
	text.setString(c);
	text.setFont(font);
	text.setCharacterSize(15);
	text.setFillColor(sf::Color(217, 17, 203));
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	float ty = (p2.y + p1.y) / 2;
	float tx = (p2.x + p1.x) / 2;
	text.setPosition(tx, ty);
}
void Trans::setP1(sf::Vector2f p) {
	p1 = p;
}
void Trans::setP2(sf::Vector2f p) {
	p2 = p;
}
sf::Text Trans::getText() {
	return text;
}
void Trans::setText() {
	sf::Vector2f s1Pos = s1->getPosition();
	sf::Vector2f s2Pos = s2->getPosition();
	float ty = (s2Pos.y + s1Pos.y) / 2;
	float tx = (s2Pos.x + s1Pos.x) / 2;
	text.setPosition(tx, ty);
}
sf::Vector2f Trans::getP1() {
	return p1;
}
sf::Vector2f Trans::getP2() {
	return p2;
}
void Trans::setLine(sf::Vector2f p1, sf::Vector2f p2) {
	line[0] = p1;
	line[1] = p2;
	line[0].color = sf::Color::Black;
	line[1].color = sf::Color(1, 235, 224);
}
sf::Vertex* Trans::getLine() {
	return line;
}
std::pair<std::shared_ptr<StateCircle>, std::shared_ptr<StateCircle>> Trans::getStates(void) {
	return std::pair<std::shared_ptr<StateCircle>, std::shared_ptr<StateCircle>>(s1,s2);
}
void Trans::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(line, 2, sf::Lines);
	target.draw(text);
}