cmake_minimum_required(VERSION 3.16)

project(HLA-NoVR-Launcher-Helper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(HLA-NoVR-Launcher-Helper main.cpp)

include(GNUInstallDirs)
install(TARGETS HLA-NoVR-Launcher-Helper
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
