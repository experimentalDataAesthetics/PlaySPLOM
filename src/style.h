//
//  style.h
//  PlaySPLOM
//
//  Created by Chris Sattinger on 15/10/15.
//  Copyright 2015 Chris Sattinger
//
//

#ifndef SRC_STYLE_H_
#define SRC_STYLE_H_

#include "ofMain.h"

const ofColor plotterBackground = ofColor(230);
const ofColor settingsBackground = ofColor(230);
const ofColor labelColor = ofColor(10);
const ofColor borderColor = ofColor(164, 164, 162);  // rgb(164, 164, 163)
const ofColor pointColor = ofColor(20, 160);
const ofColor hoverPointColor = ofColor(255, 0, 0, 120);
const ofColor hoverFrameColor = ofColor(0, 50, 250);
const ofColor hoverBrushColor = ofColor(255, 0, 0, 120);

const ofColor engagedPointColor = ofColor(255, 0, 0, 120);
const ofColor engagedFrameColor = ofColor(0, 0, 250);
const ofColor engagedBrushColor = ofColor(250, 0, 0, 120);

// the label/identity box background color when brush is engaged
const ofColor inverseBoxColor = ofColor(0, 20, 250, 40);
const ofColor inverseTextColor = ofColor(0);

const int gutter = 5;

#endif  // SRC_STYLE_H_
