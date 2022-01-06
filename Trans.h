#ifndef TRANS_H
#define TRANS_H
#include "StateCircle.h"
#include <SFML/Graphics.hpp>
#include <string>
class Trans : public sf::Drawable {
public:
	Trans();
	Trans(std::shared_ptr<StateCircle> s1, std::shared_ptr<StateCircle> s2);
	void setPoints(std::shared_ptr<StateCircle> s1, std::shared_ptr<StateCircle> s2);
private:
	sf::Vertex line[2];
	sf::Vector2f p1;
	sf::Vector2f p2;
	sf::Vertex arrow[2];
	sf::Vector2f a1;
	sf::Vector2f a2;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
};

#endif 
