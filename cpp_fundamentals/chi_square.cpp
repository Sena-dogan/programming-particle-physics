#include <iostream>
#include <vector>
#include <cmath> // Required for sqrt(), pow(), etc.

// 1. A function to calculate the chi-square value.
//    It compares 'observed' data to 'expected' (model) data.
double chiSquare(const std::vector<double> &observed,
                 const std::vector<double> &expected)
{
    double chi2 = 0.0;
    for (size_t i = 0; i < observed.size(); i++)
    {
        // 2. The Chi-Square formula: sum[ (obs - exp)^2 / exp ]
        if (expected[i] > 0)
        { // Avoid division by zero
            double diff = observed[i] - expected[i];
            chi2 += (diff * diff) / expected[i];
        }
    }
    return chi2;
}

int main()
{
    // 1. Our data: 5 bins of observed counts.
    std::vector<double> observed = {95, 105, 98, 102, 100};
    // 2. Our model: We expected 100 counts in every bin.
    std::vector<double> expected = {100, 100, 100, 100, 100};

    // 3. Calculate the chi-square value.
    double chi2 = chiSquare(observed, expected);

    // 4. 'Degrees of freedom' (NDF) is (number of bins) - (number of fitted parameters)
    //    Here, we didn't fit parameters (just a flat line), so it's N_bins - 1.
    int ndf = observed.size() - 1;

    std::cout << "Chi-square: " << chi2 << std::endl;
    std::cout << "NDF: " << ndf << std::endl;

    // 5. A good fit has chi2/ndf close to 1.
    std::cout << "Chi-square / NDF: " << chi2 / ndf << std::endl;
    return 0;
}