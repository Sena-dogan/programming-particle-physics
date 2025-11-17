#include <fstream>
#include <iostream>
#include <vector>

int main()
{
    // 1. A vector of data we want to save.
    std::vector<double> energies = {45.3, 67.8, 89.2, 34.5, 78.9};

    // 2. Create an "output file stream" to write to a file.
    std::ofstream outputFile("analysis_results.txt");

    // 3. Check if the file was successfully created.
    if (!outputFile.is_open())
    {
        std::cerr << "Error: Cannot create file!" << std::endl;
        return 1;
    }

    // --- Write data ---
    // 4. Write to the file just like you write to 'std::cout'.
    outputFile << "Event Analysis Results" << std::endl;
    outputFile << "==========================" << std::endl;

    // 5. Loop through the vector and write each energy value, one per line.
    for (int i = 0; i < energies.size(); i++)
    {
        outputFile << "Event " << i << ": "
                   << energies[i] << " GeV" << std::endl;
    }

    outputFile.close(); // Close the file to ensure all data is saved
    std::cout << "Results saved to analysis_results.txt" << std::endl;
    return 0;
}