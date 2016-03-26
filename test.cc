#include "amigo.h"
#include "kifu.h"

int main(int argc, char** argv) {
    std::string file_name("in.sgf");
    if (argc == 2)
        file_name = argv[1];

    std::cout << file_name << '\n';
    amigo::kifu k(file_name);
    auto board = k.position_at(12);
    board.draw();
    for (auto& g : board.get_groups("white")){
        board.draw_layer(g.first);
        board.draw_layer(g.second);
    }

    return 0;
}
