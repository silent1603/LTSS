cmake_minimum_required(VERSION 3.14)

project(RayTracing VERSION 1.0 DESCRIPTION "parallel programming" LANGUAGES C CXX)
add_executable(RayTracing)
set(CMAKE_DEBUG_POSTFIX d)
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor)

target_sources(RayTracing PUBLIC ${CMAKE_SOURCE_DIR}/src/main.cpp)



target_include_directories(RayTracing PUBLIC ${CMAKE_SOURCE_DIR}/vendor )
target_link_directories(RayTracing PUBLIC  ${CMAKE_SOURCE_DIR}/lib)
target_compile_features(RayTracing PRIVATE cxx_std_17)

if (MSVC)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT RayTracing)
    set_property(TARGET RayTracing PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    set_target_properties(RayTracing PROPERTIES  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
endif()


set_target_properties( RayTracing
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)