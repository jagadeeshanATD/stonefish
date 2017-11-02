//
//  Pressure.cpp
//  Stonefish
//
//  Created by Patryk Cieslak on 02/11/2017.
//  Copyright (c) 2017 Patryk Cieslak. All rights reserved.
//

#include "Pressure.h"
#include "SimulationApp.h"

Pressure::Pressure(std::string uniqueName, SolidEntity* attachment, const btTransform& geomToSensor, btScalar frequency, unsigned int historyLength) : SimpleSensor(uniqueName, frequency, historyLength)
{
    attach = attachment;
    g2s = UnitSystem::SetTransform(geomToSensor);
    channels.push_back(SensorChannel("Pressure", QUANTITY_PRESSURE));
}

void Pressure::InternalUpdate(btScalar dt)
{
    btTransform pressureTrans = attach->getTransform() * attach->getGeomToCOGTransform().inverse() * g2s;
    btScalar data(101325.); //Pa (1 atm)
    
    Liquid* liq = SimulationApp::getApp()->getSimulationManager()->getLiquid();
    if(liq != NULL)
        data += liq->GetPressure(pressureTrans.getOrigin());
    
    //Record sample
    Sample s(1, &data);
    AddSampleToHistory(s);
}