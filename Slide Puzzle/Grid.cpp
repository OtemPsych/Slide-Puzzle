#include "Grid.h"

#include <SFML/Graphics/RenderTarget.hpp>

// Constructor(s)
	// Default
Grid::Grid(int tilesInRow, sf::IntRect windowBounds)
	: mTilePositions(tilesInRow * tilesInRow)
{
	setupOutline(windowBounds);
	setupTilePositions();
}

// Private Method(s)
	// Setup Tile Positions
void Grid::setupTilePositions()
{
	int tilesSquared = static_cast<int>(sqrt(mTilePositions.size()));
	int curCol = 0, curRow = 0;

	sf::FloatRect outlineRect = mOutline.getGlobalBounds();
	sf::Vector2f tileSize(mOutline.getSize().x / tilesSquared, mOutline.getSize().y / tilesSquared);
	for (auto& tilePos : mTilePositions) {
		tilePos = sf::Vector2f(outlineRect.left + curCol * tileSize.x,
							   outlineRect.top + curRow * tileSize.y);
		curCol++;

		if (curCol % tilesSquared == 0) {
			curRow++;
			curCol = 0;
		}
	}
}
	// Setup Outline
void Grid::setupOutline(sf::IntRect windowBounds)
{
	sf::Vector2f rectSize(windowBounds.width / 2.2f, windowBounds.height / 1.5f);
	mOutline.setSize(rectSize);
	mOutline.setPosition(windowBounds.width / 2 - rectSize.x / 2,
						 windowBounds.height / 2 - rectSize.y / 2);

	mOutline.setFillColor(sf::Color::Transparent);
	mOutline.setOutlineColor(sf::Color::Cyan);
	mOutline.setOutlineThickness(2.f);
}

// Public Method(s)
	// Draw
void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mOutline, states);
}