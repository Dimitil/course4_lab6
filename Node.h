#pragma once
#include <iostream>
#include "Shape.h"

class List;

class Node {

    Node* m_pPrev;
    Node* m_pNext;
    Shape* m_Shape;

public:

    Node() : m_pPrev(nullptr), m_pNext(nullptr), m_Shape(nullptr) {}

    Node(const Shape* shape, Node* prev);

    ~Node();

    friend class List;
    friend std::ostream& operator<< (std::ostream& out, const List& l);
    friend std::ofstream& operator<< (std::ofstream& out, const List& l);
};
