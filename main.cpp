/*	UNIVERSIDADE FEDERAL DO CEARA
/	CURSO DE COMPUTACAO
/	METODOS NUMERICOS 1
/	PROFESSOR: JOAQUIM BENTO CAVALCANTE NETO
/
/	FLAVIO FREITAS DE SOUSA			344068
/	JONAS LIMA DA SILVA				344090
/	LIVIO DE LIMA SALES				343158
/	PAULO BRUNO DE SOUSA SERAFIM	354086
*/

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

    double H[] =
    {
        1, 1, 1,
        1, 1, -1,
        2, 1, 2
    };

    //double B1[] = {16, 38, 38};
    double V[] = {6, 0, 10};

    LU s1 (H, V, 3, true, true);

    s1.showB();
    s1.showA();
    s1.run();
    s1.showY();
    s1.showX();
    s1.showP();

    system("PAUSE");
    return 0;
}
