#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
* Калькулятор с файлом. Автор - Плотникова К.Е.
* Для работы программы необходимо заполнить файл source.txt входными параметрами:первый символ - операция('+', '-', '*', '/', '^', '!' - обычный калькулятор; '+', '-','*' - векторный калькулятор)
* далее через пробел обозначение использования отдельных чисел (s) или векторов (v), далее координаты, каждое из чисел так же отделяется пробелом.
* Результат выполнения записывается в output.txt
*/

/*
* список,в котором хранятся данные из входного файла
*/

typedef struct node {
	char operation;
	char calc_type;
	int size;
	float *var1;
	float *var2;
	struct node *next;
} node;

float fact(float a) {
    return a == 0 ? 1 : a * fact(a - 1);
}

/*
* функция расчета простого калькулятора
*/

int simple_calculator(node *data_list, FILE *out_file) {
	float *a = NULL, *b = NULL;

	a = calloc(1, sizeof(float));
	b = calloc(1, sizeof(float));

    a = data_list->var1;
    b = data_list->var2;
	switch(data_list->operation) {
		case '+':
			fprintf(out_file, "%.2f + %.2f = %.2f", (*a), (*b), (*a) + (*b));
			break;
		case '-':
			fprintf(out_file, "%.2f - %.2f = %.2f", (*a), (*b), (*a) - (*b));
			break;
		case '*':
			fprintf(out_file, "%.2f * %.2f = %.2f", (*a), (*b), (*a) * (*b));
			break;
		case '/':
			fprintf(out_file, "%.2f / %.2f = %.2f", (*a), (*b), (*a) / (*b));
			break;
		case '^':
			fprintf(out_file, "%.2f ^ %.2f = %.2f", (*a), (*b), pow(*a, *b));
			break;
		case '!':
			fprintf(out_file, "%.2f ! = %.2f", (*a), fact(*a));
			break;
	}

	free(a);
	free(b);

	return EXIT_SUCCESS;
}

/*
* функция расчета векторного калькулятора
*/

float calculator_vector(node *data_list, FILE *out_file) {

	float *vector1, *vector2;
	int size;

    size = data_list->size;
	vector1 = calloc(size,sizeof(int));
	vector2 = calloc(size,sizeof(int));

	vector1 = data_list->var1;
	vector2 = data_list->var2;

	float result = 0;
	switch(data_list->operation) {
		case '+':
			fprintf(out_file, "(");

			for (int i = 0; i < size; i++) {
				fprintf(out_file, "%.2f", vector1[i]);
				if (i != size-1) {
					fprintf(out_file, " ");
				}
			}

			fprintf(out_file, ") + (");

			for (int i = 0; i < size; i++) {
				fprintf(out_file, "%.2f", vector2[i]);
				if (i != size-1) {
					fprintf(out_file, " ");
				}
			}

			fprintf(out_file, ") = (");

			for (int i = 0; i < size; i++) {
				fprintf(out_file, "%.2f", vector1[i] + vector2[i]);
				if (i != size-1) {
					fprintf(out_file, " ");
				}
			}

			fprintf(out_file, ")");
			break;
		case '-':
			fprintf(out_file, "(");
			for (int i = 0; i < size; i++) {
				fprintf(out_file, "%.2f", vector1[i]);
				if (i != size-1) {
					fprintf(out_file, " ");
				}
			}

			fprintf(out_file, ") - (");

			for (int i = 0; i < size; i++) {
				fprintf(out_file, "%.2f", vector2[i]);
				if (i != size-1) {
					fprintf(out_file, " ");
				}
			}

			fprintf(out_file, ") = (");

			for (int i = 0; i < size; i++) {
				fprintf(out_file, "%.2f", vector1[i] - vector2[i]);
				if (i != size-1) {
					fprintf(out_file, " ");
				}
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

/*
* функция для получения последнего элемента из списка
*/

node* getLast(node *data_list) {
	if (data_list == NULL) {
		return NULL;
	}
	while (data_list->next) {
		data_list = data_list->next;
	}
	return data_list;
}

/*
* функция считывания элементов из входного файла
*/

void fill_list(node *data_list, FILE *in_file) {
	while (!feof(in_file)) {
		node *last = getLast(data_list);
		node *tmp = (node*)malloc(sizeof(node));
		fscanf(in_file, " %c %c", &tmp->operation, &tmp->calc_type);

		if (tmp->calc_type == 'v') {
			fscanf(in_file, "%d", &tmp->size);
			tmp->var1 = malloc(tmp->size*sizeof(float));
			tmp->var2 = malloc(tmp->size*sizeof(float));

			for (int i = 0; i < tmp->size; i++) {
				fscanf(in_file, "%f", &tmp->var1[i]);
			}

			for (int i = 0; i < tmp->size; i++) {
				fscanf(in_file, "%f", &tmp->var2[i]);
			}
		} else {
			tmp->var1 = malloc(sizeof(float));
			tmp->var2 = malloc(sizeof(float));
			fscanf(in_file, "%f %f", tmp->var1, tmp->var2);
		}
		tmp->next = NULL;
		last->next = tmp;
	}
}

/*
* функция выбора калькулятора
*/

void write_list(node *data_list, FILE *out_file) {
    if (data_list) {
        if (data_list->calc_type == 'v') {
            calculator_vector(data_list, out_file);
		} else {
			simple_calculator(data_list, out_file);
		}
		if (data_list->calc_type != 0) {
            fprintf(out_file, "\n");
        }
		write_list(data_list->next, out_file);
    }
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	FILE *in_file, *out_file;

	in_file = fopen("source.txt", "r");
	out_file = fopen("output.txt", "w");

	node *data_list;
	data_list = (node*)malloc(sizeof(node));
	fill_list(data_list, in_file);
	write_list(data_list, out_file);

	fclose(in_file);
	fclose(out_file);

	return EXIT_SUCCESS;
}
