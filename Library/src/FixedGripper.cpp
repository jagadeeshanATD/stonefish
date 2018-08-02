//
//  FixedGripper.cpp
//  Stonefish
//
//  Created by Patryk Cieslak on 17/05/17.
//  Copyright(c) 2017 Patryk Cieslak. All rights reserved.
//

#include "FixedGripper.h"
#include "SimulationApp.h"

FixedGripper::FixedGripper(std::string uniqueName, Manipulator* m, SolidEntity* hand) : Gripper(uniqueName, m)
{
    mechanism = new FeatherstoneEntity(uniqueName + "/FE", 1, hand, SimulationApp::getApp()->getSimulationManager()->getDynamicsWorld(), false);
}

void FixedGripper::SetState(btScalar openFraction)
{
    //Nothing to be done
}