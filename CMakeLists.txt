cmake_minimum_required(VERSION 3.14)

project(LTSS_PRJ VERSION 1.0 DESCRIPTION "parallel programming" LANGUAGES C CXX)
add_executable(LTSS_PRJ)

add_subdirectory(Examples)
add_subdirectory(vendor)

target_sources(LTSS_PRJ PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_include_directories(LTSS_PRJ PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
target_link_directories(LTSS_PRJ PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
target_link_libraries(LTSS_PRJ PUBLIC OpenMP)
target_compile_features(LTSS_PRJ PRIVATE cxx_std_17)

if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LTSS_PRJ)
endif()