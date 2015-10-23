//
//  Sonifier.hpp
//  PlaySPLOM
//
//  Created by Chris Sattinger on 23/10/15.
//
//

#ifndef Sonifier_hpp
#define Sonifier_hpp

#include <stdio.h>
#include "SuperCollider.hpp"
#include "Brush.hpp"
#include "PointsEvent.hpp"


class Sonifier {
 public:
    explicit Sonifier(Brush* brush, SuperCollider* superCollider)
        : brush(brush), superCollider(superCollider)
        {
            setup();
        }
    void pointsEntered(PointsEvent &event);
 private:
    void setup();
    Brush* brush;
    SuperCollider* superCollider;
};

#endif /* Sonifier_hpp */
