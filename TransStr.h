#ifndef TRANSSTR_H
#define TRANSSTR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class TransStr {
public:
    TransStr(std::string initstate1, std::string initc, std::string initstate2) {
        state1 = initstate1;
        if (initc == "") {
            c = ' ';
        }
        else {
            c = initc[0];
        }
        state2 = initstate2;
    }
    void setS1(std::string s) { state1 = s; }
    void setC(char sc) { c = sc; }
    void setC(std::string sc) { 
        if (sc == "") {
            c = ' ';
        }
        else {
            c = sc[0];
        }
    }
    void setS2(std::string s) { state2 = s; }
    std::string getStr() {
        std::string temp = "";
        temp.push_back(c);
        return "d(" + state1 + ", " + temp + ") = " + state2;
    }
    void print() {
        std::string temp = "";
        temp.push_back(c);
        std::cout << "d(" + state1 + ", " + temp + ") = " + state2;
    }
private:
    std::string state1;
    char c;
    std::string state2;
};

#endif