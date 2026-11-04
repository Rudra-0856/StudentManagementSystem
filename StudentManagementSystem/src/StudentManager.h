#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include <string>
#include <vector>

#include "Student.h"

class StudentManager {
public:
    explicit StudentManager(std::string filePath);

    bool load();        // read records from file (OK if file is missing)
    bool save() const;  // write all records to file

    bool addStudent(const Student& s);              // false if roll no. exists
    bool updateStudent(int rollNo, const Student& s);
    bool deleteStudent(int rollNo);
    Student* findByRoll(int rollNo);
    std::vector<const Student*> searchByName(const std::string& query) const;

    const std::vector<Student>& all() const { return students_; }
    bool empty() const { return students_.empty(); }

    static void printHeader();
    static void printRow(const Student& s);

private:
    std::string filePath_;
    std::vector<Student> students_;
};

#endif
