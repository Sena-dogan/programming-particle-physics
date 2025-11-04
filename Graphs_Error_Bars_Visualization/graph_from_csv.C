#include <fstream>
#include <vector>
#include <sstream>
#include <TCanvas.h>

void graph_from_csv(const char *csv = "data_points.csv")
{
    std::ifstream fin(csv);
    if (!fin)
    {
        Error("graph_from_csv", "Cannot open %s", csv);
        return;
    }
    std::vector<double> vx, vy, vex, vey;
    std::string line;
    // expected columns: x,y,ex,ey (with header)
    std::getline(fin, line); // skip header
    while (std::getline(fin, line))
    {
        std::stringstream ss(line);
        double x, y, ex, ey;
        char comma;
        if (!(ss >> x >> comma >> y >> comma >> ex >> comma >> ey))
            continue;
        vx.push_back(x);
        vy.push_back(y);
        vex.push_back(ex);
        vey.push_back(ey);
    }
    auto c = new TCanvas("c", "CSV Graph", 900, 600);
    auto ge = new TGraphErrors(vx.size(), vx.data(), vy.data(), vex.data(), vey.data());
    ge->SetTitle("CSV data with errors;X;Y");
    ge->SetMarkerStyle(21);
    ge->SetMarkerColor(kBlue + 1);
    ge->SetLineColor(kBlue + 1);
    ge->Draw("AP");
    c->SaveAs("graph_from_csv.png");
}