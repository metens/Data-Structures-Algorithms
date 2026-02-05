#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string>
using namespace std;

// Abbreviate long addresses to two sig figs
string abbrev_addr(const void* addr) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%p", addr);

    int len = strlen(buffer);
    char last2[3] = { buffer[len - 2], buffer[len - 1], '\0' };

    return string("0x") + last2;
}

// Works for int
void display_var(const string& name, int value, const void* addr) {

      /*  num
        |------|
        |  10  |
        |------| 
          0x5a  */

    string addr_str = abbrev_addr(addr);

    cout << "\n    " << name << endl;;
    cout << "  |------|\n";
    cout << "  |  " << value << "  |\n";
    cout << "  |------|\n";
    cout << "    " << addr_str << "\n\n";
}

string format_float(double value) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%.1f", value);
    return string(buffer);
}

// Convert any value to a nice string for the box
template <typename T>
string value_to_string(const T& v) {
    // Pointer types: show the address they store (abbreviated)
    if constexpr (is_pointer_v<T>) {
        if (v == nullptr) return "NULL";
        return abbrev_addr((const void*)v);
    }
    // bool: show true/false (or "1"/"0" if you prefer)
    else if constexpr (is_same_v<T, bool>) {
        return v ? "true" : "false";
    }
    // char: show the character, not ASCII code
    else if constexpr (is_same_v<T, char>) {
        string s = "'";
        s += v;
        s += "'";
        return s;
    }
    // Everything else that to_string supports (int, double, etc.)
    else if constexpr (is_floating_point_v<T>) {
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "%.1f", v);
        return string(buffer);
    }
}

// Generic display_var: works with any type
template <typename T>
void display_var(const string& name, const T& value, const void* addr) {
      /*  num
        |------|
        |  10  |
        |------| 
          0x5a  */

    string val_str = value_to_string(value);
    string addr_str = abbrev_addr(addr);

    // Optional: trim long strings (to keep box pretty)
    //if (val_str.size() > 6) val_str = val_str.substr(0, 6);

    cout << "\n    " << name << "\n";
    cout << "  |------|\n";

    // crude centering: pad to 6 chars
    if (val_str.size() < 6) {
        int left = (6 - (int)val_str.size()) / 2;
        int right = 6 - (int)val_str.size() - left;
        cout << "  |" << string(left, ' ') << val_str << string(right, ' ') << "|\n";
    } else {
        cout << "  |" << val_str << "|\n";
    }
    cout << "  |------|\n";
    cout << "    " << addr_str << "\n\n";
}
