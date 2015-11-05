//
//  Sonifier.hpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 23/10/15.
//
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
    void selectSynthDef(int ix);
    string sound();

    SynthDef synthDef;

 private:
    void setup();
    ScatterPlots* scatterPlots;
    SuperCollider* superCollider;
};

#endif /* Sonifier_hpp */
