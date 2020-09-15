//include headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//main function
int main(int argc,  char** argv) 

    char *string = argv[1];
    
    int i;
    printf(string);
    printf("\n");

    int key = 0xBA55C1EF; //key

    //encrypting the string with key.
    for(i = 0; i < strlen(string) ; i++){ 
        string[i] = string[i] ^ key;
    }

    printf(string); 


    return 0;
}