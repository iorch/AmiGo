FLAGS=-std=c++11 -g -D__DOCHECK
INCLUDES=-I ./include

test_x: test.cc include/amigo.h include/kifu.h include/policy.h include/engine.h include/value.h include/boardfeatures.h
	${CXX} ${FLAGS} ${INCLUDES} $< -o $@


test: test_x
	echo "done."
