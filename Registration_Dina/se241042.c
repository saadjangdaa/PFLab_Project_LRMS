#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char registerStudents[20];
    char displayStudents[50];
    char searchStudents[30];
    printf("Enter your registerStudents: ");
    fgets(registerStudents, sizeof(registerStudents), stdin);

    printf("Enter your displayStudents: ");
    fgets(displayStudents, sizeof(displayStudents), stdin);
    file = fopen("Studendata.txt", "w");
    if (file == NULL) {
        printf("Error creating file!\n");
        return 1;
    }
    fprintf(file, "searchStudents: %s", searchStudents);
    fprintf(file, "searchStudents: %s", searchStudents);
    fclose(file);

    printf("Information has been written to info.txt and the file is closed.\n");

    return 0;
}

