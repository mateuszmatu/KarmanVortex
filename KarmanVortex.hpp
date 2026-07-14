#ifndef __KarmanVortex_hpp__
#define __KarmanVortex_hpp__
#include <iostream>
#include <vector>

class KarmanVortex {
public:
    KarmanVortex(double h_, int cr);
    void initialize();
    void printGrid(const std::vector<std::vector<double>>& grid);

private:
    int N;
    int M;
    int cx;
    int cy;
};
#endif // __KarmanVortex_hpp__