#include "RotatingBehaviour.hpp"

#include <iostream>
#include "../glm.hpp"
#include "../GameObject.hpp"

RotatingBehaviour::RotatingBehaviour( GameObject * aParent )
:	Behaviour( aParent )
{
	//ctor
}

RotatingBehaviour::~RotatingBehaviour()
{
	//dtor
}

void RotatingBehaviour::update( float step )
{
	parent->rotate( step * 0, glm::vec3( step * 45, 1.0f, 0.0f ) ); // rotates 45° per second
}
