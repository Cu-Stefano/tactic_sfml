#include "../headers/button.h"

#include "../headers/state.h"

std::optional<Button> Button::isAnyButtonPressed = std::nullopt;

Button::Button(Vector2f Pos, Vector2f size, Sprite spr) : sprite(spr)
{
	state = not_pressed;
	shape.setSize(size);
	shape.setPosition(Pos);
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

        if ((!isAnyButtonPressed.has_value() || isAnyButtonPressed == *this)
            && Mouse::isButtonPressed(Mouse::Button::Left))
        {
            state = pressed;
            shape.setOutlineColor(Color::Red);
            shape.setOutlineThickness(-3);

            isAnyButtonPressed = *this;

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
        isAnyButtonPressed.reset();
    
}


void Button::draw(::state& gs_state) const
{
   gs_state.window.draw(sprite);
   gs_state.window.draw(shape);
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

