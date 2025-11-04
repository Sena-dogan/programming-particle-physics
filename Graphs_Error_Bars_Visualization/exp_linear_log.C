#include <TCanvas.h>

void exp_linear_log()
{
    const int n = 50;
    double x[n], y[n];
    for (int i = 0; i < n; ++i)
    {
        x[i] = i * 0.5;
        y[i] = 2.0 * exp(-0.3 * x[i]) * (1 + 0.05 * gRandom->Gaus());
    }
    auto c = new TCanvas("c", "Exp", 1000, 500);
    c->Divide(2, 1);
    c->cd(1);
    gPad->SetGrid(1, 1);
    auto g1 = new TGraph(n, x, y);
    g1->SetTitle("Linear;Time;Amplitude");
    g1->SetMarkerStyle(20);
    g1->Draw("AP");
    c->cd(2);
    gPad->SetLogy(1);
    auto g2 = (TGraph *)g1->Clone("g2");
    g2->SetTitle("LogY;Time;Amplitude");
    g2->Draw("AP");
    c->SaveAs("exp_linear_log.png");
}