set(SYS_FILE
    SystemDate.hpp
    SystemDate.cpp
)

add_library(System STATIC ${SYS_FILE})
target_include_directories(System PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(System
                Qt${QT_VERSION_MAJOR}::Core
                Qt${QT_VERSION_MAJOR}::Quick
)
