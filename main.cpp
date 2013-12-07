#include <iostream>
#include "EquationSystem.h"
#include "Gauss.h"
#include "lu.h"

using namespace std;

int main()
{
    double A[] =
    {
        3, 2,  4,
        1, 1,  2,
        4, 3, -2
    };

    double B[] = {1, 2, 3};

    EquationSystem s1 (A, B, 3, false, true);
    //EquationSystem m;

    //e.run();
    s1.showA();
    s1.showB();
    //s1.showX();
    s1.showP();

    return 0;
}
