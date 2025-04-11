#pragma once

#include <string>
#include "SFML/Graphics.hpp"

class AnimatedSprite
{
	int n_frames = 4;
	int curr_frame;
	int sprite_width = 32;
	float swap_interval = 0.3f; // sec
	sf::Clock clock = sf::Clock();

public:
	int sprite_y = 0;
	sf::Texture texture;
	sf::Sprite* sprite;
	AnimatedSprite(sf::Texture t);
	AnimatedSprite();

	void set_pos(sf::Vector2i coord);
	void update();
	void draw(sf::RenderWindow& window) const;
};
