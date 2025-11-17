#include <iostream>
#include <vector>
int main()
{
    std ::vector<double> energies; // Dynamic size

    // Add particle energies
    energies.push_back(45.3);
    energies.push_back(67.8);
    energies.push_back(23.1);
    energies.push_back(89.5);

    // Calculate total energy
    double totalEnergy = 0.0;

    for (int i = 0; i < energies.size(); i++)
    {
        totalEnergy += energies[i];
    }

    // Modern C ++ range - based for loop
    std ::cout << " Individual energies : " << std ::endl;

    for (double E : energies)
    {
        std ::cout << " " << E << " GeV " << std ::endl;
    }

    std ::cout << " Total : " << totalEnergy << " GeV " << std ::endl;
    
    return 0;
}