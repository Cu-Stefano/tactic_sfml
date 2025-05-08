#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "TurnSM.h"
#include "attackGui.h"
#include "unit.h"
#include "SFML/Audio.hpp"
class Tile;

constexpr unsigned WINDOW_WIDTH = 1400;
constexpr unsigned WINDOW_HEIGHT = 840;

constexpr sf::Color ENEMY_ATTACK_COLOR(190, 52, 52, 190);
constexpr sf::Color ALLAY_ATTACK_COLOR(52,	151,	163, 190);
constexpr sf::Color ENEMY_PATH_COLOR(245, 130, 150, 180);
constexpr sf::Color ALLAY_PATH_COLOR(173, 220, 245, 180);
constexpr sf::Color UNIT_MOVED(135, 135, 135, 255);
constexpr sf::Color ROUTE_COLOR(0, 50, 255, 200);
constexpr sf::Color ENEMY_ROUTE_COLOR(255, 0, 50, 200);

class state
{
public:
    sf::RenderWindow window;
    const float menubar_attack_window_x = WINDOW_WIDTH - 200;
    const float menubar_attack_y = WINDOW_HEIGHT - 200;

    int turn = 0;
    sf::Text* turnNumber = nullptr;
    TurnSM TurnSM;
	AttackGui attackGui;
    std::vector<std::vector<Tile*>> map;
    Tile* selectedTile;

    sf::Font font = sf::Font("resources/font/16x16_font.ttf");
    sf::Texture ui = sf::Texture("resources/Ui/Ui_assets.png");

    sf::SoundBuffer allayBuffer = sf::SoundBuffer("resources/Sounds/allay.mp3");
    sf::SoundBuffer winBuffer = sf::SoundBuffer("resources/Sounds/win.mp3");
    sf::SoundBuffer gameoverBuffer = sf::SoundBuffer("resources/Sounds/gameover.mp3");
    sf::SoundBuffer missBuffer = sf::SoundBuffer("resources/Sounds/miss.wav");
    sf::SoundBuffer hitBuffer = sf::SoundBuffer("resources/Sounds/hit.wav");
    sf::SoundBuffer critBuffer = sf::SoundBuffer("resources/Sounds/crit.wav");
    sf::SoundBuffer clickBuffer = sf::SoundBuffer("resources/Sounds/click.wav");
    sf::SoundBuffer healBuffer = sf::SoundBuffer("resources/Sounds/heal.wav");
	sf::Sound attackSound = sf::Sound(hitBuffer);
	sf::Sound turnsoundSound = sf::Sound(allayBuffer);
	sf::Sound clickSound = sf::Sound(clickBuffer);
	sf::Sound healSound = sf::Sound(healBuffer);

	state(unsigned w, unsigned h, const std::string& title) : TurnSM(*this), attackGui(*this),
	                                                          selectedTile(nullptr)
    {
        turnsoundSound.setBuffer(allayBuffer);
        turnsoundSound.setVolume(25);
        turnsoundSound.setLooping(true);
        turnsoundSound.play();

	    window = sf::RenderWindow(sf::VideoMode({w, h}), title);
    }

    Tile* get_tile_from_mouse_position(const sf::Vector2f mousePos) const
    {
        int tileX = static_cast<int>(mousePos.x) / 40;
        int tileY = static_cast<int>(mousePos.y) / 40;
        if (isMouseOutOfRange(mousePos))
            return nullptr;
        return map[tileY][tileX];
    }

    sf::Vector2i getCoordFromTile(const Tile* tile) const
    {
        for (int i = 0; i < map.size(); ++i)
        {
            for (int j = 0; j < map[i].size(); ++j)
            {
                if (map[i][j] == tile)
                {
                    return { i, j };
                }
            }
        }
        return { -1, -1 };
    }

    bool isMouseOutOfRange(const sf::Vector2f mousePos) const
    {
       return mousePos.x >= menubar_attack_window_x || mousePos.y >= menubar_attack_y || mousePos.x < 0 || mousePos.y < 0;
    }

    static bool check_all_units_moved(int type)
	{
        if (type == 0)
        {
	        return std::all_of(allay_list.begin(), allay_list.end(), [](Unit* unit) 
			   {return !unit->canMove;});
        }

        return std::all_of(enemy_list.begin(), enemy_list.end(), [](Unit* unit)
            {return !unit->canMove; });
	}
};


