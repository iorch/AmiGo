#include "amigo.h"
#include "kifu.h"
#include "policy.h"
#include "value.h"
#include "engine.h"


int main(int argc, char** argv) {
    std::string file_name("in.sgf");
    if (argc == 2)
        file_name = argv[1];

    std::cout << file_name << '\n';
    amigo::kifu k(file_name);
    auto board = k.position_at(12);
    board.draw();

//    amigo::engine e;
//    e.think();

    for (auto& g : board.get_groups("white")){
        board.draw_layer(g.first);
        board.draw_layer(g.second);
    }

    return 0;
}
