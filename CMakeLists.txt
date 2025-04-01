#######################################################
#            Command Center Unit (GCS)                #
#######################################################

cmake_minimum_required(VERSION 3.20)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(GeneralOptions)

project(GroundControlStation VERSION ${APP_VERSION} LANGUAGES C CXX)

include(Toolchain)

if(UNIX AND NOT APPLE AND NOT ANDROID)
    set(LINUX TRUE)
endif()

if(APPLE AND NOT IOS)
    set(MACOS TRUE)
endif()

if(IOS OR ANDROID)
    set(MOBILE TRUE)
    add_compile_definitions(__mobile__)
endif()

if(WIN32 OR MSVC)
    set(WINDOWS TRUE)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Quick Core Gui Qml)
find_package(Qt${QT_VERSION_MAJOR}
            REQUIRED
            COMPONENTS
            Core
            Quick
            Concurrent
            Core5Compat
            Widgets
            Multimedia
            MultimediaQuickPrivate
            Sensors
            Network
            Positioning
            Location
            SerialPort
            Bluetooth
            Gui
)

qt_standard_project_setup(REQUIRES 6.8)

list(APPEND GCS_RESOURCES
    ${CMAKE_SOURCE_DIR}/resources.qrc
)

add_subdirectory(src)

add_executable(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${GCS_RESOURCES}
)

target_link_libraries(${PROJECT_NAME}
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    GCS
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
