#include "Trans.h"
#include <SFML/Graphics.hpp>
Trans::Trans() {

	line[0].color = sf::Color::Black;
	line[1].color = sf::Color::Black;
}
Trans::Trans(std::shared_ptr<StateCircle> s1, std::shared_ptr<StateCircle> s2) {
	p1 = s1->getPosition();
	p2 = s2->getPosition();
	
	line[0] = p1;
	line[1] = p2;
	line[0].color = sf::Color::Black;
	line[1].color = sf::Color::Black;
}
void Trans::setPoints(std::shared_ptr<StateCircle> s1, std::shared_ptr<StateCircle> s2) {
	p1 = s1->getPosition();
	p2 = s2->getPosition();

	line[0] = p1;
	line[1] = p2;
	line[0].color = sf::Color::Black;
	line[1].color = sf::Color(1, 235, 224);

	

}
void Trans::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(line, 2, sf::Lines);
	target.draw(arrow, 2, sf::Lines);
}