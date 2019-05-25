/*
 ============================================================================
 Name        : vector.c
 Author      : Kseniya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/*
Программа для вычисления сложения, вычитания и вычисления скалярного произведения
для сложения испльзуйте команду - "1"
для вычитания используйте команду -"2"
для вычисления скалярного произведения используйте команду "3"
*/

/*
Функция сложения векторов
W1,W2 - векторы
number - кол-во координат в векторе
*/
void plusProc(float *W1, float *W2, int number) {
	printf("Coordinate new vector = "); 
    
    for (int i = 0; i < number; i++) {
    	printf("%.1f ", W1[i]+W2[i]);
	}
}

/*
Функция вычитания векторов
W1,W2 - векторы
number - кол-во координат в векторе
*/
void minusProc(float *W1, float *W2, int number) {
	printf("Coordinate new vector = ");
	
    for (int i = 0; i < number; i++) {
		printf("%.1f ", W1[i]-W2[i]);
	}
}

/*
Функция получения значения скалярного произведения нескольких векторов
W1,W2 - векторы
number - кол-во координат в векторе
*/
void multiProc(float *W1, float *W2, int number) {
    //скалярное произведение    
    float scal = 0;
    
    for (int i = 0; i < number; i++) {
    	scal = scal + W1[i]*W2[i];
	}
	printf("Coordinate new vector = %.1f \n", scal);
}

/*
Функция для выбора и выполнения нужной операции: сложение, вычитание и вычисление скалярного произведения векторов
W1,W2 - векторы
namber - кол-во координат в векторе
operation - выбор нужной операции (сложение, вычитание, скалярное произведение)
*/
void calcalute(float *W1, float *W2, int number) {
    //operation - переменная для выбора нужной операции (сложение, вычитание, скалярное произведение)
    int operation;
	
	while (operation != 0) {
			printf("\nEnter operation: ");
			scanf("%i", &operation);

			if (operation == 0) {
				printf("Goodbye!");
			}

			switch(operation) {
            // операция сложения векторов
				case 1:
					plusProc(W1, W2, number);
					break;
            // операция вычитания векторов
				case 2:
					minusProc(W1, W2, number);
					break;
            // операция для вычислния скалярного произведения векторов
				case 3:
					multiProc(W1, W2, number);
					break;
			}
	}
    //очистить память,выделенную для двух векторов W1,W2
	free(W1);
	free(W2);

}

/*
Функция, которая сохраняет введённые с клавиатуры координаты каждого вектора и выделяет для них память
*/
int main(void) {
    //векторы	
    float *W1, *W2;
    //кол-во координат в векторе
	int number;

	printf("Enter the number of coordinates of the vector: ");
	scanf("%i", &number);

	if (number != 0) {
		W1 = calloc(number, sizeof(W1));
		W2 = calloc(number, sizeof(W2));
	}

	printf("Enter the coordinates of the first vector: ");

	for (int i = 0; i < number; i++) {
		scanf("%f", &W1[i]);
	}

	printf("Enter the coordinates of the second vector: ");

	for (int i = 0; i < number; i++) {
		scanf("%f", &W2[i]);
	}

    calcalute(W1, W2, number);
}
