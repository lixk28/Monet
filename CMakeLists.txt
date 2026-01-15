cmake_minimum_required(VERSION 3.16)

project(Monet VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(USE_QT6 ON)
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(Libraries/QtNodes)

set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wconversion -Wshadow -g")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall")

set(CMAKE_AUTOMOC ON)

add_subdirectory(App)

add_executable(Monet
    Main.cpp
)

target_link_libraries(Monet
PRIVATE
    # Qt6::Core Qt6::Gui Qt6::Widgets
    # QtNodes::QtNodes
    App
)

target_include_directories(Monet
PRIVATE
    ${QT_NODES_DIR}/include
    App
)




# # ImGui
# set(IMGUI_DIR Libraries/ImGui)
# set(IMGUI_SOURCES
#     ${IMGUI_DIR}/imgui.cpp
#     ${IMGUI_DIR}/imgui_draw.cpp
#     ${IMGUI_DIR}/imgui_tables.cpp
#     ${IMGUI_DIR}/imgui_widgets.cpp
#     ${IMGUI_DIR}/imgui_demo.cpp
#     ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
# )
# add_library(ImGui STATIC ${IMGUI_SOURCES})
# target_include_directories(ImGui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)

# if(UNIX)
#     find_package(glfw3 REQUIRED)
#     find_package(OpenGL REQUIRED)
#     find_package(X11 REQUIRED)
#     target_link_libraries(ImGui PRIVATE glfw OpenGL::GL X11)
#     set(IMGUI_RENDERER_BACKEND ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)
#     set(IMGUI_PLATFORM_BACKEND ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp)
# else()
#     message("You are unwelcome since you are on a non-unix system.")
#     message("Goodbye :D")
# endif()

# target_sources(ImGui PRIVATE
#     ${IMGUI_RENDERER_BACKEND}
#     ${IMGUI_PLATFORM_BACKEND}
# )

# # copy fonts
# file(GLOB FONT_SOURCES ${CMAKE_SOURCE_DIR}/Libraries/ImGui/misc/fonts/*.ttf)
# set(FONT_DEST ${CMAKE_BINARY_DIR}/fonts)
# file(MAKE_DIRECTORY ${FONT_DEST})

# foreach(font_file ${FONT_SOURCES})
#     get_filename_component(font_filename ${font_file} NAME)
#     configure_file(${font_file} ${FONT_DEST}/${font_filename} COPYONLY)
# endforeach()



# # ImNodeFlow
# set(IMNODE_FLOW_DIR Libraries/ImNodeFlow)
# set(IMNODE_FLOW_SOURCES ${IMNODE_FLOW_DIR}/src/ImNodeFlow.cpp)
# add_library(ImNodeFlow STATIC ${IMNODE_FLOW_SOURCES})
# target_include_directories(ImNodeFlow PRIVATE ${IMNODE_FLOW_DIR}/include ${IMGUI_DIR} ${IMGUI_DIR}/backends)
# target_compile_definitions(ImNodeFlow PUBLIC IMGUI_DEFINE_MATH_OPERATORS)


# # ImGuiNodeEditor
# set(IMGUI_NODE_EDITOR_DIR Libraries/ImGuiNodeEditor)
# set(IMGUI_NODE_EDITOR_SOURCES
#     ${IMGUI_NODE_EDITOR_DIR}/crude_json.cpp
#     ${IMGUI_NODE_EDITOR_DIR}/imgui_canvas.cpp
#     ${IMGUI_NODE_EDITOR_DIR}/imgui_node_editor.cpp
#     ${IMGUI_NODE_EDITOR_DIR}/imgui_node_editor_api.cpp
# )
# add_library(ImGuiNodeEditor STATIC ${IMGUI_NODE_EDITOR_SOURCES})
# target_include_directories(ImGuiNodeEditor PRIVATE ${IMGUI_NODE_EDITOR_DIR} ${IMGUI_DIR} ${IMGUI_DIR}/backends)
# target_compile_definitions(ImGuiNodeEditor PUBLIC IMGUI_DEFINE_MATH_OPERATORS)


# # ImNodes
# set(IMNODES_DIR Libraries/ImNodes)
# set(IMNODES_SOURCES ${IMNODES_DIR}/imnodes.cpp)
# add_library(ImNodes STATIC ${IMNODES_SOURCES})
# target_include_directories(ImNodes PRIVATE ${IMNODES_DIR} ${IMGUI_DIR} ${IMGUI_DIR}/backends)
# target_compile_definitions(ImNodes PUBLIC IMGUI_DEFINE_MATH_OPERATORS)

# add_subdirectory(Monet)

# add_executable(Monet Main.cpp)

# target_link_libraries(Monet PRIVATE ImGui ImNodeFlow)
# target_include_directories(Monet PRIVATE ${IMGUI_DIR} ${IMGUI_DIR}/backends ${IMNODE_FLOW_DIR}/include)

# target_link_libraries(Monet PRIVATE ImGui ImGuiNodeEditor)
# target_include_directories(Monet PRIVATE ${IMGUI_DIR} ${IMGUI_DIR}/backends ${IMGUI_NODE_EDITOR_DIR})

# target_link_libraries(Monet PRIVATE ImGui ImNodes)
# target_include_directories(Monet PRIVATE ${IMGUI_DIR} ${IMGUI_DIR}/backends ${IMNODES_DIR})
