cmake_minimum_required(VERSION 3.17)
project(SampleRateComparison)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/libsamplerate)

add_executable(libSampleRateComp src/samplerate_main.cpp)
target_link_libraries(libSampleRateComp samplerate)

add_library(r8free lib/r8brain-free-src/r8bbase.cpp lib/r8brain-free-src/pffft.cpp)
target_include_directories(r8free PUBLIC lib/r8brain-free-src)
target_compile_definitions(r8free PUBLIC R8B_PFFFT=1)

add_executable(r8Comp src/r8_main.cpp)
target_link_libraries(r8Comp r8free)


add_library(speex_dsp lib/speexdsp/libspeexdsp/buffer.c
        lib/speexdsp/libspeexdsp/fftwrap.c
        lib/speexdsp/libspeexdsp/filterbank.c
        lib/speexdsp/libspeexdsp/jitter.c
        lib/speexdsp/libspeexdsp/kiss_fft.c
        lib/speexdsp/libspeexdsp/kiss_fftr.c
        lib/speexdsp/libspeexdsp/mdf.c
        lib/speexdsp/libspeexdsp/preprocess.c
        lib/speexdsp/libspeexdsp/resample.c
        lib/speexdsp/libspeexdsp/scal.c
        lib/speexdsp/libspeexdsp/smallft.c
        )
target_include_directories(speex_dsp PUBLIC lib/speexdsp/include)
target_compile_definitions(speex_dsp PUBLIC FLOATING_POINT=1 USE_SSE=1 USE_KISS_FFT=1 EXPORT=)

add_executable(speexComp src/speex_main.cpp)
target_link_libraries(speexComp speex_dsp)