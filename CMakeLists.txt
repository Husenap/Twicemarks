cmake_minimum_required(VERSION 3.5.0)
project("Twicemarks" C CXX)

message("-- CONFIGURATION TYPES: ${CMAKE_CONFIGURATION_TYPES}")

include("cmake/compiler_features.cmake")
include("cmake/compiler_warnings.cmake")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "predefined")
set_property(GLOBAL PROPERTY CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory("dububench")
add_subdirectory("momobrot")