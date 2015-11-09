//
//  Sonifier.hpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 23/10/15.
//  Copyright 2015 Chris Sattinger
//

#ifndef Sonifier_hpp
#define Sonifier_hpp

#include <stdio.h>
#include <string>
#include "SuperCollider.hpp"
#include "ScatterPlots.hpp"
#include "PointsEvent.hpp"


class Sonifier {
 public:
    explicit Sonifier(ScatterPlots* scatterPlots, SuperCollider* superCollider)
        : scatterPlots(scatterPlots), superCollider(superCollider)
        {
            setup();
        }
    void pointsEntered(PointsEvent &event);
    void sonifyPoint(ofPoint const &point);
    void selectSynthDef(int ix);
    string sound();
    double freqBase{400};
    double sustain{0.1};
    double amp{0.2};

    SynthDef synthDef;

 private:
    void setup();
    ScatterPlots* scatterPlots;
    SuperCollider* superCollider;
};

#endif /* Sonifier_hpp */
