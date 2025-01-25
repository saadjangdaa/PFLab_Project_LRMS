#include <stdio.h>
#include <string.h>

typedef struct {
    char studentID[20];
    char name[50];
    char contact[20];
} Student;

typedef struct {
    char laptopID[20];
    char brand[50];
    char specs[100];
    int isAvailable;
} Laptop;

int login();
void searchStudent();
void searchLaptop();

int main() {
    int choice;
    if (!login()) {
        printf("Login failed. Exiting program.\n");
        return 0;
    }

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Search Student\n");
        printf("2. Search Laptop\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchStudent();
                break;
            case 2:
                searchLaptop();
                break;
            case 3:
                printf("Exiting system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

int login() {
    char username[20], password[20];
    char adminUsername[] = "admin";
    char adminPassword[] = "1234";

    printf("\n--- Login ---\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, adminUsername) == 0 && strcmp(password, adminPassword) == 0) {
        printf("Login successful!\n");
        return 1;
    } else {
        printf("Invalid credentials.\n");
        return 0;
    }
}

void searchStudent() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open student records.\n");
        return;
    }

    char searchID[20];
    Student student;
    int found = 0;

    printf("\n--- Search Student ---\n");
    printf("Enter Student ID to search: ");
    scanf("%s", searchID);

    while (fscanf(file, "%s %s %s", student.studentID, student.name, student.contact) != EOF) {
        if (strcmp(student.studentID, searchID) == 0) {
            printf("\nStudent Found:\n");
            printf("ID: %s\nName: %s\nContact: %s\n", student.studentID, student.name, student.contact);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No student found with ID: %s\n", searchID);
    }

    fclose(file);
}

void searchLaptop() {
    FILE *file = fopen("laptops.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open laptop records.\n");
        return;
    }

    char searchID[20];
    Laptop laptop;
    int found = 0;

    printf("\n--- Search Laptop ---\n");
    printf("Enter Laptop ID to search: ");
    scanf("%s", searchID);

    while (fscanf(file, "%s %s %s %d", laptop.laptopID, laptop.brand, laptop.specs, &laptop.isAvailable) != EOF) {
        if (strcmp(laptop.laptopID, searchID) == 0) {
            printf("\nLaptop Found:\n");
            printf("ID: %s\nBrand: %s\nSpecs: %s\nAvailability: %s\n",
                   laptop.laptopID, laptop.brand, laptop.specs, laptop.isAvailable ? "Available" : "Not Available");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No laptop found with ID: %s\n", searchID);
    }

    fclose(file);
}
