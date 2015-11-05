//
//  SuperCollider.hpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 22/10/15.
//  Copyright 2015 Chris Sattinger
//

#ifndef SuperCollider_hpp
#define SuperCollider_hpp

#include <Poco/Process.h>
#include <Poco/Dynamic/Var.h>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include "ofxOsc.h"

#define PORT 54312
#define HOST "localhost"

using SynthArgs = map<string, double>;

struct SynthDef {
    string name;
    vector<string> controls;
};


class SuperCollider {
 public:
    SuperCollider() {
        setup();
    }
    ~SuperCollider() {
        teardown();
    }

    void grain(const string& defName, SynthArgs args);
    std::vector<string> defNames();

    std::vector<SynthDef> synthDefs;

 private:
    void setup();
    void teardown();
    void loadSynthDefs();

    Poco::ProcessHandle::PID pid;
    ofxOscSender sender;
    string synthDefPath;
};

#endif /* SuperCollider_hpp */
