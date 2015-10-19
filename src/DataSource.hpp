//
//  DataSource.hpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 12/10/15.
//  Copyright 2015 Chris Sattinger
//
//

#ifndef DataSource_hpp
#define DataSource_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "ofMain.h"

using DataPoint = std::vector<double>;


class DataSource {
 public:
    void load(const std::string& pathName);

    unsigned int numDimensions{0};
    std::vector<DataPoint> points{};
    std::vector<std::string> titles{};
    DataPoint mins;
    DataPoint maxes;
    ofEvent<void> didLoadEvent;

 private:
    void parseLine(const std::string& line);
};


#endif /* DataSource_hpp */
