#ifndef __KIFU_H__
#define __KIFU_H__

#include "amigo.h"

#include <fstream>
#include <regex>
#include <vector>
#include <utility>
#include <string>
#include <stdexcept>
#include <iostream>

namespace amigo {

class kifu {
    std::vector<std::pair<std::string, std::string>> tags_;
    std::vector<std::pair<player, position>> moves_;

    template <class C0, class C1>
    bool parse_pairs(const std::string& str, const std::string& regex,
            std::vector<std::pair<C0,C1>>& vector) {
        std::regex regex_(regex);
        std::smatch match;

        auto begin = str.begin();
        auto end = str.end();
        bool match_found = false;
        while (std::regex_search(begin, end, match, regex_)) {
            vector.push_back( std::make_pair(
                        C0(match[1].str()),
                        C1(match[2].str())
                        ) );
            begin += match[0].length();
            match_found = true;
        }

        return match_found;
    }

    bool parse(const std::string& game) {
        std::string game_regex(
                 "^\\(;((?:[A-Z]{0,2}\\[.*?\\]\\s*)+)((?:;[BW]\\[[a-s]{0,2}\\]\\s*)*)\\)\\s*$");
        std::string tag_regex("^([A-Z]{0,2})\\[(.*?)\\]\\s*");
        std::string move_regex("^;([WB])\\[([a-s]{0,2})\\]\\s*");

        std::vector<std::pair<std::string, std::string>> game_;
        if (!parse_pairs(game, game_regex, game_))
            return false;

        std::string tags = game_[0].first;
        parse_pairs(tags, tag_regex, tags_);

        std::string moves = game_[0].second;
        parse_pairs(moves, move_regex, moves_);

        return true;
    }

    kifu();

    public:

    kifu( std::string file_name ) {
        std::ifstream  file_stream( file_name, std::ifstream::in | std::ifstream::ate );
        int size = file_stream.tellg();
        file_stream.seekg(0);

        std::string file_content(size, ' ');;
        char *begin = const_cast<char*>( file_content.data() );

        file_stream.read(begin, size);
        file_stream.close();

        if (!parse( file_content ))
            throw std::logic_error("Unable to parse file.");
    }

    void sgf() {
        std::cout << "(;";
        for ( auto& x : tags_ )
            std::cout << x.first << '[' << x.second << "]\n";
        for ( auto& x : moves_ )
            std::cout << ';' << x.first.as_char() << '[' << x.second.alphabetical() << ']';
        std::cout << ")\n";
    }

    board final_board() {
        board brd;

        for (auto& move : moves_){
            brd.move(move.first, move.second);
            brd.update_gropus(move.first, move.second);
        }
        return brd;
    }

    board position_at(int moves){
        board brd;
        int count = 0;
        for (auto& move : moves_){
            if (moves == count) break;
            brd.move(move.first, move.second);
            count++;
        }
        return brd;
    }

};


} /* amigo */

#endif
