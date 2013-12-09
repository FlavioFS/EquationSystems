#include <iostream>
#include <cstdlib>
#include "EquationSystem.h"
#include "lu.h"

using namespace std;

int main()
{
    double A[] =
    {
        20, 7, 9,
        7, 30, 8,
        9, 8, 30
    };

    double B[] = {16, 38, 38};

    LU s1 (A, B, 3, false, true);
    //EquationSystem m;
    s1.run();
    s1.showB();
    s1.showX();
    s1.showL();
    s1.showU();

    system("PAUSE");
    return 0;
}
