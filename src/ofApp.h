// Copyright 2015 Chris Sattinger
#pragma once

#ifndef SRC_OFAPP_H_
#define SRC_OFAPP_H_

#include "ofMain.h"
#include "ofxDatGui.h"
#include "DataSource.hpp"
#include "ScatterPlots.hpp"
#include "SuperCollider.hpp"
#include "Sonifier.hpp"


class ofApp : public ofBaseApp {
 public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void dataSourceDidLoad();

 private:
    void setupGui();
    
    DataSource dataSource{};
    ScatterPlots scatterPlots{};
    SuperCollider superCollider;
    Sonifier sonifier{&scatterPlots, &superCollider};
    ofxDatGui* gui;
};

#endif  // SRC_OFAPP_H_
