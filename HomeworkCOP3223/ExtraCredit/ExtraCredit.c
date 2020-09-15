//include headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//main function
int main(int argc, char** argv) {

    char *string = argv[1];
    int key = 0xBA55C1EF; 
    int i, letter;

    printf(string);
    printf("\n");

    //encrypting the string with key.
    for(i = 0; i < strlen(string) ; i++){ 
        letter = (int) string[i];
        printf("%d \n", letter);
        string[i] =  letter ^ key;
    }

    // printing the encryption
    printf(string); 
    printf("\n");

    return 0;
}