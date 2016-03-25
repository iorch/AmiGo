FLAGS=-std=c++11 -g -D__DOCHECK
INCLUDES=-I ./include

test_x: test.cc include/amigo.h include/kifu.h
	${CXX} ${FLAGS} ${INCLUDES} $< -o $@


test: test_x
	echo "done."
