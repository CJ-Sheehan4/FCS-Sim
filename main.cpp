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
#include <algorithm>
bool inGlobalBounds(std::shared_ptr<StateCircle> state, 
    std::vector<std::shared_ptr<StateCircle>> states);
pair<bool, std::shared_ptr<StateCircle>> mouseWithinAState(sf::Vector2i localPosition,
    std::vector<std::shared_ptr<StateCircle>> states);
void updateTransPosition(std::vector<std::shared_ptr<Trans>> transitions);
std::list<int> convertToList(std::string str);
bool verifyTransitions(std::vector<std::shared_ptr<Trans>> transitions,
    std::shared_ptr<StateCircle> state, list<int> alpha, bool alphabetGot);
pair<string, sf::Color> testStrOnDFA(std::vector<std::shared_ptr<StateCircle>> states,
    std::vector<std::shared_ptr<Trans>> transitions,
    std::vector<std::shared_ptr<StateCircle>> acceptStates, list<int> str);

int main(void) {
    std::list<int> str;
    std::list<int> alpha;
    std::string strInput;
    sf::RenderWindow window(sf::VideoMode(1200, 800), "DFA sim");
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
    resetBtn.enable();
    Button submitBtn("Submit", sf::Vector2f(950, 130), sf::Vector2f(125, 50));
    Button chooseAcceptBtn("Accept\nState(s)", sf::Vector2f(350, 110), sf::Vector2f(125, 50));
    // typing field for testStrBtn
    Button typeFieldBtn("", sf::Vector2f(950, 55), sf::Vector2f(375, 50));
    // display texts
    DisplayText prompt("Please click a state to transition from", sf::Vector2f(450, 25),
        sf::Color(217, 17, 203));
    TransStr tstr(" ","","");
    DisplayText transDisplay(tstr.getStr(), sf::Vector2f(450, 50),
        sf::Color(225, 225, 225));
    DisplayText textAboveInputBox("Enter alphabet:", sf::Vector2f(760, 5),sf::Color::Black);
    char transChar;
    bool transCharEntered = false;
    bool transState1 = false;
    bool transState2 = false;
    bool displayLastStr = false;
    bool alphabetGot = false;

    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        pair<bool, std::shared_ptr<StateCircle>> mouseStateRet =
            mouseWithinAState(localPosition, states);
        for (int i = 0; i < states.size(); i++) {
            states[i]->setGlobalFR(states[i]->getGlobalBounds());
        }
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();            
            }
            // This if statement handles what happens When the left mouse button is relase
            if (event.type == sf::Event::MouseButtonReleased && 
                event.mouseButton.button == sf::Mouse::Left) {
                // if the new state button is clicked on
                if (newStateBtn.getGlobalBounds().contains(localPosition.x, localPosition.y) &&
                    states.back()->getPosition() != sf::Vector2f(50,50) &&
                    (!newTransBtn.isSelected()) && alphabetGot) {
                    q0c += 1;
                    q0s.erase();
                    q0s.push_back(q0c);
                    std::shared_ptr<StateCircle> newState = std::make_shared<StateCircle>(q0s);
                    states.push_back(newState);                   
                   newStateBtn.disable();
                   newTransBtn.setColor(sf::Color::White);
                    //newTransBtn.enable();
                }
                // if the new transition button is clicked on
                if (newTransBtn.getGlobalBounds().contains(localPosition.x, localPosition.y) &&
                    states.back()->getPosition() != sf::Vector2f(50, 50) && alphabetGot &&
                    (!typeFieldBtn.isSelected())) {
                    // all buttons disables when this is clicked on
                    newStateBtn.disable();
                    chooseAcceptBtn.disable();
                    typeFieldBtn.disable();
                    submitBtn.disable();
                    newTransBtn.disable();
                    newTransBtn.setSelected(true);
                }
                // if the reset button is clicked on 
                if (resetBtn.getGlobalBounds().contains(localPosition.x, localPosition.y)) {                  
                    newTransBtn.setSelected(false);
                    states.clear();
                    transitions.clear();
                    acceptStates.clear();
                    states.push_back(q0);
                    tempState = q0;
                    states[0]->setPosition(sf::Vector2i(50, 50));
                    q0c = 'A';
                    prompt.changeStr("");
                    tempState->unmakeAcceptState();
                    newStateBtn.disable();
                    newTransBtn.disable();
                    chooseAcceptBtn.disable();
                    alphabetGot = false;
                }
                // if the field is clicked on it type a string in
                if (typeFieldBtn.getGlobalBounds().contains(localPosition.x, localPosition.y) &&
                    (!newTransBtn.isSelected())) {
                    typeFieldBtn.setSelected(true);
                    typeFieldBtn.enable();
                    newTransBtn.disable();                    
                }
                // if test string button is clicked on
                // within here a DFA is created and the string is sent through it
                // to see if it accepts or rejects it
                if (submitBtn.getGlobalBounds().contains(localPosition.x, localPosition.y) &&
                    (!newTransBtn.isSelected())) {
                    typeFieldBtn.disable();
                    submitBtn.disable();
                    
                    typeFieldBtn.setSelected(false);
                    
                    if (!alphabetGot) {                      
                        strInput.clear();
                        str = convertToList(strInput);
                        typeFieldBtn.changeName(strInput);
                        alphabetGot = true;
                        prompt.changeStr("Now you can click and drag\nthe states to create your DFA");
                    }
                    else {
                        alpha.unique();
                        for (int i = 0; i < states.size(); i++) {
                            verifyTransitions(transitions, states[i], alpha, alphabetGot);
                        }                     
                        str = convertToList(strInput);
                        pair<string, sf::Color> res = testStrOnDFA(states, transitions, acceptStates, str);
                        prompt.changeStr(res.first);
                        prompt.changeColor(res.second);

                       
                        strInput.clear();
                        typeFieldBtn.changeName(strInput);
                    }
                }
                // if the choose accept state button is clicked on
                if (chooseAcceptBtn.getGlobalBounds().contains(localPosition.x, localPosition.y) &&
                    (!newTransBtn.isSelected()) && alphabetGot) {
                    chooseAcceptBtn.setSelected(true);
                    tempState->makeAcceptState();
                    acceptStates.push_back(tempState);
                }
            }
            // handles what happends when the left mouse button is held down
            // only applicable for clicking and dragging states
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && alphabetGot) {
               
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
                if (tempState->getGlobalFR().contains(localPosition.x, localPosition.y)) {
                    sf::Vector2i newMousePosition = sf::Mouse::getPosition(window);
                    tempState->setPosition(newMousePosition);
                    //newStateBtn.setColor(sf::Color::White);
                    newStateBtn.enable();
                    newTransBtn.enable();
                    chooseAcceptBtn.enable();
                }
            }    
            // if transition button was pressed, it goes through the process of 
            // selecting thhe state to transition from, the character, and the 
            // state it will transition to, according to the character
            if (newTransBtn.isSelected() && (!typeFieldBtn.isSelected())) {
                // if after the transition button is pressed, a state is selected
                prompt.changeColor(sf::Color(217, 17, 203));
                submitBtn.setColor(sf::Color(193, 193, 193, 193));
                prompt.changeStr("Please click a state to transition from");  
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
                    prompt.changeStr("Enter a Character");          
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
                    prompt.changeStr("Click a State to transition to");                     
                    tstr.setC(transChar);
                    transDisplay.changeStr(tstr.getStr());
                    if (tempState->getGlobalFR().contains(localPosition.x, localPosition.y) &&
                        event.type == sf::Event::MouseButtonReleased) {
                        // store the selected state in a temp state
                        tempState->stateSelected(states);
                        // first state selected is true
                        newTransBtn.setSelected(false);
                        transCharEntered = false;
                        transState1 = false;    
                        displayLastStr = true;
                        std::shared_ptr<Trans> t = std::make_shared<Trans>();
                        t->setPoints(tempState2, tempState);
                        t->setC(transChar);
                        transitions.push_back(t);
                        prompt.changeStr("Transition made:");
                        tstr.setS2(tempState->getState());
                        transDisplay.changeStr(tstr.getStr());
                        newStateBtn.enable();
                        chooseAcceptBtn.enable();
                        typeFieldBtn.enable();
                        submitBtn.enable();
                        newTransBtn.enable();
                    }
                }

            }
            if (twoStatesSelected(states) && event.type == sf::Event::MouseButtonPressed &&
                mouseStateRet.first == false) {
                   resetTextColor(states); 
                   displayLastStr = false;
                  
            }
            if (typeFieldBtn.isSelected()) {
                if (event.type == sf::Event::TextEntered) {      
                    if (event.text.unicode < 128 && strInput.size() < 40) {
                        if (!alphabetGot) {
                            strInput.push_back(static_cast<char>(event.text.unicode));
                            typeFieldBtn.changeName(strInput);
                            submitBtn.enable();
                            alpha = convertToList(strInput);
                        }
                        else {
                            strInput.push_back(static_cast<char>(event.text.unicode)); 
                            typeFieldBtn.changeName(strInput);
                            submitBtn.enable();
                        }
                    }
                }
            }
            if (alphabetGot) {
                textAboveInputBox.changeStr("Enter a string to test:");
            }
            else {
                prompt.changeStr("An alphabet must be entered to begin");
            }
            updateTransPosition(transitions);
        }
        window.clear();
        window.RenderTarget::clear(sf::Color(153, 153, 153, 153));
        window.draw(stateDock);
        window.draw(newStateBtn);
        window.draw(newTransBtn);
        window.draw(resetBtn);
        window.draw(submitBtn);
        window.draw(typeFieldBtn);
        window.draw(chooseAcceptBtn);
        window.draw(textAboveInputBox);
        // draw all the transitions
        for (int i = 0; i < transitions.size(); i++) {
            window.draw(*transitions[i]);
        }
        // draw all the states
        for (int i = 0; i < states.size(); i++) {
            window.draw(*states[i]);
        }
        // draw all the prompts and text
       // if (newTransBtn.isSelected() || displayLastStr || displayResults) {
            window.draw(prompt);
            if (newTransBtn.isSelected() || displayLastStr ) {
            window.draw(transDisplay);            
            }
        //}
       // else {
           // prompt.changeStr("Please click a state to transition from");
            //tstr.setS1(" ");
           // tstr.setC("");
           // tstr.setS2("");
            //transDisplay.changeStr(tstr.getStr());
       // }

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
bool verifyTransitions(std::vector<std::shared_ptr<Trans>> transitions,
    std::shared_ptr<StateCircle> state, list<int> alpha, bool alphabetGot) {
    bool ret = true;
    for (int j = 0; j < transitions.size(); j++) {
        if (state == transitions[j]->getStates().first) {
            char c = transitions[j]->getC();
            auto found = find(alpha.begin(), alpha.end(),
            static_cast<int>(c));
            if (found != alpha.end()) {
                alpha.remove(c);
            }
            else {
                cout << "error: transition character not in alphabet";
                ret = false;
            }
        }
    }
    if (!alpha.empty() && alphabetGot) {
        cout << "Error: All states must have exactly one transition per character";
        ret = false;
    }
    return ret;
}
pair<string, sf::Color> testStrOnDFA(std::vector<std::shared_ptr<StateCircle>> states,
    std::vector<std::shared_ptr<Trans>> transitions, 
    std::vector<std::shared_ptr<StateCircle>> acceptStates, list<int> str) {
    pair<string, sf::Color> ret;
    // DFA Object
    DFA<int, int>* dfa = new DFA<int, int>(
        [states](int s) {
            for (int i = 0; i < states.size(); i++) {
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
                if (s == static_cast<int>(acceptStates[i]->getStateChar())) {
                    return true;
                }
            }
            return false;
        });
    if (dfa->accept(str)) {
        ret.first = "ACCEPT";
        ret.second = sf::Color::Green;        
    }
    else {        
        ret.first = "Reject";
        ret.second = sf::Color::Red;
    }
    return ret;
}