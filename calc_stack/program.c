#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
* Калькулятор с файлом. Автор - Плотникова К.Е.
* Для работы программы необходимо заполнить файл source.txt входными параметрами: первый символ - тип калькулятора (s)-обычный и (v)-векторный
* В векторном калькуляторе доступны операции ( '+', '-', '*'), а в обычном операции ( '+', '-', '*', '/', '!' и '^')
* первый символ операции - тип калькулятора,второй симол - операция, третий символ - размерность векторов (сколько координат в одном векторе)
* далее координаты векторов
* для обычного калькулятора используется польская нотация (3 + 3 -> 3 3 +) 
* Результат выполнения записывается в output.txt
*/

typedef struct stack {
	float result;
	struct stack *next;
} stack;

typedef struct list_number {
	char value;
	struct list_number *next;
} list_number;

typedef struct vector {
	char operation;
	int size;
	float *var1;
	float *var2;
} vector;

typedef struct node {
	char calc_type;
	vector *vector;
	float polish_result;
	struct node *next;
} node;

float fact(float num) {
	return num == 0 ? 1 : num * fact(num - 1);
}

/*
* функция записи результатов работы векторного калькулятора
*/
float calculator_vector(node *data_list, FILE *out_file) {

	float *vector1, *vector2;
	int size;

    size = data_list->vector->size;
	vector1 = calloc(size, sizeof(float));
	vector2 = calloc(size, sizeof(float));

	vector1 = data_list->vector->var1;
	vector2 = data_list->vector->var2;

	float result = 0;
	switch(data_list->vector->operation) {
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
* функция получения последнего элемента в списке структуры типа node
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
* функция записывающая число в стек
*/
stack* put_number(char *number, stack* headstack) {
	stack* tmp = (stack*) malloc(sizeof(stack));
	if (!headstack->result && !headstack->next) {
		tmp = headstack;
	} else {
		tmp->next = headstack;
	}
	tmp->result = atof(number);
	return tmp;
}

/*
* функция записи результатов в стек после вычисления
*/
stack* process(char oper, stack* element) {
	switch (oper) {
		case '+':
			element->next->result = element->next->result + element->result;
			break;
		case '-':
			element->next->result = element->next->result - element->result;
			break;
		case '*':
			element->next->result = element->next->result * element->result;
			break;
		case '/':
			element->next->result = element->next->result / element->result;
			break;
		case '^':
			element->next->result = pow(element->next->result, element->result);
			break;
		case '!':
			element->next->result = fact(element->result);
			break;
	}
	free(element);
	return element->next;
}

int is_operation(char ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '!' || ch == '^';
}

/*
* функция получения результатов работы обычного калькулятора
*/
float get_polish_result(FILE *in_file) {
	list_number* headnumber = (list_number*) malloc(sizeof(list_number)); //инициализировали 1й элем списка
	list_number* lastnumber = (list_number*) malloc(sizeof(list_number));
	stack* headstack = (stack*) malloc(sizeof(stack*));

	lastnumber = headnumber;
	char c;
	fscanf(in_file, " %c", &c);

	while (c != '$') {
		while (!is_operation(c)) {
			int size = 0;
			while (c != ' ') {
				size++;
				if (size == 1) {
					headnumber->value = c;
					headnumber->next = NULL;
					lastnumber = headnumber;
				} else {
					list_number* tmpnumber = (list_number*) malloc(sizeof(list_number));
					tmpnumber->value = c;
					tmpnumber->next = NULL;
					lastnumber->next = tmpnumber;
					lastnumber = lastnumber->next;
				}
				fscanf(in_file, "%c", &c);
			}

			lastnumber = headnumber;

			char *numbers = malloc(size * sizeof(char));
			for (int i = 0; i < size; i++) {
				numbers[i] = lastnumber->value;
				if (lastnumber->next) {
					lastnumber = lastnumber->next;
				}
			}

			headstack = put_number(numbers, headstack);
			fscanf(in_file, "%c", &c);

		}

		headstack = process(c, headstack);
		fscanf(in_file, " %c", &c);
	}

	return headstack->result;
}

/*
* функция заполнения списка из файла в структуру node
*/
void fill_list(node *data_list, FILE *in_file) {
	while (!feof(in_file)) {
		node *last = getLast(data_list);
		node *tmp = (node*)malloc(sizeof(node));
		// fscanf(in_file, " %c %c", &tmp->operation, &tmp->calc_type);
		fscanf(in_file, " %c", &tmp->calc_type);

		if (tmp->calc_type) {
			if (tmp->calc_type == 'v') {
				vector *new_vector = (vector*)malloc(sizeof(vector));
				fscanf(in_file, " %c", &new_vector->operation);
				fscanf(in_file, "%d", &new_vector->size);
				new_vector->var1 = malloc(new_vector->size*sizeof(float));
				new_vector->var2 = malloc(new_vector->size*sizeof(float));

				for (int i = 0; i < new_vector->size; i++) {
					fscanf(in_file, "%f", &new_vector->var1[i]);
				}

				for (int i = 0; i < new_vector->size; i++) {
					fscanf(in_file, "%f", &new_vector->var2[i]);
				}
				tmp->vector = new_vector;
			} else if (tmp->calc_type == 's') {
				tmp->polish_result = get_polish_result(in_file);
			}
			tmp->next = NULL;
			last->next = tmp;
		}
	}
}

/*
функция записи результатов
*/
void write_list(node *data_list, FILE *out_file) {
    if (data_list) {
        if (data_list->calc_type == 'v') {
        	calculator_vector(data_list, out_file);
		} else {
			fprintf(out_file, "Результат: %.2f", data_list->polish_result);
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
	write_list(data_list->next, out_file);

	fclose(in_file);
	fclose(out_file);

	return EXIT_SUCCESS;
}
