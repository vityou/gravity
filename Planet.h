/* CSCI 261 Final Project: Zack and Kenny Go To Space
* Author: Zachary Lee
* Section B
* Author: Kenny Pham
* Section C
*/


#ifndef PLANET_H
#define PLANET_H

#include <SFML/Graphics/CircleShape.hpp>
#include "Vector2D.h"

class Planet {
public:
    Planet(double mass, const Vector2D& position, const Vector2D& velocity);
    void apply_force(const Vector2D& force, double time);
    void step(double time);
    double getMass() const ;
    Vector2D getPosition() const ;
    sf::CircleShape getShape() const ;
    Vector2D velocity;
private:
    Vector2D _position;
    double _mass;
    sf::CircleShape _shape;
};

#endif