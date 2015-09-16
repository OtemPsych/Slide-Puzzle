#ifndef Puzzle_H_
#define Puzzle_H_

#include "Grid.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>

class Puzzle : public sf::Drawable,
			   private sf::NonCopyable
{
private:
	// Private Typedef(s)
	using SprPtr = std::unique_ptr<sf::Sprite>;
	// Private Member(s)
	std::vector<std::pair<SprPtr, int>> mTiles;
	Grid								mGrid;
	sf::Texture							mTexture;

private:
	// Private Method(s)
	void setupTiles();
	void jumbleTilePositions();
	void checkVictory();
	void createSprites();
	void loadRandomTexture();
public:
	// Constructor(s)
	Puzzle(int tilesInRow, sf::IntRect windowBounds);
	// Public Method(s)
	void update(sf::Time dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif