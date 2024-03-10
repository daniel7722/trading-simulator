cmake_minimum_required(VERSION 3.27)
project(option_pricing)

set(CMAKE_CXX_STANDARD 17)

add_executable(option_pricing main.cpp
        include/Pricing.h
        src/Pricing.cpp
)
