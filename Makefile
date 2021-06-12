# Makefile

LIB_DIRS = ${dir ${wildcard include/*/}}
DIRS_INCLUDE = ${patsubst %/, -I%/, ${LIB_DIRS}}

# Setting the compiler and the default linker program
# CC = gcc
# Compiler for debug target
CC = gcc -g3 #-fsanitize=address
# Options for pre-processor (-I, -include, -D ... )
CPPFLAGS = ${DIRS_INCLUDE}

# Main compilation options
CFLAGS = -Wall -Wextra -Werror -D_POSIX_C_SOURCE=200112L -std=c99 -O2
# Linker options (probably always empty)
LDFLAGS =
# Libs and path for linker
LDLIBS = -lm -lpthread

# Executables names
EXAMPLES_DIR = examples/
BIN = ${patsubst ${EXAMPLES_DIR}%.c, %.out, ${EXAMPLES}}
EXAMPLES = ${wildcard ${EXAMPLES_DIR}*.c}
EX_OBJ = ${patsubst ${EXAMPLES_DIR}%.c, ${EXAMPLES_DIR}${BIN_DIR}%.o, ${EXAMPLES}}

# Directory for object files
BIN_DIR = bin/
SRC_DIR = src/
DEBUG_DIR = debug/
DIRS = ${dir ${wildcard ${SRC_DIR}*/}}
# DO NOT EDIT BELOW, unless you know exactly what you are doing

BUILD_DIR = ${BIN_DIR}${SRC_DIR}
DIRS_BIN = ${patsubst %/, ${BIN_DIR}%/, ${DIRS}}
build_dir = ${shell mkdir -p ${DIRS_BIN}}
ex_dir = ${shell mkdir -p ${EXAMPLES_DIR}${BIN_DIR}}

SRC = ${wildcard src/*/*.c}

OBJ = ${patsubst ${SRC_DIR}%.c,${BUILD_DIR}%.o,${SRC}}

all: ${build_dir} ${ex_dir} ${BIN}

${EXAMPLES_DIR}${BIN_DIR}%.o: ${EXAMPLES_DIR}%.c
	${CC} ${CPPFLAGS} ${CGLAGS} -o $@ -c $^

%.out: ${EXAMPLES_DIR}${BIN_DIR}%.o ${OBJ}
	${CC} ${OBJ} $< -o $@ ${LDLIBS} ${LDFLAGS}

${BUILD_DIR}%.o: ${SRC_DIR}%.c
	${CC} ${CPPFLAGS} ${CFLAGS} -o $@ -c $^

.PRECIOUS: ${OBJ}

clean:
	${RM} -r ${BIN_DIR}			# Remove object files
	${RM} -r ${EXAMPLES_DIR}${BIN_DIR}		# Remove object files of examples
	${RM} ${BIN} ${DEBUG}		# Remove executable files

.PHONY: all clean ${DEBUG}
# END
