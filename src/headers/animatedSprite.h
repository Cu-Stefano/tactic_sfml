#pragma once
#include "SFML/Graphics.hpp"

class AnimatedSprite
{
	int n_frames = 4;
	int curr_frame = 0;
	int sprite_width = 32;
	sf::Clock clock = sf::Clock();

public:
	float swap_interval = 0.3; // sec
	int sprite_y = 0;
	sf::Texture texture;
	sf::Sprite* sprite;
	AnimatedSprite(sf::Texture t);
	AnimatedSprite();

	void set_pos(sf::Vector2i coord);
	void update();
	void draw(sf::RenderWindow& window) const;
};
