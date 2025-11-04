#include "TCanvas.h"

void multiplot_log()
{
    auto c = new TCanvas("c", "Multiplot", 1000, 500);
    c->Divide(2, 1);
    // Left: linear
    c->cd(1);
    gPad->SetGrid(1, 1);
    const int n = 30;
    double x[n], y[n];
    for (int i = 0; i < n; ++i)
    {
        x[i] = i + 1;
        y[i] = TMath::Exp(-0.15 * x[i]) + 0.02 * gRandom->Gaus();
    }
    auto g1 = new TGraph(n, x, y);
    g1->SetTitle("Linear scale;Time;Signal");
    g1->SetMarkerStyle(20);
    g1->Draw("AP");
    // Right: logY
    c->cd(2);
    gPad->SetLogy(1);
    auto g2 = (TGraph *)g1->Clone("g2");
    g2->SetTitle("Log scale;Time;Signal");
    g2->Draw("AP");
    c->SaveAs("multiplot_log.png");
}
