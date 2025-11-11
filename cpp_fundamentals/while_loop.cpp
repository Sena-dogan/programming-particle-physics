#include <iostream>

int main()
{
    double totalEnergy = 0.0;
    double threshold = 500.0; // GeV
    int i = 0;

    // Keep reading events until threshold reached
    while (totalEnergy < threshold)
    {
        double eventEnergy = 10.0 + (rand() % 50);
        totalEnergy += eventEnergy;
        i++;
        std ::cout << " Event " << i
                   << " : E = " << eventEnergy
                   << " GeV ( Total : " << totalEnergy
                   << " GeV ) " << std ::endl;
    }
    std ::cout << "\nThreshold reached after "
               << i << " events " << std ::endl;

    return 0;
}