#include <TCanvas.h>

void graph_errors()
{
    const int n = 8;
    double x[n] = {1, 2, 3, 4, 5, 6, 7, 8};
    double y[n] = {1.1, 1.9, 3.2, 4.0, 4.9, 6.2, 7.1, 8.1};
    double ex[n] = {0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05}; // x-errors
    double ey[n] = {0.10, 0.12, 0.12, 0.10, 0.12, 0.14, 0.15, 0.15}; // y-errors
    auto c = new TCanvas("c", "Errors", 900, 600);
    auto ge = new TGraphErrors(n, x, y, ex, ey);
    ge->SetTitle("Response with uncertainties;Beam setting;Signal");
    ge->SetMarkerStyle(21);
    ge->SetMarkerColor(kBlue + 1);
    ge->SetLineColor(kBlue + 1);
    ge->SetFillColorAlpha(kBlue - 9, 0.1); // subtle
    ge->Draw("AP");                        // points with axes; error bars shown by default
    auto leg = new TLegend(0.60, 0.15, 0.88, 0.30);
    leg->AddEntry(ge, "Measurement", "lep");
    leg->Draw();
    c->SaveAs("graph_errors.png");
}