//Esteban Lau koo, class nbr:62226, Program4(Project4), 5/31/20

#include <stdio.h>

int main() {
    
    //variable declaration
    int type, numDonation = 0, numInvestment = 0;
    double initFund, donation, fundTotal, investment;
    
    //writting the print outs
    printf("Welcome!\n");

    printf("What is the initial balance of the fund?\n");
    scanf("%lf", &initFund);
    
    // set the fundtotal equal to the init fund
    fundTotal = initFund;

    //print menu for the user
    printf("What would you like to do?\n");
    printf("\t1) - Make a donation\n");
    printf("\t2) - Make an investment\n");
    printf("\t3) - Print balance of fund\n");
    printf("\t4) - Quit\n");

    scanf("%d", &type);

    //continue until the user enters 4 for quit
    while (type != 4) {

        switch (type) {
            // for donation
            case 1:
                printf("How much would you like to donate?\n");
                scanf("%lf", &donation);

                fundTotal += donation;
                numDonation++;

                break;
            
            //for investment
            case 2:
                printf("How much would you like to invest?\n");
                scanf("%lf", &investment);

                if (initFund > fundTotal - investment) {
                    printf("you cannot make an invest of the amount.\n");
                    break;
                }    

                    fundTotal -= investment;
                    numInvestment++;

                break;
            //for balance
            case 3:
                printf("the current balance is $%.2f.\n", fundTotal);
                printf("There has been %d donations and %d investments.\n", numDonation, numInvestment);
                break;
            case 4:
                break;
            default:
                printf("Sorry, that was not a valid option.\n");
                break;
        }//end switch

        //reprint menu
        printf("What would you like to do?\n");
        printf("\t1) - Make a donation\n");
        printf("\t2) - Make an investment\n");
        printf("\t3) - Print balance of fund\n");
        printf("\t4) - Quit\n");

        scanf("%d", &type);

    }//end of while loop

    // priunts the total balance, donations and investments
    printf("the final balance is $%.2f.\n", fundTotal);
    printf("There has been %d donations and %d investments.\n", numDonation, numInvestment);

    return 0;
}