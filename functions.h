/* CSCI 261 Final Project: Zack and Kenny Go To Space
* Author: Zachary Lee
* Section B
* Author: Kenny Pham
* Section C
*/


#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include "Planet.h"
#include <SFML/Graphics.hpp>

Vector2D calcForce(std::vector<Planet>& planets, unsigned int index);

void redraw(std::vector<Planet>& planets, sf::RenderWindow& window);

void forwardAll(std::vector<Planet> &planets, const bool &paused, const bool &running);

#endif