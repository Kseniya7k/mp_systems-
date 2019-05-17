/*
 ============================================================================
 Name        : calkulytor.c
 Author      : Kseniya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*   Вы можете ввести операцию с помощью символов.
 * "+" - сложение;
 * "-" - вычитание;
 * "*" - умножение;
 * "/" - деление;
 * "!" - факториал числа;
 * "^" - степень числа.   */

int fact(int num) {
return num == 0 ? 1 : num * fact(num - 1);
}

void plusProc() {
	unsigned short int x,y;
	/* x - 1 слагаемое;
	   y - 2 слагаемое; */

	printf("x = ");
	scanf("%hu%*c", &x);
	printf("y = ");
	scanf("%hu%*c", &y);
	printf("Result = %i\n", x+y);
}

void factProc() {
	unsigned short int num;

	printf("num = ");
	scanf("%hu%*c", &num);
	printf("Result = %i\n", fact(num));
}

void minusProc() {
	unsigned short int x,y;
	/* x - уменьшаемое;
	   y - вычитаемое; */

	printf("x = ");
	scanf("%hu%*c", &x);
	printf("y = ");
	scanf("%hu%*c", &y);
	printf("Result = %i\n", x-y);
}

void multiProc() {
	unsigned short int x,y;
	/* x - 1 число;
	   y - 2 число; */

	printf("x = ");
	scanf("%hu%*c", &x);
	printf("y = ");
	scanf("%hu%*c", &y);
	printf("Result = %i\n", x*y);
}

void divProc() {
	float x,y;
	/* x - делимое;
	   y - делитель; */

	printf("x = ");
	scanf("%f%*c", &x);
	printf("y = ");
	scanf("%f%*c", &y);


	if (y == 0) {
		printf("Do not divide by 0\n");
		printf("Result = 0\n");
	}

	else {
		printf("Result = %.2f\n", x/y);
	}
}

void powProc() {
	int num, power;
	/* num - число;
	   power - степень, в которую нужно возвести; */

	printf("number = ");
	scanf("%i%*c", &num);
	printf("power = ");
	scanf("%i%*c", &power);
	printf("Result = %.2f\n", pow(num, power));
}

int main(void) {
	char operation;

	while (operation != '0') {
		printf("Enter operation: ");
		scanf("%c", &operation);

		if (operation == '0') {
			printf("goodbye!");
			break;
			}

		switch (operation) {
			case '+':
				plusProc();
				break;
			case '-':
				minusProc();
				break;
			case'/':
				divProc();
				break;
			case '*':
				multiProc();
				break;
			case '!':
				factProc();
				break;
			case '^':
				powProc();
				break;
			default:
				printf("Operation is not correct\n");
				break;
		}
	}
}
