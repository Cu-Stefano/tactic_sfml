#include "../headers/mapBuilder.h"
#include <iostream>
#include <random>

const Texture texture("resources/Tiles/FullTileset.png");
constexpr Vector2i texture_tile_size(16, 16);

std::vector<std::vector<int>> map_generator()
{
    return
    {
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
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
		{ 1, 1, 0, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1},
        { 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
}

void initialize_Map(state& gs)
{
    float tileSize = 40.0f;
    float x = 0.0f, y = 0.0f;

    auto map = map_generator();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    int offset;
    int allay_index = 0;
    int enemy_index = 1;

    for (size_t i = 0; i < map.size(); ++i)
    {
        std::vector<Tile> row;
        x = 0.0f;
        
        for (size_t j = 0; j < map[i].size(); ++j)
        {
            sf::Vector2i tile;
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
                walkable = true;
                break;
            case -1:
                //enemy
                unit = enemy_list.at(enemy_index);
                unit->set_sprite_pos({ static_cast<int>(x), static_cast<int>(y) });
                enemy_index++;

                tileName = "grass";
                walkable = true;
                break;
			case 0:
                //alleato
                unit = allay_list.at(allay_index);
                unit->set_sprite_pos({ static_cast<int>(x), static_cast<int>(y) });
                allay_index++;

                tileName = "grass";
                walkable = true;
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

            sf::Sprite grass_sprite = sf::Sprite(texture);
			set_tile_sprite(grass_sprite, tileName, { x, y });

            Tile new_tile(tileName, walkable, unit, { x, y }, { tileSize, tileSize }, grass_sprite);

            // Evento di prova
            new_tile.set_click_function([i, j]() {
                std::cout << "Tile clicked at (" << i << ", " << j << ")" << std::endl;
                });

			new_tile.set_hover_function([i, j, &gs]() {
                if (gs.Map[i][j].UnitOn != nullptr) gs.selected_tile = &gs.Map[i][j];
                else{
                    gs.selected_tile = nullptr;
                }
				});

            row.push_back(new_tile);
            x += tileSize;
        }
        gs.Map.push_back(row);
        y += tileSize;
    }
}

void draw_map(state& gs)
{
    for (auto& row : gs.Map)
    {
        for (auto& button : row)
        {
            button.draw(gs.window);
        }
    }

    for (auto allay : allay_list)
    {
        allay->draw(gs.window);
    }
    for (auto enemy : enemy_list)
    {
        enemy->draw(gs.window);
    }


}

void update_map(state& gs)
{
    for (auto& row : gs.Map)
    {
        for (auto& button : row)
        {
            button.update(gs.window);
        }
    }

    for (auto allay : allay_list)
    {
        allay->update();
    }
    for (auto enemy : enemy_list)
    {
        enemy->update();
    }
}

static void set_tile_sprite(sf::Sprite& sprite, const std::string& tileType, const sf::Vector2f& position)
{
    sf::Vector2i tileOffset;

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

    sprite.setTextureRect(sf::IntRect(tileOffset, texture_tile_size));
    sprite.setScale({ 2.48f, 2.48f });
    sprite.setPosition(position);
    sprite.move({ 0.5f, 0.5f });

}