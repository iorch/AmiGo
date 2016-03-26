#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "amigo.h"

namespace amigo {

class engine {
    policy policy_;
    gut    value_;

    struct node_;
    using shared_node_ = std::shared_ptr<node_>;

    // It seems that is better to have dinamic allocation (at least for size )
    // the price is calculate every time the policy and the cost of allocation
    // With this implementation sizeof(node_) = 8840, while sizeof(board) = 152
    // (with 3 layers);
    struct node_ {
        const board state;
        const float value;
        const std::array<priority_, NPOSITIONS> priorities;
        std::array<shared_node_, NPOSITIONS> children;

        node_(const board& brd, gut& v, policy& p) :
            state(brd),
            value(v.evaluate(brd)),
            priorities(p.evaluate(brd)) {}
    };

    shared_node_  root_;

    shared_node_ make_shared_node_(const board& b) {
        return std::make_shared<node_>(b, value_, policy_);
    }


    /* Deep first search up to deep considering only priority > priority_cut
     * */
    int explore(shared_node_& node, int deep, float priority_cut) {
        int expanded = 0;

        if (deep <= 0 )
            return expanded;

        for (int i = 0; i < NPOSITIONS; ++i ) {
            auto& pos  = node->priorities[i].pos;
            auto& pri  = node->priorities[i].pri;
            if (pri < priority_cut) break;

            auto& child = node->children[i];
            if (!child.use_count()) {
                board bxard = node->state;  // Make a copy;
                bxard.move(pos);
                child = make_shared_node_(bxard);
                ++expanded;
            }
            expanded += explore(child, deep - 1, priority_cut);
        }

        return expanded;
    } 

    public:
    engine() : root_(make_shared_node_(board())) {}

    void think() {
        int expanded = explore( root_, 5, 0.97 );
        std::cout << "expanded = " << expanded << '\n';
    }


};

} /* amigo */

#endif
