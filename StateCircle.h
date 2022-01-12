#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>
#include <string>
class StateCircle : public sf::Drawable {
public:
	StateCircle(std::string initState);
	void setPosition(sf::Vector2i pos);
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	void setGlobalFR(sf::FloatRect initFr);
	sf::FloatRect getGlobalFR();
	sf::FloatRect getLocalBounds();
	void setTextColor(sf::Color color);
	sf::Color getTextColor();
	std::string getState();
	char getStateChar();
	void stateSelected(std::vector<std::shared_ptr<StateCircle>> states);
	void makeAcceptState(void);
private:
	std::string state;
	sf::CircleShape shape;
	sf::Font font;
	sf::Text text;
	sf::FloatRect global_fr;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
};

void resetTextColor(std::vector<std::shared_ptr<StateCircle>> states);
bool twoStatesSelected(std::vector<std::shared_ptr<StateCircle>> states);
#endif
