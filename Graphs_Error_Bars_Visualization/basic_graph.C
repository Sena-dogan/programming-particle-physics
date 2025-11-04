#include <TCanvas.h>

void basic_graph()
{
    double x[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double y[] = {1.1, 1.9, 3.2, 4.0, 4.9, 6.2, 7.1, 8.1};
    auto c = new TCanvas("c", "Basic Graph", 900, 600);
    auto g = new TGraph(8, x, y);
    g->SetTitle("Detector response;Beam setting (arb.);Signal (arb.)");
    g->SetMarkerStyle(20);
    g->SetMarkerSize(1.1);
    g->SetLineWidth(2);
    g->Draw("APL"); // A: axes, P: points, L: lines
    c->SaveAs("basic_graph.png");
}