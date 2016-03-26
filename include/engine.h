#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "amigo.h"

namespace amigo {

class engine {
    struct node_;
    using shared_node_ = std::shared_ptr<node_>;

    // It seems that is better to have dinamic allocation (at least for size )
    // the price is calculate every time the policy and the cost of allocation
    // With this implementation sizeof(node_) = 8840, while sizeof(board) = 152
    // (with 3 layers);
    struct node_ {
        const board state;
        const std::array<priority_, NPOSITIONS> priorities;
        std::array<shared_node_, NPOSITIONS> children;

        node_(const board& brd, policy& policy_) :
            state(brd), priorities(policy_.evaluate(brd)) {}
    };

    shared_node_  root_;
    policy policy_;


    void expand(shared_node_& node, int deep) {
        if (deep < 0 )
            return;

        for (int i = 0; i < NPOSITIONS; ++i ) {
            auto& pos  = node->priorities[i].pos;
            auto& val  = node->priorities[i].val;
            if (val < 0.99) break;

            auto& child = node->children[i];
            if (!child.use_count()) {
                board bxard = node->state;  // Make a copy;
                bxard.move(pos);
                bxard.draw();
                child = std::make_shared<node_>(bxard, policy_);
                expand( child, deep - 1 );
            }
        }
    } 

    public:
    engine() : policy_() ,root_(std::make_shared<node_>(board(), policy_)) {}

    void think() {
        expand( root_, 20 );
    }


};

} /* amigo */

#endif
