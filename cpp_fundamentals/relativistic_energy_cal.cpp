#include <iostream>
#include <cmath>

// Function to calculate relativistic energy
// Relativistic energy calculation: E^2 = (pc)^2 + (mc^2)^2
// In natural units c = 1
double calculateEnergy(double momentum, double mass)
{
    return sqrt(momentum * momentum + mass * mass);
}
// Function to calculate Lorentz factor
// Lorentz factor: gamma = E/m -> (c=1)
double lorentzFactor(double energy, double mass)
{
    return energy / mass;
}
int main()
{
    double p = 100.0; // GeV / c
    double m = 0.938; // GeV / c ˆ2 ( proton )
    double E = calculateEnergy(p, m);
    double gamma = lorentzFactor(E, m);
    std ::cout << " Momentum : " << p << " GeV / c " << std ::endl;
    std ::cout << " Energy : " << E << " GeV " << std ::endl;
    std ::cout << " Gamma : " << gamma << std ::endl;
    return 0;
}