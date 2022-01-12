#include <iostream>
#include <SFML/Graphics.hpp>
#include "DFA.h"
#include "DFA.cpp"
#include "StateCircle.h"
#include "Button.h"
#include "Trans.h"
#include "DisplayText.h"
#include "TransStr.h"
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <utility>
bool inGlobalBounds(std::shared_ptr<StateCircle> state, 
    std::vector<std::shared_ptr<StateCircle>> states);
pair<bool, std::shared_ptr<StateCircle>> mouseWithinAState(sf::Vector2i localPosition,
    std::vector<std::shared_ptr<StateCircle>> states);
void updateTransPosition(std::vector<std::shared_ptr<Trans>> transitions);
std::list<int> convertToList(std::string str);

int main(void) {
    std::list<int> str;
    std::string strInput;
    sf::RenderWindow window(sf::VideoMode(1200, 800), "state machine sim");
    std::vector<std::shared_ptr<StateCircle>> states;
    std::vector<std::shared_ptr<Trans>> transitions;
    std::vector<std::shared_ptr<StateCircle>> acceptStates;
    std::shared_ptr<StateCircle> tempState;
    std::shared_ptr<StateCircle> tempState2;
    // The dock that the newly created states populate on
    sf::RectangleShape stateDock;
    stateDock.setSize(sf::Vector2f(100,100));
    stateDock.setFillColor(sf::Color(115,115,115));
    stateDock.setOutlineColor(sf::Color::Black);
    stateDock.setOutlineThickness(10.f);
    // First state
    char q0c = 'A';
    std::string q0s;
    q0s.push_back(q0c);
    std::shared_ptr<StateCircle> q0 = std::make_shared<StateCircle>(q0s);
    q0->setGlobalFR(q0->getGlobalBounds());
    states.push_back(q0);
    tempState = q0;
    sf::Vector2f mouseDownPosition;
    // buttons
    Button newStateBtn("New State", sf::Vector2f(200, 35), sf::Vector2f(125, 50));
    Button newTransBtn("Transition", sf::Vector2f(350, 35), sf::Vector2f(125, 50));
    Button resetBtn("Reset", sf::Vector2f(200, 110), sf::Vector2f(125, 50));
    resetBtn.setColor(sf::Color::White);
    Button testStrBtn("Test String", sf::Vector2f(950, 110), sf::Vector2f(125, 50));
    testStrBtn.setColor(sf::Color::White);
    Button chooseAcceptBtn("Pick Accept\nState(s)", sf::Vector2f(350, 110), sf::Vector2f(125, 50));
    // typing field for testStrBtn
    Button typeFieldBtn("", sf::Vector2f(950, 35), sf::Vector2f(375, 50));
    // display texts
    DisplayText transPrompt("Please click a state to transition from", sf::Vector2f(450, 25),
        sf::Color(217, 17, 203));
    TransStr tstr(" ","","");
    DisplayText transDisplay(tstr.getStr(), sf::Vector2f(450, 50),
        sf::Color(225, 225, 225));
    char transChar;
    bool transBtnSelected = false;
    bool transCharEntered = false;
    bool transState1 = false;
    bool transState2 = false;
    bool displayLastStr = false;
    bool typeFieldBtnSelected = false;
    bool chooseAcceptBtnSelected = false;
   

    while (window.isOpen()) {
        //// DFA Object
        //DFA<int, int>* dfa = new DFA<int, int>(
        //    [states](int s) {
        //        for (int i = 0; i < states.size(); i++) {
        //            cout << static_cast<int>(states[i]->getStateChar());
        //            if (s == static_cast<int>(states[i]->getStateChar())) {
        //                return true;
        //            }
        //        }
        //        return false;
        //    },
        //    0,
        //        [transitions](int s, int c) {
        //        for (int i = 0; i < transitions.size(); i++) {
        //            if (s == static_cast<int>(transitions[i]->getStates().first->getStateChar()) &&
        //                c == transitions[i]->getC()) {
        //                return static_cast<int>(transitions[i]->getStates().second->getStateChar());
        //            }
        //        }
        //        return -1;
        //    },
        //        [acceptStates](int s) {
        //        for (int i = 0; i < acceptStates.size(); i++) {
        //            cout << static_cast<int>(acceptStates[i]->getStateChar());
        //            if (s == static_cast<int>(acceptStates[i]->getStateChar())) {
        //                return true;
        //            }
        //        }
        //        return false;
        //    }
        //    );

        sf::Event event;
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        pair<bool, std::shared_ptr<StateCircle>> mouseStateRet =
            mouseWithinAState(localPosition, states);
        for (int i = 0; i < states.size(); i++) {
            states[i]->setGlobalFR(states[i]->getGlobalBounds());
        }
        sf::FloatRect newStateBtnBounds = newStateBtn.getGlobalBounds();
        sf::FloatRect newTransBtnBounds = newTransBtn.getGlobalBounds();
        sf::FloatRect resetBtnBounds = resetBtn.getGlobalBounds();
        sf::FloatRect typeFieldBtnBounds = typeFieldBtn.getGlobalBounds();
        sf::FloatRect testStrBtnBounds = testStrBtn.getGlobalBounds();
        sf::FloatRect chooseAcceptBtnBounds = chooseAcceptBtn.getGlobalBounds();

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
                        newTransBtn.setColor(sf::Color::White);
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
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (newTransBtnBounds.contains(localPosition.x, localPosition.y) &&
                        states.back()->getPosition() != sf::Vector2f(50, 50)) {
                        transBtnSelected = true;
                        newTransBtn.setColor(sf::Color(193, 193, 193, 193));
                    }
                }
            }
            // if transition button is pressed 
            if (transBtnSelected == true && typeFieldBtnSelected == false) {
                // if after the transition button is pressed, a state is selected
                testStrBtn.setColor(sf::Color(193, 193, 193, 193));
                if (tempState->getGlobalFR().contains(localPosition.x, localPosition.y) && transState1 == false
                    && event.type == sf::Event::MouseButtonReleased) {
                    // store the selected state in a temp state
                    tempState->stateSelected(states);
                    tempState2 = tempState;
                    // first state selected is true
                    transState1 = true;
                }
                // if after transition button pressed, and first state selected, 
                // enter a character to assign a transition to
                if (transState1 == true) {
                    transPrompt.changeStr("Enter a Character");          
                    tstr.setS1(tempState2->getState());
                    transDisplay.changeStr(tstr.getStr());
                    if (event.type == sf::Event::TextEntered) {
                        if (event.text.unicode < 128) {
                            transChar = static_cast<char>(event.text.unicode);
                            transCharEntered = true;
                        }
                    }
                }
                // after selecting state, and character, select State to transition to
                if (transCharEntered == true && transState1 == true) {
                    transPrompt.changeStr("Click a State to transition to");                     
                    tstr.setC(transChar);
                    transDisplay.changeStr(tstr.getStr());
                    if (tempState->getGlobalFR().contains(localPosition.x, localPosition.y) &&
                        event.type == sf::Event::MouseButtonReleased) {
                        // store the selected state in a temp state
                        tempState->stateSelected(states);
                        // first state selected is true
                        transBtnSelected = false;
                        transCharEntered = false;
                        transState1 = false;    
                        displayLastStr = true;
                        std::shared_ptr<Trans> t = std::make_shared<Trans>();
                        t->setPoints(tempState2, tempState);
                        t->setC(transChar);
                        transitions.push_back(t);
                        transPrompt.changeStr("Transition made:");
                        tstr.setS2(tempState->getState());
                        transDisplay.changeStr(tstr.getStr());
                        newTransBtn.setColor(sf::Color::White);
                        testStrBtn.setColor(sf::Color::White);
                    }
                }
            }
            if (twoStatesSelected(states) && event.type == sf::Event::MouseButtonPressed &&
                mouseStateRet.first == false) {
                   resetTextColor(states); 
                   displayLastStr = false;
            }
            if (event.type == sf::Event::MouseButtonReleased && 
                event.mouseButton.button == sf::Mouse::Left){
                if (resetBtnBounds.contains(localPosition.x, localPosition.y)) {
                    std::cout << "Reset";
                    states.clear();
                    transitions.clear();
                    states.push_back(q0);
                    tempState = q0;
                    states[0]->setPosition(sf::Vector2i(50, 50));
                    q0c = 'A';
                }
                if (typeFieldBtnBounds.contains(localPosition.x, localPosition.y)) {
                    typeFieldBtnSelected = true;
                }
                if (testStrBtnBounds.contains(localPosition.x, localPosition.y)) {
                    cout << strInput;
                    
                    typeFieldBtn.changeName(strInput);
                    typeFieldBtnSelected = false;
                    str = convertToList(strInput);
                    // DFA Object
                    DFA<int, int>* dfa = new DFA<int, int>(
                        [states](int s) {
                            for (int i = 0; i < states.size(); i++) {
                                cout << "Q:" << static_cast<int>(states[i]->getStateChar());
                                if (s == static_cast<int>(states[i]->getStateChar())) {
                                    return true;
                                }
                            }
                            return false;
                        },
                        65,
                            [transitions](int s, int c) {
                            for (int i = 0; i < transitions.size(); i++) {
                                if (s == static_cast<int>(transitions[i]->getStates().first->getStateChar()) &&
                                    c == transitions[i]->getC()) {
                                    return static_cast<int>(transitions[i]->getStates().second->getStateChar());
                                }
                            }
                            return -1;
                        },
                            [acceptStates](int s) {
                            for (int i = 0; i < acceptStates.size(); i++) {
                                cout << "F:"<<static_cast<int>(acceptStates[i]->getStateChar()) << endl;
                                if (s == static_cast<int>(acceptStates[i]->getStateChar())) {
                                    return true;
                                }
                            }
                            return false;
                        }
                        );
                    if (dfa->accept(str)) {
                        cout << endl << "ACCEPT" << endl;
                    }
                    else {
                        cout << "str:";
                        
                           cout <<  dfa->d(0,str.front());
                        
                        cout << endl << "FAIL" << endl;
                    }
                    strInput.clear();
                    typeFieldBtn.changeName(strInput);
                }
                if (chooseAcceptBtnBounds.contains(localPosition.x, localPosition.y)) {
                    chooseAcceptBtnSelected = true;
                    tempState->makeAcceptState();
                    acceptStates.push_back(tempState);
                }
            }
            if (typeFieldBtnSelected) {
                if (event.type == sf::Event::TextEntered) {      
                    if (event.text.unicode < 128 && strInput.size() < 40) {
                        strInput.push_back(static_cast<char>(event.text.unicode)); 
                        typeFieldBtn.changeName(strInput);
                    }
                }
            }          
            updateTransPosition(transitions);
        }
        window.clear();
        window.RenderTarget::clear(sf::Color(153, 153, 153, 153));
        window.draw(stateDock);
        window.draw(newStateBtn);
        window.draw(newTransBtn);
        window.draw(resetBtn);
        window.draw(testStrBtn);
        window.draw(typeFieldBtn);
        window.draw(chooseAcceptBtn);
        // draw all the transitions
        for (int i = 0; i < transitions.size(); i++) {
            window.draw(*transitions[i]);
        }
        // draw all the states
        for (int i = 0; i < states.size(); i++) {
            window.draw(*states[i]);
        }
        // draw all the prompts and text
        if (transBtnSelected || displayLastStr) {
            window.draw(transPrompt);
            window.draw(transDisplay);            
        }
        else {
            transPrompt.changeStr("Please click a state to transition from");
            tstr.setS1(" ");
            tstr.setC("");
            tstr.setS2("");
            transDisplay.changeStr(tstr.getStr());
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
// if the mouse is within a states bounds this function returns that state,
// otherwise it returns false
pair<bool, std::shared_ptr<StateCircle>> mouseWithinAState(sf::Vector2i localPosition, 
    std::vector<std::shared_ptr<StateCircle>> states) {
        for (int i = 0; i < states.size(); i++) {
            if (states[i]->getGlobalFR().contains(localPosition.x, localPosition.y)) {
                return pair<bool, std::shared_ptr<StateCircle>>(true, states[i]);
            }
        }
        return pair<bool, std::shared_ptr<StateCircle>>(false, nullptr);
}
void updateTransPosition(std::vector<std::shared_ptr<Trans>> transitions) {
    for (int i = 0; i < transitions.size(); i++) {
        std::pair<std::shared_ptr<StateCircle>, std::shared_ptr<StateCircle>> ret = 
            transitions[i]->getStates();
        for (int j = 0; j < transitions.size(); j++) {
            std::pair<std::shared_ptr<StateCircle>, std::shared_ptr<StateCircle>> ret2 =
                transitions[j]->getStates();
            if ((ret.first == ret2.second) && (ret.second == ret2.first) && (!transitions[j]->isSelfLoop)) {
                transitions[j]->moveLine(ret2.first->getPosition(), ret2.second->getPosition());
                //transitions[i]->setText();
            }
            else{
                transitions[i]->setLine(ret.first->getPosition(), ret.second->getPosition());
                transitions[i]->setText();
            }
        }
            
    }
}
std::list<int> convertToList(std::string str) {
    list<int> ret;
    for (int i = 0; i < str.size(); i++) {
        ret.push_back(static_cast<int>(str[i]));
    }
    return ret;
}

