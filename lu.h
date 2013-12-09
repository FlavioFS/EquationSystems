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
    void showY();

    // Solves the system
    // (Virtual method inherited from EquationSystem)
    void run();

protected:
    void genericConstructor(double A[], double B[], int size, bool pivoting, bool printable);

private:
    // Clears
    bool clearL();
    bool clearU();
    bool clearY();

    // Resets
    void resetL();
    void resetU();
    void resetY();

    double
        **L, // Lower Matrix
        **U, // Upper Matrix
         *Y; // Half-way solution vector
};

#endif // LU_H
