#include <iostream>
#include <string>
#include <map>

#include "random.h"

void display_list(node* head) {

    std::map<std::string, int> addresses;   // Map of addresses for each node
    addresses.insert ( std::pair<string, int>(,100) );

    // The linear linked list will be displayed as such:

    // top_line:     ___ ______      ___ ___
    // mid_line:    | 5 | 0x5a |--> | 8 | / |
    // bot_line:     --- ------      --- ---
    // addr_line:       0x11           0x5a

    std::string top_line = "";
    std::string mid_line = "";
    std::string bot_line = "";
    std::string addr_line ="";

    for (node* current = head; current != nullptr; current = current -> next) {
        
        top_line += " ___ ______     ";

        if (current -> next) {
            mid_line += "| " + std::to_string(num) + " |" + " 0x" + std::hex std::to_string(addresses()) + " |--> ";
        }
        else if (!current) {
            mid_line += "| " + std::to_string(num) + " | / |";
            bot_line += " --- ---";
        }
        else {
            bot_line += " --- -------     "
            addr_line += "   " + node_addr + "        "
        }
    }

    cout << top_line << endl;
    cout << mid_line << endl;
    cout << bot_line << endl;
    cout << addr_line << endl;
}
