cmake_minimum_required(VERSION 3.16.3)

project(imgui_animlib)
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
file(GLOB IMGUI_SRC ${PARENT_DIR}/imgui/imgui*.cpp)
file(GLOB ANIMLIB_IMGUI_SRC imgui_*.cpp)
#add_executable (imgui_animlib ${IMGUI_SRC} ${ANIMLIB_IMGUI_SRC} )
add_library (imgui_animlib SHARED ${IMGUI_SRC} ${ANIMLIB_IMGUI_SRC})
target_include_directories(imgui_animlib PUBLIC ${PARENT_DIR}/imgui)
