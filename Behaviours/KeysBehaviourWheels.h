#ifndef KEYSBEHAVIOURWHEELS_H
#define KEYSBEHAVIOURWHEELS_H

#include "../Behaviour.hpp"
#include "../Game.hpp"
#include "../Time.hpp"
#include <SFML/Audio.hpp>


class KeysBehaviourWheels : public Behaviour
{
    private:
        RaceCar * raceCar;

	public:
		KeysBehaviourWheels( GameObject * aParent, RaceCar * aRaceCar );
		virtual ~KeysBehaviourWheels();
		virtual void update( float step );
};

#endif // KEYSBEHAVIOURWHEELS_H
