VERSION = 0.1
INCS = -Iinclude
LIBS = -lm
CFLAGS += -std=gnu17 ${INCS} -march=native -O2 -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -pipe -fasynchronous-unwind-tables
DEBUG_CFLAGS += -std=gnu17 ${INCS} -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Dcolorconvert_DEBUG -O0 -g -ggdb -pipe -fasynchronous-unwind-tables -fsanitize=undefined
LDFLAGS += ${LIBS} -flto
DEBUG_LDFLAGS += ${LIBS}
TEST_LDFLAGS += ${DEBUG_LDFLAGS} -lcriterion
CC ?= gcc
STRIP ?= strip

SRC = $(wildcard src/*.c)
release_OBJ = $(patsubst src/%.c, target/release/%.o, ${SRC})
debug_OBJ = $(patsubst src/%.c, target/debug/%.o, ${SRC})
SRC_TEST = $(wildcard tests/*_test.c)
OBJ_TEST = ${SRC_TEST:.c=.o}

target/release/%.o: src/%.c
	@mkdir -p target/release
	@${CC} ${CFLAGS} -c $< -o $@

target/release/colorconvert: ${release_OBJ}
	@${CC} $^ ${CFLAGS} ${LDFLAGS} -o $@
	@${STRIP} $@

target/debug/%.o: src/%.c
	@mkdir -p target/debug
	@${CC} ${DEBUG_CFLAGS} -c $< -o $@

target/debug/colorconvert: ${debug_OBJ}
	@${CC} $^ ${DEBUG_CFLAGS} ${DEBUG_LDFLAGS} -o $@

target/tests/test: $(filter-out %/main.o, ${debug_OBJ}) ${SRC_TEST} target/debug/colorconvert
	@mkdir -p target/tests
	@${CC} $(filter-out target/debug/colorconvert, $^) ${DEBUG_CFLAGS} -fprofile-arcs -ftest-coverage ${TEST_LDFLAGS} -o target/tests/test

clean:
	@rm -f target/release/* target/debug/* target/tests/*

all: target/release/colorconvert

release: target/release/colorconvert

debug: target/debug/colorconvert

test: target/tests/test
	@./target/tests/test -j0 || true

.PHONY: all release debug tests/test test clean


