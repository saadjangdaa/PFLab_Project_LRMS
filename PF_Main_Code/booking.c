#include <stdio.h>
#define line_length 300

void displayBookings(int id_position);

void main()
{
    displayBookings(1);
}

void displayBookings(int id_position)
{
    remove("ShowBookings.txt");
    char read;
    FILE *fptr = fopen("BookingData.txt", "r");
    FILE *temp_file = fopen("showBookings.txt", "w");
    printf("******Reading File******\n\n");

    if (fptr == NULL)
    {
        printf("File does not exist\n");
        return;
    }
    // else {
    //     while ((read = getc(fptr)) != EOF) {
    //         printf("%c", read);
    //     }

    char line[line_length];

    while (fgets(line, sizeof(line), fptr))
    {
        int student_ID;
        int laptop_id;
        int status;
        sscanf(line, "Student ID: %d, Laptop ID: %d , Status: %d", &student_ID, &laptop_id, &status);
        if (status == 1)
        {
            fprintf(temp_file, "Student ID: %d, Laptop ID: %d , Status: Not-Available\n", student_ID, laptop_id, status);
        }
        else
        {
            fprintf(temp_file, "Student ID: %d, Laptop ID: %d , Status: Available\n", student_ID, laptop_id, status);
        }
    }
    fclose(fptr);
    fclose(temp_file);
    FILE *readBookings = fopen("showBookings.txt","r");
    while ((read = getc(readBookings))!=EOF){
        printf("%c", read);
    }
    fclose(readBookings);
    // printf("\nFile Read Successfully!\n\n");
    // fclose(fptr);
}
