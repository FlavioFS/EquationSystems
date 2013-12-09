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

    // Prints
    void showL();
    void showU();

protected:
    void genericConstructor(double A[], double B[], int size, bool pivoting, bool printable);

    // Solves the system
    // (Virtual method inherited from EquationSystem)
    void run();

private:
    // Clears
    bool clearL();
    bool clearU();

    // Resets
    void resetL();
    void resetU();

    double
        **L, // Lower Matrix
        **U; // Upper Matrix
};

#endif // LU_H
