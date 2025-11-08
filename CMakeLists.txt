cmake_minimum_required(VERSION 3.16)
project(qml-niri VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(
    Qt6 6.5
    COMPONENTS
                Core
                Quick
                Test
    REQUIRED)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_library(Niri SHARED)
qt_add_qml_module(Niri
    URI Niri  # Module name for imports
    VERSION 0.1
    SOURCES
        src/icon.h src/icon.cpp
        src/ipcclient.h src/ipcclient.cpp
        src/niri.h src/niri.cpp
        src/windowmodel.h src/windowmodel.cpp
        src/workspacemodel.h src/workspacemodel.cpp
    OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Niri  # Optional
)

target_include_directories(Niri PUBLIC src)

target_link_libraries(Niri PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
)
