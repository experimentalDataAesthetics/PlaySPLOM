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
#include "mapping.hpp"


void ScatterPlots::draw() {
    // always set color to white before drawing an FBO to main
    ofSetColor(255, 255, 255);
    plotterFbo.draw(0, 0);

    ofPushMatrix();
    // unflip opengl so that origin is bottom left, going up
    glTranslated(0, plotterFbo.getHeight(), 0);
    glScalef(1, -1, 1);
    {
        // hovering box
        // focused box
        // hovering/playing color on top of activated points
        brush.draw();
        highlightPoints(brush.pointsUnderBrush, hoverPointColor);
    }
    ofPopMatrix();
}

void ScatterPlots::redrawPlotter() {
    plotterFbo.begin();
    ofClear(plotterBackground.r, plotterBackground.b, plotterBackground.g, plotterBackground.a);

    ofPushMatrix();
    ofPushStyle();
    {
        // unflip opengl so that origin is bottom left, going up
        glTranslated(0, plotterFbo.getHeight(), 0);
        glScalef(1, -1, 1);

        // outer border
        ofSetColor(borderColor);
        ofNoFill();
        ofDrawRectangle(frame.x, frame.y, frame.width, frame.height);

        ofSetCircleResolution(8);
        // auto&& access by reference
        for (auto &box : boxes) {
            // border
            ofSetColor(borderColor);
            ofNoFill();
            ofDrawRectangle(box.frame);

            ofSetColor(pointColor);
            ofFill();
            ofPushMatrix(); {
                ofTranslate(box.frame.x, box.frame.y);
                for (auto &point : box.points) {
                    ofDrawCircle(
                                 point.x * box.frame.width,
                                 point.y * box.frame.height,
                                 pointRadius);
                }
                char label[20];
                snprintf(label, sizeof(label), "%d,%d", box.m, box.n);
                ofSetColor(labelColor);
                ofDrawBitmapString(label, gutter, gutter);
            } ofPopMatrix();
        }
    }
    ofPopStyle();
    ofPopMatrix();
    plotterFbo.end();
}

void ScatterPlots::highlightPoints(const set<int> &points, const ofColor &color) {
    ofSetColor(color);
    for (auto &box : boxes) {
        ofPushMatrix(); {
            ofTranslate(box.frame.x, box.frame.y);
            for (auto p : points) {
                ofDrawCircle(
                  box.points[p].x * box.frame.width,
                  box.points[p].y * box.frame.height,
                  pointRadius);
            }
        } ofPopMatrix();
    }
}


void ScatterPlots::setFrame(ofRectangle rect) {
    frame = rect;
    updateBoxSizes();
    if (plotterFbo.isAllocated()) {
        plotterFbo.clear();
    }
    plotterFbo.allocate(rect.width, rect.height, GL_RGBA);  // 32F_ARB
    redrawPlotter();
}

void ScatterPlots::updateBoxSizes() {
    if (numDimensions > 0) {
        boxWidth = (frame.width - gutter) / numDimensions;
        boxHeight = (frame.height - gutter) / numDimensions;
    } else {
        boxWidth = frame.width - gutter;
        boxHeight = frame.height - gutter;
    }
    if (boxWidth < boxHeight) {
        boxHeight = boxWidth;
    } else {
        boxWidth = boxHeight;
    }
    // center them
    leftMargin = (frame.width -  (boxWidth * numDimensions)) / 2;
    for (auto &box : boxes) {
        box.frame.x = box.m * boxWidth + gutter + leftMargin;
        box.frame.y = box.n * boxHeight + gutter;
        box.frame.width = boxWidth - gutter;
        box.frame.height = boxHeight - gutter;
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
    redrawPlotter();
}

BoxCoordinates ScatterPlots::boxForPoint(int x, int y) {
    const int m = (x - leftMargin) / boxWidth;
    const int n = y / boxHeight;
    return BoxCoordinates(m, n);
}

ofRectangle ScatterPlots::boxFrameAt(const BoxCoordinates &coords) {
    // TODO(crucialfelix): use a map
    for (auto box : boxes) {
        if (box.m == coords.m && box.n == coords.n) {
            return box.frame;
        }
    }
    return ofRectangle();
}

vector<ofPoint> ScatterPlots::normalizedPointsAtBox(const BoxCoordinates &coords) {
    // TODO(crucialfelix): use a map
    for (auto box : boxes) {
        if (box.m == coords.m && box.n == coords.n) {
            return box.points;
        }
    }
    // empty set
    return vector<ofPoint>();
}
