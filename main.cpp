#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <algorithm>

#include "Item.hpp"

int width = 1600;
int height = 960;
int itemSize = 2;
float itemHeight = itemSize / 2;

float speed = 1.f / 40;

std::vector<int> insertionSort(std::vector<int> arr, int index)
{
	int n = arr[index];

	int j;
	for (j = index; j > 0 && n < arr[j - 1]; j--)
	{
		arr[j] = arr[j - 1];
	}

	arr[j] = n;

	return arr;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Sorting Visualiser");
	window.setFramerateLimit(60);

	std::srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	std::vector<int> order;

	int fitsX = width / itemSize;

	for (int i = 0; i < fitsX; i++)
	{
		order.push_back(i);
	}

	std::random_shuffle(order.begin(), order.end());

	std::vector<Item> items;

	for (int i = 0; i < order.size(); i++)
	{
		sf::RectangleShape shape;
		shape.setSize(sf::Vector2f(itemSize, itemSize + (order[i] * itemHeight)));
		shape.setPosition(itemSize * i, height - shape.getSize().y);
		Item item(shape, i);
		items.push_back(item);
	}

	int index = 0;
	sf::Clock clock;

	bool started = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (clock.getElapsedTime().asSeconds() >= speed && index < fitsX)
		{
			order = insertionSort(order, index);
			index++;

			clock.restart();
		}

		items.clear();

		for (int i = 0; i < order.size(); i++)
		{
			sf::RectangleShape shape;
			shape.setSize(sf::Vector2f(itemSize, itemSize + (order[i] * (itemSize / 2))));
			shape.setPosition(itemSize * i, height - shape.getSize().y);
			Item item(shape, i);
			items.push_back(item);
		}

		window.clear();

		for (int i = 0; i < items.size(); i++)
		{
			window.draw(items[i].shape);
		}

		window.display();
	}
}