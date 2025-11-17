#include <iostream>
#include <random>
#include <cmath> // Not strictly needed here, but good practice for physics code

int main()
{
    // 1. Set up the random number generator (for uniform 0.0 to 1.0)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0); // Generates numbers between 0.0 and 1.0

    double lambda = 0.1; // Decay constant (probability of decay per unit time)
    int initialParticles = 1000;
    int remainingParticles = initialParticles;
    double time = 0.0;
    double dt = 1.0; // The size of our time step

    std::cout << "Time\tParticles" << std::endl;

    // 2. Loop as long as we have particles and time is less than 50.
    while (remainingParticles > 0 && time < 50.0)
    {
        std::cout << time << "\t" << remainingParticles << std::endl;

        int decayed = 0;
        // 3. For each particle, see if it decays in this time step.
        for (int i = 0; i < remainingParticles; i++)
        {
            // Generate a random number [0, 1]. If it's less than the decay
            // probability (lambda * dt), the particle decays.
            if (dis(gen) < lambda * dt)
            {
                decayed++;
            }
        }
        remainingParticles -= decayed; // Subtract the decayed particles
        time += dt;                    // Move to the next time step
    }
    return 0;
}