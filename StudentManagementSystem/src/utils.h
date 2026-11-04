#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace util {

std::string trim(const std::string& s);
std::string readLine(const std::string& prompt);
int readInt(const std::string& prompt, int lo, int hi);
double readDouble(const std::string& prompt, double lo, double hi);
bool confirm(const std::string& prompt);
void pause();
void line(char c = '-', int n = 72);

}  // namespace util

#endif
