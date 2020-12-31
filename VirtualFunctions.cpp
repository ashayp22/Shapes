// VirtualFunctions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include "Constants.h"

class Shape {
public:
    //pure virtual print function
    virtual std::ostream& print(std::ostream& out) const = 0;

	//purse virtual function for calculating area
	virtual float getArea() const = 0; 
       
    //overloading << operator
    friend std::ostream& operator<<(std::ostream& out, const Shape& p) {
        return p.print(out);
    }

    //defualt destructor
	virtual ~Shape() = default;

};

class Point
{
private:
	int m_x{ 0 };
	int m_y{ 0 };
	int m_z{ 0 };

public:
	Point(int x, int y, int z)
		: m_x{ x }, m_y{ y }, m_z{ z } // always directly initialize our member variables
	{

	}

	//overloading << operator
	friend std::ostream& operator<<(std::ostream& out, const Point& p)
	{
		out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ')';
		return out;
	}


	int getX() const {
		return m_x;
	}

	int getY() const {
		return m_y;
	}

	int getZ() const {
		return m_z;
	}

};


class Triangle : public Shape {
private:
	Point m_point1;
	Point m_point2;
	Point m_point3;
public:
	Triangle(const Point& point1, const Point& point2, const Point& point3) : m_point1{ point1 }, m_point2{ point2 }, m_point3{ point3 } // directly initialize our member variables
	{

	}

	//overloading print method
	virtual std::ostream& print(std::ostream& out) const override {
		out << "Triangle(" << m_point1 << ", " << m_point2 << ", " << m_point3 << ")";
		return out;
	}

	//overloading area method
	virtual float getArea() const override {

		//here, we use cross product to determine the area of the triangle

		//construct two vectors
		int vect_A[] = { m_point2.getX() - m_point1.getX(), m_point2.getY() - m_point1.getY(), m_point2.getZ() - m_point1.getZ() };
		int vect_B[] = { m_point3.getX() - m_point1.getX(), m_point3.getY() - m_point1.getY(), m_point3.getZ() - m_point1.getZ() };
		int cross_P[3];

		//find the cross product
		math::crossProduct(vect_A, vect_B, cross_P);
			
		//return half the magnitude of the resultant vector
		return sqrt(cross_P[0] * cross_P[0] + cross_P[1] * cross_P[1] + cross_P[2] * cross_P[2]) / 2;
	}

};

class Circle : public Shape {
private:
	Point m_center;
	int m_radius;
public:
	Circle(const Point& center, int radius) : m_center{ center }, m_radius{ radius } // always directly initialize our member variables
	{

	}

	//overloading print method
	virtual std::ostream& print(std::ostream& out) const override {
		out << "Circle(" << m_center << ", radius " << m_radius << ")";
		return out;
	}

	int getRadius() const { //constant function
		return m_radius;
	}

	//overloading area method
	virtual float getArea() const override {
		return math::Pi * m_radius * m_radius; //pi * r^2 is the area of a circle
	}

};

int getLargestRadius(const std::vector<Shape*> &v) { //pass in a reference to the std::vector
	int largestRadius{ 0 };

	for (const auto* shape : v) {
		//check if the shape is a circle

		const Circle* circle{ dynamic_cast<const Circle*>(shape) }; //use dynamic cast to convert Shape pointer into Circle pointer

		if (circle) { //make sure circle is non-null
			int newRadius{ circle->getRadius() };
			if (newRadius > largestRadius) { //found a larger radius
				largestRadius = newRadius; //assign radius
			}
		}

	}

	return largestRadius;
}


int main()
{
	std::vector<Shape*> v{
	  new Circle{Point{1, 2, 3}, 7},
	  new Triangle{Point{1, 2, 3}, Point{-4, 5, -6}, Point{7, 8, 9}},
	  new Circle{Point{4, 5, 6}, 3}
	};

	// print each shape in vector v on its own line here

	for (const auto *shape : v) {
		std::cout << *shape << " has an area of " << shape->getArea() << "\n"; //gets value from pointer and prints it out
	}

	std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // write this function


	// delete each element in the vector here

	for (const auto* shape : v) { //use auto for iterators
		delete shape;
	}

	return 0;

}

