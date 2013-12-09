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
    // Sets
    void setA(double A[]);
    void setChangedA(bool changedA);

    // Clears
    bool clearL();
    bool clearU();
    bool clearY();

    // Resets
    void resetL();
    void resetU();
    void resetY();

    // Calculations
    void calcLU();
    void applyLU();

    double
        **L, // Lower Matrix
        **U, // Upper Matrix
         *Y; // Half-way solution vector

    bool
        changedA;   // Has the value of A changed?
};

#endif // LU_H
