#include <iostream>
#include <cstdlib>
#include "EquationSystem.h"
#include "lu.h"

using namespace std;

int main()
{
    double A[] =
    {
        3, 2,  4, 1,
        1, 1,  2, 1,
        4, 3, -2, 1,
        5, 7,  9, 4
    };

    double B[] = {1, 2, 3, 1};

    LU s1 (A, B, 4, false, true);
    //EquationSystem m;

    //e.run();
    s1.showA();
    s1.showB();
    s1.showX();
    s1.showP();

    system("PAUSE");
    return 0;
}
