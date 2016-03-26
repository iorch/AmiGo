#ifndef __POLICY_H_
#define __POLICY_H_

#include "amigo.h"

#include <random>

namespace amigo {

struct priority_ {
    position pos;
    float pri;

    bool operator< (const priority_& other) {
        return this->pri > other.pri;        // High priority is sorted first.
    }
};

class policy {
    std::random_device rd_;
    std::mt19937 rnd_engine_;
    std::uniform_real_distribution<> rnd_real_;

    public:
    policy() : rnd_engine_(rd_()), rnd_real_(0,1) {}

    std::array<priority_, NPOSITIONS> evaluate(const board& brd) {
        std::array<priority_, NPOSITIONS> result;
        position p = position::A19;
        int i  = 0;
        do {
            result[i].pos = p;
            result[i].pri = rnd_real_(rnd_engine_);
            p.next();
            ++i;
        } while (!p.is_none());
        result[i].pos = position::NONE;
        result[i].pri = rnd_real_(rnd_engine_);

        std::sort(result.begin(), result.end());

        return result;
    }
};

} /* amigo */

#endif
