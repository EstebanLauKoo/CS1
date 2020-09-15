#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  
// The same function is used to encrypt and 
// decrypt 
void encryptDecrypt(char inpString[]) 
{ 
    // Define XOR key 
    // Any character value will work 
    int xorKey = 0xBA55C1EF; 
  
    // calculate length of input string 
    int len = strlen(inpString); 
  
    // perform XOR operation of key 
    // with every caracter in string 
    for (int i = 0; i < len; i++) 
    { 
        inpString[i] = inpString[i] ^ xorKey; 
        printf("%c",inpString[i]); 
    } 
} 
  
// Driver program to test above function 
int main() 
{ 
    char sampleString[] = "hello"; 
  
    // Encrypt the string 
    printf("Encrypted String: "); 
    encryptDecrypt(sampleString); 
    printf("\n"); 
  
    // Decrypt the string 
    printf("Decrypted String: "); 
    encryptDecrypt(sampleString); 
  
    return 0; 
} 