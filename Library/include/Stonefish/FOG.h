//
//  FOG.h
//  Stonefish
//
//  Created by Patryk Cieslak on 02/11/2017.
//  Copyright (c) 2017 Patryk Cieslak. All rights reserved.
//

#ifndef __Stonefish_FOG__
#define __Stonefish_FOG__

#include "SimpleSensor.h"
#include "SolidEntity.h"

class FOG : public SimpleSensor
{
public:
    FOG(std::string uniqueName, SolidEntity* attachment, const btTransform& geomToSensor, btScalar frequency = btScalar(-1.), unsigned int historyLength = 0);
    
    void InternalUpdate(btScalar dt);
    
private:
    SolidEntity* attach;
    btTransform g2s;
};

#endif