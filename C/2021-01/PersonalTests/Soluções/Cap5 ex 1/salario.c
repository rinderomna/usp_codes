#include <stdio.h>
int main() {
	int ano, anoAtual;
	float taxa, salario;
	
	printf("Entre com o ano atual: ");
	scanf("%d%*c",&anoAtual);

	salario = 1000.00;
	taxa = 0.015;

	for(ano = 2015; ano < anoAtual; ano++) {
		salario = salario * (1 + taxa);
		taxa = 2 * taxa;
	}
	printf("\n O salário neste ano de %d é de R$%.2f\n\n", anoAtual, salario);

	return 0;
}
