#include <stdio.h>
#include <stdbool.h>

void bookLaptop(int studentID, int laptopID, int status);
void returnLaptop(int studentID, int laptopID);
void saveRentalDetails(int studentID, int laptopID, int rentalDurationHours, int rentalDurationDays, int rentalChargePerHour);

int main()
{

    // Variable Declartions For Booking Module
    int studentID[4] = {1, 2, 3, 4};
    int laptopID[4] = {12, 13, 14, 15};
    int rentalDurationHours = 0;
    int rentalDurationDays = 0;
    int rentalChargePerHour = 0;

    // Status
    // status 0 = Unavailable
    // status 1 = Available
    int status;

    // returnLaptop(1,12);

    bookLaptop(1, 12, 1);
    // saveRentalDetails(1,12,30,0,3000);

    return 0;
}

void bookLaptop(int studentID, int laptopID, int status)
{
    FILE *fptr = fopen("BookingData.txt", "r+");
    if (fptr == NULL)
    {
        printf("Error: Could not open file.\n");
        return;
    }

    char line[100];
    int fileStudentID, fileLaptopID, fileStatus;
    int isBooked = 0;

    while (fgets(line, sizeof(line), fptr))
    {
        sscanf(line, "Student ID: %d, Laptop ID: %d, Status: %d", &fileStudentID, &fileLaptopID, &fileStatus);
        if (fileLaptopID == laptopID && fileStatus == 1)
        {
            isBooked = 1;
            break;
        }
    }

    if (isBooked)
    {
        printf("Laptop ID: %d is already booked.\n", laptopID);
    }
    else
    {
        fprintf(fptr, "Student ID: %d, Laptop ID: %d, Status: %d\n", studentID, laptopID, status);
        printf("Booking successful! Student ID: %d, Laptop ID: %d.\n", studentID, laptopID);
        saveRentalDetails(1, 12, 48, 2, 200);
        fclose(fptr);
    }

    fclose(fptr);
}

// {

//     FILE *fptr;
//       char line[100];
//     char ch = 0;
//    int isBooked = 0;
//       int rentalDurationHours = 0;
//     int rentalDurationDays = 0;
//     int rentalChargePerHour = 0;
//         int fileStudentID, fileLaptopID, filestatus;

//     // check if student has already booked laptop
//     // fptr = fopen("BookingData.txt", "r");
//    while (fgets(line, sizeof(line), fptr)) {
//         sscanf(line, "Student ID: %d, Laptop ID: %d, Status: %d", &fileStudentID, &fileLaptopID, &filestatus);
//         if (fileLaptopID == laptopID && filestatus == 1) {
//             isBooked = 1;
//             break;
//         }
//     }

//     if (isBooked == 1)
//     {
//         printf("Laptop is already Booked");
//     }

//     // printf("booking Functions started \n");

//     // fptr = fopen("BookingData.txt", "a");
//     // printf("file opening to save data");

//     // fprintf(fptr, "Student ID: %d, Laptop ID: %d , Status: %d \n", studentID, laptopID, status);
//     // printf("data saved in file");

//     // fclose(fptr);

// if ( isBooked != 1)
// {
//     saveRentalDetails(1,12,48,2,200);
// }

// }

void returnLaptop(int studentID, int laptopID)
{

    FILE *fptr = fopen("BookingData.txt", "r");
    FILE *tempFile = fopen("TempData.txt", "w");
    if (fptr == NULL || tempFile == NULL)
    {
        printf("file not found .\n");
        return;
    }

    char line[100];
    int found = 0;
    // int status;

    while (fgets(line, sizeof(line), fptr))
    {
        int fileStudentID, fileLaptopID, status;
        sscanf(line, "Student ID: %d, Laptop ID: %d, Status: %d", &fileStudentID, &fileLaptopID, &status);

        if (fileStudentID == studentID && fileLaptopID == laptopID && status == 1)
        {
            fprintf(tempFile, "Student ID: %d, Laptop ID: %d, Status: 0\n", fileStudentID, fileLaptopID);
            found = 1;
        }
        else
        {
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
        printf("booking not found or already returned.\n");
}

void saveRentalDetails(int studentID, int laptopID, int rentalDurationHours, int rentalDurationDays, int rentalChargePerHour)
{

    FILE *fptr;
    char ch = 0;


    fptr = fopen("RentalDetailsData.txt", "a");

    // printf("Write sometjhing \n");
    // while((ch=getchar()) != '\n'){

    //     putc(ch,fptr);
    // }

    fprintf(fptr, "Student ID: %d, Laptop ID: %d ,RentalDurationHours: %d, RentalCharge: %d\n", studentID, laptopID, rentalDurationHours, rentalChargePerHour);

    fclose(fptr);
}
