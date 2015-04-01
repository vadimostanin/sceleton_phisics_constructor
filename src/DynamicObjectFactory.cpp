/*
 * DynamicObjectFactory.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: vostanin
 */

#include "DynamicObjectFactory.h"
#include <chipmunk/chipmunk.h>
#include <chipmunk/chipmunk_types.h>

DynamicObjectFactory::DynamicObjectFactory()
{
	// cpVect is a 2D vector and cpv() is a shortcut for initializing them.
	cpVect gravity = cpv( 0, -1000 );

	// Create an empty space.
	cpSpace *space = cpSpaceNew();
	cpSpaceSetGravity(space, gravity);

	// Add a static line segment shape for the ground.
	// We'll make it slightly tilted so the ball will roll off.
	// We attach it to space->staticBody to tell Chipmunk it shouldn't be movable.
	cpShape *ground = cpSegmentShapeNew( cpSpaceGetStaticBody( space ), cpv(-1000, 0), cpv(1000, 0), 0);

	cpShapeSetFriction(ground, 1);
	cpSpaceAddShape(space, ground);
}

DynamicObjectFactory::~DynamicObjectFactory()
{
}

