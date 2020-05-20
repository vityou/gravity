#include "Vector2D.h"
#include <cmath>

Vector2D & Vector2D::operator*=(const double &scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

Vector2D Vector2D::operator*(const double &scalar) const {
    return Vector2D(this->x * scalar, this->y * scalar);
}

Vector2D &Vector2D::operator+=(const Vector2D &target) {
    this->x += target.x;
    this->y += target.y;
    return *this;
}

double Vector2D::magnitude() const {
    return std::sqrt(x*x + y*y);
}

Vector2D Vector2D::operator-(const Vector2D &target) {
    return Vector2D(this->x - target.x, this->y - target.y);
}

