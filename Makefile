# Makefile

# Setting the compiler and the default linker program
# CC = gcc
# Compiler for debug target
CC = gcc -g3 -fsanitize=address
# Options for pre-processor (-I, -include, -D ... )
CPPFLAGS = -Iinclude
# Main compilation options
CFLAGS = -Wall -Wextra -Werror -std=c99 -O2
# Linker options (probably always empty)
LDFLAGS =
# Libs and path for linker
LDLIBS =

# Executables names
BIN = main
DEBUG = debug

# Directory for object files
BIN_DIR = bin/
SRC_DIR = src/
DEBUG_DIR = debug/

# DO NOT EDIT BELOW, unless you know exactly what you are doing

BUILD_DIR = ${BIN_DIR}${SRC_DIR}
build_dir = ${shell mkdir -p ${BUILD_DIR}}

SRC = ${wildcard src/*.c}
OBJ = ${patsubst ${SRC_DIR}%.c,${BUILD_DIR}%.o,${SRC}}

all: ${BIN}

${BIN}: ${build_dir} ${OBJ}
	${CC} ${OBJ} -o $@ ${LDLIBS} ${LDFLAGS}

${BUILD_DIR}%.o: ${SRC_DIR}%.c
	${CC} ${CPPFLAGS} ${CFLAGS} -o $@ -c $^

clean:
	${RM} -r ${BIN_DIR}		# Remove object files
	${RM} ${BIN} ${DEBUG}	# Remove executable files

.PHONY: all clean ${DEBUG}
# END

