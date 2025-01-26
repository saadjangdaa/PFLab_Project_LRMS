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
    int PassWord;
    int rollNo;
    

    printf("Enter student's name: ");
    scanf(" %[^\n]", name); // Read a line of text
    printf("Enter PassWord: ");
    scanf("%d", &PassWord);
    printf("Enter rollNo: ");
    scanf("%d", &rollNo);

    fprintf(file, "%s,%d,%d\n", name, PassWord, rollNo); // Write data to the file
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

    FILE *outputFile = fopen("OutputDisplay.txt", "w"); // File for storing display output
    if (outputFile == NULL) {
        printf("Error opening output file!\n");
        fclose(file);
        return;
    }

    char line[100];
    printf("\nList of Students:\n");
    printf("Name\t\tPassWord\tRollNo\n");
    printf("--------------------------------\n");
    fprintf(outputFile, "Name\t\tPassWord\tRoll No\n");
    fprintf(outputFile, "--------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        char name[50];
        int PassWord;
        int rollNo;
        
        sscanf(line, "%[^,],%d,%d", name, PassWord, rollNo); // Parse the data
        printf("%s\t\t%d\t%d\n", name, PassWord, rollNo);
        fprintf(outputFile, "%s\t\t%d\t%d\n", name, PassWord, rollNo);
    }

    fclose(file);
    fclose(outputFile);
    printf("Data has also been saved to 'OutputDisplay.txt'.\n");
}

// Function to search for a student
void searchStudent() {
    FILE *file = fopen(FILE_NAME, "r"); // Open the file in read mode
    if (file == NULL) {
        printf("No student data found!\n");
        return;
    }

    FILE *outputFile = fopen("OutputSearch.txt", "w"); // File for storing search results
    if (outputFile == NULL) {
        printf("Error opening output file!");
        fclose(file);
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
        int PassWord;
        sscanf(line, "%[^,],%d,%d", name, &PassWord, &rollNo); // Parse the data
        if (rollNo == searchRollNo) {
            printf("\nStudent Found:\n");
            printf("Name: %s\n", name);
            printf("PassWord: %d\n", PassWord);
            printf("Roll No: %d\n", rollNo);

            fprintf(outputFile, "Student Found:\n");
            fprintf(outputFile, "Name: %s\n", name);
            fprintf(outputFile, "PassWord: %d\n", PassWord);
            fprintf(outputFile, "Roll No: %d\n", rollNo);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nNo student found with roll number %d!\n", searchRollNo);
        fprintf(outputFile, "No student found with roll number %d!\n", searchRollNo);
    }

    fclose(file);
    fclose(outputFile);
    printf("Search results have been saved to 'OutputSearch.txt'.\n");
}

// Main function
int main() {
    int choice;

    do {
        printf("Menu:");
        printf("1. Register Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Exit\n");
        printf("Enter your choice:\n ");
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
                printf("Exiting the program...");
                break;
            default:
                printf("Invalid choice! Please try again.");
        }
    } while (choice != 4);

    return 0;
}

