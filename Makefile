NAME = uls

INC = ./inc/uls.h

HEADTMP = ./uls.h

SRC = ./*.c
	#./main.c \
	#./mx_check_errors_2.c

SRCS = ./src/*.c
	#./src/main.c \
	#./src/mx_check_errors_2.c

OBJ = ./*.o
	#./main.o \
	#./mx_check_errors_2.o

OBJO = ./obj/*.o
	#./obj/main.o \
	#./obj/mx_check_errors_2.o

CFLGS = -std=c11 -Wall -Werror -Wextra -Wpedantic# -g -fsanitize=address

all: install uninstall

install:
	@make -C libmx -f Makefile install
	@cp $(INC) $(SRCS) .
	@clang $(CFLGS) -c  $(SRC)
	@mkdir  obj
	@mv $(OBJ) ./obj
	@clang $(CFLGS) $(OBJO) libmx/libmx.a -o $(NAME)

uninstall:
	@make -C libmx -f Makefile uninstall
	@rm -rf $(OBJO) $(SRC) $(HEADTMP)
	@rm -rf ./obj

clean: uninstall
	@make -C libmx -f Makefile clean
	@rm -rf $(NAME)

reinstall: clean all
