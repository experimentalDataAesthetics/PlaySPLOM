//
//  PointsEvent.hpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 23/10/15.
//  Copyright 2015 Chris Sattinger
//

#pragma once
#ifndef PointsEvent_hpp
#define PointsEvent_hpp

#include "ofMain.h"
#include "BoxCoordinates.hpp"
#include "Brush.hpp"

enum class PointsEventType {
  entering,
  exiting,
  mouseOver,
  mouseOut,
  click
};


class PointsEvent : public ofEventArgs {
 public:
   explicit PointsEvent(PointsEventType type,
                         BoxCoordinates &coords,
                         PointIndexSet &points)
                          : type(type),
                            coords(coords),
                            points(points)
                          { }

    PointsEventType type;
    BoxCoordinates coords;
    PointIndexSet points;

    static ofEvent <PointsEvent> events;
};

#endif /* PointsEvent_hpp */
