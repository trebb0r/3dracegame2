#include <cassert>
#include <iostream>
#include <cstdio>
#include <GL/glew.h>
#include "FPS.hpp"
#include "Hud.hpp"

Hud::Hud( sf::RenderWindow * aWindow )
:	window( aWindow )
{
	assert ( window != NULL );
    keysBehaviour = 0;
    //if ( marvinTex.loadFromFile("models/marvin.png") ) {
	//	marvin.setTexture( marvinTex);
	//	marvin.setPosition(150,150);
    //} else {
	//	std::cout << "Coulf not load sprite" << std::endl;
	//}
}

Hud::~Hud()
{
	//dtor
}

void Hud::setKeysBehaviour(KeysBehaviour * aKeysBehaviour){
    keysBehaviour = aKeysBehaviour;
}

void Hud::draw()
{
	glDisable( GL_CULL_FACE ); // needed for text, dont know why
	char fps[] = "Test";
	sprintf( fps, "%4d", FPS::getFPS() );
	sf::Text text( fps );
	//text.setFont(font);
	text.setCharacterSize(20);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::White);
	text.setPosition( 10,10);

    if(keysBehaviour != 0){

        char laptime[] = "Pass a checkpoint\n to start...";
        if(keysBehaviour->getStart_time() != 0){
            float time = Time::now();
            float current_time = time - keysBehaviour->getStart_time();
            sprintf( laptime, "Time: %2.1f", current_time );
        }
        sf::Text laptext( laptime );
        laptext.setCharacterSize(20);
        laptext.setStyle(sf::Text::Bold);
        laptext.setColor(sf::Color::White);
        laptext.setPosition( 750,0);
        assert ( window != NULL );
        window->draw(laptext);

        char steeringAngle[] = "Angle";
        sprintf(steeringAngle, "angle: %4.2f", keysBehaviour->getAngle());
        sf::Text angleText(steeringAngle);
        angleText.setCharacterSize(20);
        angleText.setColor(sf::Color::White);
        angleText.setPosition(500,0);
        window->draw(angleText);

        char speed[] = "Speed";
        sprintf(speed, "Speed: %4.2f km/h", -1*keysBehaviour->getSpeed());
        sf::Text speedText(speed);
        speedText.setCharacterSize(20);
        speedText.setColor(sf::Color::White);
        speedText.setPosition(500,20);
        window->draw(speedText);

        std::vector<float> * lap_times = keysBehaviour->getLaptimes();
        for(unsigned int i = 1; i <= lap_times->size(); ++i) {
            char laptimes[] = "";
            if(i < 3){
                sprintf( laptimes, "%2d: %4.1f", i, (*lap_times)[i-1]);
            }
            else{
                sprintf( laptimes, "%2d: %4.1f\nPress ESC to close", i, (*lap_times)[i-1]);
            }
            sf::Text laptimestext( laptimes );
            if(lap_times->size() < 3){
                laptimestext.setCharacterSize(15);
                laptimestext.setPosition( 780, i*15+10);
            }
            else{
                laptimestext.setCharacterSize(40);
                laptimestext.setPosition( 500, i*40+50);
            }
            laptimestext.setStyle(sf::Text::Bold);
            laptimestext.setColor(sf::Color::White);

            window->draw(laptimestext);
        }
    }
	// Draw it
	//std::cout << "Drawing text" << std::endl;
	assert ( window != NULL );
	window->draw( marvin );
	window->draw(text);
}
