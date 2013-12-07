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
    clearX();
    clearP();
}

/* C++ does not support calling constructors inside a
 * constructor. This function encapsulates the construction
 * process.
 */
void EquationSystem::genericConstructor(double A[], double B[], int size, bool pivoting, bool printable)
{
    setSize(0);
    setA(NULL);
    setB(NULL);
    setP(NULL);

	try
	{
		// Attribution
        setSize(size);
        setA(A);
		setB(B);
	}
    catch (...) { /* Keeps NULL */ };

	// Pivoting and Print Calculations
	setPivoting(pivoting);
	setPrintCalcs(printable);
    resetP();
}

/* ==============================================================
 *                          Sets and Gets					   *
============================================================== */
// Sets matrix A in this A*X = B system
void EquationSystem::setA(double A[])
{
    try
    {
        clearA();

        // NULL case
        if (A == NULL)
        {
            this->A = NULL;
            return;
        }

        // New dynamic matrix to A
        this->A = new double* [size];
        for (int i = 0; i < size; i++)
            this->A[i] = new double [size];

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
    try
    {
        clearB();

        // NULL case
        if (B == NULL)
        {
            this->B = NULL;
            return;
        }

        // New dynamic vector to B
        this->B = new double [size];

        for (int i = 0; i < size; i++)
            this->B[i] = B[i];
    }
    catch(...) { printf("Error: invalid B (constants vector).\n"); };
}

// Sets matrix X in this A*X = B system
void EquationSystem::setX(double X[])
{
    try
    {
        clearX();

        // NULL case
        if (X == NULL)
        {
            this->X = NULL;
            return;
        }

        // New dynamic vector to B
        this->X = new double [size];

        for (int i = 0; i < size; i++)
            this->X[i] = X[i];
    }
    catch(...) { printf("Error: invalid X (solutions).\n"); };
}

// Sets pivoting matrix P (Façade)
void EquationSystem::setP(int P[])
{
    try
    {
        clearP();

        // NULL case
        if (P == NULL)
        {
            this->P = NULL;
            return;
        }

        // New dynamic matrix to P
        this->P = new int* [size];
        for (int i = 0; i < size; i++)
            this->P[i] = new int [size];

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
                this->P[i][j] = P[i*size + j];
        }
    }
    catch(...) { printf("Error: invalid P (pivoting).\n"); };
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

// Deletes the dynamic value assigned to X.
void EquationSystem::clearX()
{
    if (X != NULL)
        delete (X);
}

// Loads identity to pivoting matrix P (Façade).
void EquationSystem::clearP()
{
    if (P != NULL)
    {
        // Erasing each array in P
        for (int i = 0; i < size; i++)
            delete (P[i]);

        delete (P);
    }
}

/* ==============================================================
 *                 			   Show				               *
============================================================== */
void EquationSystem::showA()
{
    if (A == NULL)
    {
        printf("A is NULL\n");
        return;
    }

    // Row Indexes in the first line
    printf("================ A =================\n"
           "       ");
    for (int i = 0; i < size; i++)
    {
        printf ("   %4d     ", i+1);
    }
    printf("\n"
           "     ");
    for (int i = 0; i < size; i++)
    {
        printf ("____________");
    }
    printf("\n");

    // Line indexes and A values
    for (int i = 0; i < size; i++)
    {
        printf("%4d|", i);
        for (int j = 0; j < size; j++)
        {
            printf
            (
                "  %10lf", A[i][j]
            );
        }
        printf("\n");
    }
    printf("\n");
}

void EquationSystem::showB()
{
    if (B == NULL)
    {
        printf("B is NULL\n");
        return;
    }

    printf("================ B =================\n"
           "     ______________\n");

    for (int i = 0; i < size; i++)
	{
        printf("%4d|  %10lf\n", i, B[i]);
	}
    printf("\n");
}

void EquationSystem::showX()
{
    if (X == NULL)
    {
        printf("X is NULL\n");
        return;
    }

	for (int i = 0; i < size; i++)
	{
		printf("[%4d]\t%10.6lf\n", i, X[i]);
	}
    printf("\n");
}

void EquationSystem::showP()
{
    if (P == NULL)
    {
        printf("P is NULL\n");
        return;
    }

    // Row Indexes in the first line
    printf("================ P =================\n"
           "    ");
    for (int i = 0; i < size; i++)
    {
        printf ("  %4d", i+1);
    }
    printf("\n"
           "     ");
    for (int i = 0; i < size; i++)
    {
        printf ("______");
    }
    printf("\n");

    // Line indexes and P values
    for (int i = 0; i < size; i++)
    {
        printf("%4d|  ", i);
        for (int j = 0; j < size; j++)
        {
            printf ("  %1d   ", P[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* ==============================================================
 *                 			 Pivoting			               *
============================================================== */
void EquationSystem::resetP()
{
    clearP();

    // Instantiating new double matrix into P
    this->P = new int* [size];
    for (int i = 0; i < size; i++)
        this->P[i] = new int [size];

    // Setting Identity to P
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
                this->P[i][j] = 1;

            else
                this->P[i][j] = 0;
        }
    }
}
