//
//  mapping.cpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 23/10/15.
//
//

#include "mapping.hpp"
#include <stdio.h>

double linlin(double value,
              double inMin,
              double inMax,
              double outMin,
              double outMax) {
    if (inMin == inMax) {
        return (outMin + outMax) / 2;
    }
    if (outMin == outMax) {
        return outMin;
    }
    return (value - inMin) / (inMax - inMin) * (outMax - outMin) + outMin;
}


// normalize
double linlin(double value, double inMin, double inMax) {
    return linlin(value, inMin, inMax, 0.0, 1.0);
}