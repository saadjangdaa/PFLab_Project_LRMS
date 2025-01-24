#include<stdio.h>


void bookLaptop(int studentID,int laptopID);
void returnLaptop(int studentID,int laptopID);
void saveRentalDetails(int studentID,int laptopID,int rentalDurationHours,int rentalDurationDays,int rentalChargePerHour);

int main(){

    //Variable Declartions For Booking Module
    int studentID[4] = {1,2,3,4} ;
    int laptopID[4] = {12,13,14,15};
    int rentalDurationHours = 0;
    int rentalDurationDays = 0;
    int rentalChargePerHour = 0;


//    returnLaptop(1,12);
   saveRentalDetails(1,12,30,0,3000);



    



    



    
















    return 0;


}


void bookLaptop(int studentID,int laptopID){

    FILE *fptr;
    char ch = 0;



    printf("booking Functions started \n");




    fptr = fopen("BookingData.txt","w");
    printf("file opening to save data");

    fprintf(fptr, "Student ID: %d, Laptop ID: %d\n", studentID, laptopID);
    printf("data saved in file");



    fclose(fptr);








}

void returnLaptop(int studentID,int laptopID){


  FILE *fptr;
    char ch = 0;



    printf("Return Laptop Functions started \n");




    fptr = fopen("ReturnData.txt","w");
    printf("file opening to save data");

  


    // printf("Write sometjhing \n");
    // while((ch=getchar()) != '\n'){


    //     putc(ch,fptr);
    // }

    fprintf(fptr, "Student ID: %d, Laptop ID: %d\n", studentID, laptopID);
    printf("data saved in file");



    fclose(fptr);

   
}


void saveRentalDetails(int studentID,int laptopID,int rentalDurationHours,int rentalDurationDays,int rentalChargePerHour){



FILE *fptr;
    char ch = 0;



    printf("Save Rental Detial Function started \n");




    fptr = fopen("RentalDetailsData.txt","w");
    printf("file opening to save data");

  


    // printf("Write sometjhing \n");
    // while((ch=getchar()) != '\n'){


    //     putc(ch,fptr);
    // }

    fprintf(fptr, "Student ID: %d, Laptop ID: %d ,RentalDurationHours: %d, RentalCharge: %d\n",studentID, laptopID,rentalDurationHours,rentalChargePerHour);
    printf("data saved in file");



    fclose(fptr);



}
    
