#ifndef EQUATIONSYSTEM_H
#define EQUATIONSYSTEM_H

#include <stdio.h>
#include <iostream>

/* Solves a system A*X = B, where:
 * A, B and X are matrices.
 * A is n x n sized coeficients.
 * B is n x 1 sized constants vector.
 * X is n x 1 sized solution.
 */
class EquationSystem
{
public:
	// Constructors
	EquationSystem();
    EquationSystem(double A[], double B[], int size);
    EquationSystem(double A[], double B[], int size, bool pivoting, bool printable);

	// Destructor
    ~EquationSystem();
	
	// Sets
    void setA(double A[]);
    void setB(double B[]);
    void setSize(int size);
	void setPrintCalcs(bool printable);
	void setPivoting(bool pivoting);

	// Prints
	void showA();
	void showB();
    void showX();
    void showP();

	// Solve system
    //virtual void run() = 0;

protected:
    void genericConstructor(double A[], double B[], int size, bool pivoting, bool printable);

    // Fa�ade sets
    void setP(int X[]);
    void setX(double X[]);

    // Clears
	void clearA();
	void clearB();
    void clearX();
    void clearP();

    // Pivoting
    void resetP();

	// A*X = B
	double
        **A,    // Coeficients
         *B,	// Constants vector
         *X;	// Solution
	
	int
        size, 	// Order of the system (number or equations)
         **P;   // Pivoting matrix

	bool
		printable,
		pivoting;
};

#endif
