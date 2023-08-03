#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <sys/stat.h>

int MainMenu();
void displayBalance(double num);
void balanceCheck();
void withdrawalAmount();
void depositAmount();
void createFileIfNotExists(const char* filename);
void clearScreen();


int main(){
    int option;

    const char* filename = "BalanceSheet.txt";
    createFileIfNotExists(filename);

    MainMenu();

    return 0;
}

int MainMenu(){
    int option;
    while(1){
        clearScreen();
        printf("\n\t\t******* Welcome to our ATM - Your gateway to convenient and secure banking. *******");
        printf("\n\n\t1. Balance Check\n\t2. Withdrawal\n\t3. Deposit\n\t4. Exit\n");
        printf("\n\tChoose an option: ");
        scanf("%d", &option);

        switch(option){
        case 1:
            //Balance Check
            clearScreen();
            balanceCheck();
            break;

        case 2:
            //Withdrawal
            clearScreen();
            withdrawalAmount();
            break;

        case 3:
            //Deposit
            clearScreen();
            depositAmount();
            break;

        case 4:
            //Exit
            clearScreen();
            printf("\n\tThank you for using our ATM. Goodbye!...\n");
            return 0;

        default:
            //As Usual
            clearScreen();
            printf("\n\tInvalid option. Please choose a valid option.\n");
            break;
        }
        getch();
    }
}

void balanceCheck(){
    double num, amount;
    FILE *fp;
    fp = fopen("BalanceSheet.txt", "r");
    if(fp == NULL){
        printf("\n\tError: Cannot Open File\n");
        exit(1);
    }

    fscanf(fp, "%lf", &num);
    printf("\n\t-------- Balance Check --------\n");
    displayBalance(num);

    fclose(fp);
}

void withdrawalAmount(){
    double num, amount;
    FILE *fp;
    fp = fopen("BalanceSheet.txt", "r");
    if(fp == NULL){
        printf("\n\tError: Cannot Open File\n");
        exit(1);
    }

    fscanf(fp, "%lf", &num);
    printf("\n\t-------- Withdrawal Amount --------\n");
    displayBalance(num);

    fclose(fp);

    printf("\n\tEnter amount to withdrawal: RS ");
    scanf("%lf", &amount);

    if(amount > 0 && num > 0){
        num -= amount;
        fp = fopen("BalanceSheet.txt", "w");
        if(fp == NULL){
            printf("\n\tError: Cannot Open File\n");
            exit(1);
        }

        fprintf(fp, "%lf", num);
        clearScreen();
        printf("\n\t-------- CASH WITHDRAWAL --------\n");
        printf("\n\tYou successfully withdrawal \n\t\t\tRS. %.2lf\n", amount);

        fclose(fp);

        displayBalance(num);
    }else{
        if(amount <= 0){
            printf("\n\tInvalid amount. Please enter a positive value.");
        }else{
            printf("\n\tThe withdrawal cannot be processed due to insufficient funds.\n");
        }
    }

}

void depositAmount(){
    double num, amount;
    FILE *fp;
    fp = fopen("BalanceSheet.txt", "r");
    if (fp == NULL) {
        printf("\n\tError: Cannot Open File\n");
        exit(1);
    }


    fscanf(fp, "%lf", &num);
    printf("\n\t-------- Deposit Amount --------\n");
    displayBalance(num);


    fclose(fp);


    printf("\n\tEnter amount to deposit: RS. ");
    scanf("%lf", &amount);

    if(amount >= 0){
        num += amount;
        fp = fopen("BalanceSheet.txt", "w");
        if (fp == NULL) {
            printf("\n\tError: Cannot Open File\n");
            exit(1);
        }


        fprintf(fp, "%lf", num);
        clearScreen();
        printf("\n\tYou successfully deposit: RS. %.2lf\n", amount);


        fclose(fp);


        displayBalance(num);
    }else{
        printf("\n\tPlease enter positive value.\n");
    }



}

void displayBalance(double num){
    printf("\n\tAvailable Balance: RS. %.2lf\n",  num);
}

void createFileIfNotExists(const char* filename) {
    struct stat buffer;
    if(stat(filename, &buffer) != 0){
        FILE* fp = fopen(filename, "r");
        if (fp == NULL) {
            fp = fopen(filename, "w");
            if (fp != NULL) {
                fclose(fp);
            } else {
                printf("\n\tError: Cannot create file '%s'.\n", filename);
            }
        } else {
            fclose(fp);
        }
    }
}

void clearScreen(){
    system("cls");
}
