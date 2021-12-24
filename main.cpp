#include <iostream>
#include <SFML/Graphics.hpp>
#include "StateCircle.h"
#include "Button.h"
#include <string>
#include <vector>
#include <memory>
int main(void) {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "state machine sim");
    std::vector<std::shared_ptr<StateCircle>> states;
    std::vector<sf::FloatRect> stateBounds;
    char q0c = 'A';
    std::string q0s;
    q0s.push_back(q0c);
    std::shared_ptr<StateCircle> q0 = std::make_shared<StateCircle>(q0s);
    states.push_back(q0);
    sf::Vector2f mouseDownPosition;
    // button for creating a new state circle
    Button newStateBtn("New State", sf::Vector2f(1100, 35), sf::Vector2f(125, 50));

    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        for (int i = 0; i < states.size(); i++) {
            stateBounds.push_back(states[i]->getGlobalBounds());
        }
        sf::FloatRect newStateBtnBounds = newStateBtn.getGlobalBounds();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (newStateBtnBounds.contains(localPosition.x, localPosition.y)) {
                        q0c += 1;
                        q0s.erase();
                        q0s.push_back(q0c);
                        std::shared_ptr<StateCircle> newState = std::make_shared<StateCircle>(q0s);
                        states.push_back(newState);
                    }
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                for (int i = 0; i < stateBounds.size(); i++) {
                    if (stateBounds[i].contains(localPosition.x, localPosition.y)) {
                        sf::FloatRect temp = stateBounds[i];
                        for (int j = 0; j < states.size(); j++) {
                            if (temp == states[j]->getGlobalBounds()) {
                                sf::Vector2i newMousePosition = sf::Mouse::getPosition(window);
                                states[j]->setPosition(newMousePosition);
                            }
                        }
                    }
                }
            }

        }

        window.clear();
        for (int i = 0; i < states.size(); i++) {
            window.draw(*states[i]);
        }
        stateBounds.clear();
        window.draw(newStateBtn);
        window.display();
    }

    return 0;
}