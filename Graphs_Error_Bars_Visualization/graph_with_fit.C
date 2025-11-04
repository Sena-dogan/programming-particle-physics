#include <TCanvas.h>

void graph_with_fit()
{
    const int n = 10;
    double x[n], y[n], ex[n], ey[n];
    for (int i = 0; i < n; ++i)
    {
        x[i] = i + 1;
        y[i] = 1.0 + 0.9 * x[i] + gRandom->Gaus(0, 0.2); // gRandom->Gaus(mean, sigma) -> X = mean + sigma*GaussianRandom
        ex[i] = 0.0;
        ey[i] = 0.15;
    }
    auto c = new TCanvas("c", "Fit", 900, 600);
    auto ge = new TGraphErrors(n, x, y, ex, ey);
    ge->SetTitle("Data with linear fit;X;Y");
    ge->SetMarkerStyle(20);
    ge->Draw("AP");

    auto f = new TF1("f", "[0] + [1]*x", 0, 12);
    f->SetParameters(0.5, 1.0);
    ge->Fit(f, "Q"); // quiet fit
    f->SetLineColor(kGreen + 2);
    f->SetLineWidth(2);
    f->Draw("same");

    auto leg = new TLegend(0.58, 0.15, 0.88, 0.35);
    leg->AddEntry(ge, "Data (with errors)", "lep");
    leg->AddEntry(f, Form("Fit: y = %.2f + %.2f x", f->GetParameter(0), f->GetParameter(1)), "l");
    leg->Draw();

    c->SaveAs("graph_with_fit.png");
}