#include <iostream>
#include <cmath> // Required for sqrt()

// 1. Function to calculate the invariant mass of a two-particle system.
double invariantMass(double E1, double px1, double py1, double pz1,
                     double E2, double px2, double py2, double pz2)
{

    // 2. Sum the energy and momentum components.
    double E_total = E1 + E2;
    double px_total = px1 + px2;
    double py_total = py1 + py2;
    double pz_total = pz1 + pz2;

    // 3. Calculate total momentum squared (p_total^2).
    double p_total_squared = px_total * px_total + py_total * py_total + pz_total * pz_total;

    // 4. Return the mass using the relativistic formula: M = sqrt(E_tot^2 - p_tot^2)
    return sqrt(E_total * E_total - p_total_squared);
}

int main()
{
    // 1. Example: A Z boson decaying into an electron (e-) and positron (e+)
    double E1 = 50.0, px1 = 30.0, py1 = 20.0, pz1 = 35.0;
    double E2 = 45.0, px2 = -30.0, py2 = -20.0, pz2 = -30.0;

    // 2. Call the function to calculate the mass of the parent particle (Z).
    double mass = invariantMass(E1, px1, py1, pz1, E2, px2, py2, pz2);

    std::cout << "Invariant mass: " << mass << " GeV/c^2" << std::endl;
    std::cout << "(Z boson mass ~ 91.2 GeV/c^2)" << std::endl;
    return 0;
}