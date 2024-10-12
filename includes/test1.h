#ifndef TEST1_H
#define TEST1_H

#include <string>
#include <iostream>

class Print {
public:
    Print (std::string str) {
        std::cout << str << std::endl;
    }
};

#endif