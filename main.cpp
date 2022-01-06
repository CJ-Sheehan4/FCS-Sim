#include <iostream>
#include <SFML/Graphics.hpp>
#include "DFA.h"
#include "DFA.cpp"
#include "StateCircle.h"
#include "Button.h"
#include "Trans.h"
#include <string>
#include <vector>
#include <memory>
bool inGlobalBounds(std::shared_ptr<StateCircle> state, 
    std::vector<std::shared_ptr<StateCircle>> states);

int main(void) {

    DFA<int, int>* dfa = new DFA<int, int>(
        [](int s) { return s == 0; },
        0,
        [](int s, int c) { return 0; },
        [](int s) {return false; }
        );

    sf::RenderWindow window(sf::VideoMode(1200, 800), "state machine sim");
    std::vector<std::shared_ptr<StateCircle>> states;
    std::shared_ptr<StateCircle> tempState;
    sf::RectangleShape stateDock;
    stateDock.setSize(sf::Vector2f(100,100));
    stateDock.setFillColor(sf::Color(115,115,115));
    stateDock.setOutlineColor(sf::Color::Black);
    stateDock.setOutlineThickness(10.f);
    char q0c = 'A';
    std::string q0s;
    q0s.push_back(q0c);
    std::shared_ptr<StateCircle> q0 = std::make_shared<StateCircle>(q0s);
    q0->setGlobalFR(q0->getGlobalBounds());
    states.push_back(q0);
    tempState = q0;
    sf::Vector2f mouseDownPosition;
    // button for creating a new state circle
    Button newStateBtn("New State", sf::Vector2f(200, 35), sf::Vector2f(125, 50));
    Button newTransBtn("Transition", sf::Vector2f(350, 35), sf::Vector2f(125, 50));
    Trans t;
    char transChar;
    bool transBtnSelected = false;
    bool transCharEntered = false;
    while (window.isOpen()) {
        
        sf::Event event;
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        for (int i = 0; i < states.size(); i++) {
            states[i]->setGlobalFR(states[i]->getGlobalBounds());
        }
        sf::FloatRect newStateBtnBounds = newStateBtn.getGlobalBounds();
        sf::FloatRect newTransBtnBounds = newTransBtn.getGlobalBounds();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (newStateBtnBounds.contains(localPosition.x, localPosition.y) &&
                        states.back()->getPosition() != sf::Vector2f(50,50)) {
                        q0c += 1;
                        q0s.erase();
                        q0s.push_back(q0c);
                        std::shared_ptr<StateCircle> newState = std::make_shared<StateCircle>(q0s);
                        states.push_back(newState);
                        newStateBtn.setColor(sf::Color(193, 193, 193, 193));
                    }
                    if (tempState->getGlobalFR().contains(localPosition.x, localPosition.y)) {
                        tempState->stateSelected(states);
                        if (transCharEntered == true && transBtnSelected == true) {
                            transBtnSelected = false;
                            cout << "Transition Made: " << tempState->getState() <<
                                " " << transChar;
                        }
                    }
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                for (int i = 0; i < states.size(); i++) {
                    // if there is a state that has the mouse position in it, and left button 
                    // is pressed, and its not within the global bounds of any of the other states,
                    // then set it to the temp state
                    if (states[i]->getGlobalFR().contains(localPosition.x, localPosition.y)
                        && !inGlobalBounds(states[i], states)) {
                        tempState = states[i];
                        break;
                    }
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
                if (tempState->getGlobalFR().contains(localPosition.x, localPosition.y)) {
                    sf::Vector2i newMousePosition = sf::Mouse::getPosition(window);
                    tempState->setPosition(newMousePosition);
                    newStateBtn.setColor(sf::Color::White);
                }
            }
         /*   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                t.setPoints(states[0], states[1]);
            }*/
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (newTransBtnBounds.contains(localPosition.x, localPosition.y) &&
                        states.back()->getPosition() != sf::Vector2f(50, 50)) {
                        transBtnSelected = true;
                    }
                }
            }
            if (transBtnSelected == true) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) {
                        transChar = static_cast<char>(event.text.unicode);
                        transCharEntered = true;
                    }
                    
                }
            }
        }
        window.clear();
        window.RenderTarget::clear(sf::Color(153, 153, 153, 153));
        window.draw(stateDock);
        window.draw(newStateBtn);
        window.draw(newTransBtn);
        window.draw(t);

        for (int i = 0; i < states.size(); i++) {
            window.draw(*states[i]);
        }
        window.display();
    }

    return 0;
}
bool inGlobalBounds(std::shared_ptr<StateCircle> state, std::vector<std::shared_ptr<StateCircle>> states) {
    for (int i = 0; i < states.size(); i++) {
        if (states[i]->getGlobalFR().intersects(state->getGlobalFR())
            && states[i] != state) {
            return true;
        }
    }
}
