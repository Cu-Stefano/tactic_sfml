#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include <optional>
using namespace sf;

enum button_state
{
	not_pressed = 0,
	pressed = 1,
	hover = 2
};

class Button
{
	button_state state;
	std::function<void()> onClick;

    public:
        static std::optional<Button> isAnyButtonPressed;
		Sprite sprite;
        RectangleShape shape;
        Button(Vector2f Pos, Vector2f size, Sprite spr);

		bool is_pressed() const;
		bool is_hover() const;

        void update(const RenderWindow& window);
		void draw(RenderWindow& window) const;    

        //function that ggets executed when the button is clicked
        void set_click_function(const std::function<void()>& func);

        bool operator==(const Button& other) const;
};