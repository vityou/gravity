/* CSCI 261 Final Project: Zack and Kenny Go To Space
* Author: Zachary Lee
* Section B
* Author: Kenny Pham
* Section C
*/

#include "Entry.h"

Entry::Entry() : Entry(Vector2D(0, 0)) {}

// create new entry at position
Entry::Entry(const Vector2D& position)
    : _position(position)
    , _massDone(false)
    , _xVelocityDone(false)
    , _yVelocityDone(false)
{
    _displayText.setPosition(_position.x, _position.y);
    _displayText.setFont(Entry::_font);
    _displayText.setCharacterSize(24);
    _displayText.setFillColor(sf::Color::Red);
    _displayText.setStyle(sf::Text::Bold);
}
// check if entry is complete
bool Entry::done() const { return _massDone && _xVelocityDone && _yVelocityDone; };

Vector2D Entry::getVelocity() const {
    Vector2D velocity;
    std::stringstream stream;
    stream << _xVelocity;
    stream >> velocity.x;
    stream.str("");
    stream << _yVelocity;
    stream >> velocity.y;
    return velocity;
}
double Entry::getMass() const {
    double massNumber;
    std::stringstream stream;
    stream << _mass;
    stream >> massNumber;
    return massNumber;
}

Vector2D Entry::getPosition() const { return _position; }

// adds character to current field
void Entry::addChar(char c) {
    if (!_massDone) {
        _mass.push_back(c);
    } else if (!_xVelocityDone) {
        _xVelocity.push_back(c);
    } else {
        _yVelocity.push_back(c);
    }
}

// remove character from current field
void Entry::removeChar() {
    if (!_massDone) {
        _mass = _mass.substr(0, _mass.size() - 1);
    } else if (!_xVelocityDone) {
        _xVelocity.pop_back();
    } else {
        _yVelocity.pop_back();
    }
}

// goes to next entry field
void Entry::next() {
    if (!_massDone) {
        _massDone = true;
    } else if (!_xVelocityDone) {
        _xVelocityDone = true;
    } else {
        _yVelocityDone = true;
    }
}

// draws itself to window
void Entry::draw(sf::RenderWindow& window) {
    //std::cout << "Draw called" << std::endl;
    //std::cout << mass << std::endl;
    std::stringstream stream;
    stream << "Mass: " << _mass;
    if (!_massDone) {
        stream << "|";
    }
    stream << std::endl;
    stream << "X Velocity: " << _xVelocity;
    if (_massDone && !_xVelocityDone) {
        stream << "|";
    }
    stream << std::endl;
    stream << "Y Velocity: " << _yVelocity;
    if (_xVelocityDone && !_yVelocityDone) {
        stream << "|";
    }
    stream << std::endl;
    _displayText.setString(stream.str());

    window.draw(_displayText);
}

sf::Font Entry::_font;

void Entry::setFont(const sf::Font &newFont) {
    Entry::_font = newFont;
}
