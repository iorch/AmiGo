FLAGS=-std=c++11 -D__DOCHECK
INCLUDES=-I ../include `python3-config --includes`
CFLAGS=`python3-config --cflags`

all: _amigo.so

amigo_wrap.cxx: amigo.i
	swig -c++ -python -py3 $<

_amigo.so: amigo_wrap.cxx
	${CXX} ${FLAGS} ${INCLUDES} -fpic -o amigo.o -c amigo_wrap.cxx
	#${CXX} -L/Users/iorch/.pyenv/versions/3.4.4/lib -lpython3.4m -dynamic -shared amigo.o -o $@
	${CXX} -shared amigo.o -o $@
