#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#define Max_length 400
// #include "functions.h"

// // functions initialization
void keyTracker(int id_position);
void addLaptop(int id_position);
void displayLaptop(int id_position);
void updateLaptopStatus(char *id,int id_position);


void main(){
    int id_position = 1;
    keyTracker(id_position);
    // addLaptop();
    // updateLaptopStatus("Laptop ID: 001",id_position);
}

void keyTracker(int id_position){
    // char *id[50] = "Laptop ID: 001";
    int key;
    printf("Here are the Key-Bindings for navigation:-\n\nAdd Laptop\t[1]\nDisplay Laptops\t[2]\nUpdateLaptopStatus\t[3]\nExit Rental System\t[4]\n\n");
    printf("Press any key of your choice: ");
    scanf("%d", &key);
    
    if (key == 1){
        addLaptop(id_position);
    } else if (key == 2){
        displayLaptop(id_position);
    } else if (key == 3){
        updateLaptopStatus("002",id_position);
    } else if (key == 4){
        return;
    }
}

void addLaptop(int id_position){
    fflush(stdin);
    FILE *fptr = fopen("Laptop-Data.txt", "a");
    char laptop_id=0;
    char laptop_brand=0;
    char laptop_model=0;
    char laptop_processor=0;
    char laptop_specs=0;
	fprintf(fptr, "Laptop ID:\t");
    printf("Enter laptop id: ");
    while ((laptop_id = getchar())!='\n'){
    	putc(laptop_id,fptr);
	}
//    gets(laptop_id);
    // fprintf(fptr, "Laptop ID: %s,   ", laptop_id);
    // fflush(stdin);
	fprintf(fptr, "\t,\tBrand:\t");
    printf("Enter Laptop Brand: ");
    while ((laptop_brand = getchar())!='\n'){
    	putc(laptop_brand,fptr);
	}
//    gets(laptop_brand);
    // fprintf(fptr, "Laptop Brand: %s,   ", laptop_brand);
    // fflush(stdin);
	fprintf(fptr, "\t,\tModel:\t");
    printf("Enter laptop Model: ");
    while ((laptop_model = getchar())!='\n'){
    	putc(laptop_model,fptr);
	}
//    gets(laptop_model);
    // fprintf(fptr, "Laptop Model: %s,   ", laptop_model);
    // fflush(stdin);
	fprintf(fptr, "\t,\tProcessor:\t");
    printf("Enter laptop Processor: ");
    while ((laptop_processor = getchar())!='\n'){
    	putc(laptop_processor,fptr);
	}
//    gets(laptop_processor);
    // fprintf(fptr, "Laptop Processor: %s,   ", laptop_processor);
    // fflush(stdin);
	fprintf(fptr, "\t,\tSpecs:\t");
    printf("Enter laptop specifications: ");
    while ((laptop_specs = getchar())!='\n'){
    	putc(laptop_specs,fptr);
	}
	fprintf(fptr,"\n");
//    gets(laptop_specs);
//    fprintf(fptr, "Laptop ID:\t%s\t,\tBrand:\t%s\t,\tModel:\t%s\t,\tProcessor:\t%s\t,\tSpecs:\t%s\n",laptop_id, laptop_brand, laptop_model, laptop_processor, laptop_specs);
    // fflush(stdin);


    fclose(fptr);
    printf("File Updated Successfully!\n\n");
    printf("What do you want to do next?\n");
    keyTracker(id_position);
}   
void displayLaptop(int id_position){
    char read;
    FILE *fptr = fopen("Laptop-Data.txt", "r");
    if (fptr == NULL){
        printf("File does not exist");
        return;
    } else {
        printf("******Reading File******\n\n");
        while((read = getc(fptr))!=EOF){
            printf("%c", read);
        }
    }
    printf("\nFile Read Successfully!\n\n");
    fclose(fptr);
    keyTracker(id_position);
}

void updateLaptopStatus(char *id,int id_position){
    char line[Max_length];
    int found = 0;
    
    FILE *fptr = fopen("Laptop-data.txt","r");
    if (fptr == NULL){
        printf("Error opening file, file doesn't exist!");
        fclose(fptr);
        return;
    } else {
    FILE *temp_file = fopen("Temp-File.txt", "w");
    if (temp_file == NULL){
        printf("Error opening file, file doesn't exist!");
        return;
    }
    while(fgets(line, sizeof(line), fptr)!=NULL){
        char temp_line[Max_length];
        strcpy(temp_line,line);

        char *exist = strtok(temp_line,"\t");
        int current_position = 0;
        int match = 0;

        while (exist != NULL){
            if (current_position == id_position && strcmp(exist,id) == 0 ){
                match = 1;
                break;
            }
            exist = strtok(NULL, "\t");
            current_position++;
        }
        if (!match){
            fputs(line, temp_file);
        } else {
            found = 1;
        }
    }
    fclose(fptr); fclose(temp_file);

    if (found){
        remove("Laptop-data.txt");
        rename("Temp-File.txt", "Laptop-data.txt");
        printf("Laptop Has been removed!\n");
    } else {
        remove("Temp-File.txt");
        printf("Laptop Does not exist!\n");
    }

    // printf("Function running successfully!");
    // printf("\nLaptop Status Updated Successfully!\n\n");
    keyTracker(id_position);
    }
}
