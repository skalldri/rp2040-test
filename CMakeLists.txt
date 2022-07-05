cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr 3.1.0 EXACT REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(rp2040)

target_sources(app PRIVATE src/main.cpp)