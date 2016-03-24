#include "amigo.h"
#include "kifu.h"

int main(int argc, char** argv) {
    std::string file_name("in.sgf");
    if (argc == 2)
        file_name = argv[1];

    std::cout << file_name << '\n';
    amigo::kifu k(file_name);
    k.print();
   

    return 0;
}
