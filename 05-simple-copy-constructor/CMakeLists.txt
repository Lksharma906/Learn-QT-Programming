cmake_minimum_required(VERSION 3.16)

project(05-simple-copy-constructor LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(05-simple-copy-constructor
  main.cpp
  interger.h interger.cpp
)
target_link_libraries(05-simple-copy-constructor Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS 05-simple-copy-constructor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
