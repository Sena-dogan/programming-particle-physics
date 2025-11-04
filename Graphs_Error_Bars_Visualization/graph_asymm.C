#include <TCanvas.h>

void graph_asymm()
{
    const int n = 6;
    double x[n] = {1, 2, 3, 4, 5, 6};
    double y[n] = {1.1, 2.2, 2.9, 4.1, 5.1, 6.2};
    double exl[n] = {0.05, 0.05, 0.05, 0.05, 0.05, 0.05};
    double exh[n] = {0.05, 0.05, 0.05, 0.05, 0.05, 0.05};
    double eyl[n] = {0.05, 0.10, 0.08, 0.09, 0.12, 0.10}; // lower
    double eyh[n] = {0.12, 0.15, 0.11, 0.10, 0.15, 0.12}; // upper
    auto c = new TCanvas("c", "Asymmetric", 900, 600);
    auto ga = new TGraphAsymmErrors(n, x, y, exl, exh, eyl, eyh);
    ga->SetTitle("Asymmetric uncertainties;Setting;Signal");
    ga->SetMarkerStyle(33);
    ga->SetMarkerColor(kRed + 1);
    ga->SetLineColor(kRed + 1);
    ga->Draw("AP");
    c->SaveAs("graph_asymm.png");
}