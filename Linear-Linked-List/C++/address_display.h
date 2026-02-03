#include <iostream>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <cstdint>

#include "random.h"

namespace ansi {
    const std::string RESET  = "\033[0m";
    const std::string BOLD   = "\033[1m";
    const std::string RED    = "\033[31m";
    const std::string GREEN  = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE   = "\033[34m";
    const std::string CYAN   = "\033[36m";

    inline std::string color(const std::string& s, const std::string& c) {
        return c + s + RESET;
    }
}

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

    std::cout << std::string(pad, ' ') << ansi::color(label, ansi::CYAN) << "\n";
    std::cout << std::string(pad + label.length()/2, ' ') << "|\n";
    std::cout << std::string(pad + label.length()/2, ' ') << "v\n";
}

std::string short_addr(const void* p) {
    std::uintptr_t value = reinterpret_cast<std::uintptr_t>(p);

    // Keep last 1 byte (2 hex digits)
    std::uint8_t truncated = static_cast<std::uint8_t>(value & 0xFF);

    std::ostringstream oss;
    oss << "0x"
        << std::hex << std::nouppercase
        << std::setw(2) << std::setfill('0')
        << static_cast<int>(truncated);  // cast so it's printed as number, not char

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

    std::string top_line, mid_line, bot_line, addr_line;

    for (node* cur = head; cur != nullptr; cur = cur->next) {
        std::string this_addr = short_addr(cur);
        std::string next_display = cur->next ? short_addr(cur->next) : "NULL";

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
