#include <iostream>
#include "../util/IoBase.h"
#include "../util/functions.h"

using namespace std;

const double pi = 3.141593;

class CakeShape {
protected:
    double height;
public:
    virtual double volume() {
        return baseArea() * height;
    }

    virtual double baseArea() {
        return 0;
    }

    CakeShape(double height) : height(height) {}

    CakeShape() : height(0) {}
};

class SquareCake : public CakeShape {
protected:
    double side;
public:
    double baseArea() override {
        return side * side;
    }

    SquareCake(double height, double side) : CakeShape(height), side(side) {}
};

class RectangleCake : public CakeShape {
protected:
    double side1, side2;
public:
    double baseArea() override {
        return side1 * side2;
    }
    RectangleCake(double height, double side1, double side2) : CakeShape(height), side1(side1), side2(side2) {}
};

class CircleCake : virtual public CakeShape {
protected:
    double radius;
public:
    double baseArea() override {
        return pi * radius * radius;
    }
    CircleCake(double height, double radius) : CakeShape(height), radius(radius) {}
};

class ConeCake : virtual public CakeShape {
protected:
    double radius;
public:
    ConeCake(double height, double radius) : CakeShape(height), radius(radius) {}
    double baseArea() override {
        return pi * radius * radius;
    }
    double volume() override {
        return baseArea() * height / 3;
    }
};

class SpecialCake : public CircleCake, public ConeCake {
public:
    SpecialCake(double height, double radius) : CakeShape(height), CircleCake(height, radius), ConeCake(height, radius) {}
    double baseArea() {
        return ConeCake::baseArea();
    }
    double volume() override {
        return CircleCake::baseArea() * height / 2 + ConeCake::baseArea() * height / 6;
    }
};

int main() {
    // pentru prima clasa, dar si o clasa copil:
    CakeShape cake(4);
    SquareCake cube(2, 2);

    cout << cake.volume() << '\n'; // 0
    cout << cube.volume() << '\n'; // 8

    // pentru clasele derivate
    SquareCake squareCake(4, 5);
    RectangleCake rectangleCake(1, 5, 2);
    CircleCake circleCake(1, 5);

    cout << squareCake.volume() << '\n'; //     100
    cout << rectangleCake.volume() << '\n'; //  10
    cout << circleCake.volume() << '\n'; //     78.6475

    SpecialCake specialCake(6, 3);
    cout << specialCake.volume() << "\n";
    return 0;
}