#include <fstream>
#include <sstream> // Required for std::stringstream (to parse lines)
#include <iostream>
#include <string> // Required for std::string and std::getline

int main()
{
    // --- 1. Write CSV file ---
    std::ofstream csv("events.csv"); // Create an output file stream

    // Write the header line, followed by a newline (std::endl)
    csv << "EventID,Energy,Momentum,Mass" << std::endl;
    csv << "1,50.5,50.0,0.511" << std::endl;   // Electron data
    csv << "2,100.3,100.0,0.938" << std::endl; // Proton data
    csv.close();

    // --- 2. Read CSV file ---
    std::ifstream input("events.csv"); // Create an input file stream
    std::string line;                  // A string to hold each full line

    // 3. Read the first line (header) and do nothing with it (skips the header).
    std::getline(input, line);

    // 4. Loop by reading one line at a time until the file ends.
    while (std::getline(input, line))
    {

        // 5. Create a "string stream" from the line we just read.
        std::stringstream ss(line);
        std::string token; // A string to hold each piece of the line (e.g., "1", "50.5")

        int id;
        double energy, momentum, mass;

        // 6. Use 'std::getline' with a delimiter (',') to split the line.
        std::getline(ss, token, ',');
        id = std::stoi(token); // Read until ',', convert string to int
        std::getline(ss, token, ',');
        energy = std::stod(token); // Read until ',', convert string to double
        std::getline(ss, token, ',');
        momentum = std::stod(token); // Read until ',', convert string to double
        std::getline(ss, token, ',');
        mass = std::stod(token); // Read the last part

        std::cout << "Event " << id << ": E=" << energy << " GeV" << std::endl;
    }
    return 0;
}