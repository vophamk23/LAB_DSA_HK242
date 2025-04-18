#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

class Character
{
protected:
    int hp;
    int x;
    int y;

public:
    // Constructor: set the values of x and y and hp to 0
    Character();
    // Constructor: set the values of hp, x and y to each parameter
    Character(int hp, int x, int y);
    // Set and get hp
    int getHp();
    void setHp(int hp);
    // Set and get x
    int getX();
    void setX(int x);
    // Set and get y
    int getY();
    void setY(int y);
    // Get Manhattan distance to other character
    int getManhattanDistTo(Character *other);
};
// Default constructor
Character::Character()
{
    hp = 0;
    x = 0;
    y = 0;
}
// Parameterized constructor
Character::Character(int hp, int x, int y)
{
    this->hp = hp;
    this->x = x;
    this->y = y;
}
// Getter for hp
int Character::getHp()
{
    return hp;
}
// Setter for hp
void Character::setHp(int hp)
{
    this->hp = hp;
}
// Getter for x
int Character::getX()
{
    return x;
}
// Setter for x
void Character::setX(int x)
{
    this->x = x;
}
// Getter for y
int Character::getY()
{
    return y;
}
// Setter for y
void Character::setY(int y)
{
    this->y = y;
}
// Calculate Manhattan distance
int Character::getManhattanDistTo(Character *other)
{
    return abs(x - other->x) + abs(y - other->y);
}