#ifndef LU_H
#define LU_H

#include "EquationSystem.h"

class LU : public EquationSystem
{
public:
    LU();
    LU(double A[], double B[], int size);
    LU(double A[], double B[], int size, bool pivoting, bool printable);
    ~LU();

protected:
    // Solves the system
    // (Virtual method inherited from EquationSystem)
    void run();

private:
    void calcL();
    void calcU();

    double
        **L, // Lower Matrix
        **U; // Upper Matrix
};

#endif // LU_H
