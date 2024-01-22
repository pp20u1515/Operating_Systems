CC := gcc
SRC := ./src/
INC := ./inc/
OBJ := ./obj/
CFLAGS := -std=c99 -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion -Wpedantic -Wvla

.PHONY: clean

SRCS = $(wildcard $(SRC)*.c)
OBJS = $(patsubst $(SRC)%.c, $(OBJ)%.o, $(SRCS))

app.exe: $(OBJS)
	$(CC) $^ -o $@

$(OBJ)%.o: $(SRC)%.c
	mkdir -p obj && cd obj && $(CC) $(CFLAGS) -c ../$<

clean:
	rm -fr .vscode
	rm *.exe
	rm -fr ./obj/