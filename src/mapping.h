//
//  mapping.h
//  PlaySPLOM
//
//  Created by Chris Sattinger on 14/10/15.
//  Copyright 2015 Chris Sattinger
//
//

#ifndef SRC_MAPPING_H_
#define SRC_MAPPING_H_


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


double linlin(double value, double inMin, double inMax) {
    return linlin(value, inMin, inMax, 0.0, 1.0);
}


#endif  // SRC_MAPPING_H_
