//
//  Sonifier.cpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 23/10/15.
//
//

#include "Sonifier.hpp"
#include "SuperCollider.hpp"

void Sonifier::setup() {
    ofAddListener(PointsEvent::events, this, &Sonifier::pointsEntered);
}

void Sonifier::pointsEntered(PointsEvent &event) {
    if (event.type == PointsEventType::entering) {
        // BoxCoord PointsIndexSet
        // convert to args for a grain
        // |out, amp=0.1, freq=440, sustain=0.01, pan|
        // << event.points
        std::cout << event.coords.m << "@" << event.coords.n << std::endl;
    }
}
