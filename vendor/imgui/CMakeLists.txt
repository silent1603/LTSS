cmake_minimum_required(VERSION 3.14)
add_library(imgui STATIC )
set(IMGUI_H_FILES
  imgui.h
  imconfig.h
  imgui_internal.h
  imstb_rectpack.h
  imstb_textedit.h
  imstb_truetype.h
  imgui_impl_opengl3.h 
  imgui_impl_sdl2.h 
  imgui_impl_opengl3_loader.h 
)

set(IMGUI_CXX_FILES
  imgui.cpp
  imgui_draw.cpp
  imgui_widgets.cpp
  imgui_demo.cpp
  imgui_tables.cpp 
  imgui_impl_opengl3.cpp 
  imgui_impl_sdl2.cpp
)
target_sources(imgui PRIVATE ${IMGUI_H_FILES}  ${IMGUI_CXX_FILES})
target_link_libraries(RayTracing PUBLIC imgui)