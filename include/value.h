#ifndef __VALUE_H_
#define __VALUE_H_

#include "amigo.h"

namespace amigo {

class gut {
    std::random_device rd_;
    std::mt19937 rnd_engine_;
    std::normal_distribution<> rnd_real_;

    public:
    gut() : rd_(), rnd_engine_(rd_()), rnd_real_(0.5, 0.2) {}

    float evaluate(const board& brd) {
        float value = rnd_real_(rnd_engine_);
        if (value > 1.)
            value = 1.;
        if (value < 0 )
            value = 0;

        return value;
    }
};

} /* amigo */

#endif
