NAME = uls

INC = uls.h

SRC = mx_check.c \
	mx_ClearList.c \
	mx_CreateCmd.c\
	mx_flags.c \
	mx_getListOfDirectories.c \
	mx_fileAttraction.c \
	mx_LenForPrint.c \
	mx_Size.c \
	mx_islink.c \
	mx_PrintListFor.c \
	mx_ColorPrint.c \
	mx_PrintLong.c \
	mx_FormatForPrint.c \
	mx_PS.c \
	mx_PSF.c \
	mx_printT.c \
	main.c


OBJ = mx_check.o \
	mx_ClearList.o \
	mx_CreateCmd.o \
	mx_flags.o \
	mx_getListOfDirectories.o \
	mx_fileAttraction.o \
	mx_LenForPrint.o \
	mx_Size.o \
	mx_islink.o \
	mx_PrintListFor.o \
	mx_PrintLong.o \
	mx_FormatForPrint.o \
	mx_ColorPrint.o \
	mx_PS.o \
	mx_PSF.o \
	mx_printT.o \
	main.o 

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
clean:
	@make clean -sC libmx
	@rm -rf $(INC) $(SRC) ./obj

uninstall: clean
	@make uninstall -sC libmx
	@rm -rf $(NAME)


reinstall: uninstall install
