cmake_minimum_required(VERSION 3.16)

project(Cube VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER "C:/qt/Tools/mingw1310_64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/qt/Tools/mingw1310_64/bin/g++.exe")

find_package(Qt6 REQUIRED COMPONENTS Widgets Core OpenGL OpenGLWidgets)


file(GLOB UI "ui/*.ui")
file(GLOB CPP "*.cpp")
file(GLOB HPP "*.hpp")

qt6_add_resources(QRC
    resources.qrc
)

set(PROJECT_SOURCES
    ${CPP} ${HPP} ${UI} ${QRC}
)


qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    # WIN32
    ${PROJECT_SOURCES}
)


target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR})


install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(${PROJECT_NAME})