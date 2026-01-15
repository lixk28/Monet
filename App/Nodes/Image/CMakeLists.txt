set(NODES_IMAGE_SOURCES
    ImageLoadNode.cpp
    ImagePreviewNode.cpp
)

add_library(Image ${NODES_IMAGE_SOURCES})

target_link_libraries(Image Qt6::Core Qt6::Widgets QtNodes)
