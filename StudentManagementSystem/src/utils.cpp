#include "utils.h"

#include <iostream>
#include <stdexcept>

namespace util {

std::string trim(const std::string& s) {
    const char* ws = " \t\r\n";
    size_t b = s.find_first_not_of(ws);
    if (b == std::string::npos) return "";
    size_t e = s.find_last_not_of(ws);
    return s.substr(b, e - b + 1);
}

std::string readLine(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    if (!std::getline(std::cin, input)) throw std::runtime_error("Input closed");
    return trim(input);
}

int readInt(const std::string& prompt, int lo, int hi) {
    while (true) {
        std::string s = readLine(prompt);
        try {
            size_t pos = 0;
            int v = std::stoi(s, &pos);
            if (pos == s.size() && v >= lo && v <= hi) return v;
        } catch (const std::exception&) {}
        std::cout << "  Invalid input. Enter a whole number between " << lo << " and " << hi << ".\n";
    }
}

double readDouble(const std::string& prompt, double lo, double hi) {
    while (true) {
        std::string s = readLine(prompt);
        try {
            size_t pos = 0;
            double v = std::stod(s, &pos);
            if (pos == s.size() && v >= lo && v <= hi) return v;
        } catch (const std::exception&) {}
        std::cout << "  Invalid input. Enter a number between " << lo << " and " << hi << ".\n";
    }
}

bool confirm(const std::string& prompt) {
    while (true) {
        std::string s = readLine(prompt + " (y/n): ");
        if (s == "y" || s == "Y") return true;
        if (s == "n" || s == "N") return false;
        std::cout << "  Please enter y or n.\n";
    }
}

void pause() {
    readLine("\nPress Enter to continue...");
}

void line(char c, int n) {
    std::cout << std::string(n, c) << "\n";
}

}  // namespace util
