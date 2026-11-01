# CodeAlpha_StudentManagementSystem

A menu-driven C program to manage student records with permanent storage using file handling. Built as **Task 3** of the CodeAlpha C Programming Internship.

## Features

- **Add** a new student record
- **Display** all records in a formatted table
- **Search** a student by ID
- **Update** an existing record
- **Delete** a record
- Data is saved in a binary file (`students.dat`), so it persists between runs
- Prevents duplicate student IDs
- Input validation for numeric fields

## Student Record Fields

| Field | Type |
|-------|------|
| ID | `int` (unique) |
| Name | `char[50]` |
| Age | `int` |
| Course | `char[50]` |
| Marks | `float` |

## Getting Started

### Prerequisites

A C compiler such as GCC.

### Compile

```bash
gcc student_management.c -o student_management
```

### Run

```bash
./student_management
```

On Windows, run `student_management.exe` instead.

## Sample Run

```
=== Student Management System ===

1. Add Student
2. Display All Students
3. Search Student
4. Update Student
5. Delete Student
6. Exit
Enter your choice (1-6): 1
Enter ID: 101
Enter name: Alice
Enter age: 20
Enter course: Computer Science
Enter marks: 88.5
Student added successfully.

Enter your choice (1-6): 2

ID     Name                 Age   Course               Marks
---------------------------------------------------------------
101    Alice                20    Computer Science     88.50

Total records: 1
```

## How It Works

- Records are stored as `struct Student` objects in `students.dat` using `fread` and `fwrite`.
- **Add** appends to the file.
- **Update** finds the record, then overwrites it in place using `fseek`.
- **Delete** copies every record except the target into a temporary file, then replaces the original file.

## Concepts Used

- Structures (`struct`)
- File handling (`fopen`, `fread`, `fwrite`, `fseek`, `remove`, `rename`)
- Binary file I/O
- Functions and modular design
- `switch-case` menus and `do-while` loops
- Input validation

## Project Structure

```
CodeAlpha_StudentManagementSystem/
├── student_management.c
└── README.md
```
