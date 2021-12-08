/*
 * Player.hpp
 *
 *  Created on: Dec 1, 2021
 *      Author: johannes
 */

#ifndef OU_EST_LE_BEURRE_PLAYER_HPP_
#define OU_EST_LE_BEURRE_PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include "ou_est_le_beurre/globals.hpp"
#include "GameObject.hpp"

enum Direction { UP, LEFT, DOWN, RIGHT };

class Player : public GameObject
{
public:
	Player(const std::string &);
	~Player();

    void update(float) override;
    void draw(sf::RenderTarget &, sf::RenderStates) const override;

private:
	void moveTile(float);
	bool inMap(int, int);

private:
	sf::Texture texture;
	sf::Sprite sprite;

	// position + direction
	sf::Vector2i gridPostion;	// position in grid postion(2 * TILESIZE, 3 * TILESIZE) -> gridPosition(2, 3)

	Direction direction;

	// moveTile
	const float timePerTile;	// in seconds
	const float offsetTime;		// time to wait between rotating and moving
};

#endif
