#pragma once
#include <iostream>
#include <fstream>
#include "Shape.h"
#include "Node.h"

class List {

    Node m_Head;
    Node m_Tail;
    size_t m_size;

public:

    List() : m_size(0) {
        m_Head.m_pNext = &m_Tail;
        m_Tail.m_pPrev = &m_Head;
    }

    size_t size() const {
        return m_size;
    }

    void addToHead(const Shape* shape) {
        new Node(shape, &m_Head);
        m_size++;
    }

    void addToTail(const Shape* shape) {
        new Node(shape, m_Tail.m_pPrev);
        m_size++;
    }

    void remove(const Shape* shape);

    void removeAll();

    void selectionSort();

    List(const List& other);

    List& operator=(const List& other);

    List(List&& other);

    List& operator=(List&& other);

    ~List() {
        while (m_Head.m_pNext != &m_Tail)
        {
            delete m_Head.m_pNext;
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const List& l);
    friend std::ofstream& operator<<(std::ofstream& out, const List& l);
    friend std::ifstream& operator>>(std::ifstream& in, List& l);
};
