// Student Management System - console application (C++11 or later)
// Features: add, update, delete, display, search student records
// Persistence: records are stored in data/students.txt

#include <iostream>
#include <stdexcept>

#include "StudentManager.h"
#include "utils.h"

static const char* DATA_FILE = "data/students.txt";

static std::string requireText(const std::string& prompt) {
    while (true) {
        std::string s = util::readLine(prompt);
        if (!s.empty()) return s;
        std::cout << "  This field cannot be empty.\n";
    }
}

static void addStudent(StudentManager& mgr) {
    std::cout << "\n--- Add Student ---\n";
    int roll = util::readInt("Roll number (1-999999): ", 1, 999999);
    if (mgr.findByRoll(roll)) {
        std::cout << "A student with roll number " << roll << " already exists.\n";
        return;
    }
    std::string name = requireText("Name: ");
    int age = util::readInt("Age (5-100): ", 5, 100);
    std::string course = requireText("Course: ");
    double marks = util::readDouble("Marks (0-100): ", 0, 100);

    if (mgr.addStudent(Student(roll, name, age, course, marks)))
        std::cout << "Student added and saved successfully.\n";
    else
        std::cout << "Error: could not save to file.\n";
}

static void displayAll(const StudentManager& mgr) {
    std::cout << "\n--- All Students ---\n";
    if (mgr.empty()) {
        std::cout << "No records found.\n";
        return;
    }
    StudentManager::printHeader();
    for (const auto& s : mgr.all()) StudentManager::printRow(s);
    util::line('=');
    std::cout << "Total students: " << mgr.all().size() << "\n";
}

static void updateStudent(StudentManager& mgr) {
    std::cout << "\n--- Update Student ---\n";
    if (mgr.empty()) {
        std::cout << "No records to update.\n";
        return;
    }
    int roll = util::readInt("Roll number to update: ", 1, 999999);
    Student* s = mgr.findByRoll(roll);
    if (!s) {
        std::cout << "No student found with roll number " << roll << ".\n";
        return;
    }
    StudentManager::printHeader();
    StudentManager::printRow(*s);
    std::cout << "(Leave a field blank to keep its current value)\n";

    Student updated = *s;
    std::string in;

    in = util::readLine("New name [" + s->getName() + "]: ");
    if (!in.empty()) updated.setName(in);

    while (true) {
        in = util::readLine("New age [" + std::to_string(s->getAge()) + "]: ");
        if (in.empty()) break;
        try {
            size_t pos = 0;
            int a = std::stoi(in, &pos);
            if (pos == in.size() && a >= 5 && a <= 100) { updated.setAge(a); break; }
        } catch (const std::exception&) {}
        std::cout << "  Invalid age (5-100).\n";
    }

    in = util::readLine("New course [" + s->getCourse() + "]: ");
    if (!in.empty()) updated.setCourse(in);

    while (true) {
        in = util::readLine("New marks [" + std::to_string(s->getMarks()).substr(0, 5) + "]: ");
        if (in.empty()) break;
        try {
            size_t pos = 0;
            double m = std::stod(in, &pos);
            if (pos == in.size() && m >= 0 && m <= 100) { updated.setMarks(m); break; }
        } catch (const std::exception&) {}
        std::cout << "  Invalid marks (0-100).\n";
    }

    if (mgr.updateStudent(roll, updated))
        std::cout << "Student updated successfully.\n";
    else
        std::cout << "Error: could not save to file.\n";
}

static void deleteStudent(StudentManager& mgr) {
    std::cout << "\n--- Delete Student ---\n";
    if (mgr.empty()) {
        std::cout << "No records to delete.\n";
        return;
    }
    int roll = util::readInt("Roll number to delete: ", 1, 999999);
    Student* s = mgr.findByRoll(roll);
    if (!s) {
        std::cout << "No student found with roll number " << roll << ".\n";
        return;
    }
    StudentManager::printHeader();
    StudentManager::printRow(*s);
    if (util::confirm("Delete this record?")) {
        std::cout << (mgr.deleteStudent(roll) ? "Student deleted successfully.\n"
                                              : "Error: could not save to file.\n");
    } else {
        std::cout << "Deletion cancelled.\n";
    }
}

static void searchStudent(const StudentManager& mgr) {
    std::cout << "\n--- Search Student ---\n";
    std::string q = requireText("Enter name (or part of it): ");
    auto res = mgr.searchByName(q);
    if (res.empty()) {
        std::cout << "No matching students found.\n";
        return;
    }
    StudentManager::printHeader();
    for (auto p : res) StudentManager::printRow(*p);
    util::line('=');
    std::cout << res.size() << " match(es) found.\n";
}

static void showMenu() {
    std::cout << "\n";
    util::line('=');
    std::cout << "        STUDENT MANAGEMENT SYSTEM\n";
    util::line('=');
    std::cout << "  1. Add Student\n"
              << "  2. Display All Students\n"
              << "  3. Update Student\n"
              << "  4. Delete Student\n"
              << "  5. Search Student by Name\n"
              << "  0. Exit\n";
    util::line('-');
}

int main() {
    StudentManager mgr(DATA_FILE);
    mgr.load();

    try {
        while (true) {
            showMenu();
            int choice = util::readInt("Enter your choice: ", 0, 5);
            switch (choice) {
                case 1: addStudent(mgr); break;
                case 2: displayAll(mgr); break;
                case 3: updateStudent(mgr); break;
                case 4: deleteStudent(mgr); break;
                case 5: searchStudent(mgr); break;
                case 0:
                    std::cout << "Goodbye!\n";
                    return 0;
            }
            util::pause();
        }
    } catch (const std::runtime_error&) {
        std::cout << "\nInput closed. Exiting.\n";
    }
    return 0;
}
