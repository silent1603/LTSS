add_subdirectory(openmp)
add_subdirectory(imgui)
add_subdirectory(glad)
include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG  0.9.9.8 
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/glm 
    GIT_PROGRESS TRUE
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  # Fetch the content using previously declared details
  FetchContent_Populate(glm)

  # Set custom variables, policies, etc.
  # ...

  # Bring the populated content into the build
  add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()

FetchContent_Declare(sdl2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git 
    GIT_TAG release-2.28.3 
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/SDL2 
    GIT_PROGRESS TRUE
)

FetchContent_GetProperties(sdl2)
if(NOT sdl2_POPULATED)
  # Fetch the content using previously declared details
  FetchContent_Populate(sdl2)

  # Set custom variables, policies, etc.
  # ...

  # Bring the populated content into the build
  add_subdirectory(${sdl2_SOURCE_DIR} ${sdl2_BINARY_DIR})
endif()

if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(RayTracing PRIVATE SDL2::SDL2main)
endif()


set_target_properties(SDL2main SDL2 glm imgui glad 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
)
target_include_directories(imgui PRIVATE ${sdl2_SOURCE_DIR}/include)
# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
target_link_libraries(RayTracing PRIVATE SDL2::SDL2)
target_link_libraries(RayTracing PRIVATE glm )