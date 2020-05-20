/* CSCI 261 Final Project: Zack and Kenny Go To Space
* Author: Zachary Lee
* Section B
* Author: Kenny Pham
* Section C
*/

#ifndef SFML_TEMPLATE_VECTOR2D_H
#define SFML_TEMPLATE_VECTOR2D_H


struct Vector2D {
    double x, y;
    Vector2D() : Vector2D(0, 0) {}
    Vector2D(const double x, const double y) : x(x), y(y) {}
    Vector2D &operator*=(const double &scalar);
    Vector2D operator*(const double &scalar) const;
    Vector2D &operator+=(const Vector2D &target);
    Vector2D operator-(const Vector2D &target);
    double magnitude() const;
};

#endif //SFML_TEMPLATE_VECTOR2D_H
