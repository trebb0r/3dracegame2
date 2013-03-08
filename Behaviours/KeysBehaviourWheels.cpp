#include "KeysBehaviourWheels.h"
#include <sfml/window.hpp>

#include "../GameObject.hpp"
#include <math.h>


KeysBehaviourWheels::KeysBehaviourWheels( GameObject * raceWheels , RaceCar * aRaceCar)
:	Behaviour( raceWheels ), raceCar( aRaceCar )
{
}

KeysBehaviourWheels::~KeysBehaviourWheels()
{
}

void KeysBehaviourWheels::update( float step )
{
    float speed = raceCar->getSpeed();
    parent->rotate( step * speed * 20, glm::vec3( 1.0f, 0.0f, 0.0f ) );
}
