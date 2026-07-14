#ifndef __KarmanVortex_hpp__
#define __KarmanVortex_hpp__
#include <iostream>

class KarmanVortex {
public:
    KarmanVortex(double h_);
    void initialize();

private:
    int N;
    int M;
};
#endif // __KarmanVortex_hpp__