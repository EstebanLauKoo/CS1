//Esteban Lau koo, class nbr:62226, Program 6(Project6), 6/19/20

#include <stdio.h>

//This helps define array size
#define SIZE 5

//function prototypes
void menu();
void donation(int Array[SIZE]);
void request(int Array[SIZE]);
void fulfill(int donationArray[SIZE], int requestArray[SIZE], char TYPES[SIZE][20]);
void printStatus(int donationArray[SIZE], int requestArray[SIZE], char TYPES[SIZE][20]);

// main function
int main () {
    int response = 0;
    int donationArray[SIZE] = { 0, 0, 0, 0, 0};
    int requestArray[SIZE] = { 0, 0, 0, 0, 0};
    char TYPES[SIZE][20] = {"Protein", "Dairy", "Grains", "Vegetables", "Fruits"};

    // prompt user
    printf("Welcome to the Food Bank Management Program!\n");
    menu();
    scanf("%d", &response);
    printf("\n");

    // switch command menu
    while(response != 5) {
        switch (response)
        {
        case 1:
            donation(donationArray);
            break;
        case 2:
            request(requestArray);
            break;
        case 3:
            fulfill(donationArray, requestArray, TYPES);
            break;
        case 4:
            printStatus(donationArray, requestArray, TYPES);
            break;
        default:
            printf("Sorry, that was not a valid option.\n");
            break;
        }

        menu();
        scanf("%d", &response);
        printf("\n");
    }

    printf("Thank you for running our system!\n");

    return 0;
}


// menu function prints
void menu() {
    printf("What would you like to do?\n");
    printf("\t1. Enter a Donation\n");
    printf("\t2. Enter a request\n");
    printf("\t3. Fulfill Requests\n");
    printf("\t4. Print status report\n");
    printf("\t5. Exit\n");
    return;
}

// items menu print out
void itemsList() {
    printf("\t0. Protein\n");
    printf("\t1. Dairy\n");
    printf("\t2. Grains\n");
    printf("\t3. Vegetables\n");
    printf("\t4. Fruits\n");
}

// donation function
void donation(int donationArray[SIZE]) {
    int response = 0, quantity = 0;

    printf("What donation type would you like to enter?\n");
    itemsList();
    scanf("%d", &response);
    printf("\n");

    printf("How many would you like to enter?\n");
    scanf("%d", &quantity);
    printf("\n");

    donationArray[response] += quantity;
    printf("Donation Added\n");

    return;
}

// request function
void request(int requestArray[SIZE]) {
    int response = 0, quantity = 0;

    printf("What would you like to request?\n");
    itemsList();
    scanf("%d", &response);
    printf("\n");

    printf("How many would you like to request?\n");
    scanf("%d", &quantity);
    printf("\n");

    requestArray[response] += quantity;

    printf("Request Added\n");

    return;
}

// fullfillment function
void fulfill(int donationArray[SIZE], int requestArray[SIZE], char TYPES[SIZE][20]) {
    int i;

    for (i = 0; i < SIZE; i++ ) {
        if (requestArray[i] > 0) {
            if ( requestArray[i] <= donationArray[i]) {
                donationArray[i] -= requestArray[i];
                requestArray[i] = 0;
                printf("%s requests will be fulfilled\n", TYPES[i]);                
            }
            else if (donationArray[i] > 0 && donationArray[i] < requestArray[i]) {
                requestArray[i] -= donationArray[i];
                donationArray[i] = 0;
                printf("%s requests will be partially fulfilled.\n", TYPES[i]);
            }
            else if (donationArray[i] == 0) {
                printf("%s requests cannot be fulfilled.\n", TYPES[i]);
            }
                
            
        }

    }

    return;
}

// print status function (I tried to work with a 2d array but I coulnd't make it work.)
void printStatus(int donationArray[SIZE], int requestArray[SIZE], char TYPES[SIZE][20]) {
    int i;

    for(i = 0; i < SIZE; i++ ) {
        printf("\t%s\t Donations: %d Requests: %d\n", TYPES[i], donationArray[i], requestArray[i]);
    }

}

