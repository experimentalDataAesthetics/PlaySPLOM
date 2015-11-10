//
//  BoxCoordinates.hpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 15/10/15.
//  Copyright 2015 Chris Sattinger
//


#ifndef BoxCoordinates_hpp
#define BoxCoordinates_hpp

#include <ostream>

class BoxCoordinates {
 public:
    BoxCoordinates(int m, int n) : m(m), n(n) {}
    BoxCoordinates() : BoxCoordinates(-1, -1) {}

    void setNull() {
        m = -1;
        n = -1;
    }
    bool isNull() const {
        return m == -1;
    }
    bool isIdentityBox() const {
        return m == n && (m != -1);
    }
    bool equals(const BoxCoordinates& that) {
        return m == that.m && n == that.n;
    }
    // friend bool &operator==(
    //  const BoxCoordinates& a,
    //  const BoxCoordinates& b) {
    //    return a.m == b.m && a.n == b.n;
    // }
    friend std::ostream &operator<<(std::ostream &os, BoxCoordinates const &m) {
        if (m.isNull()) {
            return os << "NULL";
        }
        return os << m.m << "@" << m.n << "{" << &m << "}";
    }

    int m;
    int n;
};

// not working invalid argument BoxCoordinates
// static bool operator==(const BoxCoordinates& a, const BoxCoordinates& b) {
//    return a.m == b.m && a.n == b.n;
// }

#endif /* BoxCoordinates_hpp */
