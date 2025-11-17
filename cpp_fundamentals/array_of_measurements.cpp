#include <iostream>

int main()
{
    // Array of detector readings ( ADC counts )
    int adcReadings[10] = {150, 145, 152, 148, 151,
                           147, 149, 153, 146, 150};

    //  // Low Standard Deviation: Data points are very close to the average (mean).
    //  // (e.g., [10, 10.1, 9.9, 10]) Your measurements are very consistent.

    //  // High Standard Deviation: Data points are spread out far from the average.
    //  // (e.g., [15, 5, 20, 0]) Your measurements are very inconsistent.

    //  --- Sample Standard Deviation Formula ---
    //  s = sqrt(  sum[ (x_i - x_bar)^2 ] / (n - 1)  )

    // Calculate average
    double sum = 0.0;
    for (int i = 0; i < 10; i++)
    {
        sum += adcReadings[i];
    }
    double average = sum / 10.0;
    // Calculate standard deviation
    double variance = 0.0;
    for (int i = 0; i < 10; i++)
    {
        // sum[ (x_i - x_bar)^2 ]
        variance += (adcReadings[i] - average) *
                    (adcReadings[i] - average);
    }

    // / (n - 1)
    double stdDev = sqrt(variance / 9.0);
    std ::cout << " Average : " << average << std ::endl;
    std ::cout << " Std Dev : " << stdDev << std ::endl;
    return 0;
}