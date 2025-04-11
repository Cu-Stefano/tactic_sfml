#pragma once
#include "state.h"

using namespace std;

std::vector<std::vector<int>> map_generator();

void initialize_Map(state& gs);

void draw_map(state& gs);
void update_map(state& gs);

static void set_tile_sprite(sf::Sprite& sprite, const std::string& tileType, const sf::Vector2f& position);