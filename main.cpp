#include <iostream>
#include "KarmanVortex.hpp"

int main() {
    double h = 0.1; // Example grid spacing
    int T = 5000;
    KarmanVortex vortex(h, T);
    vortex.RunSimulation();

    // Additional code to run the simulation or display results

    return 0;
}