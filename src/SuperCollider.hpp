//
//  SuperCollider.hpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 22/10/15.
//
//

#ifndef SuperCollider_hpp
#define SuperCollider_hpp

#include <stdio.h>
#include <Poco/Process.h>
#include "ofxOsc.h"

#define PORT 54312
#define HOST "localhost"



class SuperCollider {
 public:
    SuperCollider() {
        setup();
    }
    ~SuperCollider() {
        teardown();
    }
    
 private:
    void setup();
    void teardown();
    Poco::ProcessHandle::PID pid;
    ofxOscSender sender;
};

#endif /* SuperCollider_hpp */
