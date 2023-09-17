cmake_minimum_required(VERSION 3.14)

project(RayTracing VERSION 1.0 DESCRIPTION "parallel programming" LANGUAGES C CXX)
add_executable(RayTracing)

add_subdirectory(Examples)
add_subdirectory(vendor)

target_sources(RayTracing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_include_directories(RayTracing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
target_link_directories(RayTracing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
target_link_libraries(RayTracing PUBLIC OpenMP)
target_compile_features(RayTracing PRIVATE cxx_std_17)

if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT RayTracing)
endif()