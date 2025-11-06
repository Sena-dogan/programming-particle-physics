#include <iostream>
#include <cmath> // For mathematical constants

int main()
{
    // Physical constants ( use const or constexpr )
    const double SPEED_OF_LIGHT = 299792458.0; // m / s
    const double PLANCK_CONSTANT = 6.62607015e-34; // J * s
    const double PROTON_MASS = 938.272; // MeV / c ˆ2ƒ
    const double ELECTRON_MASS = 0.511; // MeV / c ˆ2

    // Calculate energy from mass ( E = mc ˆ2)
    double energy_electron = ELECTRON_MASS; // In natural units c = 1 -> E = m

    std::cout << " Electron rest energy : "
              << energy_electron << " MeV " << std::endl;
    return 0;
}