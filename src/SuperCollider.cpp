//
//  SuperCollider.cpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 22/10/15.
//
//

#include "SuperCollider.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <Poco/Pipe.h>
#include "boost/filesystem.hpp"
#include "ofMain.h"

using Poco::Process;
using Poco::ProcessHandle;
using boost::filesystem::current_path;
using std::string;
using std::vector;
using std::cout;
using std::endl;


void SuperCollider::setup() {
    // const string command = ofToDataPath("data/supercollider/scsynth");
    // cout << command << endl;
    // cout << current_path() << endl;
    const string command = "data/supercollider/scsynth";

    vector<string> args;
    args.push_back("-u");
    args.push_back("54321");
    Poco::Pipe outPipe, errorPipe;

    ProcessHandle ph = Process::launch(command, args, 0, &outPipe, &errorPipe);
    pid = ph.id();
    auto isRunning = Process::isRunning(pid);
    cout << "scsynth pid: " << pid << " running: " << isRunning <<endl;
    // should report dead
}


void SuperCollider::teardown() {
    if (pid) {
        Process::requestTermination(pid);
        pid = -1;
    }
}
