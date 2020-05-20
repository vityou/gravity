/* CSCI 261 Final Project: Zack and Kenny Go To Space
* Author: Zachary Lee
* Section B
* Author: Kenny Pham
* Section C
*/

#include "Planet.h"
#include <cmath>


// constructor, sets mass position, and velocity
Planet::Planet(const double mass, const Vector2D& position, const Vector2D& velocity) :
_mass(mass), _position(position), velocity(velocity)
{
    const float PI = 3.141592;
    // area = pi*r^2
    // r = sqrt(area / pi)
    _shape.setRadius(std::sqrt(_mass / PI));
    _shape.setOrigin(_shape.getRadius(), _shape.getRadius());
    _shape.setPosition(position.x, position.y);
    _shape.setFillColor(sf::Color::Green);
}

void Planet::apply_force(const Vector2D& force, const double time) {
    // F=ma=m(dv/dt)
    // dv/dt = F/m
    // dv = (F/m)*dt
    // add dv to current velocity
    velocity.x += force.x / _mass * time;
    velocity.y += force.y / _mass * time;
}

// goes forward in time and changes position based on velocity
void Planet::step(const double time) {
    _position.x += velocity.x * time;
    _position.y += velocity.y * time;
    _shape.setPosition(_position.x, _position.y);
}

// getters
double Planet::getMass() const { return _mass; }
Vector2D Planet::getPosition() const { return _position; }
sf::CircleShape Planet::getShape() const { return _shape; };
