
#pragma once

#include "ranged_char.hh"


class strict_rgb {
public:
    strict_rgb() {}
    strict_rgb(
        ranged_char r,
        ranged_char g,
        ranged_char b
    ) : r_(r), g_(g), b_(b) {}

    void set_r(ranged_char r) { r_ = r; }
    void set_g(ranged_char g) { g_ = g; }
    void set_b(ranged_char b) { b_ = b; }

    ranged_char r() { return r_; }
    ranged_char g() { return g_; }
    ranged_char b() { return b_; }

    bool is_valid() {
        return 
           r_.is_valid() and
           g_.is_valid() and
           b_.is_valid();
    }

private:
   ranged_char r_;
   ranged_char g_;
   ranged_char b_;
};

