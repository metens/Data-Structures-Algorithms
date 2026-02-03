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

void display_head_label(const std::string& top_line) {
    // Width of ONE node tile (from how you build top_line)
    const int tile_width = 10;   // Adjust if your node block string length differs

    const std::string label = "head";
    int pad = (tile_width - label.length()) / 2;

    std::cout << std::string(pad, ' ') << label << "\n";
    std::cout << std::string(pad + label.length()/2, ' ') << "|\n";
    std::cout << std::string(pad + label.length()/2, ' ') << "v\n";
}

std::string short_addr(const void* p) {
    std::uintptr_t value = reinterpret_cast<std::uintptr_t>(p);

    // Keep last 2 bytes (4 hex digits)
    unsigned short truncated = static_cast<unsigned short>(value & 0xFF);

    std::ostringstream oss;
    oss << "0x"
        << std::hex << std::nouppercase
        << std::setw(4) << std::setfill('0')
        << truncated;

    return oss.str();
}

void display_single_node(int data, const std::string& next_text, const std::string& addr_text) {
    std::cout << " --- ------\n";
    std::cout << "| " << data << " | " << next_text << " |\n";
    std::cout << " --- ------\n";
    std::cout << "   " << addr_text << "\n";
}

void marker_line(int index, int tile_w, const std::string& label) {
    // prints spaces until the chosen tile, then label
    std::cout << std::string(index * tile_w + (tile_w - (int)label.size())/2, ' ')
              << label << "\n";
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
            do { a = random_number(0x10, 0xAA); }
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

    display_head_label(top_line);
    std::cout << top_line  << "\n"
              << mid_line  << "\n"
              << bot_line  << "\n"
              << addr_line << "\n";
}

void snapshot(const std::string& title, node* head) {
    std::cout << "\n=== " << title << " ===\n";
    display_list(head);  // 
}
