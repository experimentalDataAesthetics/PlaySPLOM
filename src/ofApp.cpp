// Copyright 2015 Chris Sattinger
#include "ofApp.h"
#include "ofMain.h"
#include <stdio.h>
#include "./style.h"



//--------------------------------------------------------------
void ofApp::setup() {
    ofSetVerticalSync(true);
    ofSetFrameRate(60);

    ofAddListener(dataSource.didLoadEvent, this, &ofApp::dataSourceDidLoad);

    windowResized(ofGetWidth(), ofGetHeight());

    if (sonifier.sound() == "") {
        if (superCollider.synthDefs.size() > 0) {
            sonifier.selectSynthDef(0);
        }
    }
    setupGui();
    dataSource.mock();
}

void ofApp::setupGui() {
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    controls.loadButton = gui->addButton("Click to load dataset");
    controls.selectSound = gui->addDropdown("Sound", superCollider.defNames());
    controls.selectSound->select(0);  // what is actual index of current sound ?
    controls.pointRadius = gui->addSlider("Point radius", 1, 6, scatterPlots.pointRadius);
    controls.brushWidth = gui->addSlider("Brush Width", 1, 15, scatterPlots.brush.brushWidth);
    controls.brushHeight = gui->addSlider("Brush Height", 1, 15, scatterPlots.brush.brushHeight);
    controls.amp = gui->addSlider("Amp", 0.0, 1.0, sonifier.amp);
    controls.sustain = gui->addSlider("Sustain", 0.005, 1.0, sonifier.sustain);
    controls.freqBase = gui->addSlider("Freq", 220, 3520, sonifier.freqBase);

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
    if (openLoadDialog) {
        // initial load file dialog
        ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a CSV dataset file");
        if (openFileResult.bSuccess) {
            dataSource.load(openFileResult.getPath());
        }
        openLoadDialog = false;
    }
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
        openLoadDialog = true;
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
    } else if (e.target == controls.amp) {
        sonifier.amp = e.value;
    } else if (e.target == controls.sustain) {
        sonifier.sustain = e.value;
    } else if (e.target == controls.freqBase) {
        sonifier.freqBase = e.value;
    }
}
