//
//  SuperCollider.hpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 22/10/15.
//  Copyright 2015 Chris Sattinger
//

#ifndef SuperCollider_hpp
#define SuperCollider_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <Poco/Process.h>
#include "ofxOsc.h"

#define PORT 54312
#define HOST "localhost"

using SynthArgs = map<string, double>;


class SuperCollider {
 public:
    SuperCollider() {
        setup();
    }
    ~SuperCollider() {
        teardown();
    }
    void grain(const string& defName, SynthArgs args);

 private:
    void setup();
    void teardown();
    Poco::ProcessHandle::PID pid;
    ofxOscSender sender;
};

#endif /* SuperCollider_hpp */
