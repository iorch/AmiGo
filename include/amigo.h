#ifndef  __AMIGO_H__
#define  __AMIGO_H__

#include <string>
#include <bitset>
#include <cstring>
#include <stdexcept>
#include <iostream>

#ifdef __DOCHECK
    #define __NOEXCEPT false
#else
    #define __NOEXCEPT true
#endif

#define BOARD_SIZE 19
#define BOARD_CELS BOARD_SIZE*BOARD_SIZE

namespace amigo {

    class player {
        char player_;

        public:
        enum static_player { white = 'W', black = 'B' }; 

        player(char c) noexcept(__NOEXCEPT) : player_(c)
        {
#ifdef __DOCHECK
            if ( c != white && c != black )
                throw std::logic_error("Player must be black or white.");
#endif
        }

        player(const std::string& str) {
            if (str.size() == 1 && (str[0] == 'B' || str[0] == 'W'))
                player_ = str[0];
            else if ( str == "black" )
                player_ = black;
            else if ( str == "white" )
                player_ = white;
            else
                throw std::logic_error("Player string is malformed");
        }

        char as_char() {
            return player_;
        }

        bool operator==(static_player p) const  {
            return player_ == p;
        }
    };

    class board_layer;

    class position {
        friend class board_layer;
        int position_;
        
        public:
enum {
   none = -1,
   aa, ba, ca, da, ea, fa, ga, ha, ia, ja, ka, la, ma, na, oa, pa, qa, ra, sa,
   ab, bb, cb, db, eb, fb, gb, hb, ib, jb, kb, lb, mb, nb, ob, pb, qb, rb, sb,
   ac, bc, cc, dc, ec, fc, gc, hc, ic, jc, kc, lc, mc, nc, oc, pc, qc, rc, sc,
   ad, bd, cd, dd, ed, fd, gd, hd, id, jd, kd, ld, md, nd, od, pd, qd, rd, sd,
   ae, be, ce, de, ee, fe, ge, he, ie, je, ke, le, me, ne, oe, pe, qe, re, se,
   af, bf, cf, df, ef, ff, gf, hf, if_,jf, kf, lf, mf, nf, of, pf, qf, rf, sf,
   ag, bg, cg, dg, eg, fg, gg, hg, ig, jg, kg, lg, mg, ng, og, pg, qg, rg, sg,
   ah, bh, ch, dh, eh, fh, gh, hh, ih, jh, kh, lh, mh, nh, oh, ph, qh, rh, sh,
   ai, bi, ci, di, ei, fi, gi, hi, ii, ji, ki, li, mi, ni, oi, pi, qi, ri, si,
   aj, bj, cj, dj, ej, fj, gj, hj, ij, jj, kj, lj, mj, nj, oj, pj, qj, rj, sj,
   ak, bk, ck, dk, ek, fk, gk, hk, ik, jk, kk, lk, mk, nk, ok, pk, qk, rk, sk,
   al, bl, cl, dl, el, fl, gl, hl, il, jl, kl, ll, ml, nl, ol, pl, ql, rl, sl,
   am, bm, cm, dm, em, fm, gm, hm, im, jm, km, lm, mm, nm, om, pm, qm, rm, sm,
   an, bn, cn, dn, en, fn, gn, hn, in, jn, kn, ln, mn, nn, on, pn, qn, rn, sn,
   ao, bo, co, do_,eo, fo, go, ho, io, jo, ko, lo, mo, no, oo, po, qo, ro, so,
   ap, bp, cp, dp, ep, fp, gp, hp, ip, jp, kp, lp, mp, np, op, pp, qp, rp, sp,
   aq, bq, cq, dq, eq, fq, gq, hq, iq, jq, kq, lq, mq, nq, oq, pq, qq, rq, sq,
   ar, br, cr, dr, er, fr, gr, hr, ir, jr, kr, lr, mr, nr, or_,pr, qr, rr, sr,
   as, bs, cs, ds, es, fs, gs, hs, is, js, ks, ls, ms, ns, os, ps, qs, rs, ss
};

enum {
   NONE = -1,
   A19, B19, C19, D19, E19, F19, G19, H19, J19, K19, L19, M19, N19, O19, P19, Q19, R19, S19, T19,
   A18, B18, C18, D18, E18, F18, G18, H18, J18, K18, L18, M18, N18, O18, P18, Q18, R18, S18, T18,
   A17, B17, C17, D17, E17, F17, G17, H17, J17, K17, L17, M17, N17, O17, P17, Q17, R17, S17, T17,
   A16, B16, C16, D16, E16, F16, G16, H16, J16, K16, L16, M16, N16, O16, P16, Q16, R16, S16, T16,
   A15, B15, C15, D15, E15, F15, G15, H15, J15, K15, L15, M15, N15, O15, P15, Q15, R15, S15, T15,
   A14, B14, C14, D14, E14, F14, G14, H14, J14, K14, L14, M14, N14, O14, P14, Q14, R14, S14, T14,
   A13, B13, C13, D13, E13, F13, G13, H13, J13, K13, L13, M13, N13, O13, P13, Q13, R13, S13, T13,
   A12, B12, C12, D12, E12, F12, G12, H12, J12, K12, L12, M12, N12, O12, P12, Q12, R12, S12, T12,
   A11, B11, C11, D11, E11, F11, G11, H11, J11, K11, L11, M11, N11, O11, P11, Q11, R11, S11, T11,
   A10, B10, C10, D10, E10, F10, G10, H10, J10, K10, L10, M10, N10, O10, P10, Q10, R10, S10, T10,
   A9, B9, C9, D9, E9, F9, G9, H9, J9, K9, L9, M9, N9, O9, P9, Q9, R9, S9, T9,
   A8, B8, C8, D8, E8, F8, G8, H8, J8, K8, L8, M8, N8, O8, P8, Q8, R8, S8, T8,
   A7, B7, C7, D7, E7, F7, G7, H7, J7, K7, L7, M7, N7, O7, P7, Q7, R7, S7, T7,
   A6, B6, C6, D6, E6, F6, G6, H6, J6, K6, L6, M6, N6, O6, P6, Q6, R6, S6, T6,
   A5, B5, C5, D5, E5, F5, G5, H5, J5, K5, L5, M5, N5, O5, P5, Q5, R5, S5, T5,
   A4, B4, C4, D4, E4, F4, G4, H4, J4, K4, L4, M4, N4, O4, P4, Q4, R4, S4, T4,
   A3, B3, C3, D3, E3, F3, G3, H3, J3, K3, L3, M3, N3, O3, P3, Q3, R3, S3, T3,
   A2, B2, C2, D2, E2, F2, G2, H2, J2, K2, L2, M2, N2, O2, P2, Q2, R2, S2, T2,
   A1, B1, C1, D1, E1, F1, G1, H1, J1, K1, L1, M1, N1, O1, P1, Q1, R1, S1, T1
};

        position(int p) noexcept(__NOEXCEPT) : position_(p)
        {
#ifdef __DOCHECK
            if ( p < aa || p > ss )
                throw std::logic_error("Position is invalid.");
#endif
        }

        position(const std::string& str) {
            if (str.size() == 0) {
                position_ = -1;
                return;
            }

            if (str.size() != 2)
                throw std::logic_error("Position string is malformed.");

            int y = str[0] - 'a';
            int x = str[1] - 'a';
            if ( x < 0 || x > BOARD_SIZE || y < 0 || y > BOARD_SIZE )
                throw std::logic_error("Position string is malformed.");
            position_ =  x * 19 + y;
        }

        std::string alphabetical() {
            if ( position_ == none ) {
                return std::string();
            }
            std::string p(2, '\0');
            p[0] = position_ / BOARD_SIZE + 'a';
            p[1] = position_ % BOARD_SIZE + 'a';
            return p;
        }

        bool is_top() const       { return position_ < BOARD_SIZE; }
        bool is_bottom() const    { return position_ > BOARD_CELS - BOARD_SIZE; }
        bool is_leftmost() const  { return position_ % BOARD_SIZE == 0; }
        bool is_rightmost() const { return (position_+1) % BOARD_SIZE == 0; }

        bool is_none() const { return position_ == NONE; }

        position up() {
            if (is_none() || is_top())
                return position(NONE);
            else
                return position(position_ - BOARD_SIZE);
        }

        position down() {
            if (is_none() || is_bottom())
                return position(NONE);
            else
                return position(position_ + BOARD_SIZE);
        }

        position left() {
            if (is_none() || is_leftmost())
                return position(NONE);
            else
                return position(position_ - 1);
        }

        position right() {
            if (is_none() || is_rightmost())
                return position(NONE);
            else
                return position(position_ + 1);
        }

        position up_left()    { return up().left(); };
        position up_right()   { return up().right(); };
        position down_left()  { return down().left(); };
        position down_right() { return down().right(); };

        void next() {
            if (is_none() || position_ == T1)
                position_ = NONE;
            else
                position_ += 1;
        }
    };


    class board_layer {
        std::bitset<BOARD_CELS> layer_;

        public:
        board_layer() {}
        board_layer(int fill) { if(fill) layer_ = ~layer_; }

        void place(const position& p) {
            layer_.set(p.position_);
        }

        void remove(const position& p) {
            layer_.reset(p.position_);
        }

        bool operator[] (const position& p) {
            return layer_[p.position_];
        }
    };

    class board {
        board_layer white_;
        board_layer black_;
        board_layer empty_;
        int moves_;
        player turn_;

        public:
        board() : turn_(player::black), moves_(0), empty_(1) {}

        void move(const player& py, const position& p) {
            if (p.is_none())
                return;

            if (py == player::black)
                black_.place(p);
            else
                white_.place(p);

            empty_.remove(p);
        }

        void draw() {
            position p = position::A19;
            do {
                if (white_[p])
                    std::cout << 'W';
                if (black_[p])
                    std::cout << 'B';
                if (empty_[p])
                    std::cout << '.';

                if (p.is_rightmost())
                    std::cout << '\n';

                p.next();
            } while (!p.is_none());
        }
    };
/*
    class game_meta {
        int board_size; // SZ
        std::string white_name, black_name; // PW, PB
        int white_ranking, black_ranking; // WR, BR
        std::string date;
        float komi;

        GM game 1= go
        FF file format
        SZ board_size;
        PW white_nickname;
        WR white-ranking;
        PB black_nickname;
        BR black_ranking;
        DT date;
        PC server_name;
        KM komi float something.5;
        RE result;
        RU rules;
        OT overtime;
        CA utf-8;
        ST xx
        AP application;
        TM xx;
        HA handicap #stones;
        AB handicap positions
    }
*/
} /* amigo */

#endif
