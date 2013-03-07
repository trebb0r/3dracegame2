#include "RaceCar.h"

RaceCar::RaceCar(std::string aName , glm::vec3 aPosition ) : GameObject(aName, aPosition)
{
    //ctor
    lapTimes = new std::vector<float>();
}

RaceCar::~RaceCar()
{
    //dtor
}

void RaceCar::raiseSpeed(float speedRaise){
    assert(speedRaise > 0);
    if(speed + speedRaise >= maxSpeed){
        speed = maxSpeed;
    }
    else{
        speed += speedRaise;
    }
}

float RaceCar::getSpeed(){
    return speed;
}

void RaceCar::brakeReverse(float brakePower){
    assert(brakePower > 0);
    if(speed - brakePower <= maxReverse){
        speed = maxReverse;
    }
    else{
        speed -= brakePower;
    }
}

//sideeffect steeringangle gets reset to 0
float RaceCar::getSteeringAngle(){
    //float temp = steeringAngle;
    //steeringAngle = 0;
    //return temp;
    return steeringAngle;
}

void RaceCar::steerLeft(float angle){
    assert(angle > 0);
    //left is positive right is negative
    if(steeringAngle + angle > maxSteeringAngle){
        steeringAngle = maxSteeringAngle;
    }
    else {
        steeringAngle += angle;
    }
}

void RaceCar::steerRight(float angle){
    assert(angle > 0);
    //left is positive right is negative
    if(steeringAngle - angle < -1* maxSteeringAngle){
        steeringAngle = -1 * maxSteeringAngle;
    }
    else {
        steeringAngle -= angle;
    }
}
