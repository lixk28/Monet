add_library(App INTERFACE)

add_subdirectory(Nodes)

target_link_libraries(App
INTERFACE
    Nodes
)
