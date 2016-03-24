%module amigo

%{
#define SWIG_FILE_WITH_INIT
#include "amigo.h"
#include "kifu.h"
%}

namespace amigo {
struct kifu {
    kifu(char*);
    void print();
};
}
