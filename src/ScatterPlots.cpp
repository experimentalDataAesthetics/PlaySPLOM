//
//  ScatterPlots.cpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 12/10/15.
//  Copyright 2015 Chris Sattinger
//
//

#include "ScatterPlots.hpp"
#include <vector>
#include <set>
#include "ofMain.h"
#include "mapping.h"


void ScatterPlots::draw() {
    // outer border
    ofPushStyle();
    ofSetColor(borderColor);
    ofNoFill();
    ofDrawRectangle(frame.x, frame.y, frame.width, frame.height);
    ofPopStyle();

    // auto&& access by reference
    for (auto &box : boxes) {
        // border
        ofPushStyle();
        ofSetColor(borderColor);
        ofNoFill();
        ofDrawRectangle(box.frame);
        ofPopStyle();

        ofSetColor(pointColor);
        ofPushMatrix(); {
            ofTranslate(box.frame.x, box.frame.y);
            for (auto &point : box.points) {
                ofDrawCircle(
                  point.x * boxWidth,
                  point.y * boxHeight,
                  pointRadius);
            }
        } ofPopMatrix();
    }

    // hovering box
    // focused box
    // hovering/playing color on top of activated points

    brush.draw();
    highlightPoints(brush.pointsUnderBrush, hoverPointColor);
}


void ScatterPlots::highlightPoints(const set<int> &points, const ofColor &color) {
    ofSetColor(color);
    for (auto &box : boxes) {
        ofPushMatrix(); {
            ofTranslate(box.frame.x, box.frame.y);
            for (auto p : points) {
                ofDrawCircle(
                  box.points[p].x * boxWidth,
                  box.points[p].y * boxHeight,
                  pointRadius);
            }
        } ofPopMatrix();
    }
}


void ScatterPlots::setFrame(ofRectangle rect) {
    frame = rect;
    updateBoxSizes();
}

void ScatterPlots::updateBoxSizes() {
    if (numDimensions > 0) {
        boxWidth = frame.width / numDimensions;
        boxHeight = frame.height / numDimensions;
    } else {
        boxWidth = frame.width;
        boxHeight = frame.height;
    }
    for (auto &box : boxes) {
        box.frame.x = box.m * boxWidth;
        box.frame.y = box.n * boxHeight;
        box.frame.width = boxWidth;
        box.frame.height = boxHeight;
    }
}

void ScatterPlots::setData(const DataSource& dataSource) {
    numDimensions = dataSource.numDimensions;
    boxes.clear();

    // create boxes with normalized point sets
    for (int m = 0; m < numDimensions; m++) {
        for (int n = 0; n < numDimensions; n++) {
            Box box = Box(m, n);
            for (auto point : dataSource.points) {
                auto x = linlin(point[m],
                  dataSource.mins[m],
                  dataSource.maxes[m]);
                auto y = linlin(point[n],
                  dataSource.mins[n],
                  dataSource.maxes[n]);
                ofPoint normalizedPoint = ofPoint(x, y);
                box.points.push_back(normalizedPoint);
            }
            boxes.push_back(box);
        }
    }
    updateBoxSizes();
}

ofRectangle ScatterPlots::boxFrameAt(const BoxCoordinates &coords) {
    for (auto box : boxes) {
        if (box.m == coords.m && box.n == coords.n) {
            return box.frame;
        }
    }
    return ofRectangle();
}

vector<ofPoint> ScatterPlots::normalizedPointsAtBox(const BoxCoordinates &coords) {
    for (auto box : boxes) {
        if (box.m == coords.m && box.n == coords.n) {
            return box.points;
        }
    }
    // empty set
    return vector<ofPoint>();
}
