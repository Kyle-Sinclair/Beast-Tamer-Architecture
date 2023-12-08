#include "Vector.h"

#include <chrono>

Vector::Vector(float x, float y, float z)
{
}

bool Vector::operator==(const Vector& rhs)
{
    return x == rhs.x && y == rhs.y && z == rhs.z;
}

void Vector::operator-=(const Vector& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
}
Vector Vector::operator+(const Vector& rhs)const
{
    return {x + rhs.x, y + rhs.y, z + rhs.z};
}

Vector Vector::operator-(const Vector& rhs)const
{
    return {x - rhs.x, y - rhs.y, z - rhs.z};
}

float Vector::operator*(const Vector& rhs)const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

void Vector::operator+=(const Vector& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
}
