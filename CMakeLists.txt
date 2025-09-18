cmake_minimum_required(VERSION 3.16)
project(MegaHackOverlay)

find_package(Geode REQUIRED)

geode_mod(NAME "MegaHack Overlay" ID "yourname.megahack_overlay" VERSION "0.1.0")

target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
