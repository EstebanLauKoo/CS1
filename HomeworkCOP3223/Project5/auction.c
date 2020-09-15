//Esteban Lau koo, class nbr:62226, Program 5(Project5), 6/17/20

#include <stdio.h>

int main() {


    int numAuctions, numBids;
    char filename[30];
    float total, bidAmount, maxBid;

    int auctionNumber = 1;

    int i, j;

    numBids = 0, bidAmount = 0, maxBid = 0, numAuctions = 0, total = 0;

    FILE *ifp;

    printf("Please enter the name of the file.\n");
    scanf("%s", filename);

    ifp = fopen(filename, "r");

    // Read the number of auctions from the file
    fscanf(ifp, "%d", &numAuctions);

    for (i = 0; i < numAuctions; i++) {

        // This lets me know how many bids there are
        fscanf(ifp, "%d", &numBids);

        // reads the first bid amount and sets the first bid amount
        fscanf(ifp, "%f", &bidAmount);
        maxBid = bidAmount;

        // loops through the rest of the numbers to find if the bid amount is higher than the current one and replaces it if it is
        for (j = 1; j < numBids; j++) {
            fscanf(ifp, "%f", &bidAmount);
            if (bidAmount > maxBid) {
                maxBid = bidAmount;
            }
        }

        // prints out what the auction number was and how much it sold for
        printf("Auction %d was sold for $%.2f!\n", auctionNumber, maxBid);

        // adds the highest bid to the total
        total = total + maxBid;

        // increases the auction number
        auctionNumber++;

        // resets the max bid
        maxBid = 0;
    }
    
    // prints the final total
    printf("The silent auction raised $%.2f for charity!\n", total);

    // closes the file
    fclose(ifp);

    return(0);
}