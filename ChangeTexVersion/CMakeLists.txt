cmake_minimum_required(VERSION 3.16)

project(ChangeTexVersion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ChangeTexVersion main.cpp
)

target_include_directories(ChangeTexVersion PRIVATE
    ../KsUtils
    ../KsUtils/src
)

target_link_libraries(ChangeTexVersion PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../KsUtils/build/Desktop_Qt_6_9_3_MinGW_64_bit-Release/libKsUtils.a
)

include(GNUInstallDirs)
install(TARGETS ChangeTexVersion
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
