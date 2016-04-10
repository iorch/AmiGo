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
        board_layer get_capture_ladders(){
            /*
            - [X]  look for enemy groups with 2 liberties
            - [X]  loop over those groups and liberties
            - [X] fill one liberty
            - [] can enemy kill own stones?
            - [X] place the forced move
            - [X] count liberties
            - [] check for following cases:
                * more than 2 liberties: escape, ladder fails
                * 2 liberties, fill one liberty, ....
                * 1 liberty, ladder succed
            */

            board_layer ladder_;
            board_layer own_layer_;
            board_layer opponent_layer_;
            board_layer empty_layer_;
            color_groups groups_;
            std::vector<position> threats;

            // if it is white's trun
            groups_ = board_.black_groups_; // groups to kill
            own_layer_ = board_.white_;
            opponent_layer_ = board_.black_;
            empty_layer_ = board_.empty_;
            player opponent = player::black;

            if (board_.turn_ == player::black) {
                opponent = player::white;
                groups_ = board_.white_groups_;
                own_layer_ = board_.black_;
                opponent_layer_ = board_.white_;
            }
            color_groups ladders_;//(groups_.size()); // get possible ladders

            position p = position::A19;
            auto has_two_liberties = [&](group g) {
                return (g.second[p] && g.second.count() ==2);
            };
            auto is_last_liberty = [&](group g){
                return g.second[p] && g.second.count() ==1;
            };
            //auto is_stone_in_group = [&](position p, group g){
            //    return ( g.first[p] );
            //};
            auto is_liberty_group = [](position p, group g){
                return ( g.second[p] );
            };
            auto current_liberties = [](group g){
                std::vector<position> _liberties;
                position _p = position::A19;
                do{
                    if (g.second[_p]) _liberties.push_back(_p);
                    _p.next();
                } while (!_p.is_none());
                return (_liberties);
            };
            // look for threatened groups, and threatening positions
            //auto it = ladders_.begin();
            bool group_inc;
            do {
                group_inc = false;
                for (auto& g: ladders_){
                    group_inc = group_inc || is_liberty_group( p, g );
                }
                if ( !empty_layer_[p] || group_inc) {
                    p.next();
                    continue;
                }
                auto it = std::copy_if( groups_.begin(),
                                    groups_.end(),
                                    back_inserter(ladders_),
                                    has_two_liberties );
                threats.push_back(p);
                p.next();
            } while (!p.is_none());
            //ladders_.resize( std::distance( ladders_.begin(), it ) );
            ladder_ = ladders_.begin()->first;
            std::vector<position> liberties;
            std::vector<position> liberties_tmp;
            int nliberties = liberties.size();
            group _g;
            for (auto& g: ladders_){
                auto tmp_board = board_;
                auto _tmp_board_ = tmp_board;
                auto lit = liberties.begin();
                auto lit_tmp = liberties.begin();
                _g = tmp_board.get_group_at(opponent,g.first.first());
                liberties = current_liberties(_g);
                nliberties = liberties.size();
                while (nliberties == 2){
                    nliberties = 3;
                    _g = tmp_board.get_group_at(opponent,g.first.first());
                    liberties = current_liberties(_g);
                    lit = liberties.begin();
                    for (;lit != liberties.end(); ++lit){
                        _tmp_board_ = tmp_board;
                        if ((*lit).is_none() || !_tmp_board_.empty_[*lit]) continue;
                        _g = _tmp_board_.get_group_at(opponent,g.first.first());
                        _tmp_board_.move(*lit);
                        _g = _tmp_board_.get_group_at(opponent,g.first.first());
                        liberties_tmp = current_liberties(_g);
                        lit_tmp = liberties_tmp.begin();
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
                }

                ladder_ = tmp_board.white_;
            }

            return ladder_;
        }

    };

} /* amigo */

#endif
