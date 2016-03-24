%module amigo

%{
#define SWIG_FILE_WITH_INIT
#include "amigo.h"
#include "kifu.h"
%}

namespace amigo {
struct board {
    void draw();
};

struct kifu {
    kifu(char*);
    board final_board();
};

}
