#ifndef TRANS_H
#define TRANS_H
#include "StateCircle.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <utility>
class Trans : public sf::Drawable {
public:
	Trans();
	Trans(std::shared_ptr<StateCircle> initS1, std::shared_ptr<StateCircle> initS2);
	Trans(std::shared_ptr<StateCircle> initS1, std::shared_ptr<StateCircle> initS2, char initC);
	void setPoints(std::shared_ptr<StateCircle> initS1, std::shared_ptr<StateCircle> initS2);
	char getC();
	void setC(char newC);
	void setP1(sf::Vector2f p);
	void setP2(sf::Vector2f p);
	sf::Text getText();
	void setText();
	void changeText(std::string str);
	std::string getTextStr();
	sf::Vector2f getP1();
	sf::Vector2f getP2();
	void setLine(sf::Vector2f p1, sf::Vector2f p2);
	sf::Vertex *getLine();
	void moveLine(sf::Vector2f p1, sf::Vector2f p2);
	std::pair<std::shared_ptr<StateCircle>, std::shared_ptr<StateCircle>> getStates(void);
	bool isSelfLoop;
private:
	std::shared_ptr<StateCircle> s1;
	std::shared_ptr<StateCircle> s2;
	sf::Vertex line[2];
	sf::Vector2f p1;
	sf::Vector2f p2;
	sf::CircleShape selfLoop;
	
	sf::CircleShape arrow;
	char c;
	sf::Font font;
	sf::Text text;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
};

#endif 
