//
//  DataSource.cpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 12/10/15.
//  Copyright 2015 Chris Sattinger
//

#include "DataSource.hpp"
#include <boost/filesystem.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>


// using std::cout;
// using std::endl;


void DataSource::load(const string& argPathName) {
    titles.clear();
    points.clear();
    mins.clear();
    maxes.clear();
    numDimensions = 0;

    boost::filesystem::path p(argPathName);
    pathName = p.string();
    title = p.filename().string();

    ifstream data(pathName);

    string line;
    // read first row
    if (getline(data, line)) {
        stringstream  lineStream(line);
        string        cell;
        // might be a list of field names
        if (isalpha(line[0])) {
            // titles
            while (getline(lineStream, cell, ',')) {
                titles.push_back(cell);
            }
            numDimensions = titles.size();
        } else {
            parseLine(line);
            numDimensions = points.at(0).size();
            // titles is an array of 0..numDimensions-1
            for (int i = 0; i < numDimensions; i++) {
                titles.push_back(std::to_string(i));
            }
        }
        while (getline(data, line)) {
            parseLine(line);
        }
    }

    data.close();
    ofNotifyEvent(didLoadEvent, this);
}


void DataSource::parseLine(const string& line) {
    stringstream  lineStream(line);
    string        cell;
    vector<double> point;

    while (getline(lineStream, cell, ',')) {
        auto value = atof(cell.c_str());
        // TODO(crucialfelix): handle NaN or category strings
        point.push_back(value);
    }

    // update min/max
    if (mins.size() == 0) {
        // assignment copies it
        mins = point;
        maxes = point;
    } else {
        int i = 0;
        for (auto value : point) {
            if (value < mins[i]) {
                mins[i] = value;
            }
            if (value > maxes[i]) {
                maxes[i] = value;
            }
            i++;
        }
    }

    points.push_back(point);
}
