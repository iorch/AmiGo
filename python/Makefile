FLAGS=-std=c++11 -D__DOCHECK
INCLUDES=-I ../include `python-config --includes`

all: _amigo.so

amigo_wrap.cxx: amigo.i
	swig -c++ -python $<

_amigo.so: amigo_wrap.cxx
	${CC} ${FLAGS} ${INCLUDES} -fpic -o amigo.o -c amigo_wrap.cxx
	${CC} -shared -o $@ amigo.o
