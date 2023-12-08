#pragma once

struct Vector
{
public:
    float x;
    float y;
    float z;
    
    Vector(float x = 0,float y = 0,float z = 0);
    bool operator==(const Vector &rhs);
    void operator+=(const Vector &rhs);
    void operator-=(const Vector &rhs);
    Vector operator+(const Vector &rhs)const;
    Vector operator-(const Vector &rhs)const;
    float operator*(const Vector &rhs)const;
};
