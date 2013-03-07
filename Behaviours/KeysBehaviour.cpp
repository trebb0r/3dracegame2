#include "KeysBehaviour.hpp"
#include <sfml/window.hpp>

#include "../GameObject.hpp"
#include <math.h>


KeysBehaviour::KeysBehaviour( RaceCar * aRaceCar , Game * aGame  )
:	Behaviour( aRaceCar ), raceCar(aRaceCar), game( aGame ), startFinish(0), start_time(0), lastCollider(0)
{
    laptimes = new std::vector<float>();
}

KeysBehaviour::~KeysBehaviour()
{
}

void KeysBehaviour::update( float step )
{
    if(laptimes->size() < 3){
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down )) {
            raceCar->raiseSpeed(1);
        }
        else if(raceCar->getSpeed() >= 1){
            raceCar->brakeReverse(1);
        }
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up )) {
            raceCar->brakeReverse(1);
        }
        else if(raceCar->getSpeed() <= -1){
            raceCar->raiseSpeed(1);
        }
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right )) {
            raceCar->steerRight(1);
        }
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left )) {
            raceCar->steerLeft(1);
        }
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::I )){
            std::cout << "Location of player " << parent->getLocation() << std::endl;
        }
        parent->translate( glm::vec3(0.0f, 0.0f, raceCar->getSpeed()*step ) );
        if(floor( fabs( raceCar->getSpeed()))!= 0 ){
            parent->rotate( raceCar->getSteeringAngle()*step, glm::vec3(0.0f, 1.0f, 0.0f ) );
        }
    }
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape )){
        game->stop();
	}
}

float KeysBehaviour::getAngle(){
    return raceCar->getSteeringAngle();
}

float KeysBehaviour::getStart_time(){
    return start_time;
}

std::vector<float> * KeysBehaviour::getLaptimes(){
    return laptimes;
}

float KeysBehaviour::getSpeed(){
    return raceCar->getSpeed();
}

void KeysBehaviour::onCollision(GameObject * aGameObject){
    //TODO check if colliding object is a checkpoint
    if(aGameObject == lastCollider ){
        //do nothing
    }
    else{
        lastCollider = aGameObject;
        float time = Time::now();
        if(startFinish == 0){
            startFinish = aGameObject;
            start_time = time;
        }
        else if(lastCollider == startFinish){
            float lap_time = time - start_time;
            std::cout << "Laptime: " << lap_time << std::endl;
            laptimes->push_back(lap_time);
            start_time = time;
        }
        std::cout << "Passed checkpoint on " << time << std::endl;
    }

}
