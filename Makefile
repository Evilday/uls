NAME = uls

INC = uls.h

SRC = main.c \
	mx_check_errors.c \
	mx_clear_all.c \
	mx_flag_d.c \
	mx_flag_dog.c \
	mx_flag_G.c \
	mx_flag_h.c \
	mx_flag_l_2.c \
	mx_flag_l_3.c \
	mx_flag_l_4.c \
	mx_flag_l.c \
	mx_flag_R.c \
	mx_flags_a_A.c \
	mx_flags_p_F.c \
	mx_info_prepare.c \
	mx_list_2.c \
	mx_list.c \
	mx_on_off_flags.c \
	mx_print_errors.c \
	mx_print_types_2.c \
	mx_print_types_3.c \
	mx_print_types.c \
	mx_print.c \
	mx_rotate.c \
	mx_sort_2.c \
	mx_sort_3.c \
	mx_sort.c \
	mx_start.c \
	mx_window.c \
	mx_work_with_args_2.c \
	mx_work_with_args.c \
	mx_work_with_flags.c \
	mx_your_atoi.c

OBJ = main.o \
	mx_check_errors.o \
	mx_clear_all.o \
	mx_flag_d.o \
	mx_flag_dog.o \
	mx_flag_G.o \
	mx_flag_h.o \
	mx_flag_l_2.o \
	mx_flag_l_3.o \
	mx_flag_l_4.o \
	mx_flag_l.o \
	mx_flag_R.o \
	mx_flags_a_A.o \
	mx_flags_p_F.o \
	mx_info_prepare.o \
	mx_list_2.o \
	mx_list.o \
	mx_on_off_flags.o \
	mx_print_errors.o \
	mx_print_types_2.o \
	mx_print_types_3.o \
	mx_print_types.o \
	mx_print.o \
	mx_rotate.o \
	mx_sort_2.o \
	mx_sort_3.o \
	mx_sort.o \
	mx_start.o \
	mx_window.o \
	mx_work_with_args_2.o \
	mx_work_with_args.o \
	mx_work_with_flags.o \
	mx_your_atoi.o


CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean

install:
	@make install -sC libmx
	@cp $(addprefix src/, $(SRC)) .
	@cp $(addprefix inc/, $(INC)) .
	@clang $(CFLAGS) -c $(SRC) -I $(INC)
	@clang $(CFLAGS) libmx/libmx.a $(OBJ) -o $(NAME)
	@mkdir -p obj
	@mv $(OBJ) ./obj

uninstall: clean
	@make uninstall -sC libmx
	@rm -rf $(NAME)

clean:
	@make clean -sC libmx
	@rm -rf $(INC) $(SRC) ./obj

reinstall: uninstall install