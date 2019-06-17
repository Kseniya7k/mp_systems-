#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float fact(float a) {
    return a == 0 ? 1 : a * fact(a - 1);
}

int simple_calculator(FILE *in_file, FILE *out_file, char k) {
	float *a = NULL, *b = NULL;

	a = calloc(1, sizeof(float));
	b = calloc(1, sizeof(float));

	fscanf(in_file, "%f", a);
	fscanf(in_file, "%f", b);

	int c;
	switch(k) {
		case '+':
			fprintf(out_file, "Результат: %.2f", (*a) + (*b));
			break;
		case '-':
			fprintf(out_file, "Результат: %.2f", (*a) - (*b));
			break;
		case '*':
			fprintf(out_file, "Результат: %.2f", (*a) * (*b));
			break;
		case '/':
			fprintf(out_file, "Результат: %.2f", (*a) / (*b));
			break;
		case '^':
			fprintf(out_file, "Результат: %.2f", pow(*a, *b));
			break;
		case '!':
			fprintf(out_file, "Результат: %.2f", fact(*a));
			break;
	}

	free(a);
	free(b);

	return EXIT_SUCCESS;
}

float calculator_vector(FILE *in_file, FILE *out_file, char k) {

	float *vector1, *vector2;
	int size;

	fscanf(in_file, " %d", &size);

	vector1 = calloc(size,sizeof(int));
	vector2 = calloc(size,sizeof(int));

	for (int i = 0; i < size; i++) {
		fscanf(in_file, "%f", &vector1[i]);
	}

	for (int i = 0; i < size; i++) {
		fscanf(in_file, "%f", &vector2[i]);
	}

	float result = 0;
	switch(k) {
		case '+':
			fprintf(out_file, "(");
			for (int i = 0; i < size; i++) {
				fprintf(out_file, "%.2f", vector1[i]);
				if (i != size-1) fprintf(out_file, " ");
			}

			fprintf(out_file, ") + (");

			for (int i = 0; i < size; i++) {
				fprintf(out_file, "%.2f", vector2[i]);
				if (i != size-1) fprintf(out_file, " ");
			}

			fprintf(out_file, ") = (");

			for (int i = 0; i < size; i++) {
				fprintf(out_file, "%.2f", vector1[i] + vector2[i]);
				if (i != size-1) fprintf(out_file, " ");
			}

			fprintf(out_file, ")");
			break;
		case '-':
			fprintf(out_file, "(");
			for (int i = 0; i < size; i++) {
				fprintf(out_file, "%.2f", vector1[i]);
				if (i != size-1) fprintf(out_file, " ");
			}

			fprintf(out_file, ") - (");

			for (int i = 0; i < size; i++) {
				fprintf(out_file, "%.2f", vector2[i]);
				if (i != size-1) fprintf(out_file, " ");
			}

			fprintf(out_file, ") = (");

			for (int i = 0; i < size; i++) {
				fprintf(out_file, "%.2f", vector1[i] - vector2[i]);
				if (i != size-1) fprintf(out_file, " ");
			}

			fprintf(out_file, ")");
			break;
		case '*':
			for (int i = 0; i < size; i++) {
				result += vector1[i] * vector2[i];
			}

			fprintf(out_file, "(a, b) = %.2f", result);
			break;
	}

	free(vector1);
	free(vector2);

	return EXIT_SUCCESS;
}

int main(void) {
	FILE *in_file, *out_file;
	in_file = fopen("source.txt", "r");
	out_file = fopen("output.txt", "w");

	char operation, calc;

	fscanf(in_file, "%c %c", &operation, &calc);

	if (calc == 's') {
	    simple_calculator(in_file, out_file, operation);
	} else {
	    calculator_vector(in_file, out_file, operation);
    }
	fclose(in_file);
	fclose(out_file);
	return EXIT_SUCCESS;
}
