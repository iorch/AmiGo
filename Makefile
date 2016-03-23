CC=g++
FLAGS=-std=c++11 -D__DOCHECK
INCLUDES=-I ./include

test_x: test.cc
	${CC} ${FLAGS} ${INCLUDES} $< -o $@
