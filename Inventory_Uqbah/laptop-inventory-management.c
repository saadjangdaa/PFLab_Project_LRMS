#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
// #include "functions.h"

// // functions initialization
void keyTracker();
void addLaptop();
void displayLaptop();
// void updateLaptopStatus();


void main(){
    keyTracker();
    // addLaptop();
}

void keyTracker(){
    int key;
    printf("Here are the Key-Bindings for navigation:-\nAdd Laptop\t[1]\nDisplay Laptops\t[2]\n");
    printf("Press any key of your choice: ");
    scanf("%d", &key);
    
    if (key == 1){
        addLaptop();
    } else if (key == 2){
        displayLaptop();
    }
}

void addLaptop(){
    fflush(stdin);
    FILE *fptr = fopen("Laptop-Data.txt", "a");
    char laptop_id[10];
    char laptop_brand[10];
    char laptop_model[50];
    char laptop_processor[50];
    char laptop_specs[200];

    printf("Enter laptop id: ");
    gets(laptop_id);
    // fprintf(fptr, "Laptop ID: %s,   ", laptop_id);
    // fflush(stdin);

    printf("Enter Laptop Brand: ");
    gets(laptop_brand);
    // fprintf(fptr, "Laptop Brand: %s,   ", laptop_brand);
    // fflush(stdin);

    printf("Enter laptop Model: ");
    gets(laptop_model);
    // fprintf(fptr, "Laptop Model: %s,   ", laptop_model);
    // fflush(stdin);

    printf("Enter laptop Processor: ");
    gets(laptop_processor);
    // fprintf(fptr, "Laptop Processor: %s,   ", laptop_processor);
    // fflush(stdin);

    printf("Enter laptop specifications: ");
    gets(laptop_specs);
    fprintf(fptr, "Laptop ID: %s,   Brand: %s,  Model: %s,  Processor: %s,  Specs: %s\n\n",laptop_id, laptop_brand, laptop_model, laptop_processor, laptop_specs);
    // fflush(stdin);


    fclose(fptr);
    printf("File Updated Successfully!\n\n");
    printf("What do you want to do next?\n");
    keyTracker();
}   
void displayLaptop(){
    char read;
    FILE *fptr = fopen("Laptop-Data.txt", "r");
    if (fptr == NULL){
        printf("File does not exist");
    } else {
        while((read = getc(fptr))!=EOF){
            printf("%c", read);
        }
    }
    fclose(fptr);
    printf("File Read Successfully!\n\n");
    keyTracker();
}
