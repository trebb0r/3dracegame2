#include "KeysBehaviour.hpp"
#include <sfml/window.hpp>

#include "../GameObject.hpp"


KeysBehaviour::KeysBehaviour( GameObject * aParent , Game * aGame  )
:	Behaviour( aParent ), game( aGame ), startFinish(0), start_time(0), lastCollider(0)
{
    laptimes = new std::vector<float>();
}

KeysBehaviour::~KeysBehaviour()
{
}

void KeysBehaviour::update( float step )
{
	float speed = 0.0f; //default if no keys
	float rotationSpeed = 0.0f;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down )) {
		speed = 10.0f;
		//transformation =  glm::translate( transformation, glm::vec3(0.0f, 0.0f, -10.0f*step ) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up )) {
		speed = -10.0f;
		//transformation =  glm::translate( transformation, glm::vec3(0.0f, 0.0f, 10.0f*step ) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right )) {
		rotationSpeed = -135.0f;
		//transformation = glm::rotate( transformation, -135*step, glm::vec3(0.0f, 1.0f, 0.0f ) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left )) {
		rotationSpeed = +135.0f;
		//transformation = glm::rotate( transformation, 135*step, glm::vec3(0.0f, 1.0f, 0.0f ) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape )){
        //close window
        game->stop();
	}
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::I )){
        std::cout << "Location of player " << parent->getLocation() << std::endl;
	}
	parent->translate( glm::vec3(0.0f, 0.0f, speed*step ) );
	parent->rotate( rotationSpeed*step, glm::vec3(0.0f, 1.0f, 0.0f ) );
//	transformation = glm::translate( transformation, glm::vec3(0.0f, 0.0f, speed*step ) );
//	transformation = glm::rotate( transformation, rotationSpeed*step, glm::vec3(0.0f, 1.0f, 0.0f ) );

}

float KeysBehaviour::getStart_time(){
    return start_time;
}

std::vector<float> * KeysBehaviour::getLaptimes(){
    return laptimes;
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
