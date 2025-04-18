#include "../headers/mapBuilder.h"
#include "../headers/state.hpp"
#include "../headers/tile.h"
#include "../headers/unit.h"
#include "../headers/turnState.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <iostream>
#include <random>
using namespace sf;

const Texture TEXTURE("resources/Tiles/FullTileset.png");
constexpr Vector2i TEXTURE_TILE_SIZE(16, 16);

std::vector<std::vector<int>> map_generator()
{
    return
    {
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, -1, -2, 1, 1},
        {1, 0, 0, 1, 2, 2, 2, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, -1, -1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 2, 1, -1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, -1, 2, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1},
        {1, 1, 0, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1},
		{1, 1, 0, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1},
        {1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
}

void initialize_map(state& gs)
{
	float x = 0.0f, y = 0.0f;

    auto map = map_generator();
    int allayIndex = 0;
    int enemyIndex = 1;

    for (size_t i = 0; i < map.size(); ++i)
    {
	    float tileSize = 40.0f;
	    std::vector<Tile*> row;
        x = 0.0f;
        
        for (size_t j = 0; j < map[i].size(); ++j)
        {
            std::string tileName;
            bool walkable = true;
			Unit* unit = nullptr;

            switch (map[i][j])
            {
            case -2:
                //boss
                unit = enemy_list.at(0);
                unit->set_sprite_pos({ static_cast<int>(x), static_cast<int>(y) });
                unit->an_sprite.sprite->setScale({3, 3});
                unit->an_sprite.sprite->move({ -16, -21 });

                tileName = "grass";
                walkable = false;
                break;
            case -1:
                //enemy
                unit = enemy_list.at(enemyIndex);
                unit->set_sprite_pos({ static_cast<int>(x), static_cast<int>(y) });
                enemyIndex++;

                tileName = "grass";
                walkable = false;
                break;
			case 0:
                //alleato
                unit = allay_list.at(allayIndex);
                unit->set_sprite_pos({ static_cast<int>(x), static_cast<int>(y) });
                allayIndex++;

                tileName = "grass";
                walkable = false;
				break;
            case 2:
                tileName = "water";
                walkable = false;
                break;
            case 3:
                tileName = "mountain";
                walkable = false;
                break;
            default:
                tileName = "grass";
                walkable = true;
                break;
            }

            Sprite grass_sprite = Sprite(TEXTURE);
			set_tile_sprite(grass_sprite, tileName, { x, y });

            //path_sprite
            Texture path_text;
			Sprite path_spr = Sprite(path_text);
            path_spr.setTextureRect(IntRect({0, 0}, TEXTURE_TILE_SIZE));
            path_spr.setScale({ 2.48f, 2.48f });
            path_spr.setColor(Color::Transparent);
            path_spr.setPosition({ x, y });
            path_spr.move({ 0.5f, 0.5f });

            Tile* new_tile = new Tile(tileName, walkable, unit, { x, y }, { tileSize, tileSize }, grass_sprite, path_spr);

            // Evento di prova
            new_tile->set_click_function([i, j, new_tile]() {
                std::cout << "Tile clicked at (" << i << ", " << j << ")" << '\n';
				std::cout << "Tile name: " << new_tile ->tileName << '\n';
				std::cout << "Unit on tile: " << (new_tile->unitOn ? new_tile->unitOn->name : "None") << '\n';
				std::cout << "Unit can move: " << (new_tile->unitOn ? new_tile->unitOn->canMove : "None") << '\n';
				std::cout << "walkable: " << new_tile->walkable << '\n';
				std::cout << "g: " << new_tile->G << '\n';
				std::cout << "pass: " << new_tile->passable << "\n\n\n";
                //stampo le info del tile con cout
                });

			new_tile->set_hover_function([i, j, &gs]() {
                if (gs.map[i][j]->unitOn != nullptr) gs.selected_tile = gs.map[i][j];
                else{
                    gs.selected_tile = nullptr;
                }
				});

            row.push_back(new_tile);
            x += tileSize;
        }
        gs.map.push_back(row);
        y += tileSize;
    }
}

void draw_map(state& gs)
{
    for (auto& row : gs.map)
    {
        for (auto& button : row)
        {
            button->draw(gs);
        }
    }
    gs.MapLogic.current_turnState->draw(gs);
    for (auto& allay : allay_list)
    {
        allay->draw(gs.window);
    }
    for (auto& enemy : enemy_list)
    {
        enemy->draw(gs.window);
    }
}

void update_map(state& gs)
{
    for (auto& row : gs.map)
    {
        for (auto& button : row)
        {
            button->update(gs.window);
        }
    }
}

static void set_tile_sprite(Sprite& sprite, const std::string& tileType, const Vector2f& position)
{
    Vector2i tileOffset;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);

    if (tileType == "grass")
    {
        tileOffset = { dis(gen) * 16, 32 };
    }
    else if (tileType == "water")
    {
        tileOffset = { dis(gen) * 16, 0 };
    }
    else if (tileType == "mountain")
    {
        tileOffset = { dis(gen) * 16, 208 };
    }
    else
    {
        throw std::invalid_argument("tile name not valid");
    }

    sprite.setTextureRect(IntRect(tileOffset, TEXTURE_TILE_SIZE));
    sprite.setScale({ 2.48f, 2.48f });
    sprite.setPosition(position);
    sprite.move({ 0.5f, 0.5f });

}