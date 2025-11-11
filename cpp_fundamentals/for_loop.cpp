#include <iostream>

int main()
{
    int totalEvents = 100;
    int selectedEvents = 0;

    // Process multiple events
    for (int i = 0; i < totalEvents; i++)
    {
        double energy = 50.0 + (rand() % 100); // Random energy
        // Event selection : E > 100 GeV
        if (energy > 100.0)
        {
            selectedEvents++;
            std ::cout << " Event " << i << " : E = "
                       << energy << " GeV ( SELECTED ) " << std ::endl;
        }
        else
        {
            std ::cout << " Event " << i << " : E = "
                       << energy << " GeV  ( UNSELECTED!!!!)" << std ::endl;
        }
    }
    std ::cout << "\nTotal selected : " << selectedEvents
               << " out of " << totalEvents << std ::endl;

    return 0;
}