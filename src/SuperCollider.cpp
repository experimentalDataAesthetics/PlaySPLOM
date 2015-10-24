//
//  SuperCollider.cpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 22/10/15.
//  Copyright 2015 Chris Sattinger
//

#include "SuperCollider.hpp"
#include <stdlib.h>
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
    args.push_back(std::to_string(PORT));

    // do not register with rendezvous
    args.push_back("-R");
    args.push_back("0");

    // load defs
    args.push_back("-D");
    args.push_back("1");

    auto path = current_path();
    // TODO(crucialfelix): unix only, find a boost util
    path += "/data/supercollider/synthdefs";
    const string synthDefEnvName = "SC_SYNTHDEF_PATH";
    setenv("SC_SYNTHDEF_PATH", path.c_str(), 1);

    ProcessHandle ph = Process::launch(command, args);
    pid = ph.id();
    auto isRunning = Process::isRunning(pid);
    cout << "scsynth pid: " << pid << " running: " << isRunning << endl;
    // should check sometimes and report if dead
    // TODO(crucialfelix): pipe server to stdout/stderr

    sender.setup(HOST, PORT);
}


void SuperCollider::teardown() {
    if (pid) {
        Process::requestTermination(pid);
        pid = -1;
    }
}