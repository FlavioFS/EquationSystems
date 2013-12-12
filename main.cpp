#include <iostream>
#include <cstdlib>
#include "EquationSystem.h"
#include "lu.h"

using namespace std;

int main()
{
    /*double A1[] =
    {
        20, 7, 9,
        7, 30, 8,
        9, 8, 30
    };*/

    double A2[] =
    {
        1, 1, 1,
        1, 1, -1,
        2, 1, 2
    };

    //double B1[] = {16, 38, 38};
    double B2[] = {6, 0, 10};

    LU s1 (A2, B2, 3, true, true);

    s1.showB();
    s1.showA();
    s1.run();
    s1.showY();
    s1.showX();
    s1.showP();

    system("PAUSE");
    return 0;
}
