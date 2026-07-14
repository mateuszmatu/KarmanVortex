#ifndef __KarmanVortex_hpp__
#define __KarmanVortex_hpp__
#include <iostream>
#include <vector>

class KarmanVortex {
public:
    KarmanVortex(double h_, int cr);
    void printGrid(const std::vector<std::vector<double>>& grid);
    void Update();
    void RunSimulation();
    void SetInflowVelocity(double velocity);

private:
    double h;
    std::vector<std::vector<double>> P;
    std::vector<std::vector<double>> u_1;
    std::vector<std::vector<double>> v_1;
    std::vector<std::vector<double>> u;
    std::vector<std::vector<double>> v;
    double U;
    int T;
    int N;
    int M;
    int cx;
    int cy;
    double dt;
    double visc;
    double rho;
    double g;
    double P0;
};
#endif // __KarmanVortex_hpp__