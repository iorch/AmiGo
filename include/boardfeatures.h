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
            board_layer ladder_;
            board_layer own_layer_;
            board_layer other_layer_;
            board_layer empty_layer_;
            color_groups groups_;
            color_groups sg_; // selected groups, should be 1
            std::vector<position> threats;

            groups_ = board_.black_groups_;
            own_layer_ = board_.white_;
            other_layer_ = board_.white_;
            empty_layer_ = board_.empty_;

            if (board_.turn_ == player::black) {
                groups_ = board_.white_groups_;
                own_layer_ = board_.black_;
                other_layer_ = board_.black_;
            }
            position p = position::A19;
            auto is_liberty_ladder = [&](group g) {
                return g.second[p] && g.second.count() ==2;
            };
            auto is_last_liberty = [&](group g){
                return g.second[p] && g.second.count() ==1;
            };

            // look for threatened groups, and threatening positions
            do {
                auto it = std::copy_if(groups_.begin(),groups_.end(),sg_.begin(),is_liberty_ladder);
                threats.push_back(p);
                p.next();
            } while (!p.is_none());

            //for (auto g_ : sg_){
            //    while (true) {
            //        for (auto t_ : threats){
            //
            //        }
            //    }
            //}

            return ladder_;
        }

    };

} /* amigo */

#endif
