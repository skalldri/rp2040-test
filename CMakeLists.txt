cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(rp2040 LANGUAGES C CXX)

target_sources(app PRIVATE src/main.cpp)