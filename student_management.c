/*
 * CodeAlpha - C Programming Internship
 * Task 3: Student Management System
 *
 * Menu-driven program to Add, Display, Search, Update and Delete
 * student records. Data is stored permanently in a binary file.
 *
 * Compile: gcc student_management.c -o student_management
 * Run:     ./student_management
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "students.dat"
#define TEMP_FILE "temp.dat"
#define NAME_LEN  50

typedef struct {
    int   id;
    char  name[NAME_LEN];
    int   age;
    char  course[NAME_LEN];
    float marks;
} Student;

/* ---------- Input helpers ---------- */

static void readLine(const char *prompt, char *buf, int size) {
    printf("%s", prompt);
    if (fgets(buf, size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    buf[strcspn(buf, "\n")] = '\0';
}

static int readInt(const char *prompt) {
    char line[64];
    int value;
    while (1) {
        readLine(prompt, line, sizeof(line));
        if (sscanf(line, "%d", &value) == 1)
            return value;
        printf("Invalid number. Try again.\n");
    }
}

static float readFloat(const char *prompt) {
    char line[64];
    float value;
    while (1) {
        readLine(prompt, line, sizeof(line));
        if (sscanf(line, "%f", &value) == 1)
            return value;
        printf("Invalid number. Try again.\n");
    }
}

/* ---------- File helpers ---------- */

/* Returns 1 if a student with this ID exists */
static int idExists(int id) {
    FILE *fp = fopen(DATA_FILE, "rb");
    Student s;
    if (fp == NULL) return 0;
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.id == id) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

static void printHeader(void) {
    printf("\n%-6s %-20s %-5s %-20s %-7s\n", "ID", "Name", "Age", "Course", "Marks");
    printf("---------------------------------------------------------------\n");
}

static void printStudent(const Student *s) {
    printf("%-6d %-20s %-5d %-20s %-7.2f\n",
           s->id, s->name, s->age, s->course, s->marks);
}

/* ---------- Features ---------- */

static void addStudent(void) {
    Student s;
    FILE *fp;

    s.id = readInt("Enter ID: ");
    if (idExists(s.id)) {
        printf("A student with ID %d already exists.\n", s.id);
        return;
    }
    readLine("Enter name: ", s.name, NAME_LEN);
    s.age = readInt("Enter age: ");
    readLine("Enter course: ", s.course, NAME_LEN);
    s.marks = readFloat("Enter marks: ");

    fp = fopen(DATA_FILE, "ab");
    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return;
    }
    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Student added successfully.\n");
}

static void displayStudents(void) {
    FILE *fp = fopen(DATA_FILE, "rb");
    Student s;
    int count = 0;

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }
    printHeader();
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        printStudent(&s);
        count++;
    }
    fclose(fp);
    if (count == 0)
        printf("No records found.\n");
    else
        printf("\nTotal records: %d\n", count);
}

static void searchStudent(void) {
    FILE *fp = fopen(DATA_FILE, "rb");
    Student s;
    int id, found = 0;

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }
    id = readInt("Enter ID to search: ");
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.id == id) {
            printHeader();
            printStudent(&s);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (!found)
        printf("Student with ID %d not found.\n", id);
}

static void updateStudent(void) {
    FILE *fp = fopen(DATA_FILE, "rb+");
    Student s;
    int id, found = 0;

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }
    id = readInt("Enter ID to update: ");
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.id == id) {
            printf("Enter new details for ID %d:\n", id);
            readLine("Enter name: ", s.name, NAME_LEN);
            s.age = readInt("Enter age: ");
            readLine("Enter course: ", s.course, NAME_LEN);
            s.marks = readFloat("Enter marks: ");

            fseek(fp, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (found)
        printf("Record updated successfully.\n");
    else
        printf("Student with ID %d not found.\n", id);
}

static void deleteStudent(void) {
    FILE *fp = fopen(DATA_FILE, "rb");
    FILE *temp;
    Student s;
    int id, found = 0;

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }
    temp = fopen(TEMP_FILE, "wb");
    if (temp == NULL) {
        printf("Error: could not create temporary file.\n");
        fclose(fp);
        return;
    }
    id = readInt("Enter ID to delete: ");
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.id == id)
            found = 1;               /* skip this record */
        else
            fwrite(&s, sizeof(Student), 1, temp);
    }
    fclose(fp);
    fclose(temp);

    if (found) {
        remove(DATA_FILE);
        rename(TEMP_FILE, DATA_FILE);
        printf("Record deleted successfully.\n");
    } else {
        remove(TEMP_FILE);
        printf("Student with ID %d not found.\n", id);
    }
}

/* ---------- Main ---------- */

int main(void) {
    int choice;

    printf("=== Student Management System ===\n");
    do {
        printf("\n1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        choice = readInt("Enter your choice (1-6): ");

        switch (choice) {
            case 1: addStudent();      break;
            case 2: displayStudents(); break;
            case 3: searchStudent();   break;
            case 4: updateStudent();   break;
            case 5: deleteStudent();   break;
            case 6: printf("Goodbye!\n"); break;
            default: printf("Invalid choice. Enter a number from 1 to 6.\n");
        }
    } while (choice != 6);

    return 0;
}
