//
//  Brush.cpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 15/10/15.
//  Copyright 2015 Chris Sattinger
//

#include "Brush.hpp"
#include <stdio.h>
#include <string>
#include <set>
#include "ScatterPlots.hpp"
#include "./style.h"
#include "PointsEvent.hpp"
using std::cout;
using std::endl;


void debugBox(string label, const BoxCoordinates &box) {
    cout << label << "=" << box << endl;
}


//--------------------------------------------------------------
void Brush::draw() {
    ofFill();
    ofSetColor(engaged ? engagedBrushColor : hoverBrushColor);
    ofDrawRectangle(brushRect);
}

//--------------------------------------------------------------
void Brush::mouseMoved(int x, int y) {
    engaged = false;
    brushMoved(x, y, false);
}

void Brush::brushMoved(int x, int y, bool notify) {
    //    cout << x << "@" << y << endl;
    if (scatterPlots->frame.inside(x, y)) {
        hoverCenter.x = x;
        hoverCenter.y = y;

        BoxCoordinates nowHoveringBox = scatterPlots->boxForPoint(x, y);
        if (!nowHoveringBox.equals(hoveringBox)) {
            // cout << "new box" << endl;
            if (nowHoveringBox.isIdentityBox()) {
                hoveringBox.setNull();
            } else {
                hoveringBox = nowHoveringBox;
            }
            ofNotifyEvent(boxHoverEvent, hoveringBox, this);
        }

        // updateBrushRect
        auto diam = scatterPlots->pointRadius * 2;
        brushRect.setFromCenter(hoverCenter.x,
                                hoverCenter.y,
                                brushWidth * diam,
                                brushHeight * diam);
    } else {
        hoveringBox.setNull();
        brushRect.setFromCenter(-1, -1, 0, 0);
    }

    PointIndexSet currentPointsUnderBrush = pointsInRect(brushRect);
    // std::cout << "current" << currentPointsUnderBrush.size() << endl;

    PointIndexSet entering, exiting;
    for (auto p : currentPointsUnderBrush) {
        if (pointsUnderBrush.find(p) == pointsUnderBrush.end()) {
            entering.insert(p);
        }
    }
    for (auto p : pointsUnderBrush) {
        if (currentPointsUnderBrush.find(p) == currentPointsUnderBrush.end()) {
            exiting.insert(p);
        }
    }

    if (exiting.size() == pointsUnderBrush.size()) {
        pointsUnderBrush.clear();
    } else {
        for (auto p : exiting) {
            pointsUnderBrush.erase(p);
        }
    }
    for (auto p : entering) {
        pointsUnderBrush.insert(p);
    }
    if (notify) {
        BoxCoordinates box = focusedBox;
        if (focusedBox.isNull()) {
          box = hoveringBox;
        }
            PointsEvent event = PointsEvent(PointsEventType::entering, box, entering);
        if (entering.size()) {
            ofNotifyEvent(PointsEvent::events, event);
        }
        if (exiting.size()) {
            PointsEvent event = PointsEvent(PointsEventType::exiting, box, exiting);
            ofNotifyEvent(PointsEvent::events, event);
        }
    }
}

void Brush::setFocusedBox(int x, int y) {
    if (scatterPlots->frame.inside(x, y)) {
        hoverCenter.x = x;
        hoverCenter.y = y;

        BoxCoordinates box = scatterPlots->boxForPoint(x, y);
        if (!box.equals(focusedBox)) {
            // cout << "new box" << endl;
            focusedBox = box;
            ofNotifyEvent(boxFocusEvent, focusedBox, this);
        }
    } else {
        focusedBox.setNull();
    }
}

//--------------------------------------------------------------
void Brush::mouseDragged(int x, int y, int button) {
    engaged = true;
    brushMoved(x, y, true);
}

//--------------------------------------------------------------
void Brush::mousePressed(int x, int y, int button) {
    // cout << button << endl;
    if (button == 2) {
        setFocusedBox(x, y);
        return;
    }
    engaged = true;
    // all are entering now
    pointsUnderBrush.clear();
    brushMoved(x, y, true);
}

//--------------------------------------------------------------
void Brush::mouseReleased(int x, int y, int button) {
    engaged = false;
    brushMoved(x, y, true);
}

//--------------------------------------------------------------
void Brush::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void Brush::mouseExited(int x, int y) {}


PointIndexSet Brush::pointsInRect(const ofRectangle& rect) {
    // naive version. will optimize later
    // normalize the rect
    ofRectangle normalized = ofRectangle(rect);
    ofRectangle boxFrame = scatterPlots->boxFrameAt(hoveringBox);
    // iterate points, very slow
    PointIndexSet points;
    if (boxFrame.width > 0) {
        auto widthScale = 1 / boxFrame.width;
        auto heightScale = 1 / boxFrame.height;
        normalized.setPosition(
          (rect.x - boxFrame.x) * widthScale,
          (rect.y - boxFrame.y) * heightScale);
        // scale down by width -> 1
        normalized.scale(widthScale, heightScale);

        int i = 0;
        for (auto point : scatterPlots->normalizedPointsAtBox(hoveringBox)) {
            if (normalized.inside(point)) {
                points.insert(i);
            }
            i++;
        }
    }
    return points;
}
