#include "KarmanVortex.hpp"
#include <iostream>

KarmanVortex::KarmanVortex(double h_, int cr) {
    // Constructor implementation
    h = h_;
    N = 5/h;
    M = 10/h;
    cy = N/2;
    cx = M/4;
    // cr will be used for cylinder radius later on

    dt = 0.01;
    T = 50;
    visc = 0.1;
    rho = 1;
    g = 9.81;
    P0 = 20;
    U = 1.0;
    
    P = std::vector<std::vector<double>>(N, std::vector<double>(M, P0));
    u = std::vector<std::vector<double>>(N, std::vector<double>(M, 0.0));
    v = std::vector<std::vector<double>>(N, std::vector<double>(M, 0.0));
    u_1 = u;
    v_1 = v;

    printGrid(u);
}

void KarmanVortex::SetInflowVelocity(double velocity) {
    for (int i = 0; i < N; ++i) {
        u[i][0] = velocity; // Set the inflow velocity at the left boundary
    }
}

void KarmanVortex::Update() {
    for (int i = 1; i < N - 1; ++i) {
        for (int j = 1; j < M - 1; ++j) {
            double du_dx = (u[i+1][j] - u[i-1][j]) / (2 * h);
            double du_dy = (u[i][j+1] - u[i][j-1]) / (2 * h);
            double advectionU = u[i][j] * du_dx + v[i][j] * du_dy;

            double pressureU = 1/rho * (P[i+1][j] - P[i-1][j]) / (2 * h);

            double du2_dx2 = (u[i+1][j] - 2 * u[i][j] + u[i-1][j]) / (h * h);
            double du2_dy2 = (u[i][j+1] - 2 * u[i][j] + u[i][j-1]) / (h * h);
            double diffusionU = visc * (du2_dx2 + du2_dy2);

            double dv_dx = (v[i+1][j] - v[i-1][j]) / (2 * h);
            double dv_dy = (v[i][j+1] - v[i][j-1]) / (2 * h);
            double advectionV = u[i][j] * dv_dx + v[i][j] * dv_dy;

            double pressureV = 1/rho * (P[i][j+1] - P[i][j-1]) / (2 * h);

            double dv2_dx2 = (v[i+1][j] - 2 * v[i][j] + v[i-1][j]) / (h * h);
            double dv2_dy2 = (v[i][j+1] - 2 * v[i][j] + v[i][j-1]) / (h * h);
            double diffusionV = visc * (dv2_dx2 + dv2_dy2);

            u_1[i][j] = u[i][j] + dt * (-advectionU - pressureU + diffusionU);
            v_1[i][j] = v[i][j] + dt * (-advectionV - pressureV + diffusionV);
        }
    }
    u = u_1;
    v = v_1;
    SetInflowVelocity(U);
}

void KarmanVortex::RunSimulation() {
    for (int t = 1; t < T; ++t) { // Run for 100 time steps
        Update();
        // Optionally print or visualize the grid at each step
        std::cout << "Time step: " << t << std::endl;
        printGrid(u);
    }
}

void KarmanVortex::printGrid(const std::vector<std::vector<double>>& grid) {
    for (const auto& row : grid) {
        for (const auto& value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}