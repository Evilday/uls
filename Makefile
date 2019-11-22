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

CFLGS = -std=c11 -Wall -Wextra -Wpedantic -Werror

all: install uninstall

install:
	@cd libmx && make -f Makefile install
	@cp $(INC) $(SRCS) .
	@clang $(CFLGS) -c  $(SRC)
	@mkdir  obj
	@mv $(OBJ) ./obj
	@clang $(CFLGS) $(OBJO) libmx/libmx.a -o $(NAME)

uninstall:
	@cd libmx && make -f Makefile uninstall
	@rm -rf $(OBJO) $(SRC) $(HEADTMP)
	@rm -rf ./obj

clean: uninstall
	@cd libmx && make -f Makefile clean
	@rm -rf $(NAME)

reinstall: clean all
