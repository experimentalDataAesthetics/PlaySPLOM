//
//  Brush.hpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 15/10/15.
//  Copyright 2015 Chris Sattinger
//
//

#ifndef Brush_hpp
#define Brush_hpp

#include <set>
#include "ofMain.h"
#include "BoxCoordinates.hpp"

// forward declaration
class ScatterPlots;


class Brush {
 public:
    explicit Brush(ScatterPlots* scatterPlots) : scatterPlots(scatterPlots) {}
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);

    void draw();
    set<int> pointsInRect(const ofRectangle& rect);

    // ratio of point size
    double brushWidth{4};
    double brushHeight{4};

    bool engaged{false};
    ofPoint hoverCenter{0, 0};
    set<int> pointsUnderBrush{};

    BoxCoordinates hoveringBox{};
    BoxCoordinates focusedBox{};

    // events
    ofEvent<BoxCoordinates> boxHoverEvent;
    ofEvent<BoxCoordinates> boxFocusEvent;
    ofEvent<int> pointEnteringEvent;
    ofEvent<int> pointExitingEvent;
    ofEvent<ofPoint> mouseMoveEvent;
    ofEvent<ofPoint> brushMoveEvent;

 private:
    BoxCoordinates boxForPoint(int x, int y);
    void brushMoved(int x, int y);

    ScatterPlots* scatterPlots;
    ofRectangle brushRect{-1, -1, 0, 0};
};

#endif /* Brush_hpp */
