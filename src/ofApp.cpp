// Copyright 2015 Chris Sattinger
#include "ofApp.h"
#include "ofMain.h"
#include <stdio.h>
#include "style.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetVerticalSync(true);
    ofSetFrameRate(60);

    ofAddListener(dataSource.didLoadEvent, this, &ofApp::dataSourceDidLoad);

    windowResized(ofGetWidth(), ofGetHeight());

    setupGui();
}

void ofApp::setupGui() {
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    gui->addFRM(1.0f);
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(settingsBackground);
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
    scatterPlots.brush.mouseMoved(x, ofGetHeight() - y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    scatterPlots.brush.mouseDragged(x, ofGetHeight() - y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    scatterPlots.brush.mousePressed(x, ofGetHeight() - y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    scatterPlots.brush.mouseReleased(x, ofGetHeight() - y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    const double panelWidth = 220;
    auto rect = ofRectangle(0, 0, w - panelWidth - gutter - gutter, h);
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
