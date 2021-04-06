#include <iostream>
#include <fstream>

#include "speex/speex_resampler.h"

int main() {
    int err;
    auto sps = speex_resampler_init(1, 48000, 88200, 7, &err);
    if( err != RESAMPLER_ERR_SUCCESS )
    {
        std::cout << "Sad Trombone" << std::endl;
        return 1;
    }

    static constexpr int blocksz = 64, outbs = blocksz << 3;
    float input[blocksz], output_buffer[outbs];

    // Lets just do a naive saw wave
    auto dphase = 440.0 / 48000;
    float phase = 0;

    std::ofstream f48("speex48.csv" );
    std::ofstream f881( "speex882.csv");

    int is=0, os=0;
    for( int i=0; i<10; ++i )
    {
        for( int s=0; s<blocksz; ++s)
        {
            input[s] = phase * 2 - 1;
            f48 << is * 1.0  << ", " << input[s] << std::endl;
            is++;
            phase += dphase;
            phase -= (phase > 1);

        }
        spx_uint32_t inlen = blocksz;
        spx_uint32_t outlen = outbs;
        auto gens = speex_resampler_process_float(sps, 0, input, &inlen, output_buffer, &outlen);
        std::cout << "Generated " << outlen << " from " << inlen << std::endl;
        for( int s=0; s<outlen; ++s )
        {
            f881 << os * 1.0 * 48000 / 88200 << ", " << output_buffer[s] << std::endl;
            os++;
        }
    }


    speex_resampler_destroy(sps);
    return 0;
}
