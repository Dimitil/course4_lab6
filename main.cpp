#include <iostream>
#include <typeinfo>
#include <fstream>
#include "Shape.h"
#include "Node.h"
#include "List.h"

int main()
{
    List l;

    Circle C0(15, 30, 40), C1(15, 20, 30, COLORS::WHITE), C2(20, 30, 5, COLORS::BLUE);
    Rect R;

    l.addToHead(&C0);
    l.addToHead(&C1);
    l.addToHead(&C2);
    l.addToHead(&R);
    l.selectionSort();
    std::cout << l << "\n\n";
    l.removeAll();
    std::ifstream in("in.txt");

    List a;

    in >> a;

    std::cout << a;

    std::ofstream out("out.txt");

    out << a;
    in.close();
    out.close();

    return 0;
}