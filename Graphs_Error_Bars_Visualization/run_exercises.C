#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h> // More accurate for Exercise A
#include <TF1.h>
#include <TH1D.h>
#include <TLegend.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TStyle.h>
#include <TPaveText.h>
#include <TROOT.h>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// --- Helper function to create a CSV for Exercise C ---
/**
 * Creates a dummy data file named "data_for_C.csv" to be read in Exercise C.
 * Generates data according to the model: y = 10 + 2*x + 0.5*x^2 + Gaus(0, 1.5).
 */
void create_dummy_csv_for_C()
{
    std::ofstream outfile("data_for_C.csv");
    // 1. Header row
    outfile << "x,y,ex,ey\n";

    // 2. Data rows
    for (int i = 0; i <= 10; ++i)
    {
        double x = static_cast<double>(i);
        double ex = 0.1; // Constant x error
        double ey = 1.5; // Constant y error (sigma of noise)

        // y = 10 + 2*x + 0.5*x^2 (Polynomial) + Gaus(0, sigma)
        double y = (10.0 + 2.0 * x + 0.5 * x * x) + gRandom->Gaus(0, ey);

        outfile << x << "," << y << "," << ex << "," << ey << "\n";
    }
    outfile.close();
    printf("Created 'data_for_C.csv' for Exercise C.\n");
}

// --- Exercise A: Efficiency Plot ---
void exerciseA()
{
    const int n_points = 15;
    const double p_min = 2.0;
    const double p_max = 50.0;
    const int N_total_events = 2000; // Total events per momentum point

    // Using histograms is the most robust way to simulate efficiency
    // and correctly calculate binomial errors (Clopper-Pearson).
    auto h_total = new TH1D("h_total", "Total Events", n_points, p_min, p_max);
    auto h_pass = new TH1D("h_pass", "Passed Events", n_points, p_min, p_max);

    // Simulate a realistic efficiency "turn-on" curve (sigmoid)
    // eff(p) = 0.95 * (1 - exp(-p / 8))
    for (int i = 1; i <= n_points; ++i)
    {
        double p = h_total->GetBinCenter(i);
        // True efficiency model
        double true_eff = 0.95 * (1.0 - TMath::Exp(-p / 8.0));

        // Simulate the number of passed events from a binomial distribution
        int n_pass = gRandom->Binomial(N_total_events, true_eff);

        h_total->SetBinContent(i, N_total_events);
        h_pass->SetBinContent(i, n_pass);
    }

    // Use TGraphAsymmErrors to correctly calculate binomial errors
    auto grA = new TGraphAsymmErrors();
    grA->Divide(h_pass, h_total, "cl=0.683 b(1,1) e0"); // "b" = Binomial (Clopper-Pearson)

    // Drawing
    auto cA = new TCanvas("cA", "Exercise A: Efficiency", 800, 600);
    grA->SetTitle("Simulated Detector Efficiency;Momentum p (GeV);Efficiency");
    grA->SetMarkerStyle(20);
    grA->SetMarkerColor(kBlue + 2);
    grA->SetLineColor(kBlue + 2);
    grA->GetYaxis()->SetRangeUser(0.0, 1.1); // Set Y-axis range from 0 to 1.1
    grA->Draw("AP");

    // Legend
    auto legA = new TLegend(0.6, 0.2, 0.88, 0.4);
    legA->SetHeader("Simulation");
    legA->AddEntry(grA, "Data (N=2000 / point)", "lep");
    legA->SetBorderSize(0);
    legA->Draw();

    // Save as PDF
    cA->SaveAs("exercise_A_efficiency.pdf");
    printf("Exercise A saved as 'exercise_A_efficiency.pdf'.\n");

    // Clean up memory (not essential in small macros, but good practice)
    delete h_total;
    delete h_pass;
}

// --- Exercise B: Logarithmic Plots ---
void exerciseB()
{
    const int n_points = 50;
    const double A = 150.0; // y = A * exp(-k*x)
    const double k = 0.4;
    const double noise_sigma = 5.0; // Constant Gaussian noise

    std::vector<double> vx(n_points), vy(n_points), vex(n_points), vey(n_points);

    for (int i = 0; i < n_points; ++i)
    {
        vx[i] = (10.0 * i) / (n_points - 1.0); // x goes from 0 to 10
        double y_true = A * TMath::Exp(-k * vx[i]);
        vy[i] = y_true + gRandom->Gaus(0, noise_sigma);
        vex[i] = 0.0;
        vey[i] = noise_sigma;
    }

    auto grB = new TGraphErrors(n_points, vx.data(), vy.data(), vex.data(), vey.data());
    grB->SetMarkerStyle(20);
    grB->SetMarkerSize(0.8);
    grB->SetMarkerColor(kRed + 1);

    // Two-panel canvas
    auto cB = new TCanvas("cB", "Exercise B: Log Plots", 1200, 600);
    cB->Divide(2, 1); // 2 columns, 1 row

    // Panel 1: Linear Scale
    cB->cd(1);
    grB->SetTitle("Linear Scale;X Axis;Y Axis");
    grB->Draw("AP");

    // Panel 2: LogY Scale
    cB->cd(2);
    gPad->SetLogy(); // Make the Y-axis logarithmic for this pad
    grB->SetTitle("LogY Scale;X Axis;Y Axis (log scale)");
    grB->Draw("AP"); // Draw the same graph again

    // Save as PNG
    cB->SaveAs("exercise_B_log_plots.png");
    printf("Exercise B saved as 'exercise_B_log_plots.png'.\n");
}

// --- Exercise C: CSV Read and Fit ---
void exerciseC()
{
    // 1. Create the dummy CSV file
    create_dummy_csv_for_C();

    // 2. Read the CSV file (Same as your previous example)
    const char *filename = "data_for_C.csv";
    std::ifstream fin(filename);
    if (!fin)
    {
        Error("exerciseC", "Cannot open %s", filename);
        return;
    }

    std::vector<double> vx, vy, vex, vey;
    std::string line;
    std::getline(fin, line); // Skip header line

    while (std::getline(fin, line))
    {
        std::stringstream ss(line);
        double x, y, ex, ey;
        char comma; // To read the commas
        if (!(ss >> x >> comma >> y >> comma >> ex >> comma >> ey))
            continue; // Skip malformed lines
        vx.push_back(x);
        vy.push_back(y);
        vex.push_back(ex);
        vey.push_back(ey);
    }
    fin.close();

    if (vx.empty())
    {
        Error("exerciseC", "No data read from %s", filename);
        return;
    }

    // 3. Drawing
    auto cC = new TCanvas("cC", "Exercise C: CSV Fit", 800, 600);
    auto geC = new TGraphErrors(vx.size(), vx.data(), vy.data(), vex.data(), vey.data());
    geC->SetTitle("Data from CSV with Quadratic Fit;X Value;Y Value");
    geC->SetMarkerStyle(20);
    geC->SetMarkerColor(kAzure + 7);
    geC->SetLineColor(kAzure + 7);
    geC->Draw("AP");

    // 4. Fit (pol2 = 2nd degree polynomial, p0 + p1*x + p2*x^2)
    // We generated our data in the 0-10 range.
    auto fC = new TF1("fC", "pol2", vx.front(), vx.back());
    fC->SetLineColor(kRed);
    fC->SetLineWidth(2);
    geC->Fit(fC, "R"); // "R" = Fit in the range of the graph

    // 5. Print fit parameters onto the plot
    gStyle->SetOptFit(0);                                   // Turn off the default ROOT fit box
    auto pt = new TPaveText(0.55, 0.65, 0.88, 0.88, "NDC"); // "NDC" = Normalized coordinates
    pt->SetFillColor(0);
    pt->SetBorderSize(0);
    pt->SetTextAlign(12); // Left-aligned
    pt->SetTextFont(42);
    pt->AddText("Fit: y = p0 + p1*x + p2*x^{2}");
    pt->AddText(Form("p0 = %.2f #pm %.2f", fC->GetParameter(0), fC->GetParError(0)));
    pt->AddText(Form("p1 = %.2f #pm %.2f", fC->GetParameter(1), fC->GetParError(1)));
    pt->AddText(Form("p2 = %.2f #pm %.2f", fC->GetParameter(2), fC->GetParError(2)));
    pt->AddText(Form("#chi^{2}/ndf = %.2f / %d = %.2f",
                     fC->GetChisquare(),
                     fC->GetNDF(),
                     fC->GetChisquare() / fC->GetNDF()));
    pt->Draw();

    cC->SaveAs("exercise_C_csv_fit.pdf");
    printf("Exercise C saved as 'exercise_C_csv_fit.pdf'.\n");
}

// --- Main Macro: Run All Exercises ---
void run_exercises()
{
    // Initialize the random number generator
    // (0) -> gives a different result each run (based on time)
    // (fixed number) -> gives the same result every run (reproducible)
    gRandom = new TRandom3(42);

    // General style settings
    gStyle->SetPadGridX(true);
    gStyle->SetPadGridY(true);
    gStyle->SetFrameLineWidth(2);
    gStyle->SetOptStat(0); // Turn off statistics box by default

    // Run the exercises sequentially
    exerciseA();
    exerciseB();
    exerciseC();
}