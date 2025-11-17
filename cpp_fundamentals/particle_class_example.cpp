#include <iostream>
#include <string>
#include <cmath> // REQUIRED for math functions like sqrt().
                 // (Even if it works without this, another library
                 // might be implicitly including it. For portability
                 // [to ensure it works on all systems], you must include it.)

class Particle
{
private: // Internal data, hidden from the outside.
    double momentum;
    double mass;
    std::string name;

public: // Public functions (methods) that user can call.
    // 1. Constructor Options:

    // Curly Braces (Inefficient): First, default-constructs the variables (creates them empty),
    // then assigns (copies) the values to them inside the {}. ("Default construct, then assign/overwrite").

    //     Particle(double p, double m, std::string n)
    // {
    //     momentum = p; // (assignment)
    //     mass = m;     // (assignment)
    //     name = n;     // (assignment)
    // }

    // Initializer List (Efficient): Directly constructs the variables with the desired values.
    // ("Direct construction").

    // 2. The 'Constructor': Called when a new object is created.
    //    It uses an "initializer list" to set private members.
    Particle(double p, double m, std::string n)
        : momentum(p), mass(m), name(n) {}

    // 3. 'getEnergy()': A member function that calculates energy from private data.
    double getEnergy()
    {
        return sqrt(momentum * momentum + mass * mass);
    }

    // 4. 'getBeta()': Another member function (uses another member function).
    double getBeta()
    {
        return momentum / getEnergy();
    }

    // 5. 'print()': A helper function to display all the particle's info.
    void print()
    {
        std::cout << "Particle: " << name << std::endl;
        std::cout << "  Momentum: " << momentum << " GeV/c" << std::endl;
        std::cout << "  Energy: " << getEnergy() << " GeV" << std::endl;
        std::cout << "  Beta: " << getBeta() << std::endl;
    }
};

// --- 2. Using the Class (Listing 15) ---
int main()
{
    // 1. Create 'instances' (objects) of our Particle class.
    Particle electron(50.0, 0.000511, "Electron");
    Particle proton(100.0, 0.938, "Proton");
    Particle muon(75.0, 0.106, "Muon");

    // 2. Call the 'print()' method on each object.
    electron.print();
    std::cout << std::endl; // Add a space
    proton.print();
    std::cout << std::endl;
    muon.print();

    return 0;
}