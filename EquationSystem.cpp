#include "EquationSystem.h"

/* ==============================================================
 *                 Constructors and Destructor				   *
============================================================== */
EquationSystem::EquationSystem()
    { this->genericConstructor(NULL, NULL, 0, 0.000001, false, false); }

EquationSystem::EquationSystem(double A[], double B[], int size, double error)
    { this->genericConstructor(A, B, size, error, false, true); }

EquationSystem::EquationSystem(double A[], double B[], int size, double error, bool pivoting, bool printable)
    { this->genericConstructor(A, B, size, error, pivoting, printable); }

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
void EquationSystem::genericConstructor(double A[], double B[], int size, double error, bool pivoting, bool printable)
{
    setSize(0);
    this->A = NULL;
    this->B = NULL;
    this->P = NULL;
    this->X = NULL;

    // Attribution
    setSize(size);
    setError(error);
    setA(A);
    setB(B);

	// Pivoting and Print Calculations
	setPivoting(pivoting);
	setPrintCalcs(printable);

    /* Reseting matrices
     * X = O
     * P = I
    */
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
        // Fail clear
        if (!clearA())
        {
            printf("Error in setA(double A[]): size == 0\n");
            return;
        }

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
    catch(...) { printf("Error in setA(double A[]): invalid A (coeficients).\n"); };
}

// Sets matrix B in this A*X = B system
void EquationSystem::setB(double B[])
{
    try
    {
        // Fail clear
        if (!clearB())
        {
            printf("Error in setB(double A[]): size == 0\n");
            return;
        }

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
    catch(...) { printf("Error in setB(double B[]): invalid B (constants vector).\n"); };
}

// Sets matrix X in this A*X = B system
void EquationSystem::setX(double X[])
{
    try
    {
        // Fail clear
        if (!clearX())
        {
            printf("Error in setX(double X[]): size == 0\n");
            return;
        }

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
    catch(...) { printf("Error in setX(double X[]): invalid X (solutions).\n"); };
}

// Sets pivoting matrix P (Facade)
void EquationSystem::setP(int P[])
{
    try
    {
        // Fail clear
        if (!clearP())
        {
            printf("Error in setP(double P[]): size == 0\n");
            return;
        }

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
    catch(...) { printf("Error in setP(int P[]): invalid P (pivoting).\n"); };
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

// Sets the maximum allowed value of error (epsilon)
void EquationSystem::setError(double error)
{
    if (error < 0)
        error = -error;

    this->error = error;
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
 *                            Clear     					   *
============================================================== */
// Deletes all dynamic values assigned to coeficients matrix.
bool EquationSystem::clearA()
{
    if (A != NULL)
	{
        // Size 0
        if (size == 0)
        {
            printf("Error in clearA(): size = 0.\n");
            return false;
        }

		// Erasing each array in A
		for (int i = 0; i < size; i++)
            delete (A[i]);

        delete (A);
        A = NULL;
	}

    return true;
}

// Deletes the dynamic value assigned to B.
bool EquationSystem::clearB()
{
	if (B != NULL)
    {
        // Size 0
        if (size == 0)
        {
            printf("Error in clearB(): size = 0.\n");
            return false;
        }

        delete (B);
        B = NULL;
    }

    return true;
}

// Deletes the dynamic value assigned to X.
bool EquationSystem::clearX()
{
    if (X != NULL)
    {
        // Size 0
        if (size == 0)
        {
            printf("Error in clearX(): size = 0.\n");
            return false;
        }

        delete (X);
        X = NULL;
    }

    return true;
}

// Loads identity to pivoting matrix P (Facade).
bool EquationSystem::clearP()
{
    if (P != NULL)
    {
        // Size 0
        if (size == 0)
        {
            printf("Error in clearP(): size = 0.\n");
            return false;
        }

        // Erasing each array in P
        for (int i = 0; i < size; i++)
            delete (P[i]);

        delete (P);
        P = NULL;
    }

    return true;
}

/* ==============================================================
 *                 			   Reset			               *
============================================================== */
// Sets 0 to all of X's elements
void EquationSystem::resetX()
{
    clearX();

    // Instantiating new vector with 0's into X
    this->X = new double [size];

    // Setting Identity to P
    for (int i = 0; i < size; i++)
        X[i] = 0;
}

// Sets identity to P
void EquationSystem::resetP()
{
    clearP();

    // Instantiating new int matrix into P
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

/* ==============================================================
 *                 			  Pivoting			               *
============================================================== */
void EquationSystem::swapLines(double **M, int i1, int i2)
{
    bool error = false;

    // Null case
    if (M == NULL)
    {
        printf("Error in swapLines(double **M, int i1, int i2): NULL matrix\n");
        error = true;
    }

    // Line < 0 or Line > size
    if (i1 < 0 ||
        i2 < 0 ||
        i1 > size ||
        i2 > size)
    {
        printf("Error in swapLines(double **M, int i1, int i2): Line value error\n");
        error = true;
    }

    if (error)
        return;

    try
    {
        for (int j = 0; j < size; j++)
        {
            double temp = M[i1][j];
            M[i1][j] = M[i2][j];
            M[i2][j] = temp;
        }
    }
    catch (...)
        { printf("Error in swapLines(double **M, int i1, int i2): Invalid Matrix\n"); }
}

void EquationSystem::swapLines(int **M, int i1, int i2)
{
    bool error = false;

    // Null case
    if (M == NULL)
    {
        printf("Error in swapLines(int **M, int i1, int i2): NULL matrix\n");
        error = true;
    }

    // Line < 0 or Line > size
    if (i1 < 0 ||
        i2 < 0 ||
        i1 > size ||
        i2 > size)
    {
        printf("Error in swapLines(int **M, int i1, int i2): Line value error\n");
        error = true;
    }

    if (error)
        return;

    try
    {
        for (int j = 0; j < size; j++)
        {
            int temp = M[i1][j];
            M[i1][j] = M[i2][j];
            M[i2][j] = temp;
        }
    }
    catch (...)
        { printf("Error in swapLines(int **M, int i1, int i2): Invalid Matrix\n"); }
}

void EquationSystem::swapLines(double *M, int i1, int i2)
{
    bool error = false;

    // Null case
    if (M == NULL)
    {
        printf("Error in swapLines(double *M, int i1, int i2): NULL matrix\n");
        error = true;
    }

    // Line < 0 or Line > size
    if (i1 < 0 ||
        i2 < 0 ||
        i1 > size ||
        i2 > size)
    {
        printf("Error in swapLines(double *M, int i1, int i2): Line value error\n");
        error = true;
    }

    if (error)
        return;

    try
    {
        double temp = M[i1];
        M[i1] = M[i2];
        M[i2] = temp;
    }
    catch(...)
        { printf("Error in swapLines(double *M, int i1, int i2): Invalid Matrix\n"); }
}

void EquationSystem::swapLines(int *M, int i1, int i2)
{
    bool error = false;

    // Null case
    if (M == NULL)
    {
        printf("Error in swapLines(int *M, int i1, int i2): NULL matrix\n");
        error = true;
    }

    // Line < 0 or Line > size
    if (i1 < 0 ||
        i2 < 0 ||
        i1 > size ||
        i2 > size)
    {
        printf("Error in swapLines(int *M, int i1, int i2): Line value error\n");
        error = true;
    }

    if (error)
        return;

    try
    {
        int temp = M[i1];
        M[i1] = M[i2];
        M[i2] = temp;
    }
    catch(...)
        { printf("Error in swapLines(int *M, int i1, int i2): Invalid Matrix\n"); }
}

// Finds the position of the biggest element in the row j of matrix M
int EquationSystem::findMax(double **M, int j)
{
    bool error = false;

    // Size 0
    if (size == 0)
    {
        printf("Error in findMax(double **M, int j): size = 0\n");
        error = true;
    }

    // Null case
    if (M == NULL)
    {
        printf("Error in findMax(double **M, int j): M is NULL\n");
        error = true;
    }

    if (error)
        return -1;

    try
    {
        double maxV = M[0][j];
        int maxI = 0;
        for (int i = 1; i < size; i++)
        {
            if (M[i][j] > maxV)
            {
                maxV = M[i][j];
                maxI = i;
            }
        }

        return maxI;
    }
    catch (...)
    {
        printf("Error in findMax(double **M, int j): Invalid M\n");
        return -1;
    }
}

// Finishes the solution, multiplying P by X ( X = P*X )
void EquationSystem::pivotX()
{
    bool error = false;

    // Null cases
    if (X == NULL)
    {
        printf("Error in pivotX(): X is NULL\n");
        error = true;
    }
    if (P == NULL)
    {
        printf("Error in pivotX(): P is NULL\n");
        error = true;
    }

    // Size 0
    if (size == 0)
    {
        printf("Error in pivotX(): size = 0\n");
        error = true;
    }

    if (error)
        return;

    try
    {
        // Result is going to be stored in Xf
        double *Xf = new double [size];

        // Calculating and storing without modify X
        for (int i = 0; i < size; i++)
        {
            Xf[i] = 0;
            for (int j = 0; j < size; j++)
                Xf[i] += P[i][j]*X[j];
        }

        // Saving into X and deleting Xf
        for (int i = 0; i < size; i++)
            X[i] = Xf[i];

        delete(Xf);
    }
    catch(...)
        { printf("Error in pivotX(): Invalid element in P\n"); }
}
