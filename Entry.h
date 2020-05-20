/* CSCI 261 Final Project: Zack and Kenny Go To Space
* Author: Zachary Lee
* Section B
* Author: Kenny Pham
* Section C
*/

#ifndef SFML_TEMPLATE_ENTRY_H
#define SFML_TEMPLATE_ENTRY_H

#include <sstream>
#include <SFML/Graphics.hpp>
#include "Vector2D.h"

class Entry {
public:
    Entry();
    explicit Entry(const Vector2D& position);
    bool done() const;
    Vector2D getVelocity() const ;
    double getMass() const ;
    Vector2D getPosition() const ;
    void addChar(char c);
    void removeChar();
    void next();
    void draw(sf::RenderWindow& window);
    static void setFont(const sf::Font &font);
private:
    bool _massDone, _xVelocityDone, _yVelocityDone;
    Vector2D _position;
    std::string _mass, _xVelocity, _yVelocity;
    static sf::Font _font;
    sf::Text _displayText;
};

#endif //SFML_TEMPLATE_ENTRY_H
