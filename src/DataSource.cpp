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


/** 
  * Fill a data set with evenly distributed points
  * in two dimensions for testing purposes.
  */
void DataSource::mock() {
    titles.clear();
    points.clear();
    mins.clear();
    maxes.clear();

    title = "Test Data";
    numDimensions = 2;
    titles.push_back("x");
    titles.push_back("y");
    mins.push_back(0);
    mins.push_back(0);
    maxes.push_back(1);
    maxes.push_back(1);
    const int numPoints = 40;
    for (auto x=0; x < numPoints; x++) {
        for (auto y=0; y < numPoints; y++) {
            vector<double> point;
            point.push_back(double(x) / double(numPoints));
            point.push_back(double(y) / double(numPoints));
            // cout << point[0] << "@" << point[1] << endl;
            points.push_back(point);
        }
    }
    ofNotifyEvent(didLoadEvent, this);
}

