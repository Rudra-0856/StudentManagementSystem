#include "StudentManager.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "utils.h"

StudentManager::StudentManager(std::string filePath) : filePath_(std::move(filePath)) {}

bool StudentManager::load() {
    students_.clear();
    std::ifstream in(filePath_);
    if (!in) return true;  // no file yet: start with empty database
    std::string line;
    while (std::getline(in, line)) {
        if (util::trim(line).empty()) continue;
        Student s;
        if (Student::deserialize(line, s)) students_.push_back(s);
        else std::cerr << "Warning: skipped corrupted record: " << line << "\n";
    }
    return true;
}

bool StudentManager::save() const {
    std::ofstream out(filePath_, std::ios::trunc);
    if (!out) return false;
    for (const auto& s : students_) out << s.serialize() << '\n';
    return static_cast<bool>(out);
}

Student* StudentManager::findByRoll(int rollNo) {
    for (auto& s : students_)
        if (s.getRollNo() == rollNo) return &s;
    return nullptr;
}

bool StudentManager::addStudent(const Student& s) {
    if (findByRoll(s.getRollNo())) return false;
    students_.push_back(s);
    std::sort(students_.begin(), students_.end(),
              [](const Student& a, const Student& b) { return a.getRollNo() < b.getRollNo(); });
    return save();
}

bool StudentManager::updateStudent(int rollNo, const Student& s) {
    Student* p = findByRoll(rollNo);
    if (!p) return false;
    *p = s;
    return save();
}

bool StudentManager::deleteStudent(int rollNo) {
    auto it = std::remove_if(students_.begin(), students_.end(),
                             [rollNo](const Student& s) { return s.getRollNo() == rollNo; });
    if (it == students_.end()) return false;
    students_.erase(it, students_.end());
    return save();
}

static std::string lower(std::string s) {
    for (char& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

std::vector<const Student*> StudentManager::searchByName(const std::string& query) const {
    std::vector<const Student*> res;
    std::string q = lower(query);
    for (const auto& s : students_)
        if (lower(s.getName()).find(q) != std::string::npos) res.push_back(&s);
    return res;
}

void StudentManager::printHeader() {
    util::line('=');
    std::cout << std::left << std::setw(8) << "Roll" << std::setw(22) << "Name" << std::setw(6) << "Age"
              << std::setw(20) << "Course" << std::setw(9) << "Marks" << "Grade\n";
    util::line('=');
}

void StudentManager::printRow(const Student& s) {
    std::cout << std::left << std::setw(8) << s.getRollNo() << std::setw(22) << s.getName().substr(0, 20)
              << std::setw(6) << s.getAge() << std::setw(20) << s.getCourse().substr(0, 18) << std::setw(9)
              << std::fixed << std::setprecision(1) << s.getMarks() << s.getGrade() << "\n";
}
