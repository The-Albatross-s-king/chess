# Makefile

CC = gcc
CPPFLAGS = -Iinclude
CFLAGS = -fsanitize=address -Wall -Wextra -Werror -std=c99 -O0 -g3
LDFLAGS =
LDLIBS =

BIN = main
SRC = ${shell find ./src/ -name *.c}
OBJ = ${SRC:.c=.o}


all: ${BIN}

${BIN}: ${OBJ}
	${CC} ${CPPFLAGS} ${CFLAGS} $^ -o $@ ${LDLIBS} ${LDFLAGS}

clean:
	rm -f ${OBJ} ${BIN}

.PHONY: all clean
# END
