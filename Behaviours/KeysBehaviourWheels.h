#ifndef KEYSBEHAVIOURWHEELS_H
#define KEYSBEHAVIOURWHEELS_H

#include "../Behaviour.hpp"
#include "../Game.hpp"
#include "../Time.hpp"
#include <SFML/Audio.hpp>


class KeysBehaviourWheels : public Behaviour
{
    private:
        RaceWheels * raceWheels;
        Game * game;
        GameObject * startFinish;
        float start_time;
        GameObject * lastCollider;
        std::vector<float> * laptimes;
        sf::SoundBuffer * bufferBusy;
        sf::SoundBuffer * bufferIdle;
        sf::Sound * soundIdle;
        sf::Sound * soundBusy;
	public:
		KeysBehaviourWheels( RaceWheels * aParent, Game * aGame );
		virtual ~KeysBehaviourWheels();
		float getStart_time();
		float getAngle();
		float getSpeed();
        std::vector<float> * getLaptimes();
		virtual void update( float step );
		virtual void onCollision(GameObject * aGameObject);
};

#endif // KEYSBEHAVIOURWHEELS_H
