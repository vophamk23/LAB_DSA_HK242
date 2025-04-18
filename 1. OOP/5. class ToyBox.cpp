#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

// Enum for toy colors and sizes
enum Color
{
    red,
    green,
    blue
};
enum Size
{
    small,
    medium,
    big
};

class Toy
{
protected:
    double price;

public:
    Toy(double price) : price(price) {}
    virtual ~Toy() {} // Virtual destructor to ensure correct cleanup
    virtual void printType() = 0;
    friend class ToyBox;
};

class CarToy : public Toy
{
private:
    Color color;

public:
    CarToy(double price, Color color) : Toy(price), color(color) {}

    void printType() override
    {
        cout << "This is a car toy\n";
    }

    friend class ToyBox;
};

class PuzzleToy : public Toy
{
private:
    Size size;

public:
    PuzzleToy(double price, Size size) : Toy(price), size(size) {}

    void printType() override
    {
        cout << "This is a puzzle toy\n";
    }

    friend class ToyBox;
};

class ToyBox
{
private:
    Toy *toyBox[5];
    int numberOfItems;

public:
    ToyBox() : numberOfItems(0)
    {
        for (int i = 0; i < 5; i++)
        {
            toyBox[i] = nullptr; // Initialize to nullptr
        }
    }

    ~ToyBox()
    {
        for (int i = 0; i < numberOfItems; i++)
        {
            delete toyBox[i]; // Free dynamically allocated toys
        }
    }

    int addItem(const CarToy &carToy)
    {
        if (numberOfItems >= 5)
            return -1;                                // If full, return -1
        toyBox[numberOfItems++] = new CarToy(carToy); // Deep copy
        return numberOfItems;
    }

    int addItem(const PuzzleToy &puzzleToy)
    {
        if (numberOfItems >= 5)
            return -1;                                      // If full, return -1
        toyBox[numberOfItems++] = new PuzzleToy(puzzleToy); // Deep copy
        return numberOfItems;
    }

    void printBox()
    {
        for (int i = 0; i < numberOfItems; i++)
            toyBox[i]->printType();
    }
};
