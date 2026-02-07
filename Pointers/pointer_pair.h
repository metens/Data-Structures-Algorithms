#include <iostream>
#include <string>
#include "colors.h"

#include <type_traits>

// Color for an "address-looking thing"
inline std::string addr_color(const std::string& s) {
    return (s == "NULL") ? ansi::dim(s) : ansi::blue(s);
}

// Color for a normal "data value"
inline std::string data_color(const std::string& s) {
    return ansi::green(s);
}

// Color for names
inline std::string name_color(const std::string& s) {
    return ansi::red(s);
}

std::string pad6(const std::string& s) {
    if ((int)s.size() >= 6) return s.substr(0, 6);
    int left = (6 - (int)s.size()) / 2;
    int right = 6 - (int)s.size() - left;
    return std::string(left, ' ') + s + std::string(right, ' ');
}

// Make a value field: pointer values are addresses, non-pointers are data
template <typename X>
std::string value_field_colored(const X& x) {
    std::string raw = pad6(value_to_string(x));
    if constexpr (std::is_pointer_v<X>) return addr_color(raw);
    else return data_color(raw);
}

// Address line is always an address
inline std::string addr_field_colored(const void* p) {
    return ansi::blue(abbrev_addr(p));
}

template <typename P, typename T>
void display_pointer_pair(const std::string& ptr_name, const P& ptr,
                          const std::string& var_name, const T& var) {

    std::string ptr_stores_col = value_field_colored(ptr);     // BLUE (address) or dim NULL
    std::string var_val_col    = value_field_colored(var);     // GREEN (data)

    std::string ptr_addr_col   = addr_field_colored(&ptr);     // BLUE
    std::string var_addr_col   = addr_field_colored(&var);     // BLUE

    std::cout << "\n" << name_color(ptr_name) << "  --->  " << name_color(var_name) << "\n\n";

    std::cout << "name:    " << name_color(ptr_name) << "               " << name_color(var_name) << "\n";
    std::cout << "        |------|             |------|\n";
    std::cout << "value:  |" << ptr_stores_col << "| ----------> |" << var_val_col << "|\n";
    std::cout << "        |------|             |------|\n";
    std::cout << "addr:     " << ptr_addr_col << "                 " << var_addr_col << "\n";
}
template <typename P, typename T>
void display_pointer_deref(const std::string& ptr_name, const P& ptr,
                           const std::string& var_name, const T& var) {

    std::string ptr_stores_col = value_field_colored(ptr);     // BLUE (address)
    std::string var_val_col    = value_field_colored(var);     // GREEN (data)
    std::string var_addr_col   = addr_field_colored(&var);     // BLUE

    std::cout << "\n*" << name_color(ptr_name) << " == " << name_color(var_name) << "\n\n";

    std::cout << "name:    " << name_color(ptr_name) << "\n";
    std::cout << "        |------|\n";
    std::cout << "value:  |" << ptr_stores_col << "|\n";
    std::cout << "        |------|\n";

    std::cout <<
        "           |\n"
        "           | dereference (*)\n"
        "           v\n";

    std::cout << "        |------|\n";
    std::cout << "value:  |" << var_val_col << "|\n";          // GREEN here ✅
    std::cout << "        |------|\n";
    std::cout << "addr:     " << var_addr_col << "\n";
}
#pragma once
