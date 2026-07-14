#ifndef __KarmanVortex_hpp__
#define __KarmanVortex_hpp__
#include <iostream>
#include <vector>

class KarmanVortex {
public:
    KarmanVortex(double h_);
    void initialize();
    void printGrid(const std::vector<std::vector<double>>& grid);
    
private:
    int N;
    int M;
};
#endif // __KarmanVortex_hpp__