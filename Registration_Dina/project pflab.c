#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "StudentData.txt"

// Function to register a student
void registerStudent() {
    FILE *file = fopen(FILE_NAME, "a"); // Open the file in append mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char name[50];
    int rollNo;
    float marks;

    printf("Enter student's name: ");
    scanf(" %[^\n]", name); // Read a line of text
    printf("Enter roll number: ");
    scanf("%d", &rollNo);
    printf("Enter marks: ");
    scanf("%f", &marks);

    fprintf(file, "%s,%d,%.2f\n", name, rollNo, marks); // Write data to the file
    fclose(file);
    printf("Student registered successfully!\n");
}

// Function to display all students
void displayStudents() {
    FILE *file = fopen(FILE_NAME, "r"); // Open the file in read mode
    if (file == NULL) {
        printf("No student data found!\n");
        return;
    }

    char line[100];
    printf("List of Students:\n");
    printf("Name\t\tRoll No\tMarks\n");
    printf("--------------------------------\n");
    while (fgets(line, sizeof(line), file)) {
        char name[50];
        int rollNo;
        float marks;
        sscanf(line, "%[^,],%d,%f", name, &rollNo, &marks); // Parse the data
        printf("%s\t%d\t%.2f\n", name, rollNo, marks);
    }

    fclose(file);
}

// Function to search for a student
void searchStudent() {
    FILE *file = fopen(FILE_NAME, "r"); // Open the file in read mode
    if (file == NULL) {
        printf("No student data found!\n");
        return;
    }

    int searchRollNo;
    printf("Enter roll number to search: ");
    scanf("%d", &searchRollNo);

    char line[100];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        char name[50];
        int rollNo;
        float marks;
        sscanf(line, "%[^,],%d,%f", name, &rollNo, &marks); // Parse the data
        if (rollNo == searchRollNo) {
            printf("Student Found:\n");
            printf("Name: %s\n", name);
            printf("Roll No: %d\n", rollNo);
            printf("Marks: %.2f\n", marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No student found with roll number %d!\n", searchRollNo);
    }

    fclose(file);
}

// Main function
int main() {
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Register Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}