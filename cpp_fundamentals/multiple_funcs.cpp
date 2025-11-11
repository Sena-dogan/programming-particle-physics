#include <iostream>
#include <cmath>

// Calculate energy from momentum ( massless particle )
double calculateEnergy(double momentum)
{
    return momentum; // E = p for massless particles
}

// Calculate energy from momentum and mass
double calculateEnergy(double momentum, double mass)
{
    return sqrt(pow(momentum, 2) + pow(mass, 2));
}

int main()
{
    // Photon ( massless )
    double E_photon = calculateEnergy(50.0);
    // Electron ( massive )
    double E_electron = calculateEnergy(50.0, 0.000511);
    std ::cout << " Photon energy : " << E_photon << " GeV " << std ::endl;
    std ::cout << " Electron energy : " << E_electron << " GeV " << std ::endl;
    return 0;
}