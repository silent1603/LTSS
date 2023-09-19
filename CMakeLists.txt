cmake_minimum_required(VERSION 3.14)

project(RayTracing VERSION 1.0 DESCRIPTION "parallel programming" LANGUAGES C CXX)
add_executable(RayTracing)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Examples)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor)

target_sources(RayTracing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)



include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

ExternalProject_Add(glm
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/vendor
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG  0.9.9.8 
    BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/$<CONFIG>
)

ExternalProject_Add(sdl2
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/vendor
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git 
    GIT_TAG release-2.28.3 
    BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/$<CONFIG>
)

add_dependencies(RayTracing glm sdl2)

target_include_directories(RayTracing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor )
target_link_directories(RayTracing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
target_compile_features(RayTracing PRIVATE cxx_std_17)

if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT RayTracing)
    set_property(TARGET RayTracing PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>)
    set_target_properties(RayTracing PROPERTIES  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
endif()

