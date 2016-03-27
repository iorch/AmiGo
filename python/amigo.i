%module amigo

%{
#define SWIG_FILE_WITH_INIT
#include "amigo.h"
#include "kifu.h"
#include "policy.h"
#include "value.h"
%}

namespace amigo {
struct player {
    player(char*);
    void toggle();
    char as_char();
};

struct position {
    position(char*);
    std::string alphabetical();
    bool is_top();
    bool is_bottom();
    bool is_leftmost();
    bool is_rightmost();

    bool is_none();

    position up();
    position down();
    position left();
    position right();

    position up_left();
    position up_right();
    position down_left();
    position down_right();

    void next();
};

struct board {
    board();
    void move(player, position);
    void move(position);
    void draw();
};

struct kifu {
    kifu(char*);
    void sgf();
    board position_at(int);
};

struct policy {
    policy();
};

struct gut {
    float evaluate(board);
};

}
