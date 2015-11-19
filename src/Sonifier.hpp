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
#include <map>
#include "SuperCollider.hpp"
#include "ScatterPlots.hpp"
#include "PointsEvent.hpp"


enum MappingAlgo {
    LINEAR,
    EXP,
    FREQ
};


class SynthDefMapping {
 public:
    void init(SynthDef synthDef);
    double map(double v, double freqBase, string const &argName, MappingAlgo algo);

    SynthDef synthDef;
    string xArg;
    MappingAlgo xMap{LINEAR};
    string yArg;
    MappingAlgo yMap{LINEAR};

    string xDescription();
    string yDescription();
};


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
    std::map<std::string, SynthDefMapping> mappings;

    ofEvent<void> synthDefSelectedEvent;

 private:
    void setup();
    ScatterPlots* scatterPlots;
    SuperCollider* superCollider;
};

#endif /* Sonifier_hpp */
