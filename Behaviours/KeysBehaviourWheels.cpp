#include "KeysBehaviourWheels.h"
#include <sfml/window.hpp>

#include "../GameObject.hpp"
#include <math.h>


KeysBehaviourWheels::KeysBehaviourWheels( RaceWheels * aRaceWheels , Game * aGame  )
:	Behaviour( aRaceWheels ), raceWheels(aRaceWheels), game( aGame ), startFinish(0), start_time(0), lastCollider(0)
{
    laptimes = new std::vector<float>();
    bufferBusy = new sf::SoundBuffer();
    if (!bufferBusy->loadFromFile("engine.wav"))
        std::cout << "ERROR engine.wav" << std::endl;
    bufferIdle = new sf::SoundBuffer();
    if (!bufferIdle->loadFromFile("hotidle.wav"))
        std::cout << "ERROR hotidle.wav" << std::endl;
    soundBusy = new sf::Sound();
    soundBusy->setBuffer(*bufferBusy);
    soundBusy->setLoop(true);
    soundIdle = new sf::Sound();
    soundIdle->setBuffer(*bufferIdle);
    soundIdle->setLoop(true);
    soundIdle->play();
}

KeysBehaviourWheels::~KeysBehaviourWheels()
{
}

void KeysBehaviourWheels::update( float step )
{
    if(raceWheels->getSpeed() == 0){
        if(soundBusy->getStatus() == 2){
            soundBusy->pause();
            soundIdle->play();
        }
    }
    else if(soundIdle->getStatus() == 2){
            soundIdle->pause();
            soundBusy->play();
    }
    if(laptimes->size() < 3){
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down )) {
            raceWheels->raiseSpeed(1);
        }
        else if(raceWheels->getSpeed() >= 1){
            raceWheels->brakeReverse(1);
        }
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up )) {
            raceWheels->brakeReverse(1);
            parent->rotate( raceWheels->getSteeringAngle()*step, glm::vec3(0.0f, 1.0f, 0.0f ) );
        }
        else if(raceWheels->getSpeed() <= -1){
            raceWheels->raiseSpeed(1);
        }
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right )) {
            raceWheels->steerRight(1);
        }
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left )) {
            raceWheels->steerLeft(1);
        }
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::I )){
            std::cout << "Location of wheels " << parent->getLocation() << std::endl;
        }
        parent->translate( glm::vec3(0.0f, 0.0f, raceWheels->getSpeed()*step ) );
        if(floor( fabs( raceWheels->getSpeed()))!= 0 ){
           // parent->rotate( raceWheels->getSteeringAngle()*step, glm::vec3(0.0f, 1.0f, 0.0f ) );
        }
    }
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape )){
        game->stop();
	}
}

float KeysBehaviourWheels::getAngle(){
    return raceWheels->getSteeringAngle();
}

float KeysBehaviourWheels::getStart_time(){
    return start_time;
}

std::vector<float> * KeysBehaviourWheels::getLaptimes(){
    return laptimes;
}

float KeysBehaviourWheels::getSpeed(){
    return raceWheels->getSpeed();
}

void KeysBehaviourWheels::onCollision(GameObject * aGameObject){
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
