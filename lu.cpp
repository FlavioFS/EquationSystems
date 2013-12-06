#include "lu.h"

/* ==============================================================
 *                 Constructors and Destructor				   *
============================================================== */
LU::LU()
    { this->genericConstructor(NULL, NULL, 0, false, true); }

LU::LU(double A[], double B[], int size)
    { this->genericConstructor(A, B, size, false, true); }

LU::LU(double A[], double B[], int size, bool pivoting, bool printable)
    { this->genericConstructor(A, B, size, pivoting, printable); }

LU::~LU()
{
    this->clearA();
    this->clearB();

    delete(this);
}

/* ==============================================================
 *                 		Solving the system                     *
============================================================== */
void LU::run()
{
    bool invalid = false;

    if (A == NULL)
    {
        printf("Error: A is NULL\n");
        invalid = true;
    }

    if (B == NULL)
    {
        printf("Error: B is NULL\n");
        invalid = true;
    }

    if (pivoting) return;

    if(invalid) return;

    for (int step = 0; step < size; step++)
    {
        for (int i = step+1; i < size; i++)
        {
            double ratio = A[i][step]/A[step][step];

            for (int j = step; j < size; j++)
                A[i][j] -= ratio*A[step][j];

            B[i] -= ratio*B[step];
        }
    }

}
