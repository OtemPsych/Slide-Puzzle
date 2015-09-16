#ifndef GameState_H_
#define GameState_H_

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "Puzzle.h"

class GameState : private sf::NonCopyable
{
private:
	// Private Member(s)
	sf::RenderWindow mWindow;
	sf::IntRect		 mWindowBounds;
	sf::VertexArray  mBackground;
	Puzzle			 mPuzzle;

private:
	// Private Method(s)
	void setupBackground();
	void processInput();
	void update(sf::Time dt);
	void render();
public:
	// Constructor(s)
	GameState();
	// Public Method(s)
	void run();
};
#endif