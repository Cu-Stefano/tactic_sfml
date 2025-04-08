#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

using namespace sf;

enum button_state
{
	not_pressed = 0,
	pressed = 1,
	hover = 2
};

class Button
{
	int Maptate;
	std::function<void()> onClick;

    public:
        static std::optional<Button> isAnyButtonPressed;
		//Sprite sprite;
        RectangleShape shape;
        Button(Vector2f Pos, Vector2f size);

		bool is_pressed() const; //averlo a const ottimiza il programma a livello del compialtore e indica che non viene modifcato alcun valore al suo interno
		bool is_hover() const;

        void update(const RenderWindow& window);
		void draw(RenderWindow& window) const;    

        // Metodo per impostare l'evento una volta che il bottone viene premuto
        void set_click_function(const std::function<void()>& func);

        bool operator==(const Button& other) const;
};