#include <fstream>  // Required for file input/output (ifstream, ofstream)
#include <iostream> // Required for console I/O (std::cout, std::cerr)
#include <vector>   // Required for std::vector (dynamic array)

int main()
{
    // 1. Create an "input file stream" and try to open the file.
    std::ifstream inputFile("particle_data.txt");

    // 2. Always check if the file successfully opened.

    // ifstream (input): Only reads from files that *already exist*.
    // It will NOT create a file. If the file is missing, it fails to open.
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Cannot open file!" << std::endl;
        return 1; // Exit with an error code
    }

    std::vector<double> energies; // A dynamic array to store the numbers
    double energy;                // A temporary variable to hold each number as we read it

    // 3. Read numbers from the file one by one until the file ends.
    //    'inputFile >> energy' works like 'std::cin >> energy'
    while (inputFile >> energy)
    {
        energies.push_back(energy); // Add the read number to our vector
    }

    inputFile.close(); // Close the file stream

    // --- Calculate statistics ---
    double sum = 0.0;

    // 4. Use a range-based 'for' loop to sum all energies in the vector.
    for (double E : energies)
    {
        sum += E;
    }

    double average = sum / energies.size();

    std::cout << "Read " << energies.size() << " events" << std::endl;
    std::cout << "Average energy: " << average << " GeV" << std::endl;
    return 0;
}