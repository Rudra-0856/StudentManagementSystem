#include "Student.h"

#include <sstream>
#include <vector>

Student::Student(int rollNo, std::string name, int age, std::string course, double marks)
    : rollNo_(rollNo), name_(sanitize(name)), age_(age), course_(sanitize(course)), marks_(marks) {}

char Student::getGrade() const {
    if (marks_ >= 90) return 'A';
    if (marks_ >= 75) return 'B';
    if (marks_ >= 60) return 'C';
    if (marks_ >= 40) return 'D';
    return 'F';
}

void Student::setName(const std::string& n) { name_ = sanitize(n); }
void Student::setCourse(const std::string& c) { course_ = sanitize(c); }

std::string Student::sanitize(const std::string& s) {
    std::string r = s;
    for (char& ch : r)
        if (ch == '|' || ch == '\n' || ch == '\r') ch = ' ';
    return r;
}

std::string Student::serialize() const {
    std::ostringstream os;
    os << rollNo_ << '|' << name_ << '|' << age_ << '|' << course_ << '|' << marks_;
    return os.str();
}

bool Student::deserialize(const std::string& line, Student& out) {
    std::vector<std::string> parts;
    std::string field;
    std::istringstream is(line);
    while (std::getline(is, field, '|')) parts.push_back(field);
    if (parts.size() != 5) return false;
    try {
        out = Student(std::stoi(parts[0]), parts[1], std::stoi(parts[2]), parts[3], std::stod(parts[4]));
    } catch (const std::exception&) {
        return false;
    }
    return true;
}
