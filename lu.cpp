#include "lu.h"

/* ==============================================================
 *                 Constructors and Destructor				   *
============================================================== */
LU::LU()
    { this->genericConstructor(NULL, NULL, 0, false, true); }

LU::LU(double A[], double B[], int size)
    { this->genericConstructor(A, B, size, false, true); }

LU::LU(double A[], double B[], int size, bool pivoting, bool printable)
    { this->genericConstructor(A, B, size, pivoting, printable); }

LU::~LU()
{
    this->clearA();
    this->clearB();
    this->clearP();
    this->clearX();
    this->clearL();
    this->clearU();
}

void LU::genericConstructor(double A[], double B[], int size, bool pivoting, bool printable)
{
    setSize(0);

    // Cleaning pointers
    this->A = NULL;
    this->B = NULL;
    this->P = NULL;
    this->X = NULL;
    this->L = NULL;
    this->U = NULL;

    // Attribution
    setSize(size);
    setA(A);
    setB(B);

    // Pivoting and Print Calculations
    setPivoting(pivoting);
    setPrintCalcs(printable);

    /* Reseting matrices
     * X = O
     * P = I
     * L = O
     * U = O
    */
    resetX();
    resetP();
    resetL();
    resetU();
}

/* ==============================================================
 *                             Sets     					   *
============================================================== */
// Overriding base class' setA()
void LU::setA(double A[])
{
    EquationSystem::setA(A);
    this->setChangedA(true);
}

void LU::setChangedA(bool changedA)
    { this->changedA = changedA; }

/* ==============================================================
 *                 		Solving the system                     *
============================================================== */
// Solves the system to the given B
void LU::run()
{
    // Copy from Gauss.h. Next step: modify it.
    bool invalid = false;

    if (A == NULL)
    {
        printf(" Error in run(): A is NULL\n");
        invalid = true;
    }

    if (B == NULL)
    {
        printf(" Error in run(): B is NULL\n");
        invalid = true;
    }

    if (size == 0)
    {
        printf(" Error in run(): size = 0\n");
        invalid = true;
    }

    if(invalid) return;

    if (changedA)
        calcLU();

    applyLU();
}

// Calculates L and U. They are not re-calculated when B changes.
void LU::calcLU()
{
    resetL();
    resetU();

    for (int step = 0; step < size; step++)
    {
        if (pivoting)
        {
            int max = findMax(A, step, step);

            if (max != NOMAXFOUND)
            {
                swapLines(A, step, max);
                swapLines(P, step, max);
            }
        }
        else if(A[step][step] == 0)
        {
            setSparse(true);
            printf(" This system leads to a sparse matrix.\n"
                   " Therefore, it cannot be solved without pivoting.\n"
                   " Please activate pivoting in order to solve it.\n\n");
            return;
        }

        // Calculating U
        for (int j = step; j < size; j++)
            U[step][j] = A[step][j];

        // Calculating L
        for (int i = step+1; i < size; i++)
        {
            double ratio = A[i][step]/A[step][step];
            L[i][step] = ratio;

            for (int j = step; j < size; j++)
                A[i][j] -= ratio*A[step][j];
        }

        if (printable)
        {
            printf("----->> STEP: %d <<-----\n", step);
            showA();
            showL();
            showU();
            printf("\n\n");
        }
    }

    setChangedA(false);
}

// Applies already calculated L and U to B.
void LU::applyLU()
{
    if (!pivoting && sparse)
        return;

    resetX();
    resetY();

    multiply(P, B);

    // Calculating Y
    for (int i = 0; i < size; i++)
    {
        Y[i] = B[i];
        for (int j = 0; j < i; j++)
            Y[i] -= L[i][j]*Y[j];

        Y[i] /= L[i][i];
    }

    // Calculating X
    for (int i = size-1; i >= 0; i--)
    {
        X[i] = Y[i];
        for (int j = size-1; j > i; j--)
            X[i] -= U[i][j]*X[j];

        X[i] /= U[i][i];
    }
}

/* ==============================================================
 *                 			   Show				               *
============================================================== */
void LU::showL()
{
    // Null case
    if (L == NULL)
    {
        printf("L is NULL\n\n");
        return;
    }

    // Row Indexes in the first line
    printf("================ L =================\n"
           "     ");
    for (int i = 0; i < size; i++)
        printf ("    %4d    ", i+1);

    // Horizontal line
    printf("\n"
           "     ");

    for (int i = 0; i < size; i++)
        printf ("____________");

    printf("\n");

    // Lines indexes and L values
    for (int i = 0; i < size; i++)
    {
        printf("%4d|", i+1);
        for (int j = 0; j < size; j++)
            printf ("  %10lf", L[i][j]);

        printf("\n");
    }
    printf("\n");
}

void LU::showU()
{
    // Null case
    if (U == NULL)
    {
        printf("U is NULL\n\n");
        return;
    }

    // Row Indexes in the first line
    printf("================ U =================\n"
           "     ");
    for (int i = 0; i < size; i++)
        printf ("    %4d    ", i+1);

    // Horizontal line
    printf("\n"
           "     ");

    for (int i = 0; i < size; i++)
        printf ("____________");

    printf("\n");

    // Lines indexes and U values
    for (int i = 0; i < size; i++)
    {
        printf("%4d|", i+1);
        for (int j = 0; j < size; j++)
            printf ("  %10lf", U[i][j]);

        printf("\n");
    }
    printf("\n");
}

void LU::showY()
{
    // Null case
    if (Y == NULL)
    {
        printf("Y is NULL\n\n");
        return;
    }

    // Title and horizontal bar
    printf("================ Y =================\n"
           "     ____________\n");

    // Lines indexes and B values
    for (int i = 0; i < size; i++)
        printf("%4d|  %10lf\n", i+1, Y[i]);

    printf("\n");
}

/* ==============================================================
 *                            Clear                            *
============================================================== */
// Deletes all dynamic values assigned to Lower matrix.
bool LU::clearL()
{
    if (L != NULL)
    {
        // Size 0
        if (size == 0)
        {
            printf(" Error in clearL(): size = 0.\n");
            return false;
        }

        // Erasing each array in L
        for (int i = 0; i < size; i++)
            delete (L[i]);

        delete (L);
        L = NULL;
    }

    return true;
}

// Deletes all dynamic values assigned to Upper matrix.
bool LU::clearU()
{
    if (U != NULL)
    {
        // Size 0
        if (size == 0)
        {
            printf(" Error in clearU(): size = 0.\n");
            return false;
        }

        // Erasing each array in U
        for (int i = 0; i < size; i++)
            delete (U[i]);

        delete (U);
        U = NULL;
    }

    return true;
}

// Deletes the dynamic value assigned to half-solution vector
bool LU::clearY()
{
    if (Y != NULL)
    {
        // Size 0
        if (size == 0)
        {
            printf(" Error in clearY(): size = 0.\n");
            return false;
        }

        delete (Y);
        Y = NULL;
    }

    return true;
}

/* ==============================================================
 *                             Reset                           *
============================================================== */
// Sets 0 to all of L's elements
void LU::resetL()
{
    clearL();

    // Instantiating new double matrix into L
    this->L = new double* [size];
    for (int i = 0; i < size; i++)
        this->L[i] = new double [size];

    // Setting Identity to L
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            if (i == j)
                this->L[i][j] = 1;
            else
                this->L[i][j] = 0;
        }
}

// Sets 0 to all of U's elements
void LU::resetU()
{
    clearU();

    // Instantiating new double matrix into U
    this->U = new double* [size];
    for (int i = 0; i < size; i++)
        this->U[i] = new double [size];

    // Setting O to U
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            this->U[i][j] = 0;
}

// Sets 0 to all of Y's elements
void LU::resetY()
{
    clearY();

    // Instantiating new vector with 0's into Y
    this->Y = new double [size];

    // Setting Identity to P
    for (int i = 0; i < size; i++)
        Y[i] = 0;
}
