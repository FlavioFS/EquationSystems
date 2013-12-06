#include "matrixsystem.h"

/* ==============================================================
                   Constructors and Destructor
============================================================== */
// Constructors
MatrixSystem :: MatrixSystem() {}

MatrixSystem :: MatrixSystem(double *coeficients, double *constants, int size)
{
    this->setCoeficients(coeficients);
    this->setConstants(constants);

}

// Destructor
MatrixSystem :: ~MatrixSystem()
{
    if (this->coeficients != NULL)
        delete (this->coeficients);

    if (this->constants != NULL)
        delete (this->constants);

    if (this->solution != NULL)
        delete (this->solution);

    setSize(0);
}

/* ==============================================================
                           Sets and Gets
============================================================== */
// Sets
void MatrixSystem :: setSize(int size) { this->size = size; }

void MatrixSystem :: setCoeficients(double *coeficients)
{
    try
    {
        for (int i = 0; i < size; i++)
            this->coeficients[i] = coeficients[i];
    }
    catch (...) { std::cout << "Can't load coeficients." << std::endl; };
}

void MatrixSystem :: setConstants(double *constants)
{
    try
    {
        for (int i = 0; i < size; i++)
            this->constants[i] = constants[i];
    }
    catch (...) { std::cout << "Can't load constant vector." << std::endl; };
}

// Gets
