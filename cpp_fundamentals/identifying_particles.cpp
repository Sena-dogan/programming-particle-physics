#include <iostream>

int main()
{
    int pdgCode = 11; // PDG (Particle Data Group) particle code

    if (pdgCode == 11)
    {
        std ::cout << " Electron detected ! " << std ::endl;
    }
    else if (pdgCode == -11)
    {
        std ::cout << " Positron detected ! " << std ::endl;
    }
    else if (pdgCode == 13)
    {
        std ::cout << " Muon detected ! " << std ::endl;
    }
    else if (pdgCode == 22)
    {
        std ::cout << " Photon detected ! " << std ::endl;
    }
    else
    {
        std ::cout << " Unknown particle " << std ::endl;
    }
    return 0;
}

// PDG Codes Reference:
// Electron: 11
// Positron: -11 (Anti-particle of electron)
// Muon: 13
// Photon: 22
// Proton: 2212
// Neutron: 2112
// Pion+: 211
// Pion-: -211
// Kaon+: 321
// Kaon-: -321
// Higgs Boson: 25 