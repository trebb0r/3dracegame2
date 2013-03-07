#ifndef KEYSBEHAVIOUR_H
#define KEYSBEHAVIOUR_H

#include "../Behaviour.hpp"
#include "../Game.hpp"
#include "../Time.hpp"


class KeysBehaviour : public Behaviour
{
    private:
        Game * game;
        GameObject * lastCollider;
        GameObject * startFinish;
        RaceCar * raceCar;
        float start_time;
        std::vector<float> * laptimes;
	public:
		KeysBehaviour( RaceCar * aParent, Game * aGame );
		virtual ~KeysBehaviour();
		float getStart_time();
		float getAngle();
		float getSpeed();
        std::vector<float> * getLaptimes();
		virtual void update( float step );
		virtual void onCollision(GameObject * aGameObject);
};

#endif // KEYSBEHAVIOUR_H
