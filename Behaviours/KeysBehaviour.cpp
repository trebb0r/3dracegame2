#include "KeysBehaviour.hpp"
#include <sfml/window.hpp>

#include "../GameObject.hpp"
#include <math.h>


KeysBehaviour::KeysBehaviour( RaceCar * aRaceCar , Game * aGame  )
:	Behaviour( aRaceCar ), raceCar(aRaceCar), game( aGame ), startFinish(0), start_time(0), lastCollider(0)
{
    laptimes = new std::vector<float>();
    bufferBusy = new sf::SoundBuffer();
    if (!bufferBusy->loadFromFile("engine.wav"))
        std::cout << "ERROR engine.wav" << std::endl;
    bufferIdle = new sf::SoundBuffer();
    if (!bufferIdle->loadFromFile("hotidle.wav"))
        std::cout << "ERROR hotidle.wav" << std::endl;
    bufferAlarm = new sf::SoundBuffer();
    if (!bufferAlarm->loadFromFile("SIREN.WAV"))
        std::cout << "ERROR SIREN.WAV" << std::endl;
    soundBusy = new sf::Sound();
    soundBusy->setBuffer(*bufferBusy);
    soundBusy->setLoop(true);
    soundIdle = new sf::Sound();
    soundIdle->setBuffer(*bufferIdle);
    soundIdle->setLoop(true);
    soundIdle->play();
    soundAlarm = new sf::Sound();
    soundAlarm->setBuffer(*bufferAlarm);
    soundAlarm->setLoop(true);
}

KeysBehaviour::~KeysBehaviour()
{
}

void KeysBehaviour::update( float step )
{
    if(outOfMap()){
        if(soundAlarm->getStatus() != 2){
           soundAlarm->play();
        }
    }
    else if(soundAlarm->getStatus() == 2){
        soundAlarm->pause();
    }
    if(raceCar->getSpeed() == 0){
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
            raceCar->raiseSpeed(1);
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && raceCar->getSpeed() > 0){
            raceCar->brakeReverse(0.1);
        }
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up )) {
            raceCar->brakeReverse(1);
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && raceCar->getSpeed() < 0){
            raceCar->raiseSpeed(0.1);
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

bool KeysBehaviour::outOfMap(){
    if(raceCar->getLocation().x > 15 ){
        return true;
    }
    if(raceCar->getLocation().x < -15 ){
        return true;
    }
    if(raceCar->getLocation().z > 15){
        return true;
    }
    if(raceCar->getLocation().z < -15){
        return true;
    }
    return false;
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
