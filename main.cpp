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

    LU s1 (A, B, 3, true, true);
    s1.run();
    s1.showY();
    s1.showX();

    system("PAUSE");
    return 0;
}
