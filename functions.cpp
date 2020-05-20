/* CSCI 261 Final Project: Zack and Kenny Go To Space
* Author: Zachary Lee
* Section B
* Author: Kenny Pham
* Section C
*/


#include "functions.h"
#include <cmath>
#include <iostream>
#include <mutex>

// finds force between 2 planets
Vector2D calcForceBetween(const Planet &planet, const Planet &otherPlanet) {
    // get distance
    const Vector2D rVector = otherPlanet.getPosition() - planet.getPosition();
    const double r = rVector.magnitude();

    // F = rVector * (G*m1*m2)/r^3
    // G is a constant so we can set it to any value, in this case 5 produces ok behavior

    // instead of r, we have r + (r+50)/r - 1
    // this is so when objects are very close they dont have a distance of 0
    // but when they are far apart they have a distance close to r
    const Vector2D thisForce = rVector * ((5 * planet.getMass() * otherPlanet.getMass())
                                          / std::pow(r + ((r + 50) / r) - 1, 3));
    return thisForce;
}

// calculates the force on a planet due to gravity from other planets
// given a vector of planets and the index of itself in that vector
Vector2D calcForce(std::vector<Planet> &planets, unsigned int index) {
    Vector2D force(0, 0);
    Planet &planet = planets.at(index);
    for (int i = 0; i < planets.size(); ++i) {
        if (i != index) {
            Planet &otherPlanet = planets.at(i);
            force += calcForceBetween(planet, otherPlanet);
        }
    }
    return force;
}

// redraws all planets in given vector to given window
void redraw(std::vector<Planet> &planets, sf::RenderWindow &window) {
    for (Planet &planet : planets) {
        window.draw(planet.getShape());
    }
}

std::mutex planets_m;

void forwardAll(std::vector<Planet> &planets, const bool &paused, const bool &running) {
    sf::Clock clock;
    while (running) {
        if (!paused && clock.getElapsedTime().asSeconds() > 0.001) {
            clock.restart();
            planets_m.lock();
            for (unsigned int i = 0; i < planets.size(); i++) {
                Planet &planet = planets.at(i);
                planet.apply_force(calcForce(planets, i), 0.01);
                planet.step(0.01);
            }
            planets_m.unlock();
        }
    }
}

