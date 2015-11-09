//
//  Sonifier.cpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 23/10/15.
//  Copyright 2015 Chris Sattinger
//

#include "Sonifier.hpp"
#include "mapping.hpp"


void Sonifier::setup() {
    ofAddListener(PointsEvent::events, this, &Sonifier::pointsEntered);
}

void Sonifier::pointsEntered(PointsEvent &event) {
    if (event.type == PointsEventType::entering) {
        // convert to args for a grain
        // |out, amp=0.1, freq=440, sustain=0.01, pan|
        auto normalizedPoints = scatterPlots->normalizedPointsAtBox(event.coords);
        for (auto p : event.points) {
            std::cout << event.coords.m << "@" << event.coords.n << "::" << p << std::endl;
            sonifyPoint(normalizedPoints.at(p));
        }
    }
}

/** 
  * sonfiy a normalized point with .x and .y
  * using current sound settings
  */
void Sonifier::sonifyPoint(ofPoint const &point) {
    // using current mode
    SynthArgs args;
    args["out"] = 0;
    // was 0.1 or scaled to num points sounding
    args["amp"] = amp;

    // slider freqBase
    // freqB*pow(2., yy)
    // you could change freqB with keystrokes
    args["freq"] = expMul(freqBase, point.y);

    // slider sustain
    args["sustain"] = sustain;

    // was a slider -1 .. 1
    args["pan"] = linlin(point.x, -1, 1);

    std::cout << synthDef.name << endl;
    superCollider->grain(synthDef.name, args);
}

void Sonifier::selectSynthDef(int i) {
    if (i < superCollider->synthDefs.size()) {
        synthDef = superCollider->synthDefs[i];
    }
}

string Sonifier::sound() {
    return synthDef.name;
}

