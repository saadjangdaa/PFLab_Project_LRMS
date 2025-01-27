#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILE_NAME "StudentData.txt"
#define USER_FILE "user.txt"

// Function Declarations
bool login(int *role);
void adminMenu();
void studentMenu();
void bookLaptop(int studentID, int laptopID, int status);
void returnLaptop(int studentID, int laptopID);
void saveRentalDetails(int studentID, int laptopID, int rentalDurationHours, int rentalDurationDays, int rentalChargePerHour);
void searchStudent();
void searchLaptop();
void registerStudent();
void displayStudents();
void signup();
void keyTracker(int id_position);
void addLaptop(int id_position);
void displayLaptop(int id_position);
void updateLaptopStatus(int laptopID, int newStatus);

// Main Function
int main() {
    int role; // Role: 0 for admin, 1 for student
    int choice;

    while (1) {
        printf("\n--- Welcome to the System ---\n");
        printf("1. Login\n");
        printf("2. Signup\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (login(&role)) {
                    if (role == 0) {
                        adminMenu();
                    } else if (role == 1) {
                        studentMenu();
                    }
                } else {
                    printf("Login failed. Please try again.\n");
                }
                break;
            case 2:
                signup();
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Login Function
bool login(int *role) {
    char inputUsername[50], inputPassword[50];
    char line[100];
    bool loginSuccess = false;

    printf("\n--- Login ---\n");
    printf("Enter username: ");
    scanf("%s", inputUsername);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    FILE *file = fopen(USER_FILE, "r");
    if (file == NULL) {
        printf("No user data found! Please signup first.\n");
        return false;
    }

    while (fgets(line, sizeof(line), file)) {
        char fileUsername[50], filePassword[50];
        int fileRole;

        if (sscanf(line, "Username: %s Password: %s Role: %d", fileUsername, filePassword, &fileRole) == 3) {
            if (strcmp(inputUsername, fileUsername) == 0 && strcmp(inputPassword, filePassword) == 0) {
                *role = fileRole;
                loginSuccess = true;
                printf("Login successful! Welcome, %s.\n", fileUsername);
                break;
            }
        }
    }

    if (!loginSuccess) {
        printf("Invalid username or password.\n");
    }

    fclose(file);
    return loginSuccess;
}

// Admin Menu Function
void adminMenu() {
    int choice;
    while (1) {
        printf("\n--- Admin Menu ---\n");
        printf("1. Register Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Logout\n");
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
                printf("Logging out. Goodbye!\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Student Menu Function
void studentMenu() {
    int choice, studentID, laptopID;

    while (1) {
        printf("\n--- Student Menu ---\n");
        printf("1. Book Laptop\n");
        printf("2. Return Laptop\n");
        printf("3. Display Available Laptops\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter your Student ID: ");
                scanf("%d", &studentID);
                printf("Enter Laptop ID to book: ");
                scanf("%d", &laptopID);
                bookLaptop(studentID, laptopID, 1);
                break;
            case 2:
                printf("Enter your Student ID: ");
                scanf("%d", &studentID);
                printf("Enter Laptop ID to return: ");
                scanf("%d", &laptopID);
                returnLaptop(studentID, laptopID);
                break;
            case 3:
                displayLaptop(studentID);
                break;
            case 4:
                printf("Logging out. Goodbye!\n");
                return;
            default:
                printf("Invalid choice.\n");
        }
    }
}

// Booking Module
void bookLaptop(int studentID, int laptopID, int status) {
    FILE *fptr = fopen("BookingData.txt", "r+");
    if (fptr == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    char line[100];
    int fileStudentID, fileLaptopID, fileStatus;
    int isBooked = 0;

    while (fgets(line, sizeof(line), fptr)) {
        sscanf(line, "Student ID: %d, Laptop ID: %d, Status: %d", &fileStudentID, &fileLaptopID, &fileStatus);
        if (fileLaptopID == laptopID && fileStatus == 1) {
            isBooked = 1;
            break;
        }
    }

    if (isBooked) {
        printf("Laptop ID: %d is already booked.\n", laptopID);
    } else {
        fprintf(fptr, "Student ID: %d, Laptop ID: %d, Status: %d\n", studentID, laptopID, status);
        printf("Booking successful! Student ID: %d, Laptop ID: %d.\n", studentID, laptopID);
        saveRentalDetails(studentID, laptopID, 48, 2, 200);
    }

    fclose(fptr);
}

// Return Laptop
void returnLaptop(int studentID, int laptopID) {
    FILE *fptr = fopen("BookingData.txt", "r");
    FILE *tempFile = fopen("TempData.txt", "w");
    if (fptr == NULL || tempFile == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    char line[100];
    int found = 0;

    while (fgets(line, sizeof(line), fptr)) {
        int fileStudentID, fileLaptopID, status;
        sscanf(line, "Student ID: %d, Laptop ID: %d, Status: %d", &fileStudentID, &fileLaptopID, &status);

        if (fileStudentID == studentID && fileLaptopID == laptopID && status == 1) {
            fprintf(tempFile, "Student ID: %d, Laptop ID: %d, Status: 0\n", fileStudentID, fileLaptopID);
            found = 1;
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(fptr);
    fclose(tempFile);

    remove("BookingData.txt");
    rename("TempData.txt", "BookingData.txt");

    if (found)
        printf("Laptop successfully returned for Student ID: %d, Laptop ID: %d\n", studentID, laptopID);
    else
        printf("Booking not found or already returned.\n");
}

// Save Rental Details
void saveRentalDetails(int studentID, int laptopID, int rentalDurationHours, int rentalDurationDays, int rentalChargePerHour) {
    FILE *fptr = fopen("RentalDetailsData.txt", "a");
    if (fptr == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    fprintf(fptr, "Student ID: %d, Laptop ID: %d, Rental Duration: %d hours, Rental Charge: %d\n", studentID, laptopID, rentalDurationHours, rentalChargePerHour);
    fclose(fptr);
}

// Search Student Function
void searchStudent() {
    FILE *file = fopen(FILE_NAME, "r");
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
        int password, rollNo;

        sscanf(line, "%[^,],%d,%d", name, &password, &rollNo);
        if (rollNo == searchRollNo) {
            printf("Student Found: %s, Roll Number: %d, Password: %d\n", name, rollNo, password);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found!\n");

    fclose(file);
}

// Register Student
// Register Student
void registerStudent() {
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    char name[50];
    char password[50], rollNo[50];  // Using string types for rollNo and password

    printf("Enter name: ");
    scanf("%s", name);  // Read student name as a string

    printf("Enter roll number: ");
    scanf("%s", rollNo);  // Read roll number as a string (if it can contain alphanumeric values)

    printf("Enter password: ");
    scanf("%s", password);  // Read password as a string

    // Save student data to the file, assuming rollNo and password are alphanumeric
    fprintf(file, "%s,%s,%s\n", name, rollNo, password);
    fclose(file);
    printf("Student registered successfully!\n");
}


// Display Students
void displayStudents() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No student data found!\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char name[50];
        int password, rollNo;
        sscanf(line, "%[^,],%d,%d", name, &password, &rollNo);
        printf("Name: %s, Roll Number: %d, Password: %d\n", name, rollNo, password);
    }

    fclose(file);
}

// Function Definitions for the other functions (keyTracker, addLaptop, etc.) would be added as needed.

// Signup Function
void signup() {
    char username[50], password[50];

    printf("\n--- Signup ---\n");
    printf("Enter a username: ");
    scanf("%s", username);
    printf("Enter a password: ");
    scanf("%s", password);

    FILE *file = fopen(USER_FILE, "a"); // Open the file in append mode
    if (file == NULL) {
        printf("Error opening user file!\n");
        return;
    }

    fprintf(file, "Username: %s Password: %s Role: 1\n", username, password);
    fclose(file);

    printf("Signup successful! You can now login.\n");
}










// Function to add a laptop
void addLaptop(int id_position) {
    FILE *fptr = fopen("Laptop-Data.txt", "a");
    if (fptr == NULL) {
        printf("Error opening laptop data file!\n");
        return;
    }

    char laptop_id[10], laptop_brand[20];
    int laptop_status;

    printf("Enter Laptop ID: ");
    scanf("%s", laptop_id);  // Restrict size if needed
    printf("Enter Laptop Brand: ");
    scanf("%s", laptop_brand);
    printf("Enter Laptop Status (0 for available, 1 for booked): ");
    scanf("%d", &laptop_status);

    fprintf(fptr, "Laptop ID: %s, Brand: %s, Status: %d\n", laptop_id, laptop_brand, laptop_status);
    fclose(fptr);
    printf("Laptop added successfully!\n");
}

// Function to display laptops
void displayLaptop(int id_position) {
    char read;
    FILE *fptr = fopen("Laptop-Data.txt", "r");
    printf("******Reading File******\n\n");
    
    if (fptr == NULL) {
        printf("File does not exist\n");
        return;
    } else {
        while ((read = getc(fptr)) != EOF) {
            printf("%c", read);
        }
    }
    printf("\nFile Read Successfully!\n\n");
    fclose(fptr);
}

// Function to update laptop status
void updateLaptopStatus(int laptopID, int newStatus) {
    FILE *fptr = fopen("Laptop-Data.txt", "r");
    FILE *tempFile = fopen("TempLaptopData.txt", "w");
    if (fptr == NULL || tempFile == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    char line[100];
    char laptop_id[10], laptop_brand[20];
    int fileLaptopID, fileStatus;
    int found = 0;

    // Read each line from the original file and update the status if necessary
    while (fgets(line, sizeof(line), fptr)) {
        sscanf(line, "Laptop ID: %s, Brand: %s, Status: %d", laptop_id, laptop_brand, &fileStatus);
        fileLaptopID = atoi(laptop_id); // Convert the ID to integer for comparison
        
        if (fileLaptopID == laptopID) {
            // Update the status if the laptop is found
            fprintf(tempFile, "Laptop ID: %s, Brand: %s, Status: %d\n", laptop_id, laptop_brand, newStatus);
            found = 1;
        } else {
            // Otherwise, copy the line as is
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(fptr);
    fclose(tempFile);

    // Replace the original file with the updated one
    remove("Laptop-Data.txt");
    rename("TempLaptopData.txt", "Laptop-Data.txt");

    if (found)
        printf("Laptop status updated for Laptop ID: %d\n", laptopID);
    else
        printf("Laptop ID: %d not found.\n", laptopID);
}