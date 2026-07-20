#include "KarmanVortex.hpp"
#include <iostream>
#include <cmath>

KarmanVortex::KarmanVortex(double h_, int T) {
    // Constructor implementation
    h = h_;
    N = 5.0/h;
    M = 10.0/h;
    cy = N/2.0;
    cx = M/4.0;
    cr = 0.5/h;
    // cr will be used for cylinder radius later on

    dt = 0.001;
    this->T = T;
    visc = 0.1;
    rho = 1.0;
    g = 9.81;
    P0 = 1020.0;
    U = 1.0;
    
    P = std::vector<std::vector<double>>(N, std::vector<double>(M, P0));
    u = std::vector<std::vector<double>>(N, std::vector<double>(M, 0.5));
    v = std::vector<std::vector<double>>(N, std::vector<double>(M, 0.5));
    u_1 = u;
    v_1 = v;
}

void KarmanVortex::SetInflowVelocity(double velocity) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 5; ++j) {
            u[i][j] = velocity; // Set the inflow velocity at the left boundary
        }
    }
}

void KarmanVortex::Cylinder() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            double distance = std::sqrt((i - cy) * (i - cy) + (j - cx) * (j - cx));
            if (distance <= cr) {
                u[i][j] = 0.0;
                v[i][j] = 0.0; 
            }
        }
    }
}

void KarmanVortex::Update() {
    for (int i = 1; i < N - 1; ++i) {
        for (int j = 1; j < M - 1; ++j) {
            double du_dx = (u[i+1][j] - u[i-1][j]) / (2.0 * h);
            double du_dy = (u[i][j+1] - u[i][j-1]) / (2.0 * h);
            double advectionU = u[i][j] * du_dx + v[i][j] * du_dy;

            double pressureU = 1.0/rho * (P[i+1][j] - P[i-1][j]) / (2.0 * h);

            double du2_dx2 = (u[i+1][j] - 2.0 * u[i][j] + u[i-1][j]) / (h * h);
            double du2_dy2 = (u[i][j+1] - 2.0 * u[i][j] + u[i][j-1]) / (h * h);
            double diffusionU = visc * (du2_dx2 + du2_dy2);

            double dv_dx = (v[i+1][j] - v[i-1][j]) / (2.0 * h);
            double dv_dy = (v[i][j+1] - v[i][j-1]) / (2.0 * h);
            double advectionV = u[i][j] * dv_dx + v[i][j] * dv_dy;

            double pressureV = 1.0/rho * (P[i][j+1] - P[i][j-1]) / (2.0 * h);

            double dv2_dx2 = (v[i+1][j] - 2.0 * v[i][j] + v[i-1][j]) / (h * h);
            double dv2_dy2 = (v[i][j+1] - 2.0 * v[i][j] + v[i][j-1]) / (h * h);
            double diffusionV = visc * (dv2_dx2 + dv2_dy2);

            u_1[i][j] = u[i][j] + dt * (-advectionU - pressureU + diffusionU);
            v_1[i][j] = v[i][j] + dt * (-advectionV - pressureV + diffusionV);
            // printGrid(u);
        }
    }
    u = u_1;
    v = v_1;
    // printGrid(v);
    SetInflowVelocity(U);
    Cylinder();
}

void KarmanVortex::RunSimulation() {
    for (int t = 1; t < T; ++t) { // Run for T time steps
        Update();
        std::cout << "Time step: " << t << std::endl;
        // Optionally print or visualize the grid at each step
    }
    save("output/u_final.csv", u);
    save("output/v_final.csv", v);
}

void KarmanVortex::save(const std::string& filename, const std::vector<std::vector<double>>& matrix) {
    std::ofstream outFile(filename);
    
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    for (const auto& row : matrix) {
        for (size_t i = 0; i < row.size(); ++i) {
            outFile << row[i];
            
            if (i < row.size() - 1) {
                outFile << ","; 
            }
        }
        outFile << "\n"; 
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