#pragma once
#include <string>
#include <vector>
#include "SFML/Graphics/Sprite.hpp"
#include "state.hpp"

std::vector<std::vector<int>> map_generator();

void initialize_map(state& gs);

void draw_map(state& gs);
void update_map(state& gs);

static void set_tile_sprite(sf::Sprite& sprite, const std::string& tileType, const sf::Vector2f& position);

extern std::vector<Tile*> allay_tile_list;
extern std::vector<Tile*> enemy_tile_list;