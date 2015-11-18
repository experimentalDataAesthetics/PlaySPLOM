//
//  Brush.hpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 15/10/15.
//  Copyright 2015 Chris Sattinger
//

#ifndef Brush_hpp
#define Brush_hpp

#include <set>
#include "ofMain.h"
#include "BoxCoordinates.hpp"

// forward declaration
class ScatterPlots;

using PointIndexSet = set<int>;

class Brush {
 public:
    explicit Brush(ScatterPlots* scatterPlots)
        : scatterPlots(scatterPlots) { }
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);

    void draw();
    PointIndexSet pointsInRect(const ofRectangle& rect);

    // ratio of point size
    int brushWidth{4};
    int brushHeight{4};

    bool engaged{false};
    ofPoint hoverCenter{0, 0};
    PointIndexSet pointsUnderBrush{};

    BoxCoordinates hoveringBox{};
    BoxCoordinates focusedBox{};

    // events
    ofEvent<BoxCoordinates> boxHoverEvent;
    ofEvent<BoxCoordinates> boxFocusEvent;
    ofEvent<ofPoint> mouseMoveEvent;
    ofEvent<ofPoint> brushMoveEvent;

 private:
    void brushMoved(int x, int y, bool notify);
    void setFocusedBox(int x, int y);
    
    ScatterPlots* scatterPlots;
    ofRectangle brushRect{-1, -1, 0, 0};
};

#endif /* Brush_hpp */
