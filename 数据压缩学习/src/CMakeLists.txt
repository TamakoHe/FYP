cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE "/Users/hewenxiao/Documents/CPP/Vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(VCPKG_TARGET_TRIPLET "arm64-osx" CACHE STRING "")
set(quirc_DIR "/Users/hewenxiao/Documents/CPP/Vcpkg/vcpkg/installed/arm64-osx/share/quirc")
set(OpenCV_DIR "/Users/hewenxiao/Documents/CPP/Vcpkg/vcpkg/installed/arm64-osx/share/opencv4")
project(Compressed)
set(CMAKE_CXX_STANDARD 23)

find_package(OpenCV REQUIRED)

add_executable(entropy entropy/entropy.cpp
        huffman/huffman.cpp)
add_executable(Huffman huffman/huffman.cpp)
add_executable(LZW LZW/LZW.cpp)
target_include_directories(LZW PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(LZW PRIVATE ${OpenCV_LIBS})