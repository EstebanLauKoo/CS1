//Esteban Lau koo, class nbr:62226, Program 7(Project7), 6/19/20

#include <stdio.h>
#include <string.h>

//Constants to be used.
//MAXSIZE is the maximum size of all strings
//MAXAUCTIONITEMS is the maximum number of items in the auction
//MAXRAFFLE is the maximum number of available raffle tickets
#define MAXSIZE 100
#define MAXAUCTIONITEMS 1000
#define MAXRAFFLE 1000

//Function prototypes - do not change these
void initRaffle(int raffles[MAXRAFFLE]);
void initAuction(float auction[2][MAXAUCTIONITEMS]);
void buyTickets(float * totalRevenue, int * ticketsSold, int numTickets, float price);
void buyRaffle(float * totalRevenue, int raffles[MAXRAFFLE], int availTickets, int numTickets, int person);
void bid(float auction[2][MAXAUCTIONITEMS], float bid, int auctionNumber, int person, int flag);
float awardAuction(float auction[2][MAXAUCTIONITEMS], int auctionNumber);
void awardRaffle(int raffles[MAXRAFFLE], int raffleNumber, int winner);

//Main function
int main() {
    FILE * ifp;
    char filename[MAXSIZE], event[MAXSIZE], item[MAXSIZE];
    float presale, dayOf, totalRevenue = 0;
    float auctions[2][MAXAUCTIONITEMS];
    int raffles[MAXRAFFLE];
    int numPresale, numAuctions, numRaffle, numPrizes, numEvents;
    int i, ticketsSold = 0, auctionFlag = 1;

    printf("Please enter the input file name.\n");
    scanf("%s", filename);

    ifp = fopen(filename, "r");

    fscanf(ifp, "%f%f%d", &presale, &dayOf, &numPresale);

    totalRevenue += numPresale * presale;
    ticketsSold = numPresale;

    fscanf(ifp, "%d", &numAuctions);
    fscanf(ifp, "%d%d", &numRaffle, &numPrizes);
    fscanf(ifp, "%d", &numEvents);

    initRaffle(raffles);
    initAuction(auctions);

    for (i=0; i<numEvents; i++) {
        fscanf(ifp, "%s", event);

        if (strcmp(event, "BUY") == 0) {
            fscanf(ifp, "%s", item);
            if (strcmp(item, "TICKET") == 0) {
                int numTickets;
                fscanf(ifp, "%d", &numTickets);
                buyTickets(&totalRevenue, &ticketsSold, numTickets, dayOf);
            }
            else if (strcmp(item, "RAFFLE") == 0){
                int numTickets, person;
                fscanf(ifp, "%d%d", &numTickets, &person);
                buyRaffle(&totalRevenue, raffles, numRaffle, numTickets, person);
            }
        }
        else if (strcmp(event, "BIDITEM") == 0) {
            int itemNumber, person;
            float amount;
            fscanf(ifp, "%d%d%f", &itemNumber, &person, &amount);
            bid(auctions, amount, itemNumber, person, auctionFlag);
        }
        else if (strcmp(event, "CLOSEAUCTION") == 0) {
            printf("\nCLOSE AUCTION.");
            auctionFlag = 0;
        }
        else if (strcmp(event, "AWARD") == 0) {
            fscanf(ifp, "%s", item);
            if (strcmp(item, "AUCTION") == 0) {
                int auctionNumber;
                fscanf(ifp, "%d", &auctionNumber);
                totalRevenue += awardAuction(auctions, auctionNumber);
            }
            else if (strcmp(item, "RAFFLE") == 0){
                int raffleNumber, winner;
                fscanf(ifp, "%d%d", &raffleNumber, &winner);
                awardRaffle(raffles, raffleNumber, winner);
            }
        }
        else {
            printf("\nTOTALREVENUE is $%.2lf.\n", totalRevenue);
        }
    }

    fclose(ifp);
    return 0;
}

// Pre-conditions: raffles is the collection of all possible raffle tickets
// Post-condition: Each raffle ticket should have a default owner number
//                      that indicates it has not been sold yet
//
// What to do in this function: Each index number represents a different
// ticket number for the Raffle.  The value in the array at that index is
// the ticket's owner (an index that represents a person at the Fundraising
// Gala).  Initialize all the values in the array to a integer that indicates
// the ticket has not been sold yet.
void initRaffle(int raffles[MAXRAFFLE]) {
    int i;
    // goes through loop initilizes raffles[i] with -1 to show no owner
    for (i = 0; i < MAXRAFFLE; i++) {
        raffles[i] = -1;
    }
    
    return;
}

// Pre-conditions: auction is the collection of all possible auction items
// Post-condition: Each auction should have a default price of 0 and a default
//                 bidder number that indicates it has not been bid on yet
//
// What to do in this function: Each index number represents a different
// auction item for the Raffle.  Select one row of the two-dimensional
// array to be for bids; the other row will be for people (the current highest
// bidder).  Initialize all bids to zero and initialize all people to a number
// that indicates the item has not been bid on yet
void initAuction(float auction[2][MAXAUCTIONITEMS]) {
    int i;
    // goes through loop initilizes bid for the first row of the array and person for the second row
    for (i = 0; i < MAXAUCTIONITEMS; i++) {
        auction[0][i] = 0; // bid
        auction[1][i] = -1;  // person
    }

    

}

// Pre-conditions: totalRevenue is a pointer to the total amount that the Gala has earned
//                 ticketsSold is a pointer to the current number of tickets sold
//                 numTickets is the number of tickets that the person would like to purchase
//                 price is the current cost of the tickets (the DayOf price)
// Post-condition: Sells numTickets to the current person at price and updates the number
//                      of tickets sold and the current total revenue
//
// What to do in this function: Calculate the cost of the tickets and add it to the total
// revenue.  Print out the ticket numbers that were sold to the screen.  Update the number
// of tickets that have been sold.
void buyTickets(float * totalRevenue, int * ticketsSold, int numTickets, float price) {
    // calculates total price
    int totalPrice = numTickets * price;
    // adds total price to total revenue
    *totalRevenue += totalPrice;
    // prints sold tickets
    printf("\nSOLD TICKETS %d - %d", *ticketsSold, (*ticketsSold + numTickets - 1));
    // adds ticketsSold to numtickets
    *ticketsSold += numTickets;

    return;

}

// Pre-conditions: totalRevenue is a pointer to the total amount that the Gala has earned
//                 raffles is an array of all possible raffle tickets
//                 availTickets is the number of raffle tickets available to be sold
//                 numTickets is the number of raffle tickets that the person would like to purchase
//                 person is the numerical identifier of the person attempting to buy tickets
// Post-condition: Sells numTickets to the current person if tickets are available, or sells as
//                      as many as are left, or sells none if no tickets are left.  Updates totalRevenue
//                      if any tickets are sold.  Each ticket sells for $2
//
// What to do in this function: The value stored in each index of raffles should be the number of the
// person that bought that ticket.  For example if person 35 holds raffle tickets 11-15, then elements 11-15
// of raffles should all be equal to 35.
//
// Traverse to the next available ticket in the raffles array, if it exists.  If it does not exist, print
// out that no tickets will be given to this person.  If it does exist, check to see if there are enough
// tickets left for the person to get the full number they are looking for.  If there are not enough for
// the full amount, give them all the tickets that are left.  Print out which tickets they are given.
// Update totalRevenue with the number of tickets sold at $2 each.
void buyRaffle(float * totalRevenue, int raffles[MAXRAFFLE], int availTickets, int numTickets, int person) {
    int i;
    int holder = 0;
    int ticketSold = 0;

    // searches for raffle ticket without owner
    for (i = 0; i < availTickets; i++) {
        if (raffles[i] == -1) {
            holder = i;
            break;
        }

        else {
            holder = 100;
        }
    }

    // changes raffles[i] to the owner that is purchasing and adds a ticketsold counter. This does both. and adds total price
    for (i = holder; i < availTickets; i ++) {
        if ( i < (numTickets + holder) ) {
            ticketSold += 1;
            raffles[i] = person;
            * totalRevenue += 2;
        }
    }

    // prints if no tickets
    if(holder >= availTickets) {
        printf("\nNO RAFFLE TICKETS given to PERSON %d", person);
    }
    // prints ticket given to specific person
    else {
        printf("\nRAFFLE TICKETS %d - %d given to PERSON %d", holder, (ticketSold + holder -1), person);
    }

}        
 






// Pre-conditions: auction is an 2D array that holds the current highest bid and the person with
//                 the highest bid
//                 bid is a new proposed bid
//                 auctionNumber is the numerical identifier for the item being bid on
//                 person is the numerical identifier of the person attempting to bid
//                 flag is a value that indicates whether or not bids are still being accepted
// Post-condition: Updates the auctions with a new high bid if present
//                      Will not accept new bids that are not higher than old bids
//                      Will not accept new bids if the auctions are closed
//
// What to do in this function: Check to see if the auctions are still open based on flag
//
// If bids are still being accepted, check to see if bid is higher than the current bid for
// the auction.  If it is higher, update the auction with the new bid and the new person number
// Print out the result of either accepted or rejected
void bid(float auction[2][MAXAUCTIONITEMS], float bid, int auctionNumber, int person, int flag) {
    
    // makes sure if bids are acceptable
    if (flag) {
        if (bid > auction[0][auctionNumber]) { 

            // changes the values in array to bid and person
            auction[0][auctionNumber] = bid;
            auction[1][auctionNumber] = person;
            // prints the bid accepted
            printf("\nBIDITEM %d ACCEPTED for person %d at %0.2f DOLLARS", auctionNumber, person, bid);

        }

            else {

        printf("\nBIDITEM %d REJECTED for PERSON %d at %0.2f DOLLARS", auctionNumber, person, bid);
    
    }
    }

    else {

        printf("\nBIDITEM %d REJECTED for PERSON %d at %0.2f DOLLARS", auctionNumber, person, bid);
    
    }

}

// Pre-conditions: auction is an 2D array that holds the current highest bid and the person with
//                 the highest bid
//                 auctionNumber is the numerical identifier for the item being awarded
// Post-condition: Returns the value of the highest bid for the auction specified by auction number
//
// What to do in this function: Check to see if the auction identified by auctionNumber has any
// bids.  If so, award the auction to the person with the highest bid.  If not, print out that
// there have been no bids for this item.  Return the appropriate value to be added to totalRevenue
float awardAuction(float auction[2][MAXAUCTIONITEMS], int auctionNumber) {
    // checks for if a there is a bid
    if(auction[0][auctionNumber] !=  -1) {
        int buyer = 0;
        // changes float type to int
        buyer = auction[1][auctionNumber];
        // prints the winner and total price
        printf("\nAUCTION ITEM %d WON BY PERSON %d FOR $%0.2f", auctionNumber, buyer, auction[0][auctionNumber]);

        return auction[0][auctionNumber]; 
    }

    printf("\nNO BIDS FOR AUCTION ITEM %d", auctionNumber);

    return 0;
}

// Pre-conditions: raffles is an array of all possible raffle tickets
//                 winner is the winning ticket number
//                 raffleNumber is the current raffle being held
//
// Post-condition: prints out the numerical identifier of the person who
//                 holds the winning ticket number
void awardRaffle(int raffles[MAXRAFFLE], int raffleNumber, int winner) {
    // checks for raffle winner 
    while (raffles[winner] != -1)
    {
        printf("\nRAFFLE %d WON BY PERSON %d", raffleNumber, raffles[winner]);
        
        break;
    }

}
