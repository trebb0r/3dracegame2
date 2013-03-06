#ifndef KEYSBEHAVIOUR_H
#define KEYSBEHAVIOUR_H

#include "../Behaviour.hpp"
#include "../Game.hpp"


class KeysBehaviour : public Behaviour
{
    private:
        Game * game;
	public:
		KeysBehaviour( GameObject * aParent, Game * aGame );
		virtual ~KeysBehaviour();

		virtual void update( float step );
};

#endif // KEYSBEHAVIOUR_H
