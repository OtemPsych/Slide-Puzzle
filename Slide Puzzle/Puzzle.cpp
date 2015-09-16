#include "Puzzle.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

// Constructor(s)
	// Constructor 1
Puzzle::Puzzle(int tilesInRow, sf::IntRect windowBounds)
	: mTiles(tilesInRow * tilesInRow)
	, mGrid(tilesInRow, windowBounds)
{
	createSprites();
	loadRandomTexture();
	setupTiles();
	jumbleTilePositions();
}

// Private Method(s)
	// Setup Tiles
void Puzzle::setupTiles()
{
	int tilesSquared = static_cast<int>(sqrt(mTiles.size()));
	int curCol = 0, curRow = 0;

	sf::FloatRect outlineRect = mGrid.getOutlineRect();
	sf::Vector2f tileRect(outlineRect.width / tilesSquared, outlineRect.height / tilesSquared);

	sf::Vector2f textureSize(mTexture.getSize());
	sf::Vector2f textureRect(textureSize.x / tilesSquared, textureSize.y / tilesSquared);

	sf::Vector2f scalingFactor(tileRect.x / textureRect.x,
		tileRect.y / textureRect.y);

	for (unsigned i = 0; i < mTiles.size(); i++)
	{
		mTiles[i].first->setTextureRect(static_cast<sf::IntRect>
			(sf::FloatRect(curCol * textureRect.x, curRow * textureRect.y,
						   textureRect.x, textureRect.y)));
		mTiles[i].first->setTexture(mTexture);
		mTiles[i].first->scale(scalingFactor);
		mTiles[i].first->setPosition(mGrid.getTilePos(i));

		curCol++;
		if (curCol % tilesSquared == 0) {
			curRow++;
			curCol = 0;
		}
	}
}
	// Jumble Tile Positions
void Puzzle::jumbleTilePositions()
{
	std::vector<int> tiles(mTiles.size());
	for (unsigned i = 0; i < tiles.size(); i++)
		tiles[i] = i;
	std::random_shuffle(tiles.begin(), tiles.end());

	for (unsigned i = 0; i < mTiles.size(); i++)
	{
		mTiles[i].first->setPosition(mGrid.getTilePos(tiles[i]));
		mTiles[i].second = tiles[i];
	}
}
	// Check Victory
void Puzzle::checkVictory()
{
	bool gameWon = false;

	for (const auto& tile : mTiles)
		if ((tile.first != nullptr) && (tile.first->getPosition() == mGrid.getTilePos(tile.second))) {
			gameWon = true;
			break;
		}

	if (gameWon)
		std::cout << "VICTORY!\n";
}
	// Create Sprites
void Puzzle::createSprites()
{
	for (unsigned i = 0; i < mTiles.size(); i++) {
		SprPtr sprite(new sf::Sprite());
		mTiles[i].first = std::move(sprite);
		mTiles[i].second = i;
	}
}
	// Load Random Texture
void Puzzle::loadRandomTexture()
{
	int rnd = rand() % Textures::Puzzle::TypeCount;
	mTexture.loadFromFile("Assets/Textures/Texture" + std::to_string(rnd) + ".png");
}

// Public Method(s)
	// Update
void Puzzle::update(sf::Time dt)
{
	checkVictory();
}
	// Draw
void Puzzle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& tile : mTiles)
		if (tile.first != nullptr)
			target.draw(*tile.first, states);
	target.draw(mGrid, states);
}