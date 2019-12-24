#include "uls.h"

int main(int argc, char *argv[]) {
	// sending without file_name
	t_info *info = mx_info_start(argc - 1, &(argv[1]));

	mx_start(info);
	// system("leaks uls");
	return 0;
}

// виправити некоректне оформлення виводу в файли
// flag -G
// аудитор
// коли в назві кирилиця, таби рахуються неправильно
// flag_dog не працює з лінками
// чекнути ліки
