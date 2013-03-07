#include "RaceWheels.h"

RaceWheels::RaceWheels(std::string aName , glm::vec3 aPosition ) : GameObject(aName, aPosition)
{
    //ctor
    lapTimes = new std::vector<float>();
    lastCheckpoint = 0;
    startFinish = 0;
}

RaceWheels::~RaceWheels()
{
    //dtor
}

void RaceWheels::raiseSpeed(float speedRaise){
    assert(speedRaise > 0);
    if(speed + speedRaise >= maxSpeed){
        speed = maxSpeed;
    }
    else{
        speed += speedRaise;
    }
}

float RaceWheels::getSpeed(){
    return speed;
}

void RaceWheels::brakeReverse(float brakePower){
    assert(brakePower > 0);
    if(speed - brakePower <= maxReverse){
        speed = maxReverse;
    }
    else{
        speed -= brakePower;
    }
}

//sideeffect steeringangle gets reset to 0
float RaceWheels::getSteeringAngle(){
    //float temp = steeringAngle;
    //steeringAngle = 0;
    //return temp;
    return steeringAngle;
}

void RaceWheels::steerLeft(float angle){
    assert(angle > 0);
    //left is positive right is negative
    if(steeringAngle + angle > maxSteeringAngle){
        steeringAngle = maxSteeringAngle;
    }
    else {
        steeringAngle += angle;
    }
}

void RaceWheels::steerRight(float angle){
    assert(angle > 0);
    //left is positive right is negative
    if(steeringAngle - angle < -1* maxSteeringAngle){
        steeringAngle = -1 * maxSteeringAngle;
    }
    else {
        steeringAngle -= angle;
    }
}

void RaceWheels::onCollision(GameObject * aGameObject){
    GameObject::onCollision(aGameObject);
    //TODO check if colliding object is a checkpoint
    //if(aGameObject == lastCheckpoint ){
     //   //do nothing
    //}
    //else{
        //lastCheckpoint = aGameObject;
        //float time = Time::now();
        //if(startFinish == 0){
        //    startFinish = aGameObject;
        //    start_time = time;
        //}
        //else if(lastCheckpoint == startFinish){
            //float lap_time = time - start_time;
            //std::cout << "Laptime: " << lap_time << std::endl;
           // laptimes->push_back(lap_time);
         //   start_time = time;
        //}
        //std::cout << "Passed checkpoint on " << time << std::endl;
    //}
}
