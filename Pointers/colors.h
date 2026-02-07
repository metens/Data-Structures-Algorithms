#include <iostream>
#include <string>
using namespace std;

namespace ansi {
    const std::string RESET = "\033[0m";
    const std::string DIM   = "\033[2m";
    const std::string RED   = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string BLUE  = "\033[34m";
    const std::string CYAN  = "\033[36m";

    string red(const string& s)   { return RED + s + RESET; }
    string green(const string& s) { return GREEN + s + RESET; }
    string blue(const string& s)  { return BLUE + s + RESET; }
    string dim(const std::string& s) {
        return DIM + s + RESET;
    }

}

#pragma once
