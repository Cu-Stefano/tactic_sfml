#include "../headers/animatedSprite.h"

#include <iostream>

#include "../headers/unit.h"

AnimatedSprite::AnimatedSprite(sf::Texture t)
{
	this->curr_frame = 0;
	sprite = new sf::Sprite(t);
	texture = t;
	sprite->setTexture(texture);
	sprite->setScale({ 2, 2 });
	sprite->move(DEFAULT_OFFSET);
	sprite->setTextureRect(sf::IntRect({ 0 * sprite_width, 0 }, { sprite_width, sprite_width }));
	sprite_y = 0;
}

void AnimatedSprite::set_pos(sf::Vector2i coord)
{
	sprite->move(sf::Vector2f(coord));
}

AnimatedSprite::AnimatedSprite()
= default;

void AnimatedSprite::update()
{
    sf::Time elapsed = clock.getElapsedTime();

    if (elapsed.asSeconds() >= swap_interval)
    {
		this->curr_frame += 1;
		if (this->curr_frame >= n_frames)
		{
			this->curr_frame = 0;
		}
        sprite->setTextureRect(sf::IntRect({ this->curr_frame * sprite_width, sprite_y*32 }, { sprite_width, sprite_width }));
        clock.restart();
    }
}

void AnimatedSprite::draw(sf::RenderWindow& window) const
{
	window.draw(*sprite);
}