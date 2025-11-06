#include <iostream>

int main()
{
    int eventNumber = 12345;
    long long totalEvents = 10000000000LL; // 'LL' suffix indicates long long literal

    // Type Casting ((float)x): This is an operation that converts an existing variable or value from one type to another.
    // Literal Suffix (125.3f): This tells the compiler what the type of the literal value itself (the number you literally typed in the code) should be from the very beginning.

    double energy = 13.6;    // (TeV)
    float momentum = 125.3f; // (GeV/c) 125.3 -> default is double, 125.3f -> float
    bool isElectron = true;

    char particleType = 'e';

    std::cout << "Event: " << eventNumber << std::endl;
    std::cout << "Energy: " << energy << " Tev" << std::endl;
    std::cout << "Momentum: " << momentum << " Gev/c" << std::endl;

    return 0;
}