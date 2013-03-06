#ifndef KEYSBEHAVIOUR_H
#define KEYSBEHAVIOUR_H

#include "../Behaviour.hpp"
#include "../Game.hpp"


class KeysBehaviour : public Behaviour
{
    private:
        Game * game;
        GameObject * lastCollider;
        GameObject * startFinish;
        float start_time;
	public:
		KeysBehaviour( GameObject * aParent, Game * aGame );
		virtual ~KeysBehaviour();

		virtual void update( float step );
		virtual void onCollision(GameObject * aGameObject);
};

#endif // KEYSBEHAVIOUR_H
