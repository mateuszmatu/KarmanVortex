#include <iostream>
#include "KarmanVortex.hpp"

int main() {
    double h = 1; // Example grid spacing
    int cr = 1;
    KarmanVortex vortex(h, cr);
    vortex.RunSimulation();

    // Additional code to run the simulation or display results

    return 0;
}