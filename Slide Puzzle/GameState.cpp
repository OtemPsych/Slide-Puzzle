#include "GameState.h"

#include <SFML/Window/Event.hpp>

// Constructor(s)
	// Default
GameState::GameState()
	: mWindow(sf::VideoMode::getDesktopMode(), "Slide Puzzle",
			  sf::Style::Close | sf::Style::Fullscreen)
	, mWindowBounds(0, 0, mWindow.getSize().x, mWindow.getSize().y)
	, mBackground(sf::Quads, 4)
	, mPuzzle(4, mWindowBounds)
{
	mWindow.setVerticalSyncEnabled(true);
	setupBackground();
}

// Private Method(s)
	// Setup Background
void GameState::setupBackground()
{
	mBackground[0].position = static_cast<sf::Vector2f>(sf::Vector2i(mWindowBounds.left, mWindowBounds.top));
	mBackground[1].position = static_cast<sf::Vector2f>(sf::Vector2i(mWindowBounds.width, mWindowBounds.top));
	mBackground[2].position = static_cast<sf::Vector2f>(sf::Vector2i(mWindowBounds.width, mWindowBounds.height));
	mBackground[3].position = static_cast<sf::Vector2f>(sf::Vector2i(mWindowBounds.left, mWindowBounds.height));

	mBackground[0].color = sf::Color(25, 23, 29);
	mBackground[1].color = sf::Color(91, 91, 73);
	mBackground[2].color = sf::Color(91, 91, 73);
	mBackground[3].color = sf::Color(25, 23, 29);
}
	// Process Input
void GameState::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				mWindow.close();
			break;
		case sf::Event::Closed:
			mWindow.close();
		}
}
	// Update
void GameState::update(sf::Time dt)
{
	mPuzzle.update(dt);
}
	// Render
void GameState::render()
{
	mWindow.clear();
	mWindow.draw(mBackground);
	mWindow.draw(mPuzzle);
	mWindow.display();
}

// Public Method(s)
	// Run
void GameState::run()
{
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Clock clock;
	sf::Time TimeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processInput();
		TimeSinceLastUpdate += clock.restart();
		while (TimeSinceLastUpdate > TimePerFrame)
		{
			TimeSinceLastUpdate -= TimePerFrame;
			processInput();
			update(TimePerFrame);
		}
		render();
	}
}