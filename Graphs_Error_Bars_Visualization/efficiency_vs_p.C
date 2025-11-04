#include <TCanvas.h>

void efficiency_vs_p()
{
    const int n = 15;
    double p[n], eff[n], ex[n], ey[n];
    double pmin = 2, pmax = 50;
    for (int i = 0; i < n; ++i)
    {
        p[i] = pmin + (pmax - pmin) * i / (n - 1.0);
        int N = 500;                                      // trials per point
        double true_eff = 0.95 * (1 - exp(-p[i] / 15.0)); // saturating curve
        int k = gRandom->Binomial(N, true_eff);
        eff[i] = double(k) / N;
        ex[i] = 0.0;
        ey[i] = sqrt(eff[i] * (1 - eff[i]) / N); // binomial error
    }
    auto c = new TCanvas("c", "Efficiency vs p", 900, 600);
    auto ge = new TGraphErrors(n, p, eff, ex, ey);
    ge->SetTitle("Detector Efficiency;Momentum p (GeV);Efficiency");
    ge->SetMarkerStyle(20);
    ge->Draw("AP");
    c->SaveAs("efficiency_vs_p.pdf");
}