
#include <fstream>      // For std::ifstream
#include <vector>       // For std::vector
#include <sstream>      // For std::stringstream
#include <string>       // For std::string

#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TPaveText.h>
#include <TRandom3.h>    // For generating dummy data

/**
 * @brief Creates a dummy CSV file with data suitable for a linear fit.
 * @param csv The name of the file to create (e.g., "data_points.csv").
 */
void create_dummy_csv(const char* csv) {
    std::ofstream outfile(csv);
    outfile << "x_val,y_val,x_err,y_err\n"; // Header row
    
    // Generate data for: y = 5 + 3*x + noise
    for (int i = 0; i < 12; ++i) {
        double x = i + 1.0;
        double y_true = 5.0 + 3.0 * x;
        double y_measured = y_true + gRandom->Gaus(0, 1.5); // Add Gaussian noise
        outfile << x << "," << y_measured << ",0.1,1.5\n"; // x_err=0.1, y_err=1.5
    }
    outfile.close();
    printf("Helper: Created dummy file '%s' for the example.\n", csv);
}

/**
 * @brief Main function: Reads data from CSV, plots, fits, and saves.
 * This function fills the skeleton you provided.
 * @param csv The name of the input CSV file.
 */
void csv_fit_skeleton(const char* csv="data_points.csv") {
    
    // --- 1. Reuse graph_from_csv() style to load arrays ---
    std::ifstream fin(csv);
    
    // If the file doesn't exist, create a dummy one
    if (!fin) {
        Warning("csv_fit_skeleton", "Cannot open '%s'. Creating a dummy file.", csv);
        create_dummy_csv(csv); 
        fin.open(csv); // Try opening it again
        if (!fin) {
            Error("csv_fit_skeleton", "Still cannot open '%s' after creation. Exiting.", csv);
            return;
        }
    }

    // Vectors to store the data
    std::vector<double> vx, vy, vex, vey;
    std::string line;
    std::getline(fin, line); // Skip header line

    // Read data line by line
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        double x, y, ex, ey;
        char comma; // To consume the commas
        if (!(ss >> x >> comma >> y >> comma >> ex >> comma >> ey)) continue;
        
        vx.push_back(x);
        vy.push_back(y);
        vex.push_back(ex);
        vey.push_back(ey);
    }
    fin.close();

    if (vx.empty()) {
        Error("csv_fit_skeleton", "No data was read from '%s'.", csv);
        return;
    }

    // Create a canvas to draw on
    auto c = new TCanvas("c", "Fit from CSV", 800, 600);
    gStyle->SetOptFit(0); // Turn off the default statistics box

    // --- 2. Create TGraphErrors ge(...) ---
    auto ge = new TGraphErrors(vx.size(), vx.data(), vy.data(), vex.data(), vey.data());
    ge->SetTitle("Data from CSV with Linear Fit;X Value;Y Value");
    ge->SetMarkerStyle(20);
    ge->SetMarkerColor(kBlue + 1);
    ge->SetLineColor(kBlue + 1);
    ge->Draw("AP"); // "AP" = Draw Axes and Points

    // --- 3. Define TF1 f("f", "pol1", xmin, xmax) ---
    double xmin = vx.front(); // Get fit range from data (first x)
    double xmax = vx.back();  // Get fit range from data (last x)
    
    // "pol1" is a linear fit: y = [0] + [1]*x
    auto f = new TF1("f", "pol1", xmin, xmax);
    f->SetLineColor(kRed);
    f->SetLineWidth(2);
    f->SetParName(0, "p0 (Intercept)"); // Set parameter names
    f->SetParName(1, "p1 (Slope)");

    // --- 4. ge->Fit(f, "Q"); f.Draw("same"); ---
    ge->Fit(f, "Q"); // "Q" = Quiet mode (no fit info to terminal)
    f->Draw("same"); // Draw the fit function on the same canvas

    // --- 5. Add a legend with fit parameters; SaveAs("csv_fit.png"); ---
    
    // Add a simple legend for the graph and function
    auto leg = new TLegend(0.15, 0.75, 0.45, 0.88); // (x1,y1,x2,y2) in NDC
    leg->SetBorderSize(0);
    leg->AddEntry(ge, "Data from CSV", "lep");
    leg->AddEntry(f, "Linear Fit (pol1)", "l");
    leg->Draw();

    // Add a text box to display the fit parameters
    auto pt = new TPaveText(0.50, 0.15, 0.88, 0.35, "NDC"); // NDC = Normalized Coords
    pt->SetFillColor(0);
    pt->SetBorderSize(1);
    pt->SetTextAlign(12); // Left-aligned
    pt->SetTextFont(42);
    pt->AddText("Fit Results:");
    pt->AddText(Form("p0 = %.2f #pm %.2f", f->GetParameter(0), f->GetParError(0)));
    pt->AddText(Form("p1 = %.2f #pm %.2f", f->GetParameter(1), f->GetParError(1)));
    pt->AddText(Form("#chi^{2} / ndf = %.2f / %d = %.2f",
                     f->GetChisquare(),
                     f->GetNDF(),
                     f->GetChisquare() / f->GetNDF()));
    pt->Draw();

    // Save the final plot
    c->SaveAs("csv_fit.png");
    printf("Fit plot saved as 'csv_fit.png'.\n");
}

// --- Main function to run the macro ---
void run_fit() {
    gRandom = new TRandom3(0); // Initialize random generator
    csv_fit_skeleton("data_points.csv");
}