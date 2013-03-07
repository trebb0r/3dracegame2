#ifndef RACECAR_H
#define RACECAR_H

#include "GameObject.hpp"
#include "Time.hpp"


class RaceCar : public GameObject
{
    public:
        RaceCar( std::string aName = NULL, glm::vec3 aPosition = glm::vec3( 0.0f, 0.0f, 0.0f ) );;
        virtual ~RaceCar();
        float getSpeed();
        float getSteeringAngle();
        void steerLeft(float angle);
        void steerRight(float angle);
        void raiseSpeed(float speedRaise);
        void brakeReverse(float brakePower);
        virtual void onCollision(GameObject * aGameObject);
    protected:
    private:
        const static float maxSpeed = 5;
        const static float maxReverse = -10;
        const static float maxSteeringAngle = 80;
        float speed;
        float steeringAngle;
        std::vector<float> * lapTimes;
        GameObject * lastCheckpoint;
        GameObject * startFinish;
        float start_time;
};

#endif // RACECAR_H
