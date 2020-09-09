#include "List.h"

void List::remove(const Shape* shape) {

    Node* iter = m_Head.m_pNext;

    while (iter != &m_Tail) {
        Node* n = iter->m_pNext;
        if (*(iter->m_Shape) == *shape) {
            delete iter;
            m_size--;
        }
        iter = n;
    }
}

void List::removeAll() {
    while (m_Head.m_pNext != &m_Tail) {
        delete m_Head.m_pNext;
    }
    m_size = 0;
}

void List::selectionSort()
{
    Node* p = m_Head.m_pNext;
    while (p != m_Tail.m_pPrev) {
        Node* minimal = p;
        Node* d = p->m_pNext;
        while (d != &m_Tail) {
            if (minimal->m_Shape->getS() > d->m_Shape->getS()) {
                minimal = d;
            }
            d = d->m_pNext;
        }
        if (minimal != p) {
            std::swap(minimal->m_Shape, p->m_Shape);
        }
        p = p->m_pNext;
    }
}

List::List(const List& other) : m_size(other.m_size) { //выделяется новая память, копирование
    m_Head.m_pNext = &m_Tail;
    m_Tail.m_pPrev = &m_Head;

    Node* pThis = &m_Head;
    Node* pOther = other.m_Head.m_pNext;
    for (size_t i = 0; i < m_size; i++)
    {
        pThis = new Node(pOther->m_Shape, pThis);
        pOther = pOther->m_pNext;
    }
}

List& List::operator=(const List& other){//память уже есть, копирование
    if (this == &other)
    {
        return *this;
    }

    m_size = other.m_size;
    Node* pThis = m_Head.m_pNext;
    Node* pOther = other.m_Head.m_pNext;

    while ((pOther != &other.m_Tail) && (pThis != &m_Tail)) {
        if (typeid(*(pOther->m_Shape)) == typeid(*(pThis->m_Shape))) {
            pThis->m_Shape = pOther->m_Shape->clone();

        }
        else {
            auto tmp = pThis;
            pThis = pThis->m_pNext;
            delete tmp;
            pThis = new Node(pOther->m_Shape, pThis->m_pPrev);
        }
        pThis = pThis->m_pNext;
        pOther = pOther->m_pNext;
    }

    while (pOther != &other.m_Tail) {
        new Node(pOther->m_Shape, m_Tail.m_pPrev);
        pOther = pOther->m_pNext;
    }

    while (pThis != &m_Tail) {
        Node* tmp = pThis;
        pThis = pThis->m_pNext;
        delete tmp;
    }

    return *this;
}


List::List(List&& other) : m_size(other.m_size) { //выделяется новая память, перемещение
    if (other.m_Head.m_pNext == &other.m_Tail) {
        m_Head.m_pNext = &m_Tail;
        m_Tail.m_pPrev = &m_Head;
    }
    else {
        m_Head.m_pNext = other.m_Head.m_pNext;
        m_Tail.m_pPrev = other.m_Tail.m_pPrev;

        m_Head.m_pNext->m_pPrev = &m_Head;
        m_Tail.m_pPrev->m_pNext = &m_Tail;

        other.m_Head.m_pNext = &other.m_Tail;
        other.m_Tail.m_pPrev = &other.m_Head;
        other.m_size = 0;
    }
}

List& List::operator=(List&& other) {//память уже есть, перемещение
    if (this == &other) {
        return *this;
    }

    removeAll();

    if (other.m_Head.m_pNext == &other.m_Tail) {
        m_size = 0;
        m_Head.m_pNext = &m_Tail;
        m_Tail.m_pPrev = &m_Head;
    }

    else {
        m_Head.m_pNext = other.m_Head.m_pNext;
        m_Tail.m_pPrev = other.m_Tail.m_pPrev;

        m_Head.m_pNext->m_pPrev = &m_Head;
        m_Tail.m_pPrev->m_pNext = &m_Tail;

        other.m_Head.m_pNext = &other.m_Tail;
        other.m_Tail.m_pPrev = &other.m_Head;
        other.m_size = 0;
    }

    return *this;
}

std::ifstream& operator>>(std::ifstream& in, List& l) {
    int par1, par2, par3, par4;
    unsigned int col;
    char ch;

    while (in.get(ch)) {
        if (ch == 'C') {
            in >> par1 >> par2 >> par3 >> col;
            Circle* tmp = new Circle(par1, par2, par3, static_cast<COLORS>(col));
            l.addToTail(tmp);
        }
        if (ch == 'R') {
            in >> par1 >> par2 >> par3 >> par4 >> col;
            Rect* tmp = new Rect(par1, par2, par3, par4, static_cast<COLORS>(col));
            l.addToTail(tmp);
        }
    }

    return in;
}

std::ofstream& operator<< (std::ofstream& out, const List& l) {
    Node* it = l.m_Head.m_pNext;
    while (it != &l.m_Tail) {
        if (typeid(*(it->m_Shape)) == typeid(Circle)) {
            Circle* itC = dynamic_cast<Circle*>(it->m_Shape->clone());
            out << 'C' << ' ' << itC->m_xCenter << ' ' << itC->m_yCenter << ' '
                << itC->m_rad << ' ' << it->m_Shape->m_color << '\n';
            delete itC;
        }
        if (typeid(*(it->m_Shape)) == typeid(Rect)) {
            Rect* itR = dynamic_cast<Rect*>(it->m_Shape->clone());
            out << 'R' << ' ' << itR->m_x1 << ' ' << itR->m_y1 << ' '
                << itR->m_x2 << ' ' << itR->m_y2 << ' ' << it->m_Shape->m_color << '\n';
            delete itR;
        }

        it = it->m_pNext;
    }
    return out;
}

std::ostream& operator<< (std::ostream& out, const List& l) {
    if (l.m_size == 0) {
        return out;
    }
    Node* it = l.m_Head.m_pNext;
    while (it != &l.m_Tail) {

        if (typeid(*(it->m_Shape)) == typeid(Rect)) {
            out << *(dynamic_cast<Rect*>(it->m_Shape));
        }
        else {
            out << *(dynamic_cast<Circle*>(it->m_Shape));
        }

        it = it->m_pNext;
    }
    return out;
}