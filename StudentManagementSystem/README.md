# Student Management System (C++)

A console-based application to manage student records using file handling
and a menu-driven interface.

## Features
- Add, update, delete and display student records
- Search students by name
- Persistent storage in `data/students.txt` (loaded on start, saved on every change)
- Input validation, duplicate roll-number check, delete confirmation
- Automatic grade (A-F) from marks

## Project Structure
```
StudentManagementSystem/
├── src/
│   ├── main.cpp               # menu loop and user interaction
│   ├── Student.h/.cpp         # Student class + file serialisation
│   ├── StudentManager.h/.cpp  # CRUD logic + file load/save
│   └── utils.h/.cpp           # safe input helpers
├── data/students.txt          # created automatically (pipe-separated records)
├── Makefile
└── README.md
```

## Build & Run
Requires g++ (C++11 or newer).

```
make
./student_management
```
Or without make:
```
mkdir -p data && g++ -std=c++11 -o student_management src/*.cpp && ./student_management
```
Run the program from the project root so `data/students.txt` is found.

## Data Format
One record per line: `rollNo|name|age|course|marks`
