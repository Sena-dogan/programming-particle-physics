#include "histogram_class.cpp" // Includes the class definition from the other file
#include <random>              // Required for high-quality random number generation
#include <iostream>

int main()
{
    // 1. Create a Histogram object with 10 bins, ranging from 0.0 to 100.0
    Histogram h(10, 0.0, 100.0);

    // --- Generate random energy values ---
    // 2. Set up a high-quality random number generator.
    std::random_device rd;
    std::mt19937 gen(rd());

    // 3. Create a 'normal' (Gaussian) distribution with mean=50.0, std_dev=15.0
    std::normal_distribution<> dis(50.0, 15.0);

    // --- Fill histogram with 1000 events ---
    for (int i = 0; i < 1000; i++)
    {
        double energy = dis(gen); // Get a random number from the distribution
        h.fill(energy);           // Fill the histogram with this number
    }

    // --- Print histogram ---
    std::cout << "Energy [GeV]\tCounts" << std::endl;
    std::cout << "==========================" << std::endl;
    h.print(); // Call our class method to print the results
    return 0;
}