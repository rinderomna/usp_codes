#include <stdio.h>

int main(void) {
	
	int a = 10;
	int b = 12;
	int *p;

	p = &a;

	printf("\nAdress of a= %p\n\n",p);
        
	return 0;
}
