#include "TCanvas.h"

void styling_bestpractices()
{
    auto c = new TCanvas("c", "Styles", 900, 600);
    const int n = 12;
    double x[n], y1[n], y2[n];
    for (int i = 0; i < n; ++i)
    {
        x[i] = i;
        y1[i] = TMath::Sin(0.4 * i) + 1;
        y2[i] = TMath::Cos(0.4 * i) + 1;
    }
    auto g1 = new TGraph(n, x, y1);
    g1->SetTitle("Comparison;Index;Value");
    g1->SetMarkerStyle(20);
    g1->SetMarkerColor(kAzure + 2);
    g1->SetLineColor(kAzure + 2);
    g1->Draw("APL");
    auto g2 = new TGraph(n, x, y2);
    g2->SetMarkerStyle(24);
    g2->SetMarkerColor(kOrange + 7);
    g2->SetLineColor(kOrange + 7);
    g2->SetLineStyle(2);
    g2->Draw("PL same");
    gPad->SetGrid(1, 1);
    auto leg = new TLegend(0.62, 0.72, 0.88, 0.88);
    leg->AddEntry(g1, "sin-like", "lp");
    leg->AddEntry(g2, "cos-like", "lp");
    leg->Draw();
    c->SaveAs("styling_bestpractices.png");
}