//
// Created by Paul Walker on 3/17/21.
//

#include <iostream>
#include "CDSPResampler.h"

int main() {
    static constexpr int blocksz = 64;
    double input[blocksz];

    r8b::CDSPResampler24 rs(88100, 48000, blocksz);
    rs.clear();

    std::cout << rs.getInLenBeforeOutStart() << " " << rs.getLatency() << " " << rs.getMaxOutLen(blocksz) << std::endl;

    // Lets just do a naive saw wave
    auto dphase = 440.0 / 48000;
    auto phase = 0;

    for( int i=0; i<50; ++i )
    {
        double *res = nullptr;
        for( int s=0; s<blocksz; ++s)
        {
            input[s] = phase * 2 - 1;
            phase += dphase;
            phase -= (phase > 1);
        }
        auto gens = rs.process(input, blocksz, res );
        std::cout << "Generated " << gens << std::endl;
    }



    return 0;
}
