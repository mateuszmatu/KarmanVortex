#include "KarmanVortex.hpp"

KarmanVortex::KarmanVortex(double h_) {
    // Constructor implementation
    N = 100/h_;
    M = 50/h_;
}

void KarmanVortex::initialize() {
    // Initialize the grid and other parameters

    int a = N * M; 
    std::cout << a << std::endl;
    // Additional initialization code here
}