//
// Created by Paul Walker on 3/17/21.
//

#include <iostream>
#include "CDSPResampler.h"
#include <fstream>

int main() {
    static constexpr int blocksz = 64;
    double input[blocksz];

    double dstsr = 96000;
    r8b::CDSPResampler24 rs(48000, dstsr, blocksz, 8.0);
    rs.clear();

    std::cout << rs.getInLenBeforeOutStart() << " " << rs.getLatency() << " " << rs.getMaxOutLen(blocksz) << std::endl;

    // Lets just do a naive saw wave
    auto dphase = 440.0 / 48000;
    auto phase = 0.0;

    std::ofstream f48("r8_48.csv" );
    std::ofstream f881("r8_882.csv");

    // Pre-seed the resampler
    memset(input, 0, blocksz * sizeof(double));
    for( int i=0; i<0; ++i )
    {
        double *res = nullptr;
        rs.process(input, blocksz, res);
    }
    int is=0, os=0;

    for( int i=0; i<20; ++i )
    {
        double *res = nullptr;
        for( int s=0; s<blocksz; ++s)
        {
            input[s] = phase * 2 - 1;
            f48 << is * 1.0 << ", " << input[s] << std::endl;
            is++;
            phase += dphase;
            phase -= (phase > 1);
        }
        auto gens = rs.process(input, blocksz, res );
        std::cout << "Generated " << gens << std::endl;
        for( int s=0; s<gens; ++s )
        {
            f881 << os * 1.0 * 48000 / dstsr << ", "  << res[s] << std::endl;
            os++;
        }

    }



    return 0;
}
