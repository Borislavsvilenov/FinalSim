cmake_minimum_required(VERSION 4.2)
project(Falling VERSION 0.1.0 LANGUAGES C CXX)

include_directories(${PROJECT_NAME} PRIVATE objects)

include(CTest FetchContent)
enable_testing()

function(include_dependency libName gitURL gitTag)
  FetchContent_Declare(
    ${libName}
    GIT_REPOSITORY ${gitURL}
    GIT_TAG ${gitTag}
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  FetchContent_MakeAvailable(${libName})
endfunction()

set(LIB1 raylib)
find_package(${LIB1} QUIET)
if (NOT ${LIB1}_FOUND)
  include_dependency(${LIB1} http://github.com/raysan5/raylib.git 5.0)
endif()

add_executable(${PROJECT_NAME} main.cpp
  objects/Looper.cpp
  objects/Looper.hpp
  objects/Particle.cpp
  objects/Particle.hpp
  objects/Vec2.cpp
  objects/Vec2.hpp
  objects/box.cpp
  objects/box.hpp
  objects/QT.cpp
  objects/QT.hpp
  objects/Cammera.cpp
  objects/Cammera.hpp
  objects/ThreadPool.cpp
  objects/ThreadPool.hpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB1})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

set(CMAKE_CXX_STANDART 23)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
