#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
* Калькулятор с файлом. Автор - Плотникова К.Е.
* Для работы программы необходимо заполнить файл source.txt входными параметрами в форме польской нотации:первый и второй символы - это переменные через пробел
* далее операция ( '+', '-', '*', '/', '!' и '^')
* Результат выполнения записывается в output.txt
*/

/*
*очередь,в которой хранятся данные из входного файла
*/

typedef struct node {
	char operation;
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

int simple_calculator(node *tmp, FILE *out_file) {
	float *a = NULL, *b = NULL;

	a = calloc(1, sizeof(float));
	b = calloc(1, sizeof(float));

    a = tmp->var1;
    b = tmp->var2;
	switch(tmp->operation) {
		case '+':
			fprintf(out_file, "%.2f %.2f + = %.2f", (*a), (*b), (*a) + (*b));
			break;
		case '-':
			fprintf(out_file, "%.2f %.2f - = %.2f", (*a), (*b), (*a) - (*b));
			break;
		case '*':
			fprintf(out_file, "%.2f %.2f * = %.2f", (*a), (*b), (*a) * (*b));
			break;
		case '/':
			fprintf(out_file, "%.2f %.2f / = %.2f", (*a), (*b), (*a) / (*b));
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
* функция для получения последнего в очереди
*/

node* get_last(node *queue){
	if (queue == NULL) {
		return NULL;
	}
	while (queue->next) {
		queue = queue->next;
	}
	return queue;
}

/*
* функция добавления элемента в очередь
*/

void put_element(node *queue, node *tmp) {
	node *last = get_last(queue);
	if (last->operation == 0) {
		*queue = *tmp;
	} else {
		last->next = tmp;
	}
}

/*
* функция считывания элементов из входного файла
*/

void fill_list(node *queue, FILE *in_file) {
	while (!feof(in_file)) {
		node *tmp = (node*)malloc(sizeof(node));
		tmp->var1 = malloc(sizeof(float));
		tmp->var2 = malloc(sizeof(float));

		fscanf(in_file, "%f %f", tmp->var1, tmp->var2);
		fscanf(in_file, " %c", &tmp->operation);
		
        if (tmp->operation != 0) {
			put_element(queue, tmp);
		}
	}
}

/*
* функция возвращает указатель на первый элемент из очереди и перемещает указатель вершины на следующий элемент
*/

node *get_element(node *queue) {
	if (queue->operation == 0) {
		return NULL;
	}

	node *tmp = (node*)malloc(sizeof(node));
	tmp->var1 = queue->var1;
	tmp->var2 = queue->var2;
	tmp->operation = queue->operation;

	node *next = queue->next;
	
    if (!next) {
		free(queue);
	} else {
		*queue = *next;
	}
	return tmp;
}

/*
* функция выбора калькулятора
*/

void write_list(node *queue, FILE *out_file) {
	node *tmp = get_element(queue);

    while (tmp && tmp->operation != 0) {
    	simple_calculator(tmp, out_file);
		
        if (tmp->operation != 0) {
            fprintf(out_file, "\n");
        }
		tmp = get_element(queue);
    }
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	FILE *in_file, *out_file;

	in_file = fopen("source.txt", "r");
	out_file = fopen("output.txt", "w");

	node *queue;
	queue = (node*)malloc(sizeof(node));
	fill_list(queue, in_file);
	write_list(queue, out_file);

	fclose(in_file);
	fclose(out_file);

	return EXIT_SUCCESS;
}


