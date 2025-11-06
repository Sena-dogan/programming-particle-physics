#include <cmath>
#include <iostream>

int main()
{
    double momentum = 100.0; // GeV/c
    // double mass = 0.511; // MeV/c^2 (electron)
    double mass = 0.000511; // GeV (0.511 MeV / 1000)

    // Relativistic energy calculation: E^2 = (pc)^2 + (mc^2)^2
    // In natural units c = 1
    double energy = sqrt(momentum * momentum + mass * mass);

    // Lorentz factor: gamma = E/m -> (c=1)
    double gamma = energy / mass;

    // beta = v/c -> c=1 -> beta = v
    // E = gamma * m * c^2 -> c=1 -> E = gamma * m
    // p = gamma * m * v -> p/E = v = beta
    double beta = momentum / energy;

    std ::cout << " Energy : " << energy << " GeV " << std ::endl;
    std ::cout << " Gamma : " << gamma << std ::endl;
    std ::cout << " Beta : " << beta << std ::endl;
    return 0;
}