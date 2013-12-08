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
    this->A = NULL;
    this->B = NULL;
    this->P = NULL;
    this->X = NULL;

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
    resetX();
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
        A = NULL;
	}
}

// Deletes the dynamic value assigned to B.
void EquationSystem::clearB()
{
	if (B != NULL)
    {
        delete (B);
        B = NULL;
    }
}

// Deletes the dynamic value assigned to X.
void EquationSystem::clearX()
{
    if (X != NULL)
    {
        delete (X);
        X = NULL;
    }
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
        P = NULL;
    }
}

/* ==============================================================
 *                 			   Show				               *
============================================================== */
void EquationSystem::showA()
{
    // Null case
    if (A == NULL)
    {
        printf("A is NULL\n\n");
        return;
    }

    // Row Indexes in the first line
    printf("================ A =================\n"
           "     ");
    for (int i = 0; i < size; i++)
        printf ("    %4d    ", i+1);

    // Horizontal line
    printf("\n"
           "     ");

    for (int i = 0; i < size; i++)
        printf ("____________");

    printf("\n");

    // Lines indexes and A values
    for (int i = 0; i < size; i++)
    {
        printf("%4d|", i+1);
        for (int j = 0; j < size; j++)
            printf ("  %10lf", A[i][j]);

        printf("\n");
    }
    printf("\n");
}

void EquationSystem::showB()
{
    // Null case
    if (B == NULL)
    {
        printf("B is NULL\n\n");
        return;
    }

    // Title and horizontal bar
    printf("================ B =================\n"
           "     ____________\n");

    // Lines indexes and B values
    for (int i = 0; i < size; i++)
        printf("%4d|  %10lf\n", i+1, B[i]);

    printf("\n");
}

void EquationSystem::showX()
{
    // Null case
    if (X == NULL)
    {
        printf("X is NULL\n\n");
        return;
    }

    // Title and horizontal bar
    printf("================ X =================\n"
           "     ____________\n");

    // Lines indexes and B values
    for (int i = 0; i < size; i++)
        printf("%4d|  %10lf\n", i+1, X[i]);

    printf("\n");
}

void EquationSystem::showP()
{
    // Null case
    if (P == NULL)
    {
        printf("P is NULL\n\n");
        return;
    }

    // Row Indexes in the first line
    printf("================ P =================\n"
           "     ");
    for (int i = 0; i < size; i++)
        printf ("  %4d", i+1);

    // Horizontal bar
    printf("\n"
           "     ");
    for (int i = 0; i < size; i++)
        printf ("______");

    printf("\n");

    // Line indexes and P values
    for (int i = 0; i < size; i++)
    {
        printf("%4d|", i+1);
        for (int j = 0; j < size; j++)
            printf ("     %1d", P[i][j]);

        printf("\n");
    }
    printf("\n");
}

/* ==============================================================
 *                 			 Pivoting			               *
============================================================== */
void EquationSystem::resetX()
{
    clearX();

    // Instantiating new vector with 0's into X
    this->X = new double [size];

    // Setting Identity to P
    for (int i = 0; i < size; i++)
        X[i] = 0;
}

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
