cmake_minimum_required(VERSION 3.9)

project(libsurakarta 
    VERSION 1.0.1 
    DESCRIPTION "Surakarta Engine")

include(GNUInstallDirs)
include(CTest)

enable_testing()

set (CMAKE_CXX_STANDARD 11)

add_library(libsurakarta 
    SHARED 
    src/model/surakarta.cc)

set_target_properties(libsurakarta 
    PROPERTIES
        PREFIX ""
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER include/Surakarta.hpp
        DESCRIPTION "C++ implementation of a Surakarta computer engine"
        HOMEPAGE_URL https://github.com/SurakartaArcade/libsurakarta
        LANGUAGES CXX)

target_include_directories(
    libsurakarta 
    PUBLIC 
    include)

install(TARGETS libsurakarta
    LIBRARY 
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/mylib.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

if (BUILD_TESTING)
    add_executable(test_skmodel test/skmodel.cc test/factory/surakarta_factory.cc)

    target_include_directories(
        test_skmodel
        PUBLIC
        include
    )

    target_link_libraries(
        test_skmodel
        libsurakarta
    )

    add_test(SurakartaModel test_skmodel)
endif()