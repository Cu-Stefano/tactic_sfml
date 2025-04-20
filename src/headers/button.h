#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

using sf::Sprite, sf::RectangleShape, sf::Vector2f, sf::RenderWindow;

class state;
enum button_state
{
	not_pressed = 0,
	pressed = 1,
	hover = 2
};

class Button
{
	button_state state;

    public:
		//functions that gets executed when the the events trigger
		std::function<void()> onClick;
		std::function<void()> onHover;

		bool isAnotherButtonPressed = true;
		Sprite sprite;
        RectangleShape shape;
        Button(Vector2f pos, Vector2f size, Sprite spr);

		bool is_pressed() const;
		bool is_released() const;
		bool is_hover() const;

        void update(const RenderWindow& window);
		void draw(::state& gsState) const;    

		
        void set_click_function(const std::function<void()>& func);
        void set_hover_function(const std::function<void()>& func);

        bool operator==(const Button& other) const;
};


