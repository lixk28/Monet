cmake_minimum_required(VERSION 3.16)

project(Monet VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wconversion -Wshadow -g")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall")


set(IMGUI_DIR Libraries/ImGui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
)

add_library(ImGui STATIC ${IMGUI_SOURCES})

target_include_directories(ImGui PRIVATE ${IMGUI_DIR} ${IMGUI_DIR}/backends)

if(UNIX)
    find_package(glfw3 REQUIRED)
    find_package(OpenGL REQUIRED)
    target_link_libraries(ImGui PRIVATE glfw OpenGL::GL X11)
    set(IMGUI_RENDERER_BACKEND ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)
    set(IMGUI_PLATFORM_BACKEND ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp)
else()
    message("You are unwelcome since you are on a non-unix system.")
    message("Goodbye :D")
endif()

target_sources(ImGui PRIVATE
    ${IMGUI_RENDERER_BACKEND}
    ${IMGUI_PLATFORM_BACKEND}
)


# copy fonts
file(GLOB FONT_SOURCES ${CMAKE_SOURCE_DIR}/Libraries/ImGui/misc/fonts/*.ttf)
set(FONT_DEST ${CMAKE_BINARY_DIR}/fonts)
file(MAKE_DIRECTORY ${FONT_DEST})

foreach(font_file ${FONT_SOURCES})
    get_filename_component(font_filename ${font_file} NAME)
    configure_file(${font_file} ${FONT_DEST}/${font_filename} COPYONLY)
endforeach()


# add_subdirectory(Monet)

add_executable(Monet Main.cpp)

target_include_directories(Monet
    PUBLIC ${IMGUI_DIR}
    PUBLIC ${IMGUI_DIR}/backends
)

target_link_libraries(Monet PRIVATE ImGui)
