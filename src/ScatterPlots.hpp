//
//  ScatterPlots.hpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 12/10/15.
//  Copyright 2015 Chris Sattinger
//
//

#ifndef ScatterPlots_hpp
#define ScatterPlots_hpp

#include <stdio.h>
#include <vector>
#include <set>
#include "DataSource.hpp"
#include "Brush.hpp"
#include "BoxCoordinates.hpp"
#include "ofMain.h"
#include "style.h"


class ScatterPlots {
    friend class Brush;
 public:
    void setFrame(ofRectangle rect);
    void setData(const DataSource& dataSource);
    void draw();
    void highlightPoints(const set<int> &points, const ofColor &color);

    float pointRadius{2.0};
    Brush brush{this};

 private:
    struct Box {
        Box(int m, int n)
            : m(m),
              n(n)
            { }

        std::vector<ofPoint> points{};
        ofRectangle frame{0, 0, 0, 0};
        int m;
        int n;
        // TODO(crucialfelix): change to BoxCoordinates
        // BoxCoordinates coords;
    };

    void updateBoxSizes();
    ofRectangle boxFrameAt(const BoxCoordinates &coords);
    vector<ofPoint> normalizedPointsAtBox(const BoxCoordinates &coords);

    int numDimensions{0};
    float boxWidth{0};
    float boxHeight{0};
    ofRectangle frame{0, 0, 0, 0};
    std::vector<Box> boxes{};
};


#endif /* ScatterPlots_hpp */
