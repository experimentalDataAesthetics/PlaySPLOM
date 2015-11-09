//
//  mapping.cpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 23/10/15.
//  Copyright 2015 Chris Sattinger
//

#include "mapping.hpp"
#include <stdio.h>
#include "math.h"


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


double expMul(double base, double value) {
    return base * pow(2.0, value);
}
