#include <iostream>
#include <unordered_map>
#include <sstream>
#include <iomanip>

#include "random.h"

struct node {
    int data;
    node* next;
};

std::string to_hex(int value) {
    std::ostringstream oss;
    oss << "0x" << std::hex << std::nouppercase << value;
    return oss.str();
}

void display_list(node* head) {
    if (!head) {
        std::cout << "Empty list\n";
        return;
    }

    std::unordered_map<node*, int> addr;   // node → fake address
    std::unordered_map<int, bool> used;    // prevent duplicate addresses

    std::string top_line, mid_line, bot_line, addr_line;

    for (node* cur = head; cur != nullptr; cur = cur->next) {

        // Assign an address to this node if it doesn't have one yet
        if (!addr.count(cur)) {
            int a;
            do { a = random_number(0x10, 0xFF); }
            while (used[a]);
            used[a] = true;
            addr[cur] = a;
        }

        std::string this_addr = to_hex(addr[cur]);

        // Determine next pointer display
        std::string next_display;
        if (cur->next) {
            if (!addr.count(cur->next)) {
                int a;
                do { a = random_number(0x10, 0xFF); }
                while (used[a]);
                used[a] = true;
                addr[cur->next] = a;
            }
            next_display = to_hex(addr[cur->next]);
        } else {
            next_display = "NULL";
        }

        // Build ASCII art lines
        top_line += " ___ ______     ";

        std::ostringstream mid;
        mid << "| " << std::setw(1) << cur->data << " | "
            << std::setw(4) << std::left << next_display << std::right << " |";

        mid_line += mid.str();
        mid_line += (cur->next ? "--> " : "    ");

        bot_line += " --- ------     ";
        addr_line += "   " + this_addr + "         ";
    }

    std::cout << top_line  << "\n"
              << mid_line  << "\n"
              << bot_line  << "\n"
              << addr_line << "\n";
}
