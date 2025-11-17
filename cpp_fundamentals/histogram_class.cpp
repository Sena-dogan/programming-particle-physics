#include <vector>
#include <iostream>

// 1. Defines a 'blueprint' (class) for a simple Histogram object.
class Histogram
{
private:                   // Internal variables that the user doesn't need to see.
    std::vector<int> bins; // A vector to store the counts for each bin
    double min, max, binWidth;
    int nBins;

public: // Public functions (methods) that the user can call.
    // 2. The 'Constructor': This is called when you create a new Histogram.
    //    It sets up the bin vector and calculates the bin width.
    Histogram(int n, double xmin, double xmax)
        : nBins(n), min(xmin), max(xmax)
    {

        bins.resize(nBins, 0); // Resize the vector to nBins and fill with 0s
        binWidth = (max - min) / nBins;
    }

    // 3. The 'fill' method: This adds a value to the histogram.
    void fill(double value)
    {
        // Ignore values that are outside the histogram's range
        if (value < min || value >= max)
            return;

        // 4. Calculate which bin this value belongs to.
        int bin = (value - min) / binWidth;

        // Add 1 to that bin's counter
        if (bin >= 0 && bin < nBins)
            bins[bin]++;
    }

    // 5. The 'print' method: This displays the histogram data.
    void print()
    {
        for (int i = 0; i < nBins; i++)
        {
            // Calculate the center of the current bin
            double center = min + (i + 0.5) * binWidth;
            // Print the bin center and the number of counts in that bin
            std::cout << center << "\t" << bins[i] << std::endl;
        }
    }
};