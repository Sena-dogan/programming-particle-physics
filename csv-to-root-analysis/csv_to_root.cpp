// Include necessary C++ and ROOT libraries
#include <iostream>  // For printing to the console (cout)
#include <fstream>   // For reading files (ifstream)
#include <sstream>   // For parsing strings (stringstream)
#include <string>    // For string operations
#include <vector>    // For dynamic arrays (vector)

#include "TFile.h"   // For working with ROOT files
#include "TH1F.h"    // For 1-Dimensional Histograms (Float type)

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided.
    // Expected: ./csv_to_root <input_file.csv>
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.csv>" << std::endl;
        return 1; // Exit with error code
    }

    // Get the input file name from command-line arguments.
    std::string inputFileName = argv[1];
    
    // Open the input file for reading.
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file " << inputFileName << "!" << std::endl;
        return 1;
    }

    std::cout << "Input file (" << inputFileName << ") opened successfully." << std::endl;

    // We are creating our histograms for each column.
    // Constructor Parameters:
    // 1. ID ("name"): This name will be used to save and retrieve the histogram.
    // 2. Title: The title displayed on the plot. Axis labels can be set here, separated by ;
    // 3. Number of Bins: How many "slots" or "buckets" the histogram has.
    // 4. X-Axis Minimum Value
    // 5. X-Axis Maximum Value
    TH1F* h_energy = new TH1F("h_energy", "Particle Energy Distribution;Energy (GeV);Event Count", 100, 50, 150);
    TH1F* h_pt = new TH1F("h_pt", "Particle Transverse Momentum;pT (GeV);Event Count", 100, 20, 80);
    TH1F* h_eta = new TH1F("h_eta", "Particle Pseudorapidity;Eta;Event Count", 100, -4, 4);
    TH1F* h_phi = new TH1F("h_phi", "Particle Azimuthal Angle;Phi (radians);Event Count", 100, -3.2, 3.2);

    std::cout << "Histograms created. Reading data..." << std::endl;

    // A string variable to read the file line by line
    std::string line;
    
    // The first line of the CSV is the header, so we read and skip it.
    std::getline(inputFile, line); 

    // Continue reading line by line until the end of the file.
    while (std::getline(inputFile, line)) {
        // We put each line into a stringstream to easily parse it.
        std::stringstream ss(line);
        std::string token;

        // Variables to hold the values from the line
        std::string eventID_str;
        double energy, pt, eta, phi;

        // We split the line by commas
        std::getline(ss, eventID_str, ','); // EventID (we won't use this)
        std::getline(ss, token, ',');
        energy = std::stod(token); // Energy
        std::getline(ss, token, ',');
        pt = std::stod(token); // pT
        std::getline(ss, token, ',');
        eta = std::stod(token); // Eta
        std::getline(ss, token, ',');
        phi = std::stod(token); // Phi

        // We fill the read values into the respective histograms.
        h_energy->Fill(energy);
        h_pt->Fill(pt);
        h_eta->Fill(eta);
        h_phi->Fill(phi);
    }

    // File reading is complete.
    inputFile.close();
    std::cout << "Data reading finished." << std::endl;

    // We create the ROOT file where we will save the histograms.
    // "RECREATE" mode will overwrite the file if it exists, or create it if it doesn't.
    TFile* outputFile = new TFile("output.root", "RECREATE");
    
    // We write the histograms to the file.
    h_energy->Write();
    h_pt->Write();
    h_eta->Write();
    h_phi->Write();

    // We close the file and clean up the memory.
    outputFile->Close();
    delete outputFile;
    delete h_energy;
    delete h_pt;
    delete h_eta;
    delete h_phi;

    std::cout << "Histograms successfully saved to output.root." << std::endl;

    return 0; // Program finished successfully
}