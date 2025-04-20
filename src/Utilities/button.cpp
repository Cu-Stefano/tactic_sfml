#include "../headers/button.h"
#include "../headers/state.hpp"
using namespace sf;

Button::Button(Vector2f pos, Vector2f size, Sprite spr) : sprite(spr)
{
	state = not_pressed;
	shape.setSize(size);
	shape.setPosition(pos);
	shape.setFillColor(Color::Transparent);
	shape.setOutlineColor(Color(0, 0, 10, 255));
	shape.setOutlineThickness(-0.5);
}

bool Button::is_pressed() const
{
    return state == pressed;
}

bool Button::is_hover() const
{
    return state == hover;
}

void Button::update(const RenderWindow& window)
{
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

    if (shape.getGlobalBounds().contains(mousePos))
    {
        state = hover;
        shape.setOutlineColor(Color::Black);
        shape.setOutlineThickness(-2);

        if (isAnotherButtonPressed && Mouse::isButtonPressed(Mouse::Button::Left))
        {
            state = pressed;
            shape.setOutlineThickness(-2.5);

            isAnotherButtonPressed = false;

            if (onClick)
            {
                onClick();
            }
        }

        if (onHover)
        {
            onHover();
        }
    }
    else
    {
        state = not_pressed;
        shape.setOutlineColor(Color(255, 255, 255, 75));
        shape.setOutlineThickness(-0.5);
    }

    if (!Mouse::isButtonPressed(Mouse::Button::Left))
        isAnotherButtonPressed = true;
    
}


void Button::draw(::state& gsState) const
{
   gsState.window.draw(sprite);
   gsState.window.draw(shape);
}

void Button::set_click_function(const std::function<void()>& func)
{
    onClick = func;
}

void Button::set_hover_function(const std::function<void()>& func)
{
	onHover = func;
}

bool Button::operator==(const Button& other) const
{
    return shape.getPosition() == other.shape.getPosition();
}
