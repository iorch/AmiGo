#ifndef __BOARDFEATURES_H__
#define __BOARDFEATURES_H__

#include "amigo.h"

namespace amigo {

    class boardfeatures {
        board board_;

        public:

        boardfeatures(board board){
            board_ = board;
        }

        board_layer zeros(){
            board_layer zeros_;
            return zeros_;
        }

        board_layer ones(){
            board_layer ones_;
            position p = position::A19;
            do {
                ones_.place(p);
                p.next();
            } while (!p.is_none());
            return ones_;
        }

        board_layer empty(){
            return board_.empty_;
        }

        board_layer black(){
            return board_.black_;
        }

        board_layer white(){
            return board_.white_;
        }

        //********    W   I   P    *******
        board_layer capture_ladder(){
            board_layer cl;
            position p = position::A19;
            do {
                if (board_.empty_[p]){
                    if (is_capture_ladder(p)){
                        cl.place(p);
                    }
                }
                p.next();

            } while (!p.is_none());
            return cl;
        }

        bool is_capture_ladder(const position& _ptest){
            /*
            - [X]  look for enemy groups with 2 liberties
            - [X]  loop over those groups and liberties
            - [X] fill one liberty
            - [X] can enemy kill own stones?
            - [X] place the forced move
            - [X] count liberties
            - [] check for following cases:
                * more than 2 liberties: escape, ladder fails
                * 2 liberties, fill one liberty, ....
                * 1 liberty, ladder succeed
            */
            bool is_ladder = false;
            group ladder_;
            board_layer empty_layer_;
            color_groups groups_;
            std::vector<position> threats;

            // if it is white's turn
            groups_ = board_.black_groups_; // groups to kill
            empty_layer_ = board_.empty_;
            player opponent = player::black;

            if (board_.turn_ == player::black) {
                opponent = player::white;
                groups_ = board_.white_groups_;
            }
            color_groups ladders_;//(groups_.size()); // get possible ladders

            position p0 = position::A19;
            auto has_two_liberties = [&](group g) {
                return (g.second[p0] && g.second.count() ==2);
            };
            //auto is_last_liberty = [&](group g){
            //    return g.second[p0] && g.second.count() ==1;
            //};
            //auto is_stone_in_group = [&](position p, group g){
            //    return ( g.first[p0] );
            //};
            auto is_liberty_group = [](position p, group g){
                return ( g.second[p] );
            };
            // look for threatened groups, and threatening positions
            //auto it = ladders_.begin();
            bool group_inc;
            do {
                group_inc = false;
                for (auto& g: ladders_){
                    group_inc = group_inc || is_liberty_group( p0, g );
                }
                if ( !empty_layer_[p0] || group_inc) {
                    p0.next();
                    continue;
                }
                auto it = std::copy_if( groups_.begin(),
                                    groups_.end(),
                                    back_inserter(ladders_),
                                    has_two_liberties );
                threats.push_back(p0);
                p0.next();
            } while (!p0.is_none());
            auto compare_position = [&](position _p){
                return ( _ptest.alphabetical() == _p.alphabetical() );
            };
            auto _is_ptest_threat = std::find_if(threats.begin(),threats.end(),compare_position);
            if (std::distance(_is_ptest_threat,threats.end())==0) return(false);
            std::vector<position> liberties;
            std::vector<position> liberties_tmp;
            int nliberties = liberties.size();
            group _g;
            for (auto& g: ladders_){
                auto tmp_board = board_;
                auto _tmp_board_ = tmp_board;
                auto __tmp_board__ = _tmp_board_;
                auto lit = liberties.begin();
                auto lit_tmp = liberties.begin();
                _g = tmp_board.get_group_at(opponent,g.first.first());
                liberties = current_liberties(_g);
                nliberties = liberties.size();
                bool first_stone = true;
                while (nliberties == 2){
                    nliberties = 3;
                    _g = tmp_board.get_group_at(opponent,g.first.first());
                    liberties = current_liberties(_g);
                    lit = liberties.begin();
                    for (;lit != liberties.end(); ++lit){
                        tmp_board.draw();
                        std::cout << "test" << std::endl;
                        std::cout << (*lit).alphabetical() << std::endl;
                        _tmp_board_ = tmp_board;
                        //if ((*lit).is_none() || !_tmp_board_.empty_[*lit]) continue;
                        _g = _tmp_board_.get_group_at(opponent,g.first.first());
                        if ( first_stone ){
                            _tmp_board_.move(_ptest);
                            first_stone = false;
                        } else {
                            if (!_tmp_board_.is_legal(tmp_board.turn_, *lit)) {
                                continue;
                            }
                            _tmp_board_.move(*lit);
                        }
                        _tmp_board_.draw();
                        _g = _tmp_board_.get_group_at(opponent,g.first.first());
                        liberties_tmp = current_liberties(_g);
                        lit_tmp = liberties_tmp.begin();
                        for ( auto& _og: _tmp_board_.get_groups(board_.next_to_play()) ){
                            __tmp_board__ = _tmp_board_;
                            auto _ogl = current_liberties(_og);
                            if (_ogl.size() > 1) continue;
                            __tmp_board__.move(*_ogl.begin());
                            _og = __tmp_board__.get_group_at(opponent,g.first.first());
                            liberties_tmp = current_liberties(_og);
                            if (liberties_tmp.size() >= 2){
                                lit_tmp = _ogl.begin();
                                tmp_board = _tmp_board_;
                                break;
                            }
                        }
                        _tmp_board_.move(*lit_tmp);
                        _g = _tmp_board_.get_group_at(opponent,g.first.first());
                        liberties_tmp = current_liberties(_g);
                        if (liberties_tmp.size() <= 2){
                            tmp_board = _tmp_board_;
                            liberties_tmp = current_liberties(_g);
                            liberties = liberties_tmp;
                            nliberties = liberties.size();
                            if (nliberties == 1) break;
                        }
                    }
                    first_stone = false;
                }
                ladder_ = _g;
            }
            is_ladder = is_ladder || current_liberties(ladder_).size()==1;
            return is_ladder;
        }

    };

} /* amigo */

#endif
