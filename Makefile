# Makefile

CC = gcc
CC_DEB = gcc -g3 -fsanitize=address
CPPFLAGS = -Iinclude
CFLAGS = -Wall -Wextra -Werror -std=c99 -O2
LDFLAGS =
LDLIBS =

SRC_DIR = src/
BIN_DIR = bin/
DIR = ${BIN_DIR}${SRC_DIR}
build_dir = ${shell mkdir -p ${DIR}}
BIN = main
DEBUG = debug
SRC = ${wildcard src/*.c}
OBJ = ${patsubst ${SRC_DIR}%.c,${DIR}%.o,${SRC}}

all: ${BIN}

${BIN}: ${build_dir} ${OBJ}
	${CC} ${CPPFLAGS} ${CFLAGS} ${OBJ} -o $@ ${LDLIBS} ${LDFLAGS}

${BIN_DIR}${SRC_DIR}%.o: ${SRC_DIR}%.c
	${CC} ${CPPFLAGS} ${CFLAGS} -o $@ -c $^ ${LDLIBS} ${LDFLAGS}

clean:
	rm -rf ${BIN_DIR} ${BIN} ${DEBUG}

${DEBUG}: ${build_dir} ${OBJ}
	${CC_DEB} ${CPPFLAGS} ${CFLAGS} ${OBJ} -o $@ ${LDLIBS} ${LDFLAGS}


.PHONY: all clean ${DEBUG}
# END
