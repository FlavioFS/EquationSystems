#ifndef MATRIXSYSTEM_H
#define MATRIXSYSTEM_H

#include <iostream>

class MatrixSystem
{
public:
    // Constructors
    MatrixSystem();
    MatrixSystem(double *coeficients, double *constants, int size);

    // Destructor
    ~MatrixSystem();

    // Sets
    void setCoeficients(double *coeficients);
    void setConstants(double *constants);
    void setSize(int size);

    // Solve
    void

protected:
    double
        *coeficients,
        *constants,
        *solution;

    int size;

};

#endif // MATRIXSYSTEM_H
