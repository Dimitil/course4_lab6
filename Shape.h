#pragma once
#include <iostream>

class List;
const double Pi = 3.14;

enum COLORS {
    RED,
    GREEN,
    BLUE,
    WHITE,
    BLACK
};

class Shape {
    COLORS m_color;

public:

    Shape(COLORS color) : m_color(color)
    {}

    virtual double getS() const = 0;

    virtual Shape* clone() const = 0;

    virtual bool operator==(const Shape& shape) const {
        return m_color == shape.m_color;
    }

    const char* getColor() const;

    friend std::ofstream& operator<< (std::ofstream& out, const List& l);

};


class Rect : public Shape {
    int m_x1, m_y1, m_x2, m_y2;

public:
    Rect(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, COLORS color = COLORS::BLACK);

    virtual double getS() const override {
        return static_cast<double>((m_y2 - m_y1) * (m_x2 - m_x1));
    }

    virtual bool operator==(const Shape& shape) const;

    virtual Shape* clone() const override {
        return new Rect(*this);
    }

    friend std::ofstream& operator<< (std::ofstream& out, const List& l);

    friend std::ostream& operator<< (std::ostream& out, const Rect& r);
};

class Circle : public Shape {

    int m_xCenter, m_yCenter;
    int m_rad;

public:
    Circle(int xCenter = 0, int yCenter = 0, int rad = 0, 
        COLORS color = COLORS::BLACK);

    virtual double getS() const override {
        return Pi * m_rad * m_rad;
    }

    virtual bool operator==(const Shape& shape) const;

    virtual Shape* clone() const override {
        return new Circle(*this);
    }

    friend std::ofstream& operator<< (std::ofstream& out, const List& l);

    friend std::ostream& operator<< (std::ostream& out, const Circle& c);
};