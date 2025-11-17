#include <iostream>

int main()
{
    // 1. A 5x5 grid (2D array) to represent calorimeter cells, all init to 0.
    const int SIZE = 5;
    double calorimeter[SIZE][SIZE] = {0};

    // 2. Simulate a particle hit by depositing energy in specific cells.
    calorimeter[2][2] = 50.0; // Center hit
    calorimeter[2][1] = 10.0; // Adjacent cells
    calorimeter[2][3] = 10.0;
    calorimeter[1][2] = 8.0;
    calorimeter[3][2] = 8.0;

    // 3. Sum energy
    double totalEnergy = 0.0;

    // 4. Use nested 'for' loops to iterate over every cell (row 'i', column 'j').
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            totalEnergy += calorimeter[i][j];
            std::cout << "Cell (" << i << ", " << j << "): "
                      << calorimeter[i][j] << " GeV" << std::endl;
        }
    }

    std::cout << "Total deposited energy: "
              << totalEnergy << " GeV" << std::endl;
    return 0;
}