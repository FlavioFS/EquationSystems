#ifndef EQUATIONSYSTEM_H
#define EQUATIONSYSTEM_H

#define NOMAXFOUND -1

#include <cstdio>
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
    virtual void run() = 0;

    // Utility
    double abs(double x);

protected:
    void genericConstructor(double A[], double B[], int size, bool pivoting, bool printable);

    // Façade sets
    void setP(int X[]);
    void setX(double X[]);
    void setSparse(bool sparse);

    // Clears
    bool clearA();
    bool clearB();
    bool clearX();
    bool clearP();

    // Resets
    void resetP();
    void resetX();

    // Pivoting - Overloaded method
    void swapLines(double **M, int i1, int i2);
    void swapLines(int    **M, int i1, int i2);
    void swapLines(double  *M, int i1, int i2);
    void swapLines(int     *M, int i1, int i2);

    int findMax(double **M, int min, int j);
    void pivotX();

    // Utility
    void multiply(int **M, double *V);

	// A*X = B
	double
        **A,    // Coeficients
         *B,	// Constants vector
         *X;	// Solution
	
	int
        size, 	// Order of the system (number or equations)
         **P;   // Pivoting matrix

	bool
        printable,  // Toggles visibility of method private calculations
        pivoting,   // Toggles pivoting (better results, but slower)
        sparse;     // Is this system sparse?
};

#endif
