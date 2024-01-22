CC := gcc
OBJ := ./obj/
INC := ./inc/
SRC := ./src/
CFLAGS := -std=c99 #-Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-equal -Wsign-conversion -Wfloat-conversion -Wredundant-decls

.PHONY : clean

release: app.exe

SRCS = $(wildcard $(SRC)*.c)
OBJS = $(patsubst $(SRC)%.c, $(OBJ)%.o, $(SRCS))

app.exe: $(OBJS)
	$(CC) $^ -o $@

$(OBJ)%.o : $(SRC)%.c
	mkdir -p obj && cd obj && $(CC) $(CFLAGS) -c ../$<

cleaner : 
	rm *.exe
	rm -fr .vscode
