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

void plusProc(float *W1, float *W2, int number) {
	printf("Coordinate new vector = ");
    for (int i = 0; i < number; i++) {
    	printf("%.1f ", W1[i]+W2[i]);
	}
}

void minusProc(float *W1, float *W2, int number) {
	printf("Coordinate new vector = ");
	for (int i = 0; i < number; i++) {
		printf("%.1f ", W1[i]-W2[i]);
	}
}

void multiProc(float *W1, float *W2, int number) {
    float scal = 0;
    for (int i = 0; i < number; i++) {
    	scal = scal + W1[i]*W2[i];
	}
	printf("Coordinate new vector = %.1f \n", scal);
}

void calcalute(float *W1, float *W2, int number) {
	int operation;
	// printf("Enter operation: "); //
	// scanf("%i", &operation); //

	while (operation != 0) {
			printf("\nEnter operation: ");
			scanf("%i", &operation);

			if (operation == 0) {
				printf("Goodbye!");
			}

			switch(operation) {
				case 1:
					plusProc(W1, W2, number);
					break;
				case 2:
					minusProc(W1, W2, number);
					break;
				case 3:
					multiProc(W1, W2, number);
					break;
			}
	}

	free(W1);
	free(W2);

}

int main(void) {
	float *W1, *W2;
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
