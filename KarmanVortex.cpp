#include "KarmanVortex.hpp"
#include <iostream>

KarmanVortex::KarmanVortex(double h_, int cr) {
    // Constructor implementation
    N = 5/h_;
    M = 10/h_;
    cy = N/2;
    cx = M/4;
}

void KarmanVortex::initialize() {
    // Initialize the grid and other parameters
    std::vector<std::vector<double>> grid(N, std::vector<double>(M, 0.0)); 
    grid[cy][cx] = 1;
    printGrid(grid);
    // Additional initialization code here
}

void KarmanVortex::printGrid(const std::vector<std::vector<double>>& grid) {
    for (const auto& row : grid) {
        for (const auto& value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}