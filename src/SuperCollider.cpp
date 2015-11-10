//
//  SuperCollider.cpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 22/10/15.
//  Copyright 2015 Chris Sattinger
//

#include "SuperCollider.hpp"
#include <stdlib.h>
#include <json/json.h>
#include <Poco/Pipe.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "boost/filesystem.hpp"
#include "ofMain.h"

using boost::filesystem::path;
using boost::filesystem::current_path;
using Poco::Process;
using Poco::ProcessHandle;
using std::string;
using std::vector;
using std::cout;
using std::endl;


void SuperCollider::setup() {
    // boost converts paths for windows
    auto command = path("data/supercollider/scsynth");

    auto sdpath = current_path();
    sdpath /= "data/supercollider/synthdefs";
    synthDefPath = sdpath.string();

    vector<string> args;
    args.push_back("-u");
    args.push_back(std::to_string(PORT));

    // do not register with rendezvous
    args.push_back("-R");
    args.push_back("0");

    // load defs
    setenv("SC_SYNTHDEF_PATH", synthDefPath.c_str(), 1);
    args.push_back("-D");
    args.push_back("1");

    ProcessHandle ph = Process::launch(command.c_str(), args);
    pid = ph.id();
    auto isRunning = Process::isRunning(pid);
    cout << "scsynth pid: " << pid << " running: " << isRunning << endl;
    // should check sometimes and report if dead

    sender.setup(HOST, PORT);
    loadSynthDefs();
}


void SuperCollider::teardown() {
    if (pid) {
        Process::requestTermination(pid);
        pid = -1;
    }
}


void SuperCollider::loadSynthDefs() {
    auto synthDefsJsonPath = path(synthDefPath) /= "synthDefs.json";
    if (!exists(synthDefsJsonPath)) {
        return;
    }
    std::ifstream file(synthDefsJsonPath.string());
    if (file) {
        Json::Value root;
        Json::Reader reader;
        bool ok = reader.parse(file, root, false);
        file.close();
        if (!ok) {
            std::cout  << reader.getFormatedErrorMessages() << endl;
            return;
        }

        for (auto sdj : root) {
            SynthDef synthDef;
            synthDef.name = sdj["name"].asString();
            cout << synthDef.name << endl;

            for (auto cj : sdj["controls"]) {
                Control control;
                control.name = cj["name"].asString();
                control.defaultValue = cj["defaultValue"].asFloat();
                auto sj = cj["spec"];
                if (!sj.isNull()) {
                    control.spec.minval = sj["minval"].asFloat();
                    control.spec.maxval = sj["maxval"].asFloat();
                }
                synthDef.controls.push_back(control);
            }
            synthDef.canFreeSynth = sdj["canFreeSynth"].asBool();

            if (synthDef.canFreeSynth) {
                synthDefs.push_back(synthDef);
            }
        }
    }
}



/**
  * Spawn a sound grain in root group
  */
void SuperCollider::grain(const string &defName, SynthArgs args) {
    if (!pid) {
        return;
    }
    ofxOscMessage msg;
    msg.setAddress("/s_new");
    msg.addStringArg(defName);
    msg.addIntArg(-1);
    msg.addIntArg(0);
    msg.addIntArg(0);
    for (auto kv : args) {
        msg.addStringArg(kv.first);
        msg.addFloatArg(kv.second);
        cout << kv.first << " = " << kv.second << endl;
    }
    sender.sendMessage(msg);
}


vector<string> SuperCollider::defNames() {
    vector<string> names;
    for (auto sd : synthDefs) {
        names.push_back(sd.name);
    }
    return names;
}


