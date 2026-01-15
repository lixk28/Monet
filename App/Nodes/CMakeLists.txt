add_library(Nodes INTERFACE)

add_subdirectory(Image)

target_link_libraries(Nodes
INTERFACE
    Image
)
