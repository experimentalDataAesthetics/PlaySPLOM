//
//  Sonifier.cpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 23/10/15.
//  Copyright 2015 Chris Sattinger
//

#include <string>
#include "Sonifier.hpp"
#include "mapping.hpp"


void SynthDefMapping::init(SynthDef argSynthDef) {
    synthDef = argSynthDef;
    // guess default x y from synthDefs args
    for (auto control : synthDef.controls) {
        if (control.name == "out") {
            continue;
        }
        if (control.name == "amp") {
            continue;
        }
        if (control.name == "sustain") {
            continue;
        }
        if (control.name == "freq") {
            yArg = control.name;
            yMap = FREQ;
            continue;
        }
        if (xArg.empty()) {
            xArg = control.name;
            continue;
        }
        if (yArg.empty()) {
            yArg = control.name;
            continue;
        }
    }
    if (xArg.empty()) {
        xArg = "pan";
    }
    if (yArg.empty()) {
        yArg = "sustain";
    }
}

double SynthDefMapping::map(double v, double freqBase, string const &argName, MappingAlgo algo) {
    auto spec = synthDef.specAt(argName);
    switch (algo) {
        case FREQ:
            return expMul(freqBase, v);
            break;
        case EXP:
            // temp
            return expMul(freqBase, v);
            break;
        case LINEAR:
        default:
            return linlin(v, spec.minval, spec.maxval);
            break;
    }
}


void Sonifier::setup() {
    ofAddListener(PointsEvent::events, this, &Sonifier::pointsEntered);
}

void Sonifier::pointsEntered(PointsEvent &event) {
    if (event.type == PointsEventType::entering) {
        auto normalizedPoints = scatterPlots->normalizedPointsAtBox(event.coords);
        for (auto p : event.points) {
            std::cout << event.coords.m << "@" << event.coords.n << "::" << p << std::endl;
            sonifyPoint(normalizedPoints.at(p));
        }
    }
}

/**
  * sonify a normalized point with .x and .y
  * using current sound settings
  */
void Sonifier::sonifyPoint(ofPoint const &point) {
    SynthArgs args;
    args["out"] = 0;
    // was 0.1 or scaled to num points sounding
    args["amp"] = amp;
    // slider sustain
    args["sustain"] = sustain;

    SynthDefMapping mapping = mappings[synthDef.name];
    args[mapping.xArg] = mapping.map(point.x, freqBase, mapping.xArg, mapping.xMap);
    args[mapping.yArg] = mapping.map(point.y, freqBase, mapping.yArg, mapping.yMap);

    std::cout << synthDef.name << endl;
    superCollider->grain(synthDef.name, args);
}

void Sonifier::selectSynthDef(int i) {
    if (i < superCollider->synthDefs.size()) {
        synthDef = superCollider->synthDefs[i];
        if (mappings.count(synthDef.name) == 0) {
            SynthDefMapping sdm = SynthDefMapping();
            sdm.init(synthDef);
            mappings[synthDef.name] = sdm;
        }
    }
}


string Sonifier::sound() {
    return synthDef.name;
}
