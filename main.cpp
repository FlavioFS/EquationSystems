#include <iostream>
#include <cstdlib>
#include "EquationSystem.h"
#include "lu.h"

using namespace std;

int main()
{
    double A[] =
    {
        11, 12,  13, 14,
        21, 22,  23, 24,
        31, 32,  33, 34,
        41, 42,  43, 44
    };

    double B[] = {1, 2, 3, 4};

    LU s1 (A, B, 4, false, true);
    //EquationSystem m;
    s1.run();
    s1.showA();
    s1.showB();
    s1.showX();
    s1.showL();
    s1.showU();

    system("PAUSE");
    return 0;
}
