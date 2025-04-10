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
        {1, 1, 1, 0, 1, 1, 1, -1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, -1, -1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{ 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
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

    for (size_t i = 0; i < map.size(); ++i)
    {
        std::vector<Button> row;
        x = 0.0f;
        for (size_t j = 0; j < map[i].size(); ++j)
        {
            Vector2i tile;
            switch (map[i][j])
            {
            case 2:
                offset = dis(gen) * 16; 
                tile = { offset, 0 };
                break;
            case 3:
                offset = dis(gen) * 16;
                tile = { offset, 208 };
                break;
            default:
                offset = dis(gen) * 16; 
                tile = { offset, 32 };
                break;
            }

            Sprite grass_sprite = Sprite(texture);
            grass_sprite.setTextureRect(IntRect(tile, texture_tile_size));
            grass_sprite.setScale({ 2.48, 2.48 });
            grass_sprite.setPosition({ x, y });
            grass_sprite.move({ 0.5, 0.5 });

            Button button({ x, y }, { tileSize, tileSize }, grass_sprite);

            // Evento di prova
            button.set_click_function([i, j]() {
                std::cout << "Button clicked at (" << i << ", " << j << ")" << std::endl;
                });

            row.push_back(button);
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
            button.update(gs.window);
            button.draw(gs.window);
        }
    }
}
