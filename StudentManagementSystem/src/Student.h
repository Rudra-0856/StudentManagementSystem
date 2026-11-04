#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
public:
    Student() = default;
    Student(int rollNo, std::string name, int age, std::string course, double marks);

    int getRollNo() const { return rollNo_; }
    const std::string& getName() const { return name_; }
    int getAge() const { return age_; }
    const std::string& getCourse() const { return course_; }
    double getMarks() const { return marks_; }
    char getGrade() const;

    void setName(const std::string& n);
    void setAge(int a) { age_ = a; }
    void setCourse(const std::string& c);
    void setMarks(double m) { marks_ = m; }

    // File (de)serialisation: one record per line, fields separated by '|'
    std::string serialize() const;
    static bool deserialize(const std::string& line, Student& out);

private:
    static std::string sanitize(const std::string& s);

    int rollNo_ = 0;
    std::string name_;
    int age_ = 0;
    std::string course_;
    double marks_ = 0.0;
};

#endif
