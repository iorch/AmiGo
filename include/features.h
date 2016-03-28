#ifndef __FEATURES_H__
#define __FEATURES_H__

#include "amigo.h"

namespace amigo {

    class features {
        board board_;

        public:

        features(board board){
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

    };

} /* amigo */

#endif
