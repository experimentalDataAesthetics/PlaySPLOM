// Copyright 2015 Chris Sattinger
#include "ofApp.h"
#include "ofMain.h"
#include <stdio.h>

//--------------------------------------------------------------
void ofApp::setup() {
    auto width = ofGetWidth();
    auto height = ofGetHeight();
    auto rect = ofRectangle(0, 0, width, height);
    scatterPlots.setFrame(rect);

    ofAddListener(dataSource.didLoadEvent, this, &ofApp::dataSourceDidLoad);
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
    scatterPlots.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    scatterPlots.brush.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    scatterPlots.brush.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    scatterPlots.brush.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    scatterPlots.brush.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    ofRectangle rect = ofRectangle(0, 0, w, h);
    scatterPlots.setFrame(rect);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    auto path = dragInfo.files.at(dragInfo.files.size() - 1);
    dataSource.load(path);
}

void ofApp::dataSourceDidLoad() {
    scatterPlots.setData(dataSource);
}
