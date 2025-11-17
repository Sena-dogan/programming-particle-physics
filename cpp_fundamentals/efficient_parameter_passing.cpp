// We need these libraries for math (sqrt) and printing (std::cout)
#include <cmath>
#include <iostream>

/*
================================================================================
 FUNCTION 1: Pass-by-Value (Inefficient and Incorrect for this goal)
================================================================================
*/

// This is the "slow" version you provided.
// It takes COPIES of all arguments.
void calculateKinematics_slow(double p, double m, double E, double beta)
{
    // 'E' and 'beta' here are LOCAL COPIES.
    // They only exist inside the stack frame for 'calculateKinematics_slow'.
    // They have NO connection to the 'energy' and 'velocity' variables in main().
    E = sqrt(p * p + m * m);
    beta = p / E;

    // When this function ends, these local 'E' and 'beta' variables
    // (and their calculated values) are destroyed.
    // The variables in main() are untouched, left with their garbage values.
}

/*
================================================================================
 FUNCTION 2: Pass-by-Reference (The modern C++ way)
================================================================================
*/

// This is the "efficient" C++ version.
// The '&' symbol in the function signature defines 'E' and 'beta'
// as "references".
void calculateKinematics(double p, double m,
                         double &E, double &beta)
{
    // 'p' and 'm' are copies (Pass-by-Value).
    
    // 'E' is NOT a copy. It is an "alias" (a nickname) for the
    // 'energy' variable that was passed from main().
    // 'E' and 'main::energy' now refer to the EXACT SAME place in memory.
    
    // 'beta' is an alias for 'main::velocity'.

    /*
    // --- C-Style Pointer Equivalent (for comparison) ---
    // In C, the function signature would have used pointers (*):
    //
    // void calculateKinematics_C_Style(double p, double m,
    //                                  double *ptrE, double *ptrBeta)
    // {
    */


    // --- Writing to the Reference ---
    // Because 'E' is a reference (an alias), writing to 'E'...
    E = sqrt(p * p + m * m);
    
    // ...is *directly* changing the value of the 'energy' variable
    // back in main()'s stack frame.
    
    /*
    // --- C-Style Pointer Equivalent (for comparison) ---
    // In C, we would have to "de-reference" the pointer to write
    // to the memory address it points to:
    //
    // *ptrE = sqrt(p * p + m * m);
    */


    // Same thing here: we are directly changing 'main::velocity'
    beta = p / E;

    /*
    // --- C-Style Pointer Equivalent (for comparison) ---
    // *ptrBeta = p / (*ptrE); // Note the extra '*' to read from ptrE
    //
    // } // End of C-Style function
    */
}


/*
================================================================================
 MAIN FUNCTION: The Caller
================================================================================
*/
int main()
{
    // These variables are created on the 'main' function's stack frame.
    double momentum = 100.0, mass = 0.938;

    // These variables are also allocated on the stack.
    // IMPORTANT: They are uninitialized and contain GARBAGE values.
    // (e.g., 1.28823e-231, 4.20033e-314, etc.)
    double energy, velocity;

    // --- Calling the Pass-by-Reference function ---
    //
    // We pass 'energy' and 'velocity' directly.
    // The C++ compiler sees that the function 'calculateKinematics'
    // expects references (&E, &beta), so it automatically
    // passes the *addresses* (or references) of these variables
    // "under the hood".
    calculateKinematics(momentum, mass, energy, velocity);

    /*
    // --- C-Style Pointer Equivalent (for comparison) ---
    // If we were calling the C-style function, we (the caller)
    // would be forced to *explicitly* pass the memory addresses
    // using the '&' (address-of) operator.
    //
    // calculateKinematics_C_Style(momentum, mass, &energy, &velocity);
    //
    // C++ references are cleaner because the caller doesn't need
    // to use the '&' operator, making the code look simpler.
    */

    // Because we used pass-by-reference, the 'energy' and 'velocity'
    // variables in *this* function (main) have been successfully
    // updated by the 'calculateKinematics' function.
    std::cout << " Energy : " << energy << " GeV " << std::endl;
    std::cout << " Beta : " << velocity << std::endl;

    return 0;
}

// C-Style Pointer Version (for comparison)
// ------------------------------------------------------------
// // This is the C-style version using pointers.
// // 1. Function's responsibility: Take a pointer (*) and
// //    dereference it (*)
// void calculateKinematics_C_Style(double p, double m,
//                                  double *E, double *beta)
// {
//     *E = sqrt(p * p + m * m); // Write "into" the address
//     *beta = p / *E;
// }

// int main()
// {
//     double energy, velocity;
    
//     // 2. The caller's (main's) responsibility: Send the
//     //    ADDRESS (&) of the variable
//     calculateKinematics_C_Style(momentum, mass, &energy, &velocity);
// }