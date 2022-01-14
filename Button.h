#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <string>
class Button : public sf::Drawable {
public:
	Button(std::string inittext, sf::Vector2f initpos, sf::Vector2f initsize);
	void setColor(sf::Color color);
	void changeName(std::string str);
	void setSelected(bool s);
	bool isSelected(void);
	void enable(void);
	void disable(void);
	bool isEnabled(void);
	sf::FloatRect getGlobalBounds();
	sf::FloatRect getLocalBounds();
private:
	std::string buttonText;
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;
	bool selected;
	bool enabled;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
};

#endif 
