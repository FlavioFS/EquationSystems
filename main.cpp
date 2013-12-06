#include <iostream>
#include "EquationSystem.h"
#include "Gauss.h"

using namespace std;

int main()
{
    double A[9] =
    {
        3, 2,  4,
        1, 1,  2,
        4, 3, -2
    };

    double B[] = {1, 2, 3};

    Gauss e (A, B, 3);
    //e.run();
    //e.showA();
    //e.showB();

    return 0;
}
