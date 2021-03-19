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