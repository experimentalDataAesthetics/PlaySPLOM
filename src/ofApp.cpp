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
    controls.loadButton = gui->addButton("Click to load dataset");
    controls.selectSound = gui->addDropdown("Sound", superCollider.defNames());
    controls.pointRadius = gui->addSlider("Point radius", 1, 6, 2);
    controls.brushWidth = gui->addSlider("Brush Width", 1, 15, 4);
    controls.brushHeight = gui->addSlider("Brush Height", 1, 15, 4);
    // gui->addColorPicker("Brush Color", engagedPointColor);
    gui->addFRM(1.0f);

    gui->onButtonEvent(this, &ofApp::onOfxDatGuiButtonEvent);
    gui->onSliderEvent(this, &ofApp::onOfxDatGuiSliderEvent);
    gui->onDropdownEvent(this, &ofApp::onOfxDatGuiDropdownEvent);
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
    const double panelWidth = 310;
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
    controls.loadButton->setLabel(dataSource.title);
}


void ofApp::onOfxDatGuiButtonEvent(ofxDatGuiButtonEvent e) {
    if (e.target == controls.loadButton) {
        // initial load file dialog
    }
}

void ofApp::onOfxDatGuiDropdownEvent(ofxDatGuiDropdownEvent e) {
    if (e.target == controls.selectSound) {
        sonifier.selectSynthDef(e.child);
    }
}

void ofApp::onOfxDatGuiSliderEvent(ofxDatGuiSliderEvent e) {
    if (e.target == controls.brushHeight) {
        scatterPlots.brush.brushHeight = e.value;
    } else if (e.target == controls.brushWidth) {
        scatterPlots.brush.brushWidth = e.value;
    } else if (e.target == controls.pointRadius) {
        scatterPlots.pointRadius = e.value;
        scatterPlots.redrawPlotter();
    }
}
