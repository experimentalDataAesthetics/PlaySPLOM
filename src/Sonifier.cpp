//
//  Sonifier.cpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 23/10/15.
//
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
            auto normPoint = normalizedPoints.at(p);
            SynthArgs args;
            args["out"] = 0;
            args["amp"] = 0.1;
            args["freq"] = linlin(normPoint.y, 0.0, 1.0, 30, 5000);
            args["sustain"] = 0.01;
            args["pan"] = linlin(normPoint.x, -1, 1);
            superCollider->grain("grain", args);
        }
    }
}


void Sonifier::selectSynthDef(int i) {
    if (i < superCollider->synthDefs.size()) {
        synthDef = superCollider->synthDefs[i];
    }
}

string Sonifier::sound() {
    return synthDef.name;
}

