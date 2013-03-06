#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include "Behaviours/KeysBehaviour.hpp"
class Hud
{
	private:
		sf::RenderWindow * window;
		sf::Font font;
		sf::Texture marvinTex;
		sf::Sprite marvin;
		KeysBehaviour * keysBehaviour;

	public:
		Hud( sf::RenderWindow * aWindow);
		virtual ~Hud();
        void setKeysBehaviour(KeysBehaviour * aKeysBehaviour);
		void draw( );
};

#endif // HUD_H
