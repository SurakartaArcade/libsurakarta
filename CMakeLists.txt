cmake_minimum_required(VERSION 3.9)

project(libsurakarta VERSION 1.0.1 DESCRIPTION "Surakarta Engine")

include(GNUInstallDirs)

add_library(libsurakarta SHARED src/Surakarta.cpp)

set_target_properties(libsurakarta PROPERTIES
	PREFIX ""
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/Surakarta.hpp)

target_include_directories(libsurakarta PRIVATE include)

install(TARGETS libsurakarta
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/mylib.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)