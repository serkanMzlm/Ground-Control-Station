add_library(GCS STATIC
    GCSApplication.cpp
    GCSApplication.hpp
)

add_subdirectory(Communication)
add_subdirectory(System)

target_link_libraries(GCS PUBLIC
        Qt6::Quick
        Qt6::Core5Compat
        Qt6::Bluetooth
        Qt6::Core
        Qt6::Widgets
)

target_link_libraries(GCS PUBLIC
        Communication
        System
)

target_include_directories(GCS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
