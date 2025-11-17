#include <iostream>
#include <vector>
#include <cmath> // For sqrt(), log(), atan2()
#include <string> // For std::string (not in slide, but good practice)

// --- 1. Advanced Particle Class (4-Vector) ---
class Particle {
private:
    double px, py, pz; // 3-momentum components (3D momentum vector)
    double mass;
    int pdgCode; // Particle Data Group ID (e.g., 11 for electron)

public:
    // 1. Constructor initializes all private members.
    Particle(double px_, double py_, double pz_,
             double m, int pdg)
        : px(px_), py(py_), pz(pz_), mass(m), pdgCode(pdg) {}

    // 2. 'getP()': Calculates total momentum. (Magnitude of 3D momentum vector)
    double getP() { return sqrt(px * px + py * py + pz * pz); }

    // 3. 'getEnergy()': Calculates relativistic energy (E^2 = p^2 + m^2).
    double getEnergy() {
        double p = getP();
        return sqrt(p * p + mass * mass);
    }
    
    // 4. 'getPt()': Calculates Transverse Momentum (pT).
    double getPt() { return sqrt(px * px + py * py); }

    // 5. 'getEta()': Calculates Pseudorapidity (common in HEP).
    double getEta() {
        double p = getP();
        return 0.5 * log((p + pz) / (p - pz));
    }
    
    // 6. 'getPhi()': Calculates Azimuthal Angle (common in HEP).
    double getPhi() { return atan2(py, px); }
};


// --- 2. Event Class (Collection of Particles) ---
class Event {
private:
    // 1. An Event 'has a' list (vector) of Particle objects.
    std::vector<Particle> particles;
    int eventNumber;

public:
    // 2. Constructor only needs the event number.
    Event(int num) : eventNumber(num) {}

    // 3. 'addParticle()': Adds a particle object to the internal vector.
    void addParticle(Particle p) {
        particles.push_back(p);
    }

    // 4. 'getNParticles()': Returns how many particles are in the event.
    int getNParticles() { return particles.size(); }

    // 5. 'getTotalEnergy()': Loops over all particles and sums their energy.
    double getTotalEnergy() {
        double sum = 0.0;
        // 6. Uses a modern range-based 'for' loop.
        for (auto& p : particles) { // 'auto&' is "for each particle p..."
            sum += p.getEnergy();
        }
        return sum;
    }

    // 7. 'print()': Displays a summary of the event.
    void print() {
        std::cout << "Event #" << eventNumber << std::endl;
        std::cout << "  Number of particles: " << getNParticles() << std::endl;
        std::cout << "  Total energy: " << getTotalEnergy() << " GeV" << std::endl;
    }
};

// --- 3. Main function to test both classes ---
int main() {
    // 1. Create a few 'advanced' particle objects.
    //       Particle(px,   py,   pz,  mass, pdgID)
    Particle p1(10.0, 5.0,  20.0, 0.106, 13); // Muon
    Particle p2( -8.0, -5.0, 15.0, 0.106, -13); // Anti-Muon

    // 2. Create an event.
    Event myEvent(101); // Event #101

    // 3. Add the particles to the event.
    myEvent.addParticle(p1);
    myEvent.addParticle(p2);

    // 4. Print the event summary.
    myEvent.print();

    return 0;
}