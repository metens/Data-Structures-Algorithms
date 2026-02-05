#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string>
using namespace std;

namespace ansi {
    const string RESET = "\033[0m";
    const string RED   = "\033[31m";
    const string GREEN = "\033[32m";
    const string BLUE  = "\033[34m";

    string red(const string& s)   { return RED + s + RESET; }
    string green(const string& s) { return GREEN + s + RESET; }
    string blue(const string& s)  { return BLUE + s + RESET; }
}

// Abbreviate long addresses to two sig figs
string abbrev_addr(const void* addr) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%p", addr);

    int len = strlen(buffer);
    char last2[3] = { buffer[len - 2], buffer[len - 1], '\0' };

    return string("0x") + last2;
}

string format_float(double value) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%.1f", value);
    return string(buffer);
}

// Convert any value to a nice string for the box
template <typename T>
string value_to_string(const T& v) {
    if constexpr (is_pointer_v<T>) {
        if (v == nullptr) return "NULL";
        return abbrev_addr((const void*)v);
    }
    else if constexpr (is_same_v<T, bool>) {
        return v ? "true" : "false";
    }
    else if constexpr (is_same_v<T, char>) {
        string s = "'";
        s += v;
        s += "'";
        return s;
    }
    else if constexpr (is_floating_point_v<T>) {
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "%.1f", v);
        return string(buffer);
    }
    else {
        return std::to_string(v);
    }
}

// Generic display_var: works with any type
template <typename T>
void display_var(const string& name, const T& value, const void* addr) {

    string val_str  = ansi::green(value_to_string(value));   // value in green
    string addr_str = ansi::blue(abbrev_addr(addr));         // address in blue
    string name_str = ansi::red(name);                       // name in red

    cout << "\nname:     " << name_str << "\n";
    cout << "        |------|\n";

    // crude centering: pad to 6 chars (strip ANSI codes length effect is minor visually)
    string raw_val = value_to_string(value);
    if (raw_val.size() < 6) {
        int left = (6 - (int)raw_val.size()) / 2;
        int right = 6 - (int)raw_val.size() - left;
        cout << "value:  |" << string(left, ' ') << val_str << string(right, ' ') << "|\n";
    } else {
        cout << "value:  |" << val_str << "|\n";
    }

    cout << "        |------|\n";
    cout << "addr:     " << addr_str << "\n\n";
}

// Works for int
void display_var(const string& name, int value, const void* addr) {

      /*  num
        |------|
        |  10  |
        |------| 
          0x5a  */

    string val_str  = ansi::green(value_to_string(value));   // value in green
    string addr_str = ansi::blue(abbrev_addr(addr));         // address in blue
    string name_str = ansi::red(name);                       // name in red

    cout << "\nname:     " << name_str << endl;;
    cout << "        |------|\n";
    cout << "value:  |  " << val_str << "  |\n";
    cout << "        |------|\n";
    cout << "addr:     " << addr_str << "\n\n";
}

// Full display function showing the var val, the addr, and the var memory
template <typename T>
void display(const string& name, const T& value) {
    //cout << name << ": " << value_to_string(value) << endl;
    //cout << "&" << name << ": " << abbrev_addr(&value) << endl;
    display_var(name, value, &value);
}

void show_code(const string& line) {
    cout << "\033[36m" << line << "\033[0m\n"; // cyan
}
