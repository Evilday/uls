#include "uls.h"

static char *get_fract_size(char *fract_num);
static char *check_disk_sizes(char *new_size, char *dimension, int pos);
static char *get_valid_full_num(char *new_size, char* fract_num);
static char *get_size(char *new_size, char *size, char *dimension, int pos);

char *mx_flag_h(char *size) {
	char *dimension = "BKMGTP\0";
	char *new_size = NULL;
	int pos = 0;

	if (my_atoi(size) < 1000) {
		new_size = mx_strndup(size, 4);
		new_size[mx_strlen(new_size)] = dimension[0];
		free(size);
		return new_size;
	}
	else if (my_atoi(size) > 999 && my_atoi(size) < 1025) {
		free(size);
		return new_size = mx_strdup("1.0K");
	}
	else {
		new_size = get_size(new_size, size, dimension, pos);
	}
	return new_size;
}

static char *get_size(char *new_size, char *size, char *dimension, int pos) {
	char *fract_num; // fraction number .5678
	long long int buffer = my_atoi(size);

	free(size);
	while (buffer > 0) {
		if (buffer > 1024 && buffer < 1048576)// kb & mb
			fract_num = mx_itoa(buffer % 1024);
		if (buffer < 1000) {
			new_size = mx_itoa(buffer);
			break;
		}
		pos++;
		buffer /= 1024;
	}
	fract_num = get_fract_size(fract_num); // получаем дробное число
	new_size = get_valid_full_num(new_size, fract_num);// получаем целое число
	new_size = check_disk_sizes(new_size, dimension, pos);
	free(fract_num);
	return new_size;
}

// получение валидной десятичной части числа
static char *get_fract_size(char *fract_num) {
	char *temp;

	while (mx_strlen(fract_num) < 4){
		temp = fract_num;

		fract_num = "0";
		fract_num = mx_strjoin(fract_num, temp);
		free(temp);
	}
	for (int i = mx_strlen(fract_num) - 1; i > 1; i--)
		if (fract_num[i] > 53) {
			if (fract_num[i - 1] == 57) {
				fract_num[i - 1] = '0';
				fract_num[i - 2]++;
			}
			else
				fract_num[i - 1]++;
		}
	return fract_num;
}

/*
** еcли число меньше 10, то есть десятичная часть, мы округляем число, если она больше 5
** если она больше 5, то есть fract_num[0] = 1. Если же число меньше 9 и не нужно округлять
** мы дописываем дробную часть. Если число больше 10 и дробная часть больше 1024/2,
** то мы округляем на 1 целое число
*/

static char *get_valid_full_num(char *new_size, char* fract_num) {
	char *temp = new_size;

	if (mx_strlen(new_size) < 2) {
		if (fract_num[0] == 49) {
			temp[mx_strlen(temp) - 1]++;
			new_size = mx_strjoin(temp, ".0");
			free(temp);
		}
		else {
			new_size = mx_strjoin(temp, ".");
			new_size[mx_strlen(new_size)] = fract_num[1];
			free(temp);
		}
	}
	else
		if (my_atoi(fract_num) > 1024 / 2)
			new_size[mx_strlen(new_size) - 1]++;
	return new_size;
}

static char *check_disk_sizes(char *new_size, char *dimension, int pos) {
	char *temp;

	for (int j = 0; j < mx_strlen(new_size); j++)
		if (mx_isalpha(new_size[j]))
			new_size[j] = '\0';
	new_size[mx_strlen(new_size)] = dimension[pos];
	temp = mx_strndup(new_size, 4);
	free(new_size);
	return temp;
}

/*
** Килобайт	КБ	1,024					1024 Б
** Мегабайт	МБ	1,048,576				1024 КБ
** Гигабайт	ГБ	1,073,741,824			1024 МБ
** Терабайт	ТБ	1,099,511,627,776		1024 ГБ
** Петабайт	ПБ	1,125,899,906,842,624	1024 ТБ
*/
