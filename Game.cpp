#include <cassert>

#include "Time.hpp"
#include "FPS.hpp"

#include "Hud.hpp"
#include "Renderer.hpp"
#include "ShaderProgram.hpp"
#include "Game.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Behaviours/KeysBehaviour.hpp"
#include "Behaviours/KeysBehaviourWheels.h"
#include "Behaviours/WASDBehaviour.hpp"
#include "Behaviours/RotatingBehaviour.hpp"
#include "Collider.hpp"

Game::Game()
:	window(NULL), hud(NULL), renderer(NULL), world(NULL), camera(NULL), light(NULL)
{
	window = new sf::RenderWindow( sf::VideoMode( 1024, 576 ), "Saxion Game" ); // get a window
	std::cout << "Init Glew" << glewInit() << std::endl;
	hud = new Hud( window );
	//window->setVerticalSyncEnabled( true ); // sync with monitor ->60 hz approx
	renderer = new Renderer( window );
}

Game::~Game()
{
	//dtor
}

void Game::build()
{
	renderer->use(  new ShaderProgram( "shaders/default.vs", "shaders/default.fs" ) );
	camera = new Camera( "Camera", glm::vec3( 0.0f, 19.0f, 19.0f ) );
	light = new Light( "Light", glm::vec3( 0.0f, 19.0f, 19.0f ) );

	Mesh * car_no_wheels = Mesh::load( "models/car_no_wheels.obj");
	Mesh * wheelMesh = Mesh::load( "models/2wheels.obj");
	Mesh * cubeMesh = Mesh::load( "models/skybox-alt-40.obj");

	world = new World( "World" );
		world->add( camera );
		world->add( light );

		RaceCar * player = new RaceCar("Player", glm::vec3( -5.5f, 0.0f, 13.0f ));
            player->rotate( -90, glm::vec3(0.0f, 1.0f, 0.0f ) );
            KeysBehaviour * kb = new KeysBehaviour( player, this);
			player->setBehaviour( kb );
			hud->setKeysBehaviour( kb );
			player->setMesh( car_no_wheels );
			player->setColorMap( Texture::load("models/bricks.jpg") );
			player->setCollider( new Collider( player, 4 ) );
			world->add( player  );
		GameObject * wheels = new GameObject("Wheels", glm::vec3( 0, 2, -3.5 ) );
            KeysBehaviourWheels * kb2 = new KeysBehaviourWheels( wheels, player);
			wheels->setBehaviour( kb2 );
			wheels->setMesh( wheelMesh );
			wheels->setColorMap( Texture::load("models/monkey.jpg") );
			player->add( wheels );
		GameObject * wheels2 = new GameObject("Wheels2", glm::vec3( 0, 2, 2.5 ) );
            KeysBehaviourWheels * kb3 = new KeysBehaviourWheels( wheels2, player);
			wheels2->setBehaviour( kb3 );
			wheels2->setMesh( wheelMesh );
			wheels2->setColorMap( Texture::load("models/monkey.jpg") );
			player->add( wheels2 );
        GameObject * startFinish = new GameObject("Start Finish", glm::vec3( 0.4,0,13 ) );
			//startFinish->setMesh( cube );
			//startFinish->setColorMap( Texture::load("models/monkey.jpg") );
			startFinish->setCollider( new Collider( startFinish ) );
			world->add( startFinish );

       GameObject * checkpoint = new GameObject("Checkpoint", glm::vec3( -0.5,0, -12 ) );
			//checkpoint->setMesh( cube );
			//checkpoint->setColorMap( Texture::load("models/monkey.jpg") );
			checkpoint->setCollider( new Collider( checkpoint ) );
			world->add( checkpoint );
        GameObject * cube = new GameObject("Cube", glm::vec3(0.0f,0.0f,0.0f));
            cube->setMesh(cubeMesh);
            cube->setColorMap( Texture::load("models/skybox.jpg"));
            //cube->setBehaviour( new RotatingBehaviour(cube));
            world->add(cube);
		GameObject * floor = new GameObject("Floor", glm::vec3( 0,0,0 ) );
			floor->setMesh( Mesh::load( "models/floor.obj" ) );
			floor->setColorMap( Texture::load( "models/racetrack.jpg" ) );
			world->add( floor );
}

void Game::run()
{
	running = true;
	while ( running ) {
		Time::update();
		FPS::update();
		control();
		if ( running ) { // control may have changed running;
			update( Time::step() );
			draw();
		}
	}
}

void Game::stop()
{
    window->close();
    running = false;
}

// private functions

void Game::control()
{
	sf::Event event;
	while( window->pollEvent( event ) ) {
		if ( event.type == sf::Event::Closed ) {
			window->close();
			running = false; // running = false;
		}
	}
}

void Game::update( float step )
{
	assert( world != NULL );
	world->update( step );
	checkCollisions();
}

void Game::draw()
{
	assert( window != NULL );
	assert( renderer != NULL );
	assert( world != NULL );

	renderer->draw( world );
	window->pushGLStates();
	hud->draw();
	window->popGLStates();
	window->display();
}


bool Game::checkCollisions()
{
	return world->checkCollisions();
}
