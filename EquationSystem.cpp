#include "EquationSystem.h"

/* ==============================================================
 *                 Constructors and Destructor				   *
============================================================== */
EquationSystem::EquationSystem()
    { this->genericConstructor(NULL, NULL, 0, false, false); }

EquationSystem::EquationSystem(double A[], double B[], int size)
    { this->genericConstructor(A, B, size, false, true); }

EquationSystem::EquationSystem(double A[], double B[], int size, bool pivoting, bool printable)
    { this->genericConstructor(A, B, size, pivoting, printable); }

EquationSystem::~EquationSystem()
{
	clearA();
	clearB();

	delete (this);
}

/* C++ does not support calling constructors inside a
 * constructor. This function encapsulates the construction
 * process.
 */
void EquationSystem::genericConstructor(double A[], double B[], int size, bool pivoting, bool printable)
{
	try
	{
		// Defined in the "Clears" section below
        clearA();
        clearB();

		// New dynamic matrix to A
        this->A = new double* [size];
		for (int i = 0; i < size; i++)
            this->A[i] = new double [size];

		// New dynamic vector to B
        this->B = new double [size];

		// Attribution
		setA(A);
		setB(B);
		setSize(size);
	}
	catch (...)
	{
		setA(NULL);
		setB(NULL);
		setSize(0);
	};

	// Pivoting and Print Calculations
	setPivoting(pivoting);
	setPrintCalcs(printable);
}

/* ==============================================================
 *                          Sets and Gets					   *
============================================================== */
// Sets matrix A in this A*X = B system
void EquationSystem::setA(double A[])
{
    if (A == NULL)
    {
        this->A = NULL;
        return;
    }

    try
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
                this->A[i][j] = A[i*size + j];
        }
    }
    catch(...) { printf("Error: invalid A (coeficients).\n"); };
}

// Sets matrix B in this A*X = B system
void EquationSystem::setB(double B[])
{
    if (B == NULL)
    {
        this->B = NULL;
        return;
    }

    try
    {
        for (int i = 0; i < size; i++)
            this->B[i] = B[i];
    }
    catch(...) { printf("Error: invalid B (constants vector).\n"); };
}

/* Sets the size of A, B and X. Sets the n in:
 * 		A: n x n
 *		B: n x 1
 * 		X: n x 1
 */
void EquationSystem::setSize(int size)
{
	if (size >= 0)
		this->size = size;
}

/* Turns on/off the view of intermediate calculations in the
 * process of finding the solution.
 */
void EquationSystem::setPrintCalcs(bool printable)
	{ this->printable = printable; }

/* Turns on/off pivoting.
 * Pivoting may guarantee a better result, but will be slower.
 */
void EquationSystem::setPivoting(bool pivoting)
	{ this->pivoting = pivoting; }

/* ==============================================================
 *                            Clears     					   *
============================================================== */
// Deletes all dynamic values assigned to coeficients matrix.
void EquationSystem::clearA()
{
	if (A != NULL)
	{
		// Erasing each array in A
		for (int i = 0; i < size; i++)
			delete (A[i]);

		delete (A);
	}
}

// Deletes the dynamic value assigned to B.
void EquationSystem::clearB()
{
	if (B != NULL)
		delete (B);
}

/* ==============================================================
 *                 			 Show				               *
============================================================== */
void EquationSystem::showA()
{
    if (A == NULL)
        return;

	// Row Indexes in the first line
	printf("  ");
	for (int i = 0; i < size; i++)
	{
		printf ("  [%4d]  \t", i+1);
	}
	printf("\n");

	// Line indexes and A values
	for (int i = 0; i < size; i++)
	{
		printf("[%4d] ", i);
		for (int j = 0; j < size; j++)
		{
			printf
			(
				"%10.6lf\t", A[i][j]
			);
		}
		printf("\n");
	}
}

void EquationSystem::showB()
{
    if (B == NULL)
        return;

	for (int i = 0; i < size; i++)
	{
		printf("[%4d]\t%10.6lf\n", i, B[i]);
	}
}

void EquationSystem::showX()
{
	for (int i = 0; i < size; i++)
	{
		printf("[%4d]\t%10.6lf\n", i, X[i]);
	}
}
