void buyRaffle(float * totalRevenue, int raffles[MAXRAFFLE], int availTickets, int numTickets, int person) {
int i; // Declare i
int ticketCounter = 0; // Declare our ticket counter
int startTickets = 0; // Declare our starting variable

for(i = 0; i < availTickets; i++){ // For i is less than our available tickets
if(raffles[i] == -1){ // If the ticket isnt taken (-1)
startTickets = i; // That is our new ticket amount
break; // THIS BREAK IS 100% REQUIRED OR YOU WILL GET WRONG VALUES
}else{
startTickets = 100; // If not, our starting tickets is 100 as none have been taken
}
}

for(i = startTickets; i < availTickets; i++){ // For i is less than available tickets
if(i < (numTickets + startTickets)){ // If i is less than our total tickets
ticketCounter += 1; // Add one to our ticket counter
raffles[i] = person; // Assign that ticket to that person
* totalRevenue += 2; // Add $2 to our total revenue
}
}
if(startTickets >= availTickets){ // If we have more tickets to start than available...
printf("NO RAFFLE TICKETS given to PERSON %d\n", person); // Give no tickets
}else{ // ELSE...
printf("RAFFLE TICKETS %d - %d given to PERSON %d\n", startTickets, (ticketCounter+startTickets-1), person); // Give that person their tickets
}
}
