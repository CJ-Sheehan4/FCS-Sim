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
	arrow.setRadius(7.5);
	//arrow.setPointCount(3);
	arrow.setFillColor(sf::Color::Black);
	sf::FloatRect arrowRect = arrow.getLocalBounds();
	arrow.setOrigin(arrowRect.left + arrowRect.width / 2.0f,
		arrowRect.top + arrowRect.height / 2.0f);
	
	if (s1->getState() == s2->getState()) {
		selfLoop.setRadius(25.f);
		selfLoop.setFillColor(sf::Color::Transparent);
		selfLoop.setOutlineColor(sf::Color::Black);
		selfLoop.setOutlineThickness(2);
		selfLoop.setPosition(p1.x-25,p1.y-70);
		arrow.rotate(180);
		arrow.setPosition(selfLoop.getPosition().x + selfLoop.getRadius()*2, 
			selfLoop.getPosition().y + selfLoop.getRadius()-2);
		isSelfLoop = true;
	}
	else {
		line[0] = p1;
		line[1] = p2;
		line[0].color = sf::Color::Black;
		line[1].color = sf::Color(1, 235, 224);

		sf::Vector2f s1Pos = s1->getPosition();
		sf::Vector2f s2Pos = s2->getPosition();
		float ty = (s2Pos.y + s1Pos.y) / 2;
		float tx = (s2Pos.x + s1Pos.x) / 2;
		float ty2 = (ty + s2Pos.y) / 2;
		float tx2 = (tx + s2Pos.x) / 2;
		arrow.setPosition(tx2, ty2);
		isSelfLoop = false;
		//arrow.rotate(ty2);
	}
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
	if (p1 == p2) {
		sf::Vector2f s1Pos = s1->getPosition();
		float ty = selfLoop.getPosition().y;
		float tx = selfLoop.getPosition().x+25;
		text.setPosition(tx,ty);
	
	}
	else {
		sf::Vector2f s1Pos = s1->getPosition();
		sf::Vector2f s2Pos = s2->getPosition();
		float ty = (s2Pos.y + s1Pos.y) / 2;
		float tx = (s2Pos.x + s1Pos.x) / 2;
		text.setPosition(tx, ty);
	}
	
}
sf::Vector2f Trans::getP1() {
	return p1;
}
sf::Vector2f Trans::getP2() {
	return p2;
}
void Trans::setLine(sf::Vector2f p1, sf::Vector2f p2) {
	if (p1 == p2) {
		selfLoop.setPosition(p1.x - 25, p1.y - 70);
		arrow.setPosition(selfLoop.getPosition().x + selfLoop.getRadius() * 2,
			selfLoop.getPosition().y + selfLoop.getRadius() - 2);
		
	}
	else {
		line[0] = p1;
		line[1] = p2;
		line[0].color = sf::Color::Black;
		line[1].color = sf::Color(1, 235, 224);
		sf::Vector2f s1Pos = s1->getPosition();
		sf::Vector2f s2Pos = s2->getPosition();
		float ty = (s2Pos.y + s1Pos.y) / 2;
		float tx = (s2Pos.x + s1Pos.x) / 2;
		float ty2 = (ty + s2Pos.y) / 2;
		float tx2 = (tx + s2Pos.x) / 2;
		arrow.setPosition(tx2, ty2);
		
		
	}
	
}
sf::Vertex* Trans::getLine() {
	return line;
}
void Trans::moveLine(sf::Vector2f p1, sf::Vector2f p2) {
	float rangeneg = p2.x - 100;
	float rangepos = p2.x + 100;
	if (rangeneg < p1.x && p1.x < rangepos) {
		p1 = sf::Vector2f(p1.x+20, p1.y);
		line[0] = p1;
		p2 = sf::Vector2f(p2.x+20, p2.y );
		line[1] = p2;
	}
	else {
		p1 = sf::Vector2f(p1.x, p1.y + 20);
		line[0] = p1;
		p2 = sf::Vector2f(p2.x, p2.y + 20);
		line[1] = p2;
	}
	
	line[0].color = sf::Color::Black;
	line[1].color = sf::Color(1, 235, 224);
	//sf::Vector2f s1Pos = p1->getPosition();
	//sf::Vector2f s2Pos = s2->getPosition();
	float ty = (p2.y + p1.y) / 2;
	float tx = (p2.x + p1.x) / 2;
	float ty2 = (ty + p2.y) / 2;
	float tx2 = (tx + p2.x) / 2;
	arrow.setPosition(tx2, ty2);
	text.setPosition(tx, ty);
}
std::pair<std::shared_ptr<StateCircle>, std::shared_ptr<StateCircle>> Trans::getStates(void) {
	return std::pair<std::shared_ptr<StateCircle>, std::shared_ptr<StateCircle>>(s1,s2);
}
void Trans::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	
	target.draw(line, 2, sf::Lines);
	target.draw(selfLoop);
	target.draw(text);
	target.draw(arrow);
}