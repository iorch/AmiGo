#ifndef  __AMIGO_H__
#define  __AMIGO_H__

#include <string>
#include <stdexcept>

#ifdef __DOCHECK
    #define __NOEXCEPT false
#else
    #define __NOEXCEPT true
#endif

namespace amigo {

    class player {
        char player_;

        public: 
        static const char white = 'W';
        static const char black = 'B';

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
    };

    class position {
        int position_;
        
        public:
        enum { 
     aa, ab, ac, ad, ae, af, ag, ah, ai, aj, ak, al, am, an, ao, ap, aq, ar, as,
     ba, bb, bc, bd, be, bf, bg, bh, bi, bj, bk, bl, bm, bn, bo, bp, bq, br, bs,
     ca, cb, cc, cd, ce, cf, cg, ch, ci, cj, ck, cl, cm, cn, co, cp, cq, cr, cs,
     da, db, dc, dd, de, df, dg, dh, di, dj, dk, dl, dm, dn, do_, dp, dq, dr, ds,
     ea, eb, ec, ed, ee, ef, eg, eh, ei, ej, ek, el, em, en, eo, ep, eq, er, es,
     fa, fb, fc, fd, fe, ff, fg, fh, fi, fj, fk, fl, fm, fn, fo, fp, fq, fr, fs,
     ga, gb, gc, gd, ge, gf, gg, gh, gi, gj, gk, gl, gm, gn, go, gp, gq, gr, gs,
     ha, hb, hc, hd, he, hf, hg, hh, hi, hj, hk, hl, hm, hn, ho, hp, hq, hr, hs,
     ia, ib, ic, id, ie, if_, ig, ih, ii, ij, ik, il, im, in, io, ip, iq, ir, is,
     ja, jb, jc, jd, je, jf, jg, jh, ji, jj, jk, jl, jm, jn, jo, jp, jq, jr, js,
     ka, kb, kc, kd, ke, kf, kg, kh, ki, kj, kk, kl, km, kn, ko, kp, kq, kr, ks,
     la, lb, lc, ld, le, lf, lg, lh, li, lj, lk, ll, lm, ln, lo, lp, lq, lr, ls,
     ma, mb, mc, md, me, mf, mg, mh, mi, mj, mk, ml, mm, mn, mo, mp, mq, mr, ms,
     na, nb, nc, nd, ne, nf, ng, nh, ni, nj, nk, nl, nm, nn, no, np, nq, nr, ns,
     oa, ob, oc, od, oe, of, og, oh, oi, oj, ok, ol, om, on, oo, op, oq, or_, os,
     pa, pb, pc, pd, pe, pf, pg, ph, pi, pj, pk, pl, pm, pn, po, pp, pq, pr, ps,
     qa, qb, qc, qd, qe, qf, qg, qh, qi, qj, qk, ql, qm, qn, qo, qp, qq, qr, qs,
     ra, rb, rc, rd, re, rf, rg, rh, ri, rj, rk, rl, rm, rn, ro, rp, rq, rr, rs,
     sa, sb, sc, sd, se, sf, sg, sh, si, sj, sk, sl, sm, sn, so, sp, sq, sr, ss};

        position(int p) noexcept(__NOEXCEPT) : position_(p)
        {
#ifdef __DOCHECK
            if ( p < aa || p > ss )
                throw std::logic_error("Position is invalid.");
#endif
        }

        position(const std::string& str) {
            if (str.size() != 2)
                throw std::logic_error("Position string is malformed.");
            int x = str[0] - 'a';
            int y = str[1] - 'a';
            if ( x < 0 || x > 19 || y < 0 || y > 19 )
                throw std::logic_error("Position string is malformed.");
            position_ =  x * 19 + y;
        }

        std::string alphabetical() {
            std::string p(2, '\0');
            p[0] = position_ / 19 + 'a';
            p[1] = position_ % 19 + 'a';
            return p;
        }
    };

} /* amigo */

#endif
