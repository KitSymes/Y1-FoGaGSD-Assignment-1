#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#endif
#define MUNCHIECOUNT 10
#define GHOSTCOUNT 2
// Just need to include main header file
#include "S2D/S2D.h"

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.
class Pacman : public Game
{
public:
	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);

	enum Direction {
		UP, DOWN, LEFT, RIGHT
	};

	float getRotationFromDirection(Direction dir) // TODO Messes up sprite drawn position, make spritesheet instead
	{
		switch (dir)
		{
		case UP:
		case DOWN:
			return 90.0f;
			break;
		case LEFT:
		case RIGHT:
			return 0.0f;
			break;
		}
	}

	float getYPosFromDirection(Direction dir)
	{
		switch (dir)
		{
		case RIGHT:
			return 0.0f;
		case DOWN:
			return 32.0f;
		case LEFT:
			return 64.0f;
		case UP:
			return 96.0f;
		}
	}
private:
	//Input methods
	void Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState*);

	//Check methods
	void CheckViewportCollision();
	bool CollisionCheck(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2);

	//Update methods
	void UpdatePacman(int elapsedTime);
	void UpdateMunchie(int elapsedTime);

	// Data to represent Pacman
	struct PacCharacter {
		float _pacmanSpeed = 0.4;
		float _speedMulti = 1.0;
		Direction dir = RIGHT;
		int frame = 0;
		Rect* _pacmanSourceRect;
		Texture2D* _pacmanTexture;
		Vector2* _pacmanPosition;
		bool dead;
	};

	PacCharacter* _ourPac;
	Texture2D* _wallTexture;

	int _frameCount;

	// Data to represent Munchie
	struct Enemy {
		Rect* _position;
		Rect* _sourceRect;
		Texture2D* _texture;
		~Enemy() {
			delete _position;
			delete _sourceRect;
		}
	};

	Enemy* _munchies[MUNCHIECOUNT];
	Enemy* _cherry;

	struct MovingEnemy {
		Rect* _position;
		Rect* _sourceRect;
		Texture2D* _texture;
		int direction;
		double speed;
		~MovingEnemy() {
			delete _position;
			delete _sourceRect;
			delete _texture;
		}
	};

	MovingEnemy* _ghosts[GHOSTCOUNT];
	void CheckGhostCollisions();
	void UpdateGhost(MovingEnemy* ghost, int elapsedTime);

	// Position for String
	Vector2* _debugStringPosition;

	// Menu
	Texture2D* _menuBackground;
	Rect* _menuSpriteBounds;
	Vector2* _menuStringPosition;
	bool _paused, _pKeyDown;
	bool _atMenu;

	Texture2D* _gameOverTexture;
	Vector2* _gameOverPos;
	Vector2* _gameOverStringPos;
	Rect* _gameOverSource;

	SoundEffect* _pog;
	SoundEffect* _nom;
};