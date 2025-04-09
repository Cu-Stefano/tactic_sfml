#include "headers/button.h"

std::optional<Button> Button::isAnyButtonPressed = std::nullopt;

Button::Button(Vector2f Pos, Vector2f size, Sprite& spr) : sprite(spr)
{
	shape.setSize(size);
	shape.setPosition(Pos);
	shape.setFillColor(Color::Transparent);
	shape.setOutlineColor(Color::White);
	shape.setOutlineThickness(-0.5);
}

bool Button::is_pressed() const
{
    return Maptate == pressed;
}

bool Button::is_hover() const
{
    return Maptate == hover;
}

void Button::update(const RenderWindow& window)
{
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

    if (shape.getGlobalBounds().contains(mousePos))
    {
        Maptate = hover;
        shape.setOutlineColor(Color::Black);
        shape.setOutlineThickness(-2);

        if ((!isAnyButtonPressed.has_value() || isAnyButtonPressed == *this)
            && Mouse::isButtonPressed(Mouse::Button::Left))
        {
            Maptate = pressed;
            shape.setOutlineColor(Color::Red);
            shape.setOutlineThickness(-3);

            isAnyButtonPressed = *this;

            if (onClick)
            {
                onClick();
            }
        }
    }
    else
    {
        Maptate = not_pressed;
        shape.setOutlineColor(Color::White);
        shape.setOutlineThickness(-0.5);
    }

    if (!Mouse::isButtonPressed(Mouse::Button::Left))
        isAnyButtonPressed.reset();
    
}


void Button::draw(RenderWindow& window) const
{
    window.draw(sprite);
    window.draw(shape);
}

void Button::set_click_function(const std::function<void()>& func)
{
    onClick = func;
}

bool Button::operator==(const Button& other) const
{
    return shape.getPosition() == other.shape.getPosition();
	//&& sprite == other.sprite;
}

