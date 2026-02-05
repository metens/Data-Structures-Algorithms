#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string>
using namespace std;

string abbrev_addr(const void* addr) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%p", addr);

    int len = strlen(buffer);
    char last2[3] = { buffer[len - 2], buffer[len - 1], '\0' };

    return string("0x") + last2;
}

void display_var(const std::string& name, int value, const void* addr) {

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
