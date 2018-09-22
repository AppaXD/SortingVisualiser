#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class Item
{
public:
	sf::RectangleShape shape;
	int index;
	Item(sf::RectangleShape shape, int index)
	{
		this->shape = shape;
		this->index = index;
	}
};