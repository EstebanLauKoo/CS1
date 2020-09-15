// Esteban Lau Koo Homework10

#include <stdio.h>
#include <string.h>

#define MAX_LEN 14

long long convert(char word[], int length);
void printText(long long value, int length);

int main() {

    int choice;
    printf("Would you like to (1) encode or (2) decode?\n");
    scanf("%d", &choice);

    // Encode.
    if (choice == 1) {

        // Get input file name.
        char filename[MAX_LEN];
        printf("Please enter the input file name, to encode.\n");
        scanf("%s", filename);
        FILE* ifp = fopen(filename, "r");

        // Convert each word, one by one.
        while (!feof(ifp)) {
            char word[MAX_LEN];
            fscanf(ifp, "%s", word);
            int len = strlen(word);
            long long res = convert(word, len);
            printf("%lld %d\n", res, len);
        }
        fclose(ifp);
    }

    else {

        // Get input file name.
        char filename[MAX_LEN];
        printf("Please enter the input file name, to decode.\n");
        scanf("%s", filename);
        FILE* ifp = fopen(filename, "r");

        // Convert each pair of numbers, one by one.
        while (!feof(ifp)) {
            long long value;
            int len;
            fscanf(ifp, "%lld%d", &value, &len);
            printText(value, len);
        }
        fclose(ifp);

    }

    return 0;
}

long long convert(char word[], int length) {


    // this is pretty much given in the description of the homework. Horner's method.
    long long value = 0;
    int i;
    for (i = 0; i < length; i++) {
        value = 26 * value + (word[i] - 'A');
    }

    return value;

}

void printText(long long value, int length) {
    char word[MAX_LEN];

    int i,rem;
    
    word[length] = '\0';

    // takes the modulus first to find the last letter knowing the length. Then /26 to find the next number to modulus by.
    for (i = 0; i < length; i++) {
       rem = value % 26;
       value = value / 26;
       word[length - 1 -i] = (char) (65 + rem);
    }

    // prints the word
    printf("%s\n", word);

    return;
}