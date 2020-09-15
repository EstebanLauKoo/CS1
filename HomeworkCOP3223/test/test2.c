#include <stdio.h>
int main() {
	int array[] = {8, 2, 3, 4, 1};
	int i, s = 0;
	for(i=0; i<5; i++) 
   
		s += array[i];


	array[0] = s - array[0];


    
	for(i=1; i<5; i++) {
		array[i] = array[i-1] - array[i];
        printf("%d:", array[i]);
    }
	for(i=0; i<5; i++)
		printf("%d", array[i]);


	return 0;
}
