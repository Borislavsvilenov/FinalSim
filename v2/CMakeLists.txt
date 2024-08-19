cmake_minimum_required(VERSION 3.29)
project(Sim VERSION 0.1.0 LANGUAGES C CXX)

find_package(raylib REQUIRED)

include_directories(Sim PRIVATE objects)

include(CTest)
enable_testing()

add_executable(Sim main.cpp
  objects/Looper.cpp
  objects/Looper.hpp
  objects/Particle.cpp
  objects/Particle.hpp
  objects/Vec2.cpp
  objects/Vec2.hpp)

target_link_libraries(Sim PRIVATE raylib)
target_compile_features(Sim PRIVATE cxx_std_11)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
