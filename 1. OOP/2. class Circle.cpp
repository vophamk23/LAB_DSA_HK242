#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

class Point
{
private:
    double x, y;

public:
    Point()
    {
        /*
         * STUDENT ANSWER
         * TODO: set zero x-y coordinate
         */
        this->x = 0.0;
        this->y = 0.0;
    }

    Point(double x, double y)
    {
        /*
         * STUDENT ANSWER
         */
        this->x = x;
        this->y = y;
    }

    void setX(double x)
    {
        /*
         * STUDENT ANSWER
         */
        this->x = x;
    }

    void setY(double y)
    {
        /*
         * STUDENT ANSWER
         */
        this->y = y;
    }

    double getX() const
    {
        /*
         * STUDENT ANSWER
         */
        return this->x;
    }

    double getY() const
    {
        /*
         * STUDENT ANSWER
         */
        return this->y;
    }

    double distanceToPoint(const Point &pointA)
    {
        /*
         * STUDENT ANSWER
         * TODO: calculate the distance from this point to point A in the coordinate plane
         */
        return sqrt(pow(this->x - pointA.getX(), 2) + pow(this->y - pointA.getY(), 2));
    }
};

class Circle
{
private:
    Point center;
    double radius;

public:
    // Default constructor: Initializes center at (0,0) and radius 0
    Circle()
    {
        this->center = Point(0, 0);
        this->radius = 0.0;
    }

    // Parameterized constructor
    Circle(Point center, double radius)
    {
        this->center = center;
        this->radius = radius > 0 ? radius : 0; // Ensure radius is non-negative
    }

    // Copy constructor
    Circle(const Circle &circle)
    {
        this->center = circle.center;
        this->radius = circle.radius;
    }

    // Setter for center
    void setCenter(Point point)
    {
        this->center = point;
    }

    // Setter for radius
    void setRadius(double radius)
    {
        if (radius >= 0)
            this->radius = radius;
    }

    // Getter for center
    Point getCenter() const
    {
        return this->center;
    }

    // Getter for radius
    double getRadius() const
    {
        return this->radius;
    }

    // Print circle details
    void printCircle()
    {
        printf("Center: {%.2f, %.2f} and Radius %.2f\n", this->center.getX(), this->center.getY(), this->radius);
    }
};