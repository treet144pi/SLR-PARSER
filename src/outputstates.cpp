#include "outputstates.h"
#include <iostream>
#include <iomanip>

void Visualizer::printState(const std::string& stack,const std::string& input,const std::string& action)
{
    std::cout << std::left<< std::setw(20) << stack << " | "
              << std::setw(20) << input << " | "<< action << "\n";
}
void Visualizer::printHead() {
    std::cout << "---------------------------------------------------------\n";
    std::cout << std::left<< std::setw(20) << "STACK" << " | "
              << std::setw(20) << "INPUT" << " | "<< "ACTION\n";
    std::cout << "---------------------------------------------------------\n";
}


