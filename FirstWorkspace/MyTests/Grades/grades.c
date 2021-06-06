#include <stdio.h>
int main() {
	float trabLab,avalSem,examFinal,media;
	
	scanf("%f%*c",&trabLab);
	scanf("%f%*c",&avalSem);
	scanf("%f%*c",&examFinal);

	media = (2 * trabLab + 3 * avalSem + 5 * examFinal)/(2 + 3 + 5);

	printf("\nMédia: %4.1f\n",media);

	if (media >= 0.0 && media < 5.0)
		printf("E\n");
	else if (media >= 5.0 && media < 6.0)
		printf("D\n");
	else if (media >= 6.0 && media < 7.0)
		printf("C\n");
	else if (media >= 7.0 && media < 8.0)
		printf("B\n");
	else if (media >= 8.0 && media <= 10.0)
		printf("A\n");
	else
		printf("GradeOutOfRangeException\n");

	return 0;
}
