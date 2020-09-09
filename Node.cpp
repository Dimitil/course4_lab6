#include "Node.h"

Node::Node(const Shape* shape, Node* prev) {
    m_pPrev = prev;
    m_pNext = m_pPrev->m_pNext;
    m_pPrev->m_pNext = this;
    m_pNext->m_pPrev = this;

    /*if (typeid(*shape) == typeid(Circle)) {
        m_Shape = new  Circle(*static_cast<const Circle*>(shape));
    }
    else m_Shape = new Rect();*/
    m_Shape = shape->clone();
}

Node::~Node() {
    delete m_Shape;
    m_Shape = nullptr;
    if (m_pPrev)	m_pPrev->m_pNext = m_pNext;
    if (m_pNext) m_pNext->m_pPrev = m_pPrev;
    m_pNext = nullptr;
    m_pPrev = nullptr;
}
