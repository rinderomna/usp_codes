#include <stdio.h>
int main() {
	int M[3][3];
	int i,j;

	for (i=0;i<3;i++) {
		for(j=0;j<3;j++) {
			scanf("%d",&M[i][j]);
		}
	}

	printf("\n\n");

	for (i=0;i<3;i++) {
                for(j=0;j<3;j++) {
                        printf("%d ", M[i][j]);
                }
		printf("\n");
        }
	printf("\n");
}
