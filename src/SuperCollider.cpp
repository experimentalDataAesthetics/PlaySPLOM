//
//  SuperCollider.cpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 22/10/15.
//  Copyright 2015 Chris Sattinger
//

#include "SuperCollider.hpp"
#include <stdlib.h>
#include <Poco/JSON/JSON.h>
#include <Poco/Pipe.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Array.h>
#include <Poco/Dynamic/Var.h>
#include <string>
#include <vector>
#include <iostream>
#include "boost/filesystem.hpp"
#include "ofMain.h"

using boost::filesystem::path;
using boost::filesystem::current_path;
using Poco::Process;
using Poco::ProcessHandle;
using Poco::JSON::Object;
using Poco::DynamicStruct;
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
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var parsed = parser.parse(file);
        Poco::Dynamic::Var result = parser.result();
        file.close();

        Poco::DynamicStruct jsonStruct =
          *result.extract<Object::Ptr>();
        for (Object::ConstIterator itr = jsonStruct.begin(), end = jsonStruct.end(); itr != end; ++itr) {
            SynthDef synthDef;
            synthDef.name = itr->first;
            auto defData = itr->second;
            if (defData.isStruct()) {
                DynamicStruct defStruct = jsonStruct[itr->first].extract<DynamicStruct>();
                for (auto defPair : defStruct) {
                    auto key = defPair.first;
                    cout << key << endl;
                    if (key == "controlNames") {
                        auto lst = defPair.second;
                        if (lst.isVector()) {
                            for (auto controlName : lst) {
                                synthDef.controls.push_back(controlName.toString());
                            }
                        }
                    }
                }
            }
            cout << synthDef.name << endl;
            synthDefs.push_back(synthDef);
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



