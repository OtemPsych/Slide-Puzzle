#ifndef Grid_H_
#define Grid_H_

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>

class Grid : public sf::Drawable,
			 private sf::NonCopyable
{
private:
	// Private Member(s)
	sf::RectangleShape		  mOutline;
	std::vector<sf::Vector2f> mTilePositions;

private:
	// Private Method(s)
	void setupTilePositions();
	void setupOutline(sf::IntRect windowBounds);
public:
	// Constructor(s)
	Grid(int tilesInRow, sf::IntRect windowBounds);
	// Public Method(s)
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	// Public Getter Method(s)
	inline sf::FloatRect getOutlineRect() const { return mOutline.getGlobalBounds(); }
	inline sf::Vector2f getTilePos(int tileNb) const { return mTilePositions[tileNb]; }
};
#endif