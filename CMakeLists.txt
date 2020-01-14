cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
find_package(Imagine REQUIRED)

project(Crossblock)
add_executable(Crossblock main.cpp Point.cpp Param.cpp Edition.cpp Jeu.cpp Config.cpp)
ImagineUseModules(Crossblock Graphics)
