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
    FILE *fptr = fopen("Laptop-Data.txt", "a");
    char input = 0;
    fflush(stdin);
    printf("Enter the laptop data: ");  
    while ((input = getchar())!= '\n'){
        putc(input, fptr);
    }
    fprintf(fptr, "\n\n");
    fclose(fptr);
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
}
