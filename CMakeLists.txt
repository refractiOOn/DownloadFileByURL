cmake_minimum_required(VERSION 3.5)

project(DownloadFileByURL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DownloadFileByURL main.cpp)

include(GNUInstallDirs)
install(TARGETS DownloadFileByURL
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
