//
//  StaticEntity.cpp
//  Stonefish
//
//  Created by Patryk Cieslak on 24/05/2014.
//  Copyright (c) 2014 Patryk Cieslak. All rights reserved.
//

#include "StaticEntity.h"
#include "MathsUtil.hpp"

StaticEntity::StaticEntity(std::string uniqueName, Material m, int _lookId) : Entity(uniqueName)
{
    mat = m;
	objectId = -1;
    lookId = _lookId;
    wireframe = false;
	rigidBody = NULL;
    mesh = NULL;
}

StaticEntity::~StaticEntity()
{
    if(mesh != NULL)
        delete mesh;
    
    rigidBody = NULL;
}

EntityType StaticEntity::getType()
{
    return ENTITY_STATIC;
}

void StaticEntity::GetAABB(btVector3& min, btVector3& max)
{
	if(rigidBody != NULL)
		rigidBody->getAabb(min, max);
}

std::vector<Renderable> StaticEntity::Render()
{
	std::vector<Renderable> items(0);
	
    if(rigidBody != NULL && objectId >= 0 && isRenderable())
    {
		btTransform trans;
        rigidBody->getMotionState()->getWorldTransform(trans);
		
		Renderable item;
        item.type = RenderableType::SOLID;
		item.objectId = objectId;
		item.lookId = lookId;
		item.model = glMatrixFromBtTransform(trans);
		items.push_back(item);
    }
	
	return items;
}

Material StaticEntity::getMaterial()
{
    return mat;
}

void StaticEntity::BuildRigidBody(btCollisionShape* shape)
{
    btDefaultMotionState* motionState = new btDefaultMotionState();
    
    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(btScalar(0), motionState, shape, btVector3(0,0,0));
    rigidBodyCI.m_friction = rigidBodyCI.m_rollingFriction = rigidBodyCI.m_restitution = btScalar(0); //not used
    rigidBodyCI.m_linearDamping = rigidBodyCI.m_angularDamping = btScalar(0); //not used
	rigidBodyCI.m_linearSleepingThreshold = rigidBodyCI.m_angularSleepingThreshold = btScalar(0); //not used
    rigidBodyCI.m_additionalDamping = false;
    
    rigidBody = new btRigidBody(rigidBodyCI);
    rigidBody->setUserPointer(this);
    rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK | btCollisionObject::CF_STATIC_OBJECT);
}

void StaticEntity::AddToDynamicsWorld(btMultiBodyDynamicsWorld *world)
{
    AddToDynamicsWorld(world, btTransform::getIdentity());
}

void StaticEntity::AddToDynamicsWorld(btMultiBodyDynamicsWorld* world, const btTransform& worldTransform)
{
    if(rigidBody != NULL)
    {
        btDefaultMotionState* motionState = new btDefaultMotionState(UnitSystem::SetTransform(worldTransform));
        rigidBody->setMotionState(motionState);
        world->addRigidBody(rigidBody, MASK_STATIC, MASK_STATIC | MASK_DEFAULT);
    }
}

btRigidBody* StaticEntity::getRigidBody()
{
    return rigidBody;
}

void StaticEntity::SetLook(int newLookId)
{
    lookId = newLookId;
}

void StaticEntity::SetWireframe(bool enabled)
{
    wireframe = enabled;
}