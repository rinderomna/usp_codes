#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double lisp_calculator() {
    char symbol;
    char operation;
    double operand[2];
    double result;

    scanf("%*[\r\n]s");
    scanf("%*[) ]s");

    symbol = getchar();

    if (symbol != '(') {
        ungetc(symbol, stdin);

        scanf("%*[\r\n]s");
        scanf("%*[) ]s");

        scanf(" %lf", &result);
        return result;
    } else {
        scanf("%*[\r\n]s");
        scanf("%*[) ]s");

        operation = getchar();

        scanf("%*[\r\n]s");
        scanf("%*[) ]s");
        
        operand[0] = lisp_calculator();
        operand[1] = lisp_calculator();

        switch (operation) {
            case '+':
                result = operand[0] + operand[1];
                break;
            case '-':
                result = operand[0] - operand[1];
                break;
            case '*':
                result = operand[0] * operand[1];
                break;
            case '/':
                result = operand[0] / operand[1];
                break;
        }   

        return result;    
    }
}

int main() {
    char symbol;
    char c;

    do {
        scanf("%*[\r\n]s");
        scanf("%*[) ]s");

        while ((c = getchar()) == '\n' || (c == '\r'));
        ungetc(c, stdin);

        symbol = getchar();

        if (symbol != EOF) {
            ungetc(symbol, stdin);
            printf("%lf\n", lisp_calculator());
        } 
    } while (symbol != EOF);

    return 0;
}