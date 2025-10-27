// Include necessary C++ and ROOT libraries
#include <iostream>
#include <string>

#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TPad.h" // To use the gPad object (for SetLogy)

/**
 * @brief Function to print the histogram's name, underflow, and overflow values.
 * @param hist Pointer to the TH1F histogram.
 */
void printUnderflowOverflow(TH1F *hist)
{
    int nbins = hist->GetNbinsX();
    std::cout << "--- Histogram: " << hist->GetName() << " ---" << std::endl;
    std::cout << "Total Entries: " << hist->GetEntries() << std::endl;
    std::cout << "Underflow (below range): " << hist->GetBinContent(0) << std::endl;
    std::cout << "Overflow (above range): " << hist->GetBinContent(nbins + 1) << std::endl;
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    // Argument check
    // Expected: ./draw_from_root <input_file.root>
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file.root>" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];

    // Check for .root extension
    if (inputFileName.size() < 5 || inputFileName.substr(inputFileName.size() - 5) != ".root")
    {
        std::cerr << "Error: Input file must have a .root extension!" << std::endl;
        return 1;
    }

    // Open the ROOT file in "READ" mode.
    TFile *inputFile = TFile::Open(inputFileName.c_str(), "READ");
    if (!inputFile || inputFile->IsZombie())
    {
        std::cerr << "Error: " << inputFileName << " file could not be opened or is corrupted!" << std::endl;
        return 1;
    }

    std::cout << inputFileName << " file opened. Reading histograms..." << std::endl;

    // We retrieve the histograms from the file by their names.
    // We must cast the TObject* pointer returned by Get() to TH1F*.
    TH1F *h_energy = (TH1F *)inputFile->Get("h_energy");
    TH1F *h_pt = (TH1F *)inputFile->Get("h_pt");
    TH1F *h_eta = (TH1F *)inputFile->Get("h_eta");
    TH1F *h_phi = (TH1F *)inputFile->Get("h_phi");

    // Check if the histograms were read successfully.
    if (!h_energy || !h_pt || !h_eta || !h_phi)
    {
        std::cerr << "Error: Could not read histograms from the file!" << std::endl;
        inputFile->Close();
        return 1;
    }

    // Print underflow/overflow values for each histogram.
    printUnderflowOverflow(h_energy);
    printUnderflowOverflow(h_pt);
    printUnderflowOverflow(h_eta);
    printUnderflowOverflow(h_phi);

    // We create a canvas for drawing.
    TCanvas *canvas = new TCanvas("canvas", "Histogram Drawings", 800, 600);

    // --- DRAWING OPERATIONS ---
    std::cout << "Drawing histograms and saving image files..." << std::endl;

    // 1. Default Style
    h_energy->Draw();
    canvas->SaveAs("hist_default.png");

    // 2. Error Bars Style
    h_energy->Draw("E1");
    canvas->SaveAs("hist_errorbars.png");

    // 3. Filled Style
    h_energy->Draw("HIST");
    canvas->SaveAs("hist_filled.png");

    // 4. Logarithmic Y-Axis Style
    gPad->SetLogy(1); // Set Y-axis to logarithmic
    h_energy->Draw();
    canvas->SaveAs("hist_logy.png");
    gPad->SetLogy(0); // Set Y-axis back to linear for subsequent plots

    // 5. Rebinned Style
    // To avoid modifying the original histogram, we create a clone.
    TH1F *h_energy_rebinned = (TH1F *)h_energy->Clone("h_energy_rebinned");
    h_energy_rebinned->Rebin(4); // Combine 4 bins into one new bin
    h_energy_rebinned->SetTitle("Energy Distribution (4x Rebin)");
    h_energy_rebinned->Draw();
    canvas->SaveAs("hist_rebinned.png");

    // 6. Normalized Style
    // Draws the histogram normalized to an integral of 1.
    h_energy->DrawNormalized();
    canvas->SaveAs("hist_normalized.png");

    std::cout << "All images saved successfully." << std::endl;

    // Close the file and clean up memory
    inputFile->Close();
    delete inputFile;
    delete canvas;

    // delete h_energy_rebinned; // <-- CAUSES BUS ERROR / SEG FAULT!

    //  REASON (Double-Delete):
    //  'h_energy_rebinned' was already deleted when 'inputFile' was deleted.
    //  This line tries to delete it a second time, causing a crash.

    return 0;
}