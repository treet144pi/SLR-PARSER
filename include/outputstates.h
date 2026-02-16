#pragma once
#include <string>

class Visualizer {
public:
    void printHead();
    void printState(const std::string& stack,const std::string& input,const std::string& action);
};
