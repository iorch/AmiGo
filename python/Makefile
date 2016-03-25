FLAGS=-std=c++11 -D__DOCHECK
INCLUDES=-I ../include `python3-config --includes`

all: _amigo.so

amigo_wrap.cxx: amigo.i
	swig -c++ -python -py3 $<

_amigo.so: amigo_wrap.cxx
	${CXX} ${FLAGS} ${INCLUDES} -fpic -o amigo.o -c amigo_wrap.cxx
	${CXX} -shared -o $@ amigo.o
