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
            - [ * ] look for enemy groups with 2 liberties
            - [] loop over those groups
            - [] fill one liberty
            - [] place the forced move
            - [] count liberties
            - [] check for following cases:
                *) more than 2 liberties: escape, ladder fails
                *) 2 liberties, fill one liberty, ....
                *) 1 liberty, ladder succed
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

            if (board_.turn_ == player::black) {
                groups_ = board_.white_groups_;
                own_layer_ = board_.black_;
                opponent_layer_ = board_.white_;
            }
            color_groups sg_(groups_.size()); // selected groups

            position p = position::A19;
            auto has_two_liberties = [&](group g) {
                return (g.second[p] && g.second.count() ==2);
            };
            auto is_last_liberty = [&](group g){
                return g.second[p] && g.second.count() ==1;
            };
            std::cout << "test" << std::endl;
            // look for threatened groups, and threatening positions
            auto it = sg_.begin();
            do {
                if (!empty_layer_[p]) {
                    p.next();
                    continue;
                }
                it = std::copy_if(groups_.begin(),groups_.end(),sg_.begin(),has_two_liberties);
                threats.push_back(p);
                p.next();
            } while (!p.is_none());
            sg_.resize(std::distance(sg_.begin(),it));
            std::cout << sg_.size() << std::endl;

            ladder_ = sg_[0].first;
            return ladder_;
        }

    };

} /* amigo */

#endif
