#include "amigo.h"
#include "kifu.h"
#include "policy.h"
#include "value.h"
#include "engine.h"


int main(int argc, char** argv) {
    std::string file_name("in.sgf");
    if (argc == 2)
        file_name = argv[1];

    /*
    std::cout << file_name << '\n';
    amigo::kifu k(file_name);
    auto board = k.final_board();
    board.draw();
    */

    amigo::engine e;
    e.think();

    return 0;
}
